# TODO

Last updated: 2026-02-25

## Next Phase: Realism + Validation

1. [x] Implement startup warm-up/preseed path for prediction evaluator with visible `THINKING` progress.
2. [x] Add prediction score strip under activity/warning box and keep live evaluation count visible (`E#`).
3. [x] Add MAE display line for prediction quality interpretation.
4. [x] Resolve score pipeline wiring issue (non-zero `E#` confirms matured prediction evaluation is active).
5. [x] Replace synthetic glucose generator with timestamp-aligned replay/live sensor stream for CGM model input.
6. [x] Retrain `+15m`/`+30m` prediction model with corrected target alignment and feature windows.
7. [ ] Re-run validation protocol and publish measured outcomes (lag, MAE by range, alert chatter).
8. [ ] Implement pump/motor actuator realism model (latency, ramp limits, quantized dose steps, saturation).
9. [ ] Add occlusion/backpressure fault simulation and safe fallback behavior in dosing path.
10. [ ] Add hard safety interlocks for dosing assist (SQI gate, sensor-fault gate, max correction/window).
11. [x] Create and stage updated golden/failsafe restore points after model-quality improvements.
12. [x] Commit and push the updated project state to GitHub.

## UI Popup Bug Track (Settings/Help)

1. [x] Reproduce and log popup regression: missing black background, slow open/close, and `?`/`*` artifacts.
2. [x] Add modal redraw gating (`gModalDirty`) and modal invalidation points for settings/help/limits state changes.
3. [x] Restore full black modal backdrop during popup transitions to eliminate partial/missing background.
4. [x] Fix post-popup center-ball disappearance with one-shot orientation force redraw after modal close.
5. [ ] Validate on-device that settings/help text remains readable with full background and no long popup latency.
