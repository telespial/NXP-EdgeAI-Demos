# CGM AI Algorithm Explainer

Last updated: 2026-02-23

## Scope
This document explains:
- how the current demo CGM algorithm works at runtime
- what it predicts (`P15`, `P30`) and how alerts are generated
- the common medical and algorithmic patterns widely used in CGM systems

This is a software/engineering explainer for the demo codebase, not clinical advice.

## Quick Summary
The current runtime is a staged pipeline:
1. Synthetic raw signal generation (demo source).
2. Signal preprocessing and calibration/compensation (`src/cgm_preprocess.c`).
3. Trend estimation (`mg/dL/min`).
4. Short-horizon prediction (`+15m`, `+30m`) in `src/gauge_render.c`.
5. SQI/flag gating, debounce, and hysteresis for predictive hypo/hyper alerts.
6. Dose recommendation scaling based on prediction direction/severity.

## Runtime Data Flow
### 1) Raw-to-engineering preprocessing
Implemented in `src/cgm_preprocess.c` and configured by `src/cgm_preprocess.h`.

The pipeline includes:
- ADC conversion and linearization.
- Reference compensation (`ref_mv`) and temperature compensation.
- anti-alias filtering + decimation.
- impulse noise rejection (median).
- optional notch filtering.
- drift compensation and sensitivity-change checks.
- lag/kinetics low-gain correction.
- trend extraction (`trend_mgdl_min`).

Output contract fields are represented by `cgm_preprocess_output_t`:
- glucose
- filtered glucose
- trend
- SQI
- sensor flags
- prediction gate controls (`prediction_blocked`, `hold_last`)

### 2) SQI and sensor flags
Current flags are:
- `CGM_FLAG_SATURATION`
- `CGM_FLAG_DROPOUT`
- `CGM_FLAG_IMPLAUSIBLE_ROC`
- `CGM_FLAG_TEMP_OUT_OF_RANGE`
- `CGM_FLAG_CAL_STALE`
- `CGM_FLAG_DRIFT_WARN`

Current runtime flag triggers include:
- saturation near ADC rails (`<=50` or `>=4045` counts)
- dropout proxy (`ref_mv < 100`)
- implausible ROC (`abs(trend_raw) > 3.5 mg/dL/min`)
- temperature out of range (`<10C` or `>45C`)

Prediction gate behavior:
- blocked when `SQI < 40` or severe flags are present
- hold-last mode when dropout flag is active

### 3) Glucose and trend path
In `src/gauge_render.c`, per output-ready sample:
- `gUiGlucoseMgdl` and `gUiGlucoseTrendMgDlPerMin` are updated from preprocessor outputs.
- if `hold_last` is active, glucose/trend are held.
- prediction update runs immediately after each accepted sample.

## What The AI Predicts
### Prediction variables
The runtime keeps:
- `gUiPred15Mgdl` (15-minute glucose prediction)
- `gUiPred30Mgdl` (30-minute glucose prediction)

Linear forecast equations:
- `P15 = clamp(glucose + trend * 15, 40, 400)`
- `P30 = clamp(glucose + trend * 30, 40, 400)`

Where:
- glucose is current filtered estimate (`mg/dL`)
- trend is `mg/dL/min`

### Prediction gating
Prediction alerts only run when:
- `prediction_blocked == false`
- `SQI >= 45`

If gating is not satisfied:
- prediction alert state is cleared
- debounce counters reset
- no predictive warning/fault is emitted

## Predictive Alert Logic
### Entry thresholds
Hypo warning:
- `P15 <= 78` OR `P30 <= 85`

Hypo fault:
- `P15 <= 70` OR `P30 <= 75`

Hyper warning:
- `P15 >= 190` OR `P30 >= 200`

Hyper fault:
- `P15 >= 230` OR `P30 >= 240`

### Debounce (anti-chatter)
Active state requires repeated confirm samples:
- warning states: 3 samples
- fault states: 4 samples

