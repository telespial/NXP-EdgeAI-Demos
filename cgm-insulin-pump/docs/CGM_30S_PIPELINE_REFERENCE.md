# CGM 30-Second Cadence Reference Pipeline

Last updated: 2026-02-23

## Purpose
Reference architecture for a dermal-CGM pipeline running at a `30 s` output cadence, aligned to:
- `docs/CGM_DERMAL_ALGORITHM_REVIEW.md`
- `docs/CGM_RUNTIME_CONTRACT.md`
- `docs/CGM_SENSOR_FLAGS.md`

This is a planning artifact for implementation steps 5-12.

## Block Diagram

```text
AFE Raw Samples
    |
    v
[Raw Conditioning]
  - ADC linearization
  - offset/gain/reference correction
  - anti-alias + decimation
  - notch + impulse rejection
    |
    v
[Fast Dynamics Filter Path]
  - short-time-constant LP filter
  - derivative estimation
    |
    +------------------------------+
    |                              |
    v                              v
[Calibration + Compensation]   [SQI + Sensor Flags]
  - factory map                 - saturation/dropout/ROC/temp/cal/drift checks
  - temperature comp            - quality score 0..100
  - drift model update          - flag bitmask
    |                              |
    +--------------+---------------+
                   |
                   v
          [Lag/Kinetics Correction]
            - conservative, low-gain
                   |
                   v
          [Prediction + Alert Logic]
            - +15m/+30m predictions
            - SQI/flag-gated alert logic
            - debounce/hysteresis
                   |
                   v
              cgm_tuple_t @ 30 s
```

## Cadence Plan

- Internal acquisition: `1 Hz` (example baseline, configurable)
- Feature update window: rolling `30 s`
- Output tuple publish: every `30 s`
- Stale timeout: `>90 s` without fresh input sets dropout behavior

## Equations-Level Pseudocode

```text
Inputs per second:
  raw_current_nA[k], sensor_temp_C[k], timestamp[k]

At each 1 Hz step:
  1) x_lin[k] = linearize(raw_current_nA[k], adc_gain, adc_offset)
  2) x_comp[k] = ref_comp(x_lin[k], vref[k])
  3) x_aa[k] = anti_alias_filter(x_comp[k])
  4) x_notch[k] = notch_50_60Hz(x_aa[k])            // if interference present
  5) x_clean[k] = impulse_reject(x_notch[k])        // median/Hampel
  6) x_fast[k] = lp_fast(x_clean[k], tau_fast)
  7) g_uncal[k] = map_factory(x_fast[k], cal_coeffs)
  8) g_temp[k] = g_uncal[k] + Kt * (sensor_temp_C[k] - Tref)
  9) drift_state[k] = drift_update(drift_state[k-1], g_temp[k], q_drift)
 10) g_cal[k] = g_temp[k] - drift_state[k]
 11) roc[k] = d_dt(g_cal[k], g_cal[k-1], dt)
 12) lag_state[k] = lag_update(lag_state[k-1], g_cal[k], tau_lag, gain_lag)
 13) g_out[k] = g_cal[k] + gain_lag * lag_state[k]
 14) sqi[k], flags[k] = quality_eval(signals, roc[k], temp, timing, cal_age, drift_state)

Every 30 s publish tick:
  A) glucose_mgdl = clamp(round(g_out), 40, 400)
  B) trend_mgdl_min = smooth_roc(roc_history)
  C) pred15 = predict(glucose_mgdl, trend_mgdl_min, horizon=15m)
  D) pred30 = predict(glucose_mgdl, trend_mgdl_min, horizon=30m)
  E) apply flag/sqi gates:
       if DROPOUT or SATURATION or TEMP_OUT_OF_RANGE:
          pred15 = 0; pred30 = 0
  F) emit cgm_tuple_t
```

## Candidate Filter Constants (Initial)

These are initial tuning seeds, not final validated values.

- Anti-alias LPF cutoff: `0.20 Hz` (pre-decimation)
- Decimation: `1 Hz -> 0.2 Hz` optional for heavy-noise paths, or keep `1 Hz` for low-lag mode
- Fast LP filter:
  - `tau_fast = 18 s` default
  - adaptive range: `12..30 s` based on SQI
- Derivative smoothing window: `60 s` rolling robust slope
- Impulse reject:
  - median window `N=3`
  - Hampel `N=5`, threshold `3 sigma`
- Notch:
  - enable only when periodic interference detector exceeds threshold

## SQI Features And Threshold Strategy

## Feature Set

- `f_noise`: short-window residual variance after LP filtering
- `f_continuity`: missing-update ratio over last 90 s
- `f_roc`: plausibility score from `abs(trend_mgdl_min)`
- `f_temp`: distance-to-valid-range margin
- `f_cal_age`: normalized calibration age
- `f_drift`: normalized drift residual

## Composite Score

```text
sqi_raw = 100
          - w1 * f_noise
          - w2 * f_continuity
          - w3 * f_roc
          - w4 * f_temp
          - w5 * f_cal_age
          - w6 * f_drift
sqi_pct = clamp(round(sqi_raw), 0, 100)
```

Initial weights:
- `w1=0.25`, `w2=0.20`, `w3=0.20`, `w4=0.15`, `w5=0.10`, `w6=0.10`

## Threshold Bands

- `SQI >= 80`: high confidence
- `60..79`: usable with caution
- `40..59`: de-rate prediction confidence
- `<40`: suppress prediction-driven alerts

Flag-derived caps are applied per `docs/CGM_SENSOR_FLAGS.md`.

## Drift/Lag Model Structure

## Drift (slow baseline state)

State:
- `b_k`: baseline drift offset (mg/dL equivalent)

Update:

```text
b_k = b_(k-1) + eta_k
eta_k ~ N(0, q_drift)
g_cal_k = g_temp_k - b_k
```

Interpretation:
- random-walk drift state with small process noise `q_drift`
- tuned to absorb long-term bias, not short transients

## Lag (conservative correction)

State:
- `l_k`: lag residual state

Update:

```text
l_k = alpha_lag * l_(k-1) + (g_cal_k - g_cal_(k-1))
g_out_k = g_cal_k + gain_lag * l_k
```

Initial bounds:
- `alpha_lag = exp(-dt/tau_lag)`, `tau_lag = 180 s`
- `gain_lag = 0.10` (low gain by default)

Design rule:
- keep lag correction low-gain and disable aggressively when SQI degrades.

## Publish Mapping To Contract

Output tuple fields:
- `glucose_mgdl <- g_out`
- `trend_mgdl_min_x100 <- trend_mgdl_min * 100`
- `sqi_pct <- composite SQI with flag caps`
- `sensor_flags <- taxonomy from docs/CGM_SENSOR_FLAGS.md`
- `prediction_15m_mgdl <- gated prediction`
- `prediction_30m_mgdl <- gated prediction`

## Open Tuning Questions

- Confirm acquisition rate and whether `1 Hz` is available end-to-end.
- Confirm temperature sensing point (sensor die vs skin estimate) for compensation term.
- Choose median-only vs Hampel path based on MCU budget and artifact profile.
- Set final `q_drift`, `tau_fast`, and lag gain from replay tuning before alert validation.
