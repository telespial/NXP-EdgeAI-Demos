# CGM Validation Protocol

Last updated: 2026-02-24

## Purpose

Define a repeatable pass/fail validation plan for the runtime CGM pipeline with explicit thresholds for:
- lag estimation
- trend accuracy by glucose range
- alert false-positive/chatter rate
- replay robustness under dropout/noise/motion artifacts

This protocol validates the runtime tuple and behavior documented in:
- `docs/CGM_RUNTIME_CONTRACT.md`
- `docs/CGM_SENSOR_FLAGS.md`
- `docs/CGM_30S_PIPELINE_REFERENCE.md`

## Inputs and Outputs

Inputs per sample (30 s cadence unless noted):
- raw/simulated sensor signal
- reference glucose (`ref_mgdl`) from replay truth stream
- temperature, motion metadata, and dropout/noise markers

Validated outputs:
- `glucose_mgdl`
- `trend_mgdl_min_x100`
- `sqi_pct`
- `sensor_flags`
- `prediction_15m`
- `prediction_30m`
- alert states and transitions

## Dataset Partitions

Run all metrics against these partitions:
- `LOW`: `<80 mg/dL`
- `IN_RANGE`: `80-180 mg/dL`
- `HIGH`: `>180 mg/dL`

Coverage minimums:
- at least `2 hours` replay per partition
- at least `20` alert opportunities for hypo and hyper each
- at least `10` dropout/noise/motion artifact events per stress class

## Pass/Fail Thresholds

### 1) Lag Estimation

Metric:
- Cross-correlation lag between `glucose_mgdl` and `ref_mgdl` on aligned replay windows.

Pass:
- median lag `<= 120 s`
- P95 lag `<= 180 s`
- no window with lag `> 240 s`

Fail:
- any pass criterion violated

### 2) Trend Accuracy by Range

Metric:
- trend error on derivative:
  - `trend_err = trend_mgdl_min_x100/100 - ref_trend_mgdl_min`
- evaluate MAE and sign agreement.

Pass:
- `LOW`: MAE `<= 0.60 mg/dL/min`, sign agreement `>= 80%`
- `IN_RANGE`: MAE `<= 0.45 mg/dL/min`, sign agreement `>= 85%`
- `HIGH`: MAE `<= 0.55 mg/dL/min`, sign agreement `>= 82%`

Fail:
- any partition misses either MAE or sign target

### 3) Alert False-Positive and Chatter

Definitions:
- false-positive: alert raised without threshold breach in next horizon window
- chatter: repeated toggle cycles while condition remains near threshold

Pass:
- hypo false-positive rate `<= 5%`
- hyper false-positive rate `<= 5%`
- chatter rate `<= 0.10 toggles/min` per alert type
- minimum alert dwell after raise `>= 60 s` unless fault gating suppresses output

Fail:
- any pass criterion violated

### 4) Replay Robustness (Dropout/Noise/Motion)

Stress classes:
- dropout bursts: `1-3` consecutive missing samples
- impulse noise: spikes up to `+-25 mg/dL` equivalent for one sample
- motion artifact: sustained SQI degradation windows

Pass:
- `sensor_flags` correctly set/cleared with documented debounce in `>= 95%` of events
- during low SQI/dropout, prediction outputs are blocked or de-rated per contract in `100%` of flagged windows
- post-artifact recovery to valid trend (sign-stable for 2 samples) within `<= 90 s`

Fail:
- any pass criterion violated

## Test Procedure

1. Run baseline replay and compute all metrics by partition.
2. Run stress replays (dropout/noise/motion) and re-compute robustness metrics.
3. Export summary table with pass/fail per section and overall verdict.
4. Record firmware hash, replay bundle ID, and timestamp in validation report.

## Report Template (Minimum)

- Firmware build ID / git commit
- Replay dataset ID(s)
- Metrics table:
  - lag median/P95/max
  - trend MAE/sign by partition
  - alert false-positive and chatter rates
  - robustness event pass counts
- Overall result: `PASS` or `FAIL`
- If fail: corrective action and re-test target date

## Current Baseline Snapshot (2026-02-24)

Observed during live replay diagnostic runs:
- evaluator is active with high consumed count (`E#` in thousands), confirming prediction-vs-actual comparison is wired end-to-end
- prediction score remains low under current model quality (observed single-digit percent with `+-10%` tolerance mode)
- blended MAE observed around `115..120 mg/dL` in current run state

Interpretation:
- pipeline wiring is functioning
- current trained model is not yet acceptable for dosing-oriented advisory quality
- primary next action is model/data alignment and retraining, not UI plumbing changes
