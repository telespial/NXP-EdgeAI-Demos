# CGM Traceability Matrix

Last updated: 2026-02-24

## Scope
This matrix maps the current demo runtime to the algorithm stages in `docs/CGM_DERMAL_ALGORITHM_REVIEW.md`.

Status legend:
- `implemented`: present in runtime logic
- `simulated`: present as demo/simplified behavior, not a production CGM path
- `missing`: not implemented in current runtime

## Stage Mapping

| Review stage | Status | Current evidence | Gap summary |
|---|---|---|---|
| 1) Raw electrochemical signal to engineering units | simulated | Preprocessing pipeline now implemented (`src/cgm_preprocess.c`) and integrated into glucose path (`src/gauge_render.c`), including conversion/linearization, reference compensation, anti-aliasing, decimation, notch, and impulse rejection; input is still synthetic/demo raw stream. | Replace synthetic raw generator with live AFE sensor source and validate coefficient tuning on hardware data. |
| 2) Filtering tuned for fast dynamics | simulated | Adaptive low-lag filtering/trend path implemented in preprocessing (`src/cgm_preprocess.c`) and wired to runtime trend output (`src/gauge_render.c`), including SQI-driven alpha selection; upstream raw input remains synthetic. | Replace synthetic raw generator with live sensor stream and retune constants against captured dermal datasets. |
| 3) Calibration and compensation | simulated | Calibration/compensation path now implemented in preprocessing (`src/cgm_preprocess.c/.h`): runtime calibration hooks, temperature compensation, drift-state compensation, and sensitivity-change detection; runtime source is still synthetic. | Replace synthetic raw stream with live sensor input and tune calibration/drift thresholds with captured data. |
| 4) Lag and kinetics handling | simulated | Conservative lag/kinetics block now implemented in preprocessing (`src/cgm_preprocess.c/.h`) with optional low-gain correction, SQI-adaptive gain, and bounded compensation; no aggressive look-forward extrapolation. | Validate lag constants and gain bounds against live dermal data and safety envelopes. |
| 5) SQI and fault detection | simulated | Runtime now emits `sqi_pct` and `sensor_flags` from preprocessing (`src/cgm_preprocess.c/.h`), with prediction gating (`prediction_blocked`) and dropout fallback (`hold_last`) integrated into render/recommendation flow (`src/gauge_render.c`); upstream signal source remains simulated. | Replace synthetic raw source with live sensor signal and tune SQI/flag thresholds from captured dermal datasets. |
| 6) Trend, prediction, and alert logic | simulated | Trend (`dBG`) plus short-horizon predictions (P15/P30), SQI-gated predictive hypo/hyper warning/fault checks, and debounce/hysteresis state machine are implemented in runtime logic (`src/gauge_render.c`), with predictive status wired into alert and dose paths; upstream glucose source remains synthetic. | Replace synthetic glucose source with live CGM stream and tune prediction/alert thresholds against captured dermal data. |
| 7) Performance and validation metrics | implemented | Validation protocol is defined in `docs/CGM_VALIDATION_PROTOCOL.md` with explicit pass/fail thresholds for lag, trend accuracy, alert false positives/chatter, and replay robustness. Runtime UI exposes prediction score/evaluation count/MAE for live diagnostic visibility. | Execute protocol on replay/live datasets and publish measured pass/fail results for each metric partition. |
| 8) Advanced/optional transforms | missing | No FFT/wavelet diagnostic path in current CGM implementation scope. | Optional; decide later based on compute budget after core path is stable. |

## Current Runtime Notes

- The UI and help explicitly identify CGM and dosing response as simulated demo behavior (`src/gauge_render.c:2278`, `src/gauge_render.c:2279`).
- Terminal line already exposes `dBG` and dose context, which is a useful UI target when replacing simulated internals with a formal CGM tuple (`src/gauge_render.c:2587`).

## Immediate Follow-On

- Replace synthetic glucose source with timestamp-aligned replay/live source.
- Retrain prediction model with corrected feature/label alignment.
- Re-run protocol and publish quantified outcomes by partition.