### Hysteresis (separate clear thresholds)
Hypo warning clears only when:
- `P15 >= 86` AND `P30 >= 92`

Hypo fault clears only when:
- `P15 >= 79` AND `P30 >= 84`

Hyper warning clears only when:
- `P15 <= 180` AND `P30 <= 190`

Hyper fault clears only when:
- `P15 <= 210` AND `P30 <= 220`

### Priority
If multiple conditions are true, precedence is:
1. hypo fault
2. hypo warning
3. hyper fault
4. hyper warning
5. normal

This biases toward low-glucose risk first.

## UI And Alert Semantics
When predictive alert is active:
- terminal AI text becomes `PRED-HYPO` or `PRED-HYPER`
- overlay headline changes to:
  - warning: `LOW GLUCOSE` or `HIGH GLUCOSE`
  - fault: `PRED HYPO` or `PRED HYPER`
- overlay detail line includes `P15`, `P30`, and `SQI`

Otherwise, activity-state alert text is used.

## Dose Interaction
Base dose recommendation is computed from:
- activity stage
- glucose band
- trend band
- IOB attenuation

Predictive alert scaling then applies:
- hypo warning: `x0.70`
- hypo fault: `x0.45`
- hyper warning: `x1.10`
- hyper fault: `x1.20`

If prediction is blocked:
- dropout hold-last: keep last recommendation
- otherwise: de-rate by `x0.85`

Final output is bounded and quantized:
- min `0.025 U/h`
- max `6.000 U/h`
- rounded to `0.025 U/h` step

## Common Medical Concepts Used In CGM Systems
These concepts are standard across commercial CGM algorithm designs:
- glucose concentration estimate (`mg/dL`)
- rate of change (`mg/dL/min`)
- short-horizon forecast (typically 15-30 min)
- signal quality scoring/confidence
- sensor state/fault flags
- low/high glucose risk thresholds
- alert suppression and anti-chatter logic

In clinical products, thresholds are personalized by therapy mode, risk profile, and regulatory claims.

## Common Software/Math Patterns In The CGM Market
### Signal conditioning
- low-pass and anti-alias filtering
- robust outlier suppression (median/Hampel)
- interference rejection (line-frequency notch where needed)

### Calibration and compensation
- affine/quadratic calibration mapping
- temperature compensation terms
- slow drift-state adaptation

### State estimation and trend
- EMA/IIR smoothing
- robust slope estimation over rolling windows
- bounded lag compensation

### Prediction methods
- linear extrapolation from current trend (simple baseline)
- AR/ARIMA-family short-term forecasting
- Kalman/state-space observers
- hybrid model + rule systems

### Alert stability and safety
- debounce counters
- hysteresis (different enter/clear bands)
- refractory/hold windows to prevent oscillation
- confidence/SQI gating before issuing predictive alerts

### Validation metrics commonly tracked
- point accuracy: MARD, RMSE
- rate accuracy: trend/slope error
- latency/lag to blood-reference changes
- alert quality: sensitivity, specificity, PPV/NPV, false alert rate
- robustness under dropout/noise/motion/temperature stress

## What Is Demo-Specific Versus Production-Grade
Demo-specific in this repository:
- upstream glucose source is synthetic
- prediction uses linear trend projection
- thresholds are fixed engineering values for demonstration

Production-grade CGM systems usually add:
- patient/population tuning datasets
- stricter fault models and calibration workflows
- richer prediction uncertainty models
- formal verification against reference datasets and regulatory test protocols

## Practical Reading Map
- Runtime contract: `docs/CGM_RUNTIME_CONTRACT.md`
- Sensor flag taxonomy: `docs/CGM_SENSOR_FLAGS.md`
- Pipeline reference: `docs/CGM_30S_PIPELINE_REFERENCE.md`
- Current traceability status: `docs/CGM_TRACEABILITY.md`
- Implementation:
  - `src/cgm_preprocess.c`
  - `src/cgm_preprocess.h`
  - `src/gauge_render.c`
