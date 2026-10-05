# Project State

Last updated: 2026-02-26

## Restore Point
- Golden: `GOLDEN-2026-02-26-R12`
- Failsafe: `FAILSAFE-2026-02-26-R12`
- Status: active

## Current Status
- Project framework scaffold created.
- Build/flash workflow scripts added.
- Git repository initialized locally.

## Update 2026-02-26
- Change: Fixed settings/help modal touch handling so popup controls use the same tap-edge path as the main UI (removes modal-only edge gating that could ignore button taps).
  - `src/edgeai_medical_device_demo.c`
    - replaced modal-specific press-edge gate with unified `touch_press_edge` based on `s_touch_was_down`
    - removed unused `s_modal_touch_was_down` state
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: settings popup buttons should respond to touch again (not only close `X`).

## Update 2026-02-26
- Change: Reduced modal redraw latency and fixed stale settings selection state.
  - `src/gauge_render.c`
    - settings button selection now uses live state (`gUiAiEnabled`, `gUiAiBackendNpu`) for AI ON/OFF and MCU/NPU
    - modal redraw no longer clears full-screen black on every modal refresh; full clear remains on modal entry
  - `src/edgeai_medical_device_demo.c`
    - settings/limits updates now mark a dirty flag and defer `SaveUiSettingsIfReady(...)` until modal closes
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: settings/help interaction should be faster and top setting rows should update correctly when tapped.

## Update 2026-02-26
- Change: Expanded touch hitboxes for UI controls to improve small/misaligned tap behavior.
  - `src/edgeai_medical_device_demo.c`
    - added `TouchInRectExpanded(...)` helper
    - increased tap padding for top-row `*` / `?`, settings/help close controls, NEXT button, settings rows, limits panel controls, and +/- adjust regions
    - widened panel bounds slightly to reduce accidental close on near-edge taps
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: touch targets are more forgiving across settings/help/limits controls.

## Update 2026-02-26
- Change: Fixed `SENS` row touch masking by reducing vertical padding overlap between stacked settings rows.
  - `src/edgeai_medical_device_demo.c`
    - reduced settings row hitbox padding (`MODE`, `RUN`, `SENS`, `MCU/NPU`) from `(pad_x=10,pad_y=8)` to `(pad_x=8,pad_y=3)`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: `SENS` taps should no longer be intercepted by adjacent rows.

## Update 2026-02-26
- Change: Enlarged settings modal window and spread controls for better tap separation.
  - `src/gauge_render.h`
    - expanded settings panel bounds (`X0/X1: 16/464`, `Y0/Y1: 24/308`)
    - widened and re-spaced button groups (`AI`, `RUN`, `SENS`, `MCU/NPU`)
    - widened `OPEN LIMITS`, `CLEAR FLASH`, and `LOG` controls
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: larger grey settings box with more separated, easier touch targets.

## Update 2026-02-26
- Change: Promoted current settings-touch UX build to new restore baseline `R12`.
  - tags:
    - `GOLDEN-2026-02-26-R12`
    - `FAILSAFE-2026-02-26-R12`
  - artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-26-R12.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-26-R12.bin`
- Verification:
  - source binary: `mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin`
  - based on latest flashed build from 2026-02-26 settings/touch updates
- Result: `R12` is now the active golden/failsafe restore target.

## Update 2026-02-24
- Change: Promoted verified +15m-only `±10%` scoring policy build as active restore baseline `R5`.
  - tags:
    - `GOLDEN-2026-02-24-R5`
    - `FAILSAFE-2026-02-24-R5`
  - artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R5.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R5.bin`
  - policy:
    - prediction score uses `+15m` only
    - score tolerance is `±10%`
    - `+30m` remains displayed but excluded from score hit-rate
- Verification:
  - observed runtime score: `95%`
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: new golden/failsafe restore points staged for this scoring policy.

## Update 2026-02-24
- Change: Promoted current subject001 dataset-driven CGM replay runtime as active restore baseline `R4`.
  - tags:
    - `GOLDEN-2026-02-24-R4`
    - `FAILSAFE-2026-02-24-R4`
  - artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R4.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R4.bin`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: active restore points staged and ready.

## Update 2026-02-24
- Change: Published current `R4` dataset-driven CGM replay baseline to project remote.
  - branch: `main`
  - commit: `0b11472`
  - push target: `origin/main`
- Result: GitHub now contains the active restore-point firmware/docs state.

## Update 2026-02-24
- Change: Tightened prediction scoreboard tolerance from `±10%` to `±5%` for stricter hit-rate evaluation.
  - `src/gauge_render.c`
    - `PredTolerance10PctMgdl(...)` replaced by `PredTolerance5PctMgdl(...)`
    - tolerance math changed from rounded `ref/10` to rounded `ref/20` (minimum 1 mg/dL)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: device now reports prediction score under ±5% acceptance criteria.

## Update 2026-02-24
- Change: Adjusted prediction scoreboard tolerance to `±8%`.
  - `src/gauge_render.c`
    - replaced `PredTolerance5PctMgdl(...)` with `PredTolerance8PctMgdl(...)`
    - tolerance now computed as rounded `8%` of reference prediction with minimum `1 mg/dL`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: device now reports prediction score under ±8% acceptance criteria.

## Update 2026-02-24
- Change: Completed comprehensive CGM prediction improvement pass (training + runtime scoring alignment).
  - Model training/comparison/export:
    - added `tools/train_cgm_compare_export.py` to train and compare five models (`ridge`, `elastic_net`, `huber`, `random_forest`, `gradient_boosting`)
    - features expanded to 16 fields (multi-lag glucose, multi-window deltas/rollups, time-of-day sin/cos)
    - target changed to `+15m delta` (robust target form), then converted to absolute mg/dL in runtime
    - generated:
      - `model/cgm_compare_metrics.json`
      - `src/cgm_model_generated.h`
    - holdout results summary:
      - best overall: `random_forest` (MAE `5.98`, hit@10% `93.25%`)
      - best C-embeddable: `huber` (MAE `5.86`, hit@10% `92.62%`) and exported to firmware header
  - Runtime model integration:
    - `src/cgm_preprocess.c/.h`
      - model now consumes generated header coefficients/statistics
      - feature runtime updated to 16-feature set with `epoch_ds` support
      - predictor now uses trained `+15m delta` output and maps to absolute glucose
  - Score/evaluation improvements:
    - `src/gauge_render.c`
      - prediction scoring issue cadence aligned to 5-minute sample cadence (`3000 ds`)
      - low-confidence score gating added (`AI on`, SQI>=60, model_conf>=55, prediction not blocked)
      - split counters added for warmup vs steady-state scoring; steady-state score shown once available
      - score tolerance remains configurable and currently set to `±8%`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: firmware now uses auto-compared exported model with cadence-aligned, confidence-gated, steady-state-first scoring behavior.

## Update 2026-02-24
- Change: Score metric policy adjusted to match requested clinical-demo interpretation.
  - `src/gauge_render.c`
    - score tolerance set to `±10%`
    - score counters/evaluations now include `+15m` predictions only
    - `+30m` prediction remains visible in UI and MAE path but is excluded from accuracy score hit-rate until dedicated +30m training is added
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: prediction score box now reports +15m-only ±10% hit-rate.

## Update 2026-02-24
- Change: LIVE replay CGM path now ingests real `subject001` glucose samples instead of synthetic glucose generation during playback.
  - Added generated glucose replay header from holdout dataset:
    - `src/cgm_replay_subject001.h` (`CGM_REPLAY_SUBJECT001_LEN=1438`, sourced from `data/d1namo_test_subject001.csv`)
  - Firmware wiring:
    - `src/edgeai_medical_device_demo.c`
      - playback loop now feeds each replay step into CGM via `GaugeRender_IngestReplayCgmSample(...)`
      - replay CGM index resets on all playback start/restart paths
      - replay CGM ingest disabled during record/non-playback paths
    - `src/gauge_render.h/.c`
      - added `GaugeRender_IngestReplayCgmSample(...)`
      - bypass synthetic CGM generation while LIVE replay CGM ingest is active
      - UI center label shows `DATA` (instead of `SIM`) for replay-driven CGM
- Scoring alignment:
  - prediction score continues to use due-time interpolation fix from prior update and now evaluates against replay-driven glucose truth during playback.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ready for 4-day subject001 benchmark run with dataset-driven CGM path.

## Update 2026-02-24
- Change: Fixed prediction score under fast replay by evaluating each due prediction against an interpolated glucose actual at the prediction due timestamp (instead of scoring all overdue slots against one current glucose sample).
  - `src/gauge_render.c`
    - added due-time actual interpolation helper for prediction scoring
    - `PredEvalConsumeDue(...)` now uses interpolated due-time glucose
    - added rolling previous `(time, glucose)` state to support replay time jumps
- Why:
  - in warmup/full-run fast modes, timeline steps can be larger than scoring issue cadence; this previously biased score low.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ready for on-device re-check of prediction score progression.

## Update 2026-02-24
- Change: Removed synthetic startup accuracy by requiring real evaluation evidence before score priming.
  - `src/gauge_render.c`
    - `GaugeRender_PrimePredictionScore()` now requires `gUiPredEvalCount >= 6` before priming
    - if evaluations are insufficient, score remains unprimed at `0%` (no fallback 67% baseline)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Added explicit score priming at warmup completion so post-preroll score does not remain at 0 due to priming lag.
  - `src/gauge_render.h/.c`
    - added `GaugeRender_PrimePredictionScore()` to force score primed state from current MAE blend
  - `src/edgeai_medical_device_demo.c`
    - call prime hook on both warmup completion paths:
      - normal completion (`AI_WARMUP: complete ...`)
      - forced completion (`AI_WARMUP: force_complete ...`)
- Effect:
  - score is initialized immediately after warmup handoff instead of waiting for additional real-time priming cycles
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Extended fast warmup window to include additional scoring runway before LIVE realtime handoff.
  - `src/edgeai_medical_device_demo.c`
    - replaced single warmup target with phased durations:
      - preseed: `RECPLAY_WARMUP_PRESEED_DS = 2h`
      - score: `RECPLAY_WARMUP_SCORE_DS = 2h`
      - total fast window: `RECPLAY_WARMUP_TARGET_DS = 4h`
    - startup log now prints both phase durations
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed lingering `THINKING` after warmup by making warning-overlay thinking gate warmup-flag only.
  - `src/gauge_render.c`
    - `THINKING` display condition changed from:
      - `ai_enabled && (gUiWarmupThinking || !gUiPredMaePrimed)`
      - to `ai_enabled && gUiWarmupThinking`
  - effect: once warmup clears (normal or forced), warning box will not remain in `THINKING` due to MAE priming lag.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Eliminated persistent `THINKING` latch after warmup by making warning-box `THINKING` state warmup-only.
  - `src/gauge_render.c`
    - `DrawAiAlertOverlay(...)` now enters `THINKING` only when explicit warmup flag is true (`gUiWarmupThinking`)
    - removed additional `!gUiPredMaePrimed` condition from warning overlay gating
- Effect:
  - after warmup clear (or force-complete), warning box exits `THINKING` even if prediction MAE priming is still catching up
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed stuck `THINKING` state after 2h by adding a display-timeline fail-safe unlatch for warmup completion.
  - `src/edgeai_medical_device_demo.c`
    - in runtime-clock update loop, if warmup is still active but `runtime_displayed_ds >= RECPLAY_WARMUP_TARGET_DS`:
      - force warmup complete
      - clear `THINKING`
      - reset playback cadence state
      - emit `AI_WARMUP: force_complete ...`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed apparent freeze after LIVE warmup by interpolating runtime clock continuously between real-time replay samples.
  - `src/edgeai_medical_device_demo.c`
    - added replay realtime anchor state:
      - `playback_rt_anchor_ds`
      - `playback_rt_anchor_ticks`
    - when LIVE + post-warmup replay is active, runtime clock now advances from anchor using elapsed wall time until next replay sample arrives
    - anchor updates on each replay sample; anchor-based interpolation coexists with timestamp-delta sample cadence
- Effect:
  - timeline no longer appears stuck at sample boundaries (e.g. `02:15:00`) while running true real-time playback with sparse (5-minute) samples
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: After LIVE warmup completes, replay now switches to real-time playback cadence driven by replay timestamp deltas.
  - `src/edgeai_medical_device_demo.c`
    - added playback cadence state (`playback_period_us`, `playback_prev_ts_ds`, `playback_prev_ts_valid`)
    - when `LIVE` and warmup is complete, recplay period is taken from `ts_ds` delta between consecutive replay samples (`ds * 100000us`)
    - clamps real-time period range to `0.1s .. 600s`
    - resets cadence state on mode changes, restart/retry, and loop boundary to avoid stale timing
  - effect:
    - warmup still fast-forwards
    - post-warmup playback follows dataset timing instead of fixed log-rate stepping
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Decoupled LIVE sensor visualization channels from replay payload so ball/activity/IMU visuals are no longer driven by preloaded test replay samples.
  - `src/edgeai_medical_device_demo.c`
    - restored live sensor updates during playback by removing `!playback_active` gate in accel/gyro update loop
    - playback branch now treats ext-flash samples as timeline/playhead input only (no direct overwrite of accel/gyro/mag/baro/temp render channels)
  - intent:
    - keep long replay timeline behavior for CGM/timing demo
    - keep movement/activity visuals tied to real board sensors instead of synthetic replay-mapped values
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Added boot-time preload of full default replay dataset into ext flash to test 4+ day playback timeline capacity.
  - `src/edgeai_medical_device_demo.c`
    - added `PreloadDefaultReplayToExtFlash(...)`:
      - clears ext flash sample ring
      - writes all `REPLAY_TRACE_DEFAULT_LEN` samples from `kReplayTrace_Default`
      - assigns timeline spacing `REPLAY_DEFAULT_STEP_DS=3000` (5-minute intervals)
    - startup now runs preload when ext flash is ready, then rewrites UI settings metadata so saved UI config remains valid
  - expected replay timeline span from preloaded trace:
    - `(REPLAY_TRACE_DEFAULT_LEN - 1) * 3000 ds` (about 4.99 days with current 1438 samples)
  - UART markers added:
    - `EXT_FLASH_PRELOAD: start ...`
    - `EXT_FLASH_PRELOAD: done ...`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed LIVE replay timeline freeze around `07:47` by hardening runtime clock progression and playback restart behavior.
  - `src/edgeai_medical_device_demo.c`
    - playback timestamp clamp now advances by `+1 ds` on non-monotonic sample times instead of pinning to a fixed value
    - added LIVE-mode auto-retry restart path when playback becomes inactive (`EXT_FLASH_PLAY: retry_restart`)
  - intent: prevent timeline lock at a fixed time when replay timestamps repeat or when restart fails once at trace boundary
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Added startup fast-warmup flow for LIVE replay so UI stays in `THINKING` until 2 hours of replay timeline are preseeded, then automatically switches to realtime replay speed.
  - `src/edgeai_medical_device_demo.c`
    - added warmup constants:
      - `RECPLAY_WARMUP_MULTIPLIER=120`
      - `RECPLAY_WARMUP_TARGET_DS=72000` (2h)
    - added warmup state machine (`ConfigurePlaybackWarmup(...)`) and applied it to all playback start/restart paths
    - during playback, consumes accelerated replay steps during warmup and auto-handoffs to realtime once target timeline reached
    - emits UART markers:
      - `AI_WARMUP: start ...`
      - `AI_WARMUP: complete ... switching to realtime`
  - `src/gauge_render.c/.h`
    - added `GaugeRender_SetWarmupThinking(bool)` so warning box `THINKING` can be explicitly held during warmup phase
    - `THINKING` now stays active while warmup flag is set (or prediction scoring is unprimed)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Persisted AI backend selection (`AI MCU` / `AI NPU`) across reboot so settings no longer reset to NPU on boot.
  - updated UI settings metadata schema in `src/ext_flash_recorder.c/.h` to store backend selection with backward-compatible decode
  - wired backend field through save/load APIs and app startup restore in `src/edgeai_medical_device_demo.c`
  - updated settings save callsites to include `ai_use_npu`
  - startup log now prints backend in `UI_CFG_LOAD` line
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Promoted latest verified firmware/docs baseline to new restore points and staged artifacts.
  - restore tags:
    - `GOLDEN-2026-02-24-R3`
    - `FAILSAFE-2026-02-24-R3`
  - staged artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R3.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R3.bin`
  - updated `docs/TODO.md` step 0 and `docs/PROJECT_STATE.md` restore headers to R3
- Result: ok

## Update 2026-02-24
- Change: Completed CGM alignment step 12 by defining a measurable validation protocol and acceptance thresholds.
  - new doc: `docs/CGM_VALIDATION_PROTOCOL.md`
  - includes pass/fail criteria for:
    - lag estimation (median/P95/max)
    - trend accuracy by glucose range (MAE and sign agreement)
    - alert false-positive and chatter rates
    - replay robustness under dropout/noise/motion artifacts
  - TODO step 12 marked complete in `docs/TODO.md`
- Result: ok

## Update 2026-02-24
- Change: Tuned predictive CGM alert gating to reduce false low/high warnings around stable near-range glucose.
  - updated `src/gauge_render.c` `UpdatePredictionModelAndAlerts()`:
    - suppress predictive alert evaluation when `CGM_FLAG_IMPLAUSIBLE_ROC` is active
    - require trend-direction and minimum trend magnitude for hypo/hyper warning/fault entry
    - add current-glucose sanity bands for alert entry (warn/fault) to avoid unrealistic trips from transient trend spikes
  - no change to CGM preprocessing math; this is alert-decision logic only
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 1 by adding stage-by-stage traceability against the dermal CGM review.
  - new doc: `docs/CGM_TRACEABILITY.md`
  - each review stage now tagged as `implemented`, `simulated`, or `missing` with code/doc evidence references
  - TODO step 1 marked complete in `docs/TODO.md`
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 2 by defining the runtime CGM tuple contract.
  - new doc: `docs/CGM_RUNTIME_CONTRACT.md`
  - defined canonical tuple fields:
    - `glucose_mgdl`
    - `trend_mgdl_min_x100` (fixed-point)
    - `sqi_pct`
    - `sensor_flags`
    - `prediction_15m_mgdl`
    - `prediction_30m_mgdl`
  - included units/ranges/sentinel behavior, update cadence, stale rules, and initial sensor flag bit assignments
  - TODO step 2 marked complete in `docs/TODO.md`
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 3 by defining sensor-status taxonomy and trigger logic.
  - new doc: `docs/CGM_SENSOR_FLAGS.md`
  - documented set/clear logic, debounce windows, and precedence for:
    - `CGM_FLAG_SATURATION`
    - `CGM_FLAG_DROPOUT`
    - `CGM_FLAG_IMPLAUSIBLE_ROC`
    - `CGM_FLAG_TEMP_OUT_OF_RANGE`
    - `CGM_FLAG_CAL_STALE`
    - `CGM_FLAG_DRIFT_WARN`
  - updated `docs/CGM_RUNTIME_CONTRACT.md` to reference detailed flag logic
  - TODO step 3 marked complete in `docs/TODO.md`
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 4 by publishing the 30-second cadence reference pipeline artifact.
  - new doc: `docs/CGM_30S_PIPELINE_REFERENCE.md`
  - includes:
    - end-to-end block diagram
    - equations-level pseudocode at 1 Hz internal / 30 s publish cadence
    - candidate filter constants for anti-alias, fast LP, derivative smoothing, impulse reject, notch
    - SQI feature set and threshold strategy
    - drift random-walk and conservative lag correction model structure
    - contract mapping to `cgm_tuple_t`
  - TODO step 4 marked complete in `docs/TODO.md`
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 5 by implementing raw-to-engineering preprocessing in firmware.
  - added preprocessing module:
    - `src/cgm_preprocess.h`
    - `src/cgm_preprocess.c`
  - preprocessing stages implemented:
    - ADC-domain conversion with offset/gain and quadratic linearization
    - reference-voltage compensation
    - anti-alias low-pass filtering
    - decimation
    - impulse-noise rejection (median-3)
    - configurable notch filtering
  - integrated into renderer glucose path (`src/gauge_render.c`) using a synthetic raw stream adapter so UI/dose logic now consumes preprocessed glucose output
  - updated SDK overlay sources to compile new module (`sdk_example/mcuxsdk_examples_overlay/demo_apps/edgeai_medical_device_demo/CMakeLists.txt`)
  - updated traceability status for stage 1 in `docs/CGM_TRACEABILITY.md`
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Promoted current built/flashed runtime as the active golden/failsafe baseline and synchronized project docs.
  - built and flashed current firmware via `./scripts/build_and_flash.sh`
  - staged restore artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R3.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-23-R3.bin`
  - updated state/runbook/start/hardware/todo/readme/status documentation to reference R3 restore baseline
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Finalized higher-band label naming for consistent style.
  - `ACTIVE ACTIVITY` renamed to `HIGH ACTIVITY`
  - final/top band renamed from `HEAVY ACTIVITY` to `EXT ACTIVITY`
  - keeps post-`MOD` labels in compact same-format phrasing
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Renamed ACTIVE-stage alert label for wording consistency.
  - updated headline text from `ACTIVE ACTIVITY` to `HIGH ACTIVITY`
  - keeps naming progression aligned with `MOD ACTIVITY` and `HEAVY ACTIVITY`
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Prevented long activity labels from overflowing the alert box.
  - added dynamic label-fit logic in `DrawAiAlertOverlay()`:
    - headline renders at scale-2 when it fits
    - automatically falls back to scale-1 if width exceeds alert box budget
  - fixes overflow for strings such as `MOD ACTIVITY` and other long labels
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Fixed alert headline overflow for long state labels (e.g., `MODERATE ACTIVITY`).
  - added width-aware auto-fit in `DrawAiAlertOverlay()`:
    - default headline scale remains 2
    - automatically falls back to scale 1 when text width exceeds alert box width budget
  - applies to both normal and warning/fault alert render paths
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Tuned REST coverage to occupy the first three ticks of the activity arc bargraph.
  - activity arc uses `54` ticks (5-degree segments over 270 degrees)
  - set LIGHT entry threshold to `6%` (`~3/54`) so `HUMAN REST` spans the first three ticks
  - kept LIGHT split behavior (`HUMAN MOVEMENT` / `HUMAN ACTIVE`) unchanged
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Made LIGHT-band triggering much earlier and advanced HUMAN ACTIVE transition.
  - LIGHT entry threshold reduced from `10` to `3` (~75% earlier trigger)
  - LIGHT split threshold reduced from `22` to `14` so `HUMAN ACTIVE` appears earlier
  - resulting LIGHT-band labels:
    - `HUMAN MOVEMENT` for `3..13`
    - `HUMAN ACTIVE` for `14..29`
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Reduced HUMAN MOVEMENT trigger threshold so it engages earlier.
  - lowered LIGHT entry threshold in `ActivityStageFromPct()` from `13` to `10`
  - result: earlier transition from `HUMAN REST` to LIGHT-band labels (`HUMAN MOVEMENT` / `HUMAN ACTIVE`)
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Split LIGHT stage into two separate alert-scale labels (instead of LIGHT ACTIVITY wording).
  - lower LIGHT sub-threshold now shows `HUMAN MOVEMENT`
  - upper LIGHT sub-threshold now shows `HUMAN ACTIVE`
  - removed prior two-line LIGHT rendering and restored single-line threshold label behavior
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Split LIGHT activity headline into two-part human-movement wording in alert box.
  - for LIGHT stage, alert now renders two lines:
    - `HUMAN MOVEMENT`
    - `LIGHT ACTIVITY`
  - other stages continue using single-line headline labels
  - extended alert headline cache key size and logic to support two-line state redraw correctness
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Tuned human-activity stage sensitivity to make moderate/heavy states easier to enter.
  - adjusted `ActivityStageFromPct()` thresholds in `src/gauge_render.c` from:
    - `HEAVY 78`, `ACTIVE 58`, `MODERATE 38`, `LIGHT 16`
    - to `HEAVY 62`, `ACTIVE 46`, `MODERATE 30`, `LIGHT 13`
  - intent: approximately 20% easier transition into higher activity bands with no change to sensor-fusion inputs
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Reverted alert box width and reduced alert headline visual size.
  - restored alert width geometry to prior values (`ALERT_X0=147`, `ALERT_X1=325`)
  - switched headline draw path from shadowed text to crisp text at same scale for approximately 10% smaller perceived size
  - retained headline-change redraw caching fix to avoid stale glyph artifacts
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Improved alert box layout and state redraw stability.
  - increased alert-box width by ~5% (`ALERT_X0: 147 -> 142`, `ALERT_X1: 325 -> 330`)
  - added cached alert-headline tracking so headline changes force redraw and prevent stale/stray glyph artifacts
  - targeted issue: stray character appearing next to warning box during state transitions
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Refined alert headline phrasing to explicit human-state wording.
  - mapped alert labels to:
    - `HUMAN REST`
    - `LIGHT ACTIVITY`
    - `MODERATE ACTIVITY`
    - `ACTIVE ACTIVITY`
    - `HEAVY ACTIVITY`
  - implemented with new activity-headline string mapping in `src/gauge_render.c`
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Updated alert box headline text to human-state mapping across all activity stages.
  - replaced fixed/system status headline with `HUMAN <state>` text derived from runtime activity stage
  - states now displayed in alert headline: `REST`, `LIGHT`, `MODERATE`, `ACTIVE`, `HEAVY`
  - applied in `src/gauge_render.c` `DrawAiAlertOverlay()` for both normal and warning/fault render paths
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Rebuilt and reflashed current medical demo firmware on FRDM-MCXN947.
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Reformatted CGM alignment TODO into explicit numbered execution steps.
  - updated `docs/TODO.md` from unordered checklist format to `1..12` numbered checklist format
  - preserved task content while improving planning readability and review handoff
- Result: ok

## Update 2026-02-23
- Change: Finalized medical-demo repo cleanup to eliminate package-demo crossover risk.
  - removed legacy package-demo app sources/overlay paths from active tree
  - retained medical-demo app paths/scripts as the sole build/flash target
  - confirmed repo scan has no package-demo keyword references in active files
- Verification:
  - `./scripts/preflight.sh` PASS
  - `./scripts/build_and_flash.sh` PASS (build + LinkServer flash, probe `#1`)
  - repo keyword scan PASS (`edgeai_package_transport*` not found in active files)
- Result: ok

## Update 2026-02-23
- Change: Replaced legacy TODO backlog with a direct CGM-alignment task list derived from `docs/CGM_DERMAL_ALGORITHM_REVIEW.md`.
  - cleared prior mixed historical checklist in `docs/TODO.md`
  - added explicit execution steps for CGM data contract, preprocessing, filtering, compensation, SQI/fault gating, prediction/alerts, UI semantics, and validation protocol
- Result: ok

## Update 2026-02-23
- Change: Completed hygiene and operations alignment pass for medical demo baseline.
  - sanitized project command-log wording to remove internal/root path naming in `docs/COMMAND_LOG.md`
  - synced stale TODO status to reflect implemented display/runtime items in `docs/TODO.md`
  - added CI workflow `/.github/workflows/build.yml` with:
    - `./scripts/preflight.sh`
    - shell syntax checks for core scripts/tools
    - host compile smoke test (`src/main.c` + `src/medical_lcd_layout.c` + `src/medical_display_stub.c`)
- Verification:
  - `./scripts/preflight.sh` PASS
  - `./scripts/build_and_flash.sh` PASS (build + LinkServer flash, probe `#1`)
  - local CI-equivalent run PASS (shell syntax + host compile/run)
- Result: ok

## Update 2026-02-23
- Change: Completed full documentation cleanup to remove legacy naming tied to earlier non-medical wording.
  - updated `README.md`, `docs/TODO.md`, `docs/PROJECT_STATE.md`, and SDK overlay readme text for medical-demo wording consistency
  - normalized prior command-log wording in `docs/COMMAND_LOG.md` where legacy naming appeared
- Change: Promoted current baseline as restore points:
  - Golden: `GOLDEN-2026-02-23-R2`
  - Failsafe: `FAILSAFE-2026-02-23-R2`
- Verification:
  - Documentation consistency scan across markdown files: PASS (no legacy legacy wording remains)
- Result: ok

## Update 2026-02-23
- Change: Shifted all settings rows with buttons left by ~3 character widths (18 px), keeping non-button rows unchanged.
  - Updated X-start constants in `src/gauge_render.h` for:
    - `MODE`, `RUN`, `SENS`, `AI`, `OPEN LIMITS`, `CLEAR FLASH`, and `LOG HZ` controls.
- Change: Added recorder memory usage indicator to the `FLASH` row.
  - Added `ExtFlashRecorder_GetUsageInfo(...)` API in `src/ext_flash_recorder.h/.c`.
  - Settings popup now renders `% USED` text next to a narrower `CLEAR FLASH` button in `src/gauge_render.c`.
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - Build output: `mcuxsdk_ws/build/<generated_firmware>.bin`
  - Flash target: `MCXN947:FRDM-MCXN947` on probe `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Shifted only the `LOOSE / NORM / STRICT` settings row right to avoid covering the `SENS` label.
  - Updated `GAUGE_RENDER_SET_TUNE_X0` in `src/gauge_render.h` from `96` to `180`.
  - No other settings-row geometry constants were changed.
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - Build output: `mcuxsdk_ws/build/<generated_firmware>.bin`
  - Flash target: `MCXN947:FRDM-MCXN947` on probe `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Removed colon from AI settings row label text:
  - `AI:` -> `AI` in `src/gauge_render.c` so settings now reads `AI MCU NPU`.
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - Build output: `mcuxsdk_ws/build/<generated_firmware>.bin`
  - Flash target: `MCXN947:FRDM-MCXN947` on probe `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Fixed settings-row layout so `AI: MCU NPU` renders cleanly without label overlap:
  - moved AI row button start x-coordinate to align with other settings rows (`GAUGE_RENDER_SET_AI_X0: 144 -> 184` in `src/gauge_render.h`).
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - Build output: `mcuxsdk_ws/build/<generated_firmware>.bin`
  - Flash target: `MCXN947:FRDM-MCXN947` on probe `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Hardware Setup
- Board: FRDM-MCXN947
- Probe: MCU-Link CMSIS-DAP (use `#1`)
- Debug USB: J17

## Build/Flash Config
- Build Command: ./tools/build_frdmmcxn947.sh debug
- Flash Command: /usr/local/LinkServer/LinkServer flash --probe '#1' MCXN947:FRDM-MCXN947 load --addr 0x0 {BIN_PATH}
- Binary: mcuxsdk_ws/build/<generated_firmware>.bin
- Status File: STATUS.md

## Update 2026-02-22
- Change: Initial standalone framework scaffold with docs/scripts/source layout.
- Result: ok

## Update 2026-02-22
- Change: Added project-local AGENTS instructions (gitignored), initialized git, committed framework scaffold, and pushed `main` to GitHub.
- Result: ok

## Update 2026-02-22
- Change: Implemented first-pass medical LCD graphics layout slice using same 480x320 background image:
  - Added `src/medical_lcd_layout.c` and `src/medical_lcd_layout.h`
  - Added platform drawing HAL contract `src/medical_display_hal.h`
  - Added temporary no-op host compile stub `src/medical_display_stub.c`
  - Imported background asset `src/spacebox_bg.h`
  - Updated `src/main.c` to drive static+dynamic layout demo path
- UI layout coverage in this slice:
  - `NXP EDGEAI` retained in top-center region
  - elapsed time retained in bottom-center region
  - right-side graph + terminal panels retained
  - left/center medical visuals added: motor, pump, wearer-context figure
- Verification:
  - `cc -std=c11 -Wall -Wextra -I./src src/main.c src/medical_lcd_layout.c src/medical_display_stub.c -o /tmp/edgeai_medical_lcd_layout_demo`
  - execution output: `EdgeAI medical device LCD layout staged.`
- Result: ok

## Update 2026-02-22
- Change: Switched LCD background source to project image `docs/pump.png` and generated `src/pump_bg.h` (480x320 RGB565).
- Change: Updated renderer (`src/medical_lcd_layout.c`) to blit `g_pump_bg_rgb565` and keep overlay layout:
  - top-center `NXP EDGEAI`
  - bottom-center elapsed time
  - right-third graph + terminal
  - left/center motor + pump + wearer graphics
- Verification:
  - Host compile smoke test PASS:
    - `cc -std=c11 -Wall -Wextra -I./src src/main.c src/medical_lcd_layout.c src/medical_display_stub.c -o /tmp/edgeai_medical_lcd_layout_demo`
  - Scripted preflight/build PASS with `BUILD_CMD` override.
  - Flash attempt blocked by configuration (no MCU `BIN_PATH` set in project state): `Binary is empty. Set BIN_PATH or docs/PROJECT_STATE.md`.
- Result: ok (graphics milestone), flash pending MCU build artifact integration.

## Update 2026-02-22
- Change: Refreshed LCD background from the current `docs/pump.png` and regenerated `src/pump_bg.h`.
- Change: Reworked overlay strategy to align active data labels with icon regions in the new background art:
  - motor region now shows live `RPM`, `CUR`, `LOAD`, and anomaly bar indicator
  - pump region now shows `RATE`, `FILL`, and `STATE` with tank fill-level visualization and pumping activity marker
  - human center region now shows gyro ring pointer around the large central circle plus `INV`/`DROP` status labels
- Change: Extended display state contract (`src/medical_lcd_layout.h`) with dynamic fields:
  - `motor_anomaly_pct`, `pump_fill_pct`, `pump_active`, `gyro_angle_deg`, `inverted`, `drop_detected`
- Verification:
  - Host compile/run PASS:
    - `cc -std=c11 -Wall -Wextra -I./src src/main.c src/medical_lcd_layout.c src/medical_display_stub.c -lm -o /tmp/edgeai_medical_lcd_layout_demo`
  - Scripted preflight/build PASS with `BUILD_CMD` override.
  - Flash attempt remains blocked pending MCU binary config (`BIN_PATH` empty).
- Result: ok (overlay behavior implemented), flash pending firmware build artifact path.

## Update 2026-02-22
- Change: Removed legacy motion widgets from active LCD renderer path:
  - removed gyro sphere visual
  - removed accel box/ball visual
  - retained only gyro ring pointer plus motor/pump/human-aligned overlays
- Change: Wired medical project into MCU SDK build/flash flow using local `tools/build_frdmmcxn947.sh` and `tools/flash_frdmmcxn947.sh`, with overlay wrapper sourcing this repo's `src/` code.
- Verification:
  - Build PASS:
    - `./tools/build_frdmmcxn947.sh debug`
    - output binary: `mcuxsdk_ws/build/<generated_firmware>.bin`
  - Flash PASS:
    - `./tools/flash_frdmmcxn947.sh`
    - runner: `linkserver`, probe `#1`, target `MCXN947:FRDM-MCXN947`
- Notes:
  - `west update` in setup reported non-critical failures for unrelated repos; required demo build/flash path still completed successfully.
- Result: ok

## Update 2026-02-22
- Change: Restored reference visual baseline for LCD rendering behavior in medical firmware:
  - same `NXP EDGEAI` placement/color/size as reference baseline
  - same elapsed-time placement/color/size as reference baseline
  - right-third timeline buttons (`PLAY/STOP`, `REC`, `LIVE`), graph, and terminal kept in reference style/flow
- Change: Removed center motion widgets per direction:
  - removed gyro sphere/ring widget rendering path
  - removed accel wire-box and accel ball rendering path
- Change: Added transparent medical data labels (no black boxes/borders) positioned over background icons:
  - motor labels (`RPM`, current, anomaly, wear)
  - pump labels (state/rate/fill)
  - human labels (gyro values, pose inversion, drop risk)
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Applied requested medical UI refinements on top of reference-style baseline:
  - magnetometer stream disabled in render path and `MAG` removed from terminal output
  - left temperature bargraph reduced significantly while staying on far-left edge
  - motor overlay labels shifted down by two text rows
  - battery indicator moved between motor and pump regions and reduced by 20%
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Moved left temperature bargraph to bottom-edge placement and removed black bargraph background fills so the bargraph renders transparently over the background image.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Adjusted temp bargraph layout/detail styling:
  - moved bargraph upward from the previous bottom-most position so temp text is fully visible
  - increased bargraph height by 10% while keeping width unchanged
  - set temp-text background box color to match `AX` trace color
  - moved pump `IDLE/RATE/FILL` text right by ~2 characters and down by 2 text rows
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Moved temp C/F label to the very bottom edge of the LCD render area.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Increased temp C/F label text size to large (2x font scale) and expanded the bottom temp label box accordingly.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Reduced bottom temp C/F text size from large to medium (single-scale) and resized the label box to match.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Extended the blue temp label background by one character width past the trailing `F`.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Resized temp bargraph to requested dimensions:
  - height increased to approximately 2x current size
  - width increased by 25%
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Moved `(c)RICHARD HABERKERN` text to top edge of LCD render area.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Moved battery label and graphic to the lower-right corner under terminal.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Shifted battery label/graphic by requested relative offset:
  - left by 25% of battery graphic width
  - up by 50% of battery graphic height
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Refined battery widget alignment:
  - moved positive terminal to vertical center of battery body
  - moved `BATT` label to left-center of battery graphic
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Corrected battery icon readability:
  - positive terminal centered vertically on right side of battery body
  - `BATT` text rendered persistently at left-center of battery graphic
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-22
- Change: Styled battery positive terminal as a white boxed `+` and aligned it with the `BATT` text baseline; retained persistent `BATT` label redraw each frame.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Reworked battery indicator rendering for better readability on-device:
  - battery body now uses a stronger white outline around the dark interior
  - right-side positive terminal is a thicker, centered white rectangular nub attached to the battery body
  - battery frame is redrawn in the dynamic path each frame to prevent partial visual overwrite
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Moved battery widget down by ~10% of battery height to avoid upper-edge clipping against terminal area (`BATT_Y: 287 -> 289`).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Refined battery placement and SOC text alignment:
  - moved battery down 2 additional pixels (`BATT_Y: 289 -> 291`)
  - centered `82%` SOC text vertically inside the battery body/fill region
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Adjusted branding/time vertical layout:
  - moved `NXP EDGEAI` down by ~50% text-height (`y: 286 -> 293`)
  - moved elapsed-time row to maintain 5 px vertical padding from `NXP EDGEAI` (`RTC_TEXT_Y: 259 -> 274`)
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Shifted both brand and elapsed-time text down by an additional 10 px:
  - `NXP EDGEAI` y: `293 -> 303`
  - elapsed-time y (`RTC_TEXT_Y`): `274 -> 284`
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Updated human-center text overlays per request:
  - removed `AI: ACTIVE/OFF` label from center region
  - moved `GYR`, `POSE`, and `DROP` lines below the human figure into the band above elapsed time
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Updated human-status text formatting:
  - corrected `GYR` label to `GYRO`
  - increased human-status text visual size by approximately 25% using a controlled overdraw helper for scale-1 LCD font rendering
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed center human-status text ghosting/overlap artifacts by restoring the underlying background image region before redrawing `GYRO`, `POSE`, and `DROP` lines each frame.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Expanded center GYRO line to include Z-axis values (`GYRO X/Y/Z`) instead of only X/Y.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Added a human-orientation pointer gauge around the center figure:
  - speedometer-style circular tick ring
  - rotating 360-degree arrow pointer driven by accelerometer orientation
  - pointer color changes to red when upside-down is detected
  - background restore added for the gauge region to prevent pointer trails
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Refined orientation gauge visuals to match target style:
  - enlarged gauge diameter to align with the center dial graphic (`r = MAIN_R - 6`)
  - replaced needle-style pointer with a head-only arrow marker that points to tick marks
  - kept 360-degree rotation and upside-down red-state behavior
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Applied visibility/layout fixes:
  - moved warning/alert box up by 15 pixels (`ALERT_Y0: 48 -> 33`, `ALERT_Y1: 86 -> 71`)
  - clamped all seven scope traces (`AX/AY/AZ/GX/GY/GZ/T`) to the graph interior so no trace disappears on border lines
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Adjusted gyro orientation gauge geometry:
  - increased circle diameter by 25%
  - moved gauge center up by 20 pixels
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Moved gyro orientation circle center right by 2 pixels.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Moved gyro orientation circle up by 2 pixels.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Corrected layer ordering so gyro pointer/tick graphics render beneath warning-box and terminal UI layers (no clipping/overdraw of foreground panels).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Removed center `GYRO`, `POSE`, and `DROP` text overlays; the center status region is now background-only.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS (after removing now-unused helper)
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Applied combined gyro-display and pointer-style refinements:
  - terminal gyro line now shows one decimal place (`X/Y/Z` as `dps` with tenths)
  - live gyro feed to renderer upgraded to 0.1 dps resolution (with playback scaling compatibility)
  - orientation pointer circle diameter reduced by 20%
  - removed all tick marks from the pointer circle
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Re-referenced the human orientation pointer so it points down when the LCD is held facing the user (screen plane parallel to face), instead of using the prior vertical sign convention.
  - implementation: pointer angle now uses `atan2(-Y, Z)` in `DrawHumanOrientationPointer()`.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Applied additional 180-degree phase correction to orientation pointer because hardware posture still rendered inverted.
  - implementation: after `atan2(-Y, Z)`, add `+180deg` and wrap to `[0, 360)`.
  - behavior target: screen-facing posture points down toward ground.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Added a second gravity orientation access widget and stabilized the main human pointer for better visual behavior during movement.
  - main center pointer: UI-only smoothing added (low-pass on accel-derived orientation plus per-frame angular delta clamp) to reduce rolling/jitter.
  - new gravity indicator: compact `GRAV` mini-widget with circular marker and `TABLE/TILT` status, placed in left-middle region outside the human graphic.
  - sensor integrity: raw accelerometer/gyro streams and model-facing data paths are unchanged; damping is display-only.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Revised orientation UI per request:
  - removed the added left-segment gravity widget so the pump-text area remains in its prior layout.
  - replaced center arrow marker with a rolling ball inside the existing orientation circle.
  - rolling ball is accelerometer-driven (360-degree orientation mapping), light green in normal orientation, and light orange when upside down.
  - UI-only damping remains active for stable motion while leaving raw sensor/model data unchanged.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Tuned rolling-ball orientation behavior for requested kinematics:
  - reduced damping and increased per-frame angle step limit so motion responds faster.
  - changed ball radius from fixed-edge to tilt-proportional (`sqrt(X^2+Y^2)/|g|`), so:
    - table-flat posture drives ball toward center,
    - larger tilt drives ball outward toward the circle edge.
  - preserved screen-facing posture direction mapping (ball moves toward bottom when held parallel to eyes).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Increased center rolling-ball marker size by ~2x (from ~7x7 to ~14x14 visual footprint) for better readability.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Updated pump overlay typography:
  - `PUMP`, `RATE`, and `FILL` lines changed to yellow.
  - pump lines rendered ~50% larger using a new `DrawTextUi150()` helper (thickened 1x glyph pass).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Moved the full pump text block down toward the bottom-left F/C area while preserving 50%-larger yellow styling.
  - `PUMP`/`RATE`/`FILL` Y positions shifted by +20 px (`218/236/254` -> `238/256/274`).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Increased pump text size by ~20% from the previous custom enlarged style.
  - adjusted `DrawTextUi150()` glyph thickening passes to render approximately ~1.8x 1x size.
  - applies to `PUMP`, `RATE`, and `FILL` lines.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Increased `PUMP` / `RATE` / `FILL` text by an additional ~25%.
  - updated `DrawTextUi150()` to render approximately ~2.25x 1x size (from ~1.8x).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed pump text readability issue by switching from thickened pseudo-scaling to true scaled font rendering.
  - removed `DrawTextUi150()` helper.
  - `PUMP` / `RATE` / `FILL` now render with `DrawTextUi(..., scale=2, ...)`, preserving yellow color and shadow.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed bottom-circle accel-ball clipping/flicker in center area.
  - removed legacy center-region background blit (`BlitPumpBgRegion(172, 226, 322, 267)`) that overlapped the lower arc of the orientation circle.
  - kept pump-text region-only background restore active for text artifact cleanup.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Finalized pump-line artifact cleanup and unit labeling:
  - rate unit text normalized to explicit `ML/H` on the pump line.
  - pump text redraw background region narrowed (`x1: 240 -> 198`) to avoid any overlap with the center orientation-ball area.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Corrected remaining unit rendering and improved orientation-ball behavior.
  - added `/` glyph to `text5x7` font so `ML/H` renders correctly on-screen.
  - replaced center ball motion model with filtered accel X/Y projection and circular clamp:
    - table-flat -> ball near center,
    - tilt/motion -> ball moves in corresponding 2D direction within circle bounds.
  - removed now-unused angle-based ball state variables from renderer.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Corrected left/right orientation direction for the center ball.
  - inverted accel-X projection sign in ball mapping.
  - up/down mapping intentionally unchanged.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Moved `PUMP` / `RATE` / `FILL` text down by one font row (scale-2 row, +14 px) toward the bottom strip.
  - Y positions: `232/248/264` -> `246/262/278`.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed elapsed-timer clipping caused by pump text background restore overlap.
  - replaced single restore rectangle with two segmented regions that avoid the timer band in center area.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Adjusted motor headline styling/position.
  - moved `MTR RPM:...` line up by ~2.5 rows (`y: 62 -> 42`).
  - increased `MTR` line text size by ~25% using `DrawTextUi125()` helper.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Updated motor headline content and size.
  - label changed from `MTR RPM` to `RPM`.
  - headline increased by an additional ~25% by strengthening `DrawTextUi125()` expansion pass.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Moved motor `RPM` headline up by one additional text row.
  - draw position changed from `y=34` to `y=26` in `src/gauge_render.c`.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Refined motor `RPM` headline readability and placement.
  - moved one more row up (`y: 26 -> 18`).
  - switched render from thickened pseudo-scale helper to crisp native scale-2 draw for sharper edges and larger text (~30% increase vs prior 1.56x style).
  - marked legacy `DrawTextUi125` helper as `__attribute__((unused))` to satisfy `-Werror` after migration.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` first attempt FAIL (`DrawTextUi125` unused warning treated as error).
  - `./tools/build_frdmmcxn947.sh debug` PASS after helper annotation fix.
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`).
- Result: ok

## Update 2026-02-23
- Change: Improved `RPM` headline readability and horizontal placement.
  - moved right by two character cells at scale-2 (`x: 22 -> 46`, +24 px).
  - changed renderer from crisp single-pass to UI shadow style at scale-2 (`DrawTextUi`) for clearer contrast on the motor background.
  - added motor-region background restore (`BlitPumpBgRegion(20,12,220,102)`) before dynamic motor text draw to avoid stale glyph remnants after repositioning.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Tuned motor `RPM` headline position/size.
  - moved downward by about one-third row (`y: 18 -> 23`, +5 px).
  - reduced text size by about 20% by switching from scale-2 shadow render to `DrawTextUi125` pass.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed `RPM` readability regression and top-center UI clipping.
  - replaced `DrawTextUi125` with `DrawTextUi(..., scale=2)` for clearer `RPM` line rendering.
  - narrowed motor background restore from `BlitPumpBgRegion(20,12,220,102)` to `BlitPumpBgRegion(20,18,142,102)` so redraw no longer intrudes into the `* AI ON ?` row and warning panel area.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Adjusted motor `RPM` row horizontal position.
  - moved left by two character cells (`x: 46 -> 22`, -24 px).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Added synthetic RPM demo behavior for motor headline.
  - display now shows `RPM:x.y` where value is either `0.0` or random in `0.1..25.0`.
  - update interval is now random `10.0..30.0` seconds (RTC decisecond scheduler; frame-count fallback if RTC is unavailable).
  - implemented with lightweight xorshift PRNG state and decisecond next-update scheduling.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Added timed zero behavior to synthetic RPM demo.
  - when random RPM enters `0.0`, it now holds at zero for a random `5.0..20.0` seconds.
  - after zero-hold expires, it resumes non-zero random RPM updates with the existing `10.0..30.0` second cadence.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Updated motor RPM/current demo lines.
  - random RPM non-zero range expanded from `0.1..25.0` to `0.1..49.0`, so values like `21.x` and `49.0` can occur.
  - rewired the `I` row to display only current value text (`NNmA`) with no label.
  - current is now derived from RPM via linear mapping `0.0..49.0 RPM` -> `0..95 mA`.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Adjusted current (`mA`) row layout.
  - moved right by four character cells (`x: 22 -> 46`, +24 px).
  - increased text size by ~50% using `DrawTextUi125` helper.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Standardized motor text readability by matching `mA` row to `RPM` row typography.
  - `mA` row now uses `DrawTextUi(..., scale=2)` (same font style and same text size as RPM).
  - replaced prior `DrawTextUi125` path used for mA rendering.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Repositioned motor `mA` row for alignment.
  - moved left by one character width (`x: 46 -> 34`, -12 px at scale-2).
  - moved up by roughly two-thirds of a row (`y: 76 -> 71`, -5 px).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Corrected rollback for motor current row placement.
  - restored `mA` row from shifted position back to the prior center location (`x: 34 -> 46`, `y: 71 -> 76`).
  - this matches the state before the temporary left/up alignment experiment.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Adjusted motor `mA` row as requested.
  - moved left by one character width (`x: 46 -> 34`, -12 px at scale-2).
  - moved up by approximately two-thirds text height (`y: 76 -> 67`, -9 px).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Replaced motor wear row layout per request.
  - removed legacy `WR` row.
  - kept `mA` row at `x=34,y=67`.
  - added `ANOM:` row at `x=22,y=102` (exactly +35 px, i.e., 2.5 scale-2 row heights from mA row).
  - added `WEAR:` row at `x=22,y=116` (one additional scale-2 row below ANOM).
  - both `ANOM` and `WEAR` use same font/text height as `mA` (`DrawTextUi`, scale 2).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Repositioned `ANOM` and `WEAR` rows.
  - both rows moved left by one character width (`x: 22 -> 10`).
  - both rows moved down by 1.5 scale-2 rows (`+21 px`):
    - `ANOM y: 102 -> 123`
    - `WEAR y: 116 -> 137`
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Added extra vertical padding between `ANOM` and `WEAR` rows.
  - moved `WEAR` row down by 2 px (`y: 137 -> 139`) while keeping ANOM unchanged.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Added left-of-human blood glucose indicator.
  - new green text overlay: `BG 98 mg/dL`.
  - placement: `x=124`, `y=168` (left side of center human graphic).
  - rendering style: `DrawTextUi` scale 1 with green foreground (`RGB565(124,255,124)`).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Repositioned and enlarged blood sugar indicator.
  - moved from left side to centered below human figure.
  - new placement computed from center geometry (`x = MAIN_CX - 0.75*text_width`, `y = MAIN_CY + 56`).
  - increased text size by ~50% via `DrawTextUi125` while keeping green color.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Updated center blood sugar text formatting/placement.
  - removed `BG` prefix; text now `98 mg/dL`.
  - increased size to scale 3 (100% larger than previous 1.5x style).
  - moved up by roughly two rows and centered in middle segment using `SECTION2_CX` anchor.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Reduced center glucose text size.
  - switched rendering from scale `3` to scale `2` and recomputed centering with scale-2 text width.
  - text content and vertical placement unchanged.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed glucose text clipping caused by pump text background redraw.
  - extracted glucose overlay into dedicated `DrawGlucoseIndicator()` helper.
  - moved glucose rendering to late-frame order (after `DrawMedicalOverlayData`) so pump background restore cannot overdraw it.
  - preserved glucose content/style/position while changing z-order only.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Reworked glucose behavior to be slow and stable.
  - glucose now constrained to `96..106 mg/dL`.
  - value changes by `1 mg/dL` steps every `90..180` seconds (random), yielding ~15-30 minute full-range trend movement.
  - added direction state with occasional reversals plus hard boundary reversal at 96/106.
  - moved glucose text to `y=252` to keep it outside high-frequency gyro refresh blit area and eliminate rapid flashing artifacts.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Updated orientation ball color for normal posture.
  - right-side-up ball color changed from light green to medium dark blue (`RGB565(46,102,190)`).
  - upside-down color threshold/path remains unchanged (light orange when `gAccelZmg < -200`).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Moved center-segment glucose `mg/dL` row up by two row heights in LCD renderer (`src/gauge_render.c`, `bg_y: 252 -> 224`).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Wired pump state to motor RPM scheduler in `src/gauge_render.c`:
  - motor STOP phase: `0 RPM` for random `10..20s`
  - motor RUN phase: non-zero RPM for random `5..10s`
  - pump status now follows motor phase (`PUMP IDLE` when stopped, `PUMP ACTIVE` when running)
  - pump `RATE` now uses randomized dosing value (`1..95 ML/H`) generated each RUN phase
  - current (`mA`) remains mapped from RPM in `0..95mA`
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Calibrated pump reservoir simulation to insulin dosing model in `src/gauge_render.c`:
  - reservoir starts at `92%` of a `3.0 mL` cartridge on boot
  - dose modeled in `U/h` (stored as milli-units per hour), converted with U100 rule (`100 U = 1 mL`)
  - displayed flow now uses precise `mL/h` formatting (`RATE:x.xxx ML/H`)
  - fill percentage now drains from computed dose flow instead of SOC placeholder
  - motor/pump run-idle windows remain wired (`STOP 10..20s`, `RUN 5..10s`), with pulse-compensated drain to preserve realistic average dose trend toward ~3-day depletion
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Updated motor simulation to better match insulin-pump delivery behavior in `src/gauge_render.c`:
  - replaced long run/idle windows with short micro-dosing motor pulses (`0.8..1.2s`)
  - pulse interval is computed from basal dose rate (`U/h`) and fixed micro-bolus volume (`0.02 U` per pulse on U100)
  - basal target remains in pump-style `0.025 U/h` increments and retunes every `20..40 min`
  - current demo profile keeps basal centered near `4 U/h` (`3..5 U/h`) to align with 3-day 3mL depletion behavior
  - reservoir drain now occurs from each delivered pulse (discrete delivery model), not synthetic time scaling
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Removed stray text below `ANOM` and updated left-side bargraph to reservoir fill behavior:
  - deleted `WEAR` row under `ANOM`
  - added explicit background restore band below `ANOM` to clear stale/random text artifacts
  - rewired left bargraph from temperature-driven level to `FILL%` level (`gUiReservoirPct`)
  - changed bargraph label to `FILL %` and made active bars red when fill is below `20%`
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Optimized glucose line redraw behavior in `src/gauge_render.c`:
  - `mg/dL` row is now refreshed only when glucose value changes
  - added cached previous glucose value (`gPrevGlucoseMgdl`) and reset hooks on renderer reinit paths to ensure correct first redraw
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Optimized glucose line redraw behavior in `src/gauge_render.c`:
  - `mg/dL` row is now refreshed only when glucose value changes
  - added cached previous glucose value (`gPrevGlucoseMgdl`) and reset hooks on renderer reinit paths to ensure correct first redraw
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Restored `WEAR` row under `ANOM` in motor overlay (`src/gauge_render.c`) while keeping prior anti-artifact background clear.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed disappearing `mg/dL` row by removing pump-region background refresh overlap with glucose text band:
  - adjusted pump blit region from `y=228..281` to `y=240..281` in `src/gauge_render.c`
  - keeps `mg/dL` redraw-on-change optimization while preventing erase by later draw passes
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Restored lower-left temperature `C/F` text in blue box and increased text size ~20% without changing fill-driven bargraph behavior:
  - left bargraph remains wired to `FILL%` level and low-fill red threshold
  - bottom-left label text switched back to `T xx.xC xxx.xF`
  - added `DrawTextUi120()` helper for ~20% larger temp label rendering
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed intermittent `mg/dL` disappearance and added spacing between anomaly rows:
  - narrowed left bargraph background-restore span from `BAR_X0 + 188` to `BAR_X0 + 170` so it no longer clips into the `mg/dL` text zone
  - moved `WEAR` row down for added vertical padding under `ANOM` (`y: 139 -> 143`)
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed `mg/dL` row being erased by center-area background refresh:
  - in `DrawHumanOrientationPointer()`, split human-circle background restore into two blits and skipped the glucose text band (`y=220..242`)
  - preserves one-write-on-value-change behavior for `mg/dL` without center blanking side effects
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Recalibrated dosing so `ML/H` tracks motor `RPM` and `mA` behavior while preserving insulin pump math:
  - `RATE` now derived from instantaneous motor RPM (`ml/h = rpm * 0.002`), so idle motor shows `RATE:0.00 ML/H`
  - `mA` remains proportional to RPM via existing mapping, so dose/rpm/current now move together
  - basal target remains in `U/h` with `0.025 U/h` increments and uses U100 conversion (`100 U/mL`) for target volume pacing
  - pulse interval is now computed from delivered pulse volume and target `U/h`, so long-term reservoir depletion remains aligned with basal dosing profile
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Added center-segment digital tach arc in `DrawHumanOrientationPointer()`:
  - 270-degree bargraph circle with bottom 90 degrees open
  - centered on the ball-circle center, radius set to 80% of ball-circle radius (matching requested 80% diameter scaling intent)
  - zone colors by sweep order: first ~120° green, next ~90° yellow, final ~60° red
  - active bar count driven by current motor RPM (`gUiRpmTenths`)
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Updated center RPM tach arc geometry in `DrawHumanOrientationPointer()`:
  - vertically flipped arc orientation (open section moved opposite side)
  - doubled bar thickness (radial span and line thickness increased 2x)
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Refined center tach arc appearance:
  - increased arc diameter by 10% over prior setting (radius factor `0.80 -> 0.88` of ball-circle radius)
  - sharpened bars by reducing line thickness (`4 -> 3`) and tightening radial span (`-10 -> -8`)
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Increased center tach arc diameter by an additional 10% (radius factor `0.88 -> 0.97` of ball-circle radius).
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Reworked displayed error/reason/status coding to activity staging derived from motion/environment sensors:
  - activity model now fuses accelerometer dynamics, gyro magnitude, and barometric pressure-rate trend
  - stage bands: `REST`, `LIGHT`, `MODERATE`, `ACTIVE`, `HEAVY`
  - reason/detail text rewritten to activity codes (`ACT-L0..ACT-L4`) plus movement/vertical trend context
  - terminal status/system rows now report activity state and activity code instead of prior alert-reason strings
- Change: Circular 270-degree center bargraph now represents activity intensity (0-100%) instead of motor RPM while keeping requested color zones and geometry.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS (after one compile-fix iteration)
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Added barometric pressure to the right-hand scope graph overlay:
  - plotted `gTraceBaro` as an additional line in `TRACE_BARO_COLOR`
  - added `BP` in the scope legend row
- Change: Fixed blue orientation-ball trail artifact at the bottom of the center circle:
  - full center-circle background region is now restored each frame before ball redraw
  - glucose `mg/dL` text is redrawn each frame so the full restore does not blank it
- Change: Flash recorder barometric logging/playback path verified:
  - `ExtFlashRecorder_AppendSampleEx(... baro_dhpa ...)` and playback restore path were already wired and retained
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Implemented automatic transport-mode distinction to separate human effort from vehicle motion:
  - added auto classifier outputs: `FOOT`, `SKATE`, `SCOOT`, `BIKE`, `CAR`, `AIR`
  - classifier uses fused accel dynamics, gyro magnitude, and barometric pressure-rate trend
  - added transport confidence output (`gTransportConfidencePct`)
- Change: Human activity scoring is now transport-aware:
  - vehicle-like modes (`CAR`, `AIR`) downscale effort contribution to avoid vibration-driven false high activity
  - active personal mobility modes (`BIKE`, `SCOOT`, `SKATE`) apply lighter downscaling to preserve real rider effort
- Change: Terminal now shows auto transport context and confidence inline with activity (`TRN ... ACT ...`).
- Operation mode:
  - fully automatic by default; no user setting required for this behavior.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Fixed activity arc baseline so resting state maps to early green region instead of yellow.
  - corrected activity accel feature to primarily use accel-magnitude deviation from `1g` (rest baseline) rather than raw gravity-contaminated magnitude
  - added guard for linear-accel streams that still include gravity
  - tightened rest clamp (`low accel + low gyro + low baro trend`) to suppress false motion
  - adjusted transport gating so very low-motion rest no longer auto-classifies as `CAR`
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Added demo insulin recommendation controller and wired it into runtime dosing behavior.
  - recommendation uses fused inputs: transport-aware activity stage, glucose value, glucose trend (`dBG`), and insulin-on-board (`IOB`) with time decay
  - recommendation is quantized to 0.025 U/h increments and smoothed before being applied to pulse scheduling
  - terminal now shows recommendation telemetry when help popup is closed: `DOS`, `IOB`, and `dBG`
- Change: Updated on-screen `?` help popup content (both pages) to document the new transport/activity and dose recommendation system behavior.
- Change: Rewrote `README.md` with detailed project documentation:
  - safety note, system architecture, runtime semantics, transport/activity model, dose recommendation model, record/replay details, controls, and build/flash instructions
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Dated project documentation files and established current release as active restore baseline.
  - added `Last updated: 2026-02-23` to core docs and README
  - updated `STATUS.md` with explicit restore markers
  - set restore-point identifiers in project state:
    - `GOLDEN-2026-02-23`
    - `FAILSAFE-2026-02-23`
- Result: ok

## Update 2026-02-23
- Change: Flashed current medical demo firmware image to FRDM-MCXN947.
- Verification:
  - `./tools/flash_frdmmcxn947.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Shifted all settings row labels left by 3 character widths for improved separation from row buttons.
  - updated `DrawSettingsPopup()` label anchor (`label_col_right`) from `172` to `154`
  - this applies uniformly to all settings labels while leaving row option content unchanged
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - build: PASS
  - flash: PASS (`MCXN947:FRDM-MCXN947`, probe `#1` `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Fixed AI settings row label placement/format so the left-side row label is explicitly `AI:` before the `MCU` and `NPU` buttons.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Synchronized all project docs to current medical-demo baseline.
  - updated `README.md` and `STATUS.md`
  - updated `docs/START_HERE.md`, `docs/OPS_RUNBOOK.md`, `docs/HARDWARE_SETUP.md`, and `docs/TODO.md`
  - aligned docs with settings UI wording `AI: MCU/NPU`
- Result: ok

## Update 2026-02-23
- Change: Flashed current medical demo firmware image to FRDM-MCXN947.
- Verification:
  - `./tools/flash_frdmmcxn947.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Replaced AI mode wording from ON/OFF to MCU/NPU across the runtime UI and settings popup.
  - top mode pill now shows `AI MCU` (left selection) or `AI NPU` (right selection)
  - settings popup AI buttons now read `AI: MCU` on the left and `AI: NPU` on the right
- Change: Updated selection event log output in touch handler:
  - left selection prints `AI_SET,MCU`
  - right selection prints `AI_SET,NPU`
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer, probe `#1`)
- Result: ok

## Update 2026-02-23
- Change: Adjusted AI settings row format to match other settings style.
  - kept row label as `AI`
  - changed option button text to `MCU` (left) and `NPU` (right)
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
- Result: ok

## Update 2026-02-23
- Change: Flashed current medical demo firmware image to FRDM-MCXN947.
- Verification:
  - `./tools/flash_frdmmcxn947.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Restored runtime target after wrong-project flash by rebuilding/flashing the medical demo.
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (probe `#1`, target `MCXN947:FRDM-MCXN947`)
- Result: ok

## Update 2026-02-23
- Change: Removed legacy package-demo naming from medical project code/build paths to prevent project confusion.
  - renamed runtime source file to `src/edgeai_medical_device_demo.c`
  - renamed MCUX overlay app path to `demo_apps/edgeai_medical_device_demo`
  - updated build/install scripts and environment variable names to medical-demo identifiers
  - updated generated model name defaults from package naming to medical naming
- Verification:
  - `EDGEAI_WEST_BUILD_ARGS='-p always' ./tools/build_frdmmcxn947.sh debug` PASS
  - output: `mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin`
  - `./tools/flash_frdmmcxn947.sh` PASS (probe `#1`, target `MCXN947:FRDM-MCXN947`)
- Result: ok

## Update 2026-02-23
- Change: Added CGM algorithm review document to medical demo docs.
  - new file: `docs/CGM_DERMAL_ALGORITHM_REVIEW.md`
  - content covers dermal CGM preprocessing, filtering, calibration/compensation, lag handling, SQI/fault detection, prediction/alerts, and validation metrics
- Result: ok

## Update 2026-02-23
- Change: Restored board runtime to medical demo after accidental package-demo flash.
- Verification:
  - `EDGEAI_WEST_BUILD_ARGS='-p always' ./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (probe `#1`, target `MCXN947:FRDM-MCXN947`)
- Result: ok

## Update 2026-02-23
- Change: Added explicit demo-CGM simulation wording in help popup.
  - updated page-1 help text in `src/gauge_render.c` to state CGM data and dosing response are simulated
- Change: Added flash fail-fast guard and safe wrapper.
  - `tools/flash_frdmmcxn947.sh` now blocks flash if expected medical artifact is missing or build dir app path does not match project
  - new wrapper: `scripts/flash_safe.sh`
  - `scripts/flash.sh` now delegates to `scripts/flash_safe.sh`
- Verification:
  - `EDGEAI_WEST_BUILD_ARGS='-p always' ./tools/build_frdmmcxn947.sh debug` PASS
  - `./scripts/flash_safe.sh` PASS (probe `#1`, target `MCXN947:FRDM-MCXN947`)
- Result: ok

## Update 2026-02-23
- Change: Tuned activity stage entry so `HUMAN REST` spans first ~5 bargraph ticks.
  - `src/gauge_render.c`: `ActivityStageFromPct()` LIGHT threshold set to `pct >= 10` (REST below 10)
- Verification:
  - `./scripts/build_and_flash.sh` PASS (probe `#1`, target `MCXN947:FRDM-MCXN947`)
- Result: ok

## Update 2026-02-23
- Change: Unified alert headline rendering style for warning/fault states (including `HIGH ACTIVITY`) with normal alerts.
  - `src/gauge_render.c` in `DrawAiAlertOverlay()` now renders warning/fault headline at the same Y offset/scale path as normal alerts.
  - removed secondary detail line from warning/fault alert box to keep single-line headline presentation.
- Verification:
  - `./scripts/build_and_flash.sh` PASS (probe `#1`, target `MCXN947:FRDM-MCXN947`)
- Result: ok

## Update 2026-02-23
- Change: Committed and published R3 restore baseline.
  - commit: `067e438` on `main`
  - pushed tags:
    - `GOLDEN-2026-02-23-R3`
    - `FAILSAFE-2026-02-23-R3`
- Result: ok

## Update 2026-02-23
- Change: Verification test run requested after step-5 preprocessing integration.
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 6 by implementing a dermal-tuned low-lag filtering/trend path with adaptive SQI gating.
  - `src/cgm_preprocess.c`:
    - added SQI estimation from preprocessing residual-noise EMA
    - added SQI-adaptive glucose smoothing alpha (`filter_alpha_min..max`)
    - added explicit trend derivative output (`mg/dL/min`) with adaptive trend smoothing
  - `src/gauge_render.c`:
    - switched runtime trend consumption to preprocessor trend output
    - removed legacy trend-decay recompute path in dose loop
    - exposed `SQI` in terminal status line with `DOS/IOB/dBG`
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Promoted current step-6 firmware/docs state as active golden restore baseline `R4` only.
  - staged artifact:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R4.bin`
  - failsafe baseline intentionally remains:
    - `FAILSAFE-2026-02-23-R3`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-23-R3.bin`
  - updated active restore references in:
    - `README.md`, `STATUS.md`
    - `docs/START_HERE.md`, `docs/OPS_RUNBOOK.md`, `docs/HARDWARE_SETUP.md`, `docs/TODO.md`
- Verification:
  - `./scripts/build_and_flash.sh` PASS
- Result: ok

## Update 2026-02-23
- Change: Published step-6 implementation and golden-only restore promotion.
  - commit: `d7e2deb` on `main`
  - pushed tag: `GOLDEN-2026-02-23-R4`
  - failsafe tag intentionally unchanged: `FAILSAFE-2026-02-23-R3`
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 7 by implementing calibration and compensation path in preprocessing.
  - `src/cgm_preprocess.h/.c` updates:
    - runtime factory-calibration hooks: `CgmPreprocess_SetCalibration(...)`, `CgmPreprocess_ResetCalibrationAge(...)`
    - temperature compensation retained in calibrated glucose conversion path
    - aging/drift compensation state added (`drift_state_mgdl`) with bounded adaptive correction
    - sensitivity-change detection added using short/long EMA ratio with hold counter
    - output telemetry fields added: calibration age, drift compensation, calibration-stale/drift-warn/sensitivity-change flags
  - `src/gauge_render.c` integration:
    - consumes updated preprocessing outputs during glucose/trend path
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 8 with conservative lag/kinetics handling.
  - `src/cgm_preprocess.h/.c` updates:
    - added optional lag/kinetics configuration and state (`lag_enable`, `lag_tau_s`, `lag_gain_min/max`, bounded lag compensation)
    - implemented low-gain lag correction with SQI-adaptive gain and compensation clamp
    - trend derivative now computed from kinetics-corrected glucose signal
    - exposed lag diagnostics in preprocessing output (`lag_comp_mgdl`, `lag_gain_applied`)
  - behavior remains conservative by default (no aggressive look-forward extrapolation)
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 9 by adding SQI/fault gating as a runtime control path.
  - `src/cgm_preprocess.h/.c` updates:
    - added runtime `sensor_flags` output and bit taxonomy constants
    - added flag derivation for saturation, dropout, implausible ROC, temp out-of-range, calibration stale, and drift warning
    - added `prediction_blocked` and `hold_last` outputs to gate downstream logic when SQI/fault state is poor
  - `src/gauge_render.c` integration:
    - consumes preprocessing `sensor_flags`, `prediction_blocked`, and `hold_last`
    - applies dropout hold-last guard for glucose/trend presentation path
    - blocks/de-rates dose recommendation updates when prediction path is gated
    - exposes flags in terminal line (`Fxx`) with SQI for runtime visibility
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Ran additional runtime verification cycle on current CGM step-9 firmware.
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Promoted current firmware/docs runtime to golden restore baseline `R5` (failsafe remains `R3`).
  - staged artifact:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R5.bin`
  - active restore points:
    - `GOLDEN-2026-02-23-R5`
    - `FAILSAFE-2026-02-23-R3`
  - synchronized baseline references in:
    - `README.md`, `STATUS.md`
    - `docs/START_HERE.md`, `docs/OPS_RUNBOOK.md`, `docs/TODO.md`
- Verification:
  - source binary copied from latest successful build:
    - `mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin`
- Result: ok

## Update 2026-02-23
- Change: Completed CGM alignment step 10 with prediction and alert runtime behavior.
  - `src/gauge_render.c` updates:
    - added short-horizon prediction outputs (`P15`, `P30`) from current glucose and trend slope
    - added SQI/fault-gated predictive hypo/hyper checks (warn/fault bands)
    - implemented debounce and hysteresis for both hypo and hyper paths to reduce alert chatter
    - integrated predictive alert state into overlay/terminal AI status selection
    - integrated predictive alert direction/severity into dose recommendation scaling
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-23
- Change: Added detailed CGM AI explainer documentation for runtime behavior and industry-standard methods.
  - new doc: `docs/CGM_AI_ALGORITHM_EXPLAINER.md`
  - includes:
    - end-to-end runtime pipeline explanation from preprocessing to alerting
    - exact current prediction equations/thresholds/debounce/hysteresis from firmware
    - UI/alert semantics and dose interaction behavior
    - common CGM-market medical concepts and software/math patterns
    - clear separation between demo-specific behavior and production-grade expectations
- Result: ok

## Update 2026-02-24
- Change: Built/flashed current firmware and promoted both golden and failsafe restore baselines to `R1` for 2026-02-24.
  - built and flashed via `./scripts/build_and_flash.sh`
  - staged restore artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R1.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R1.bin`
  - active restore points:
    - `GOLDEN-2026-02-24-R1`
    - `FAILSAFE-2026-02-24-R1`
  - synchronized active baseline references in:
    - `README.md`, `STATUS.md`
    - `docs/START_HERE.md`, `docs/OPS_RUNBOOK.md`, `docs/HARDWARE_SETUP.md`, `docs/TODO.md`
  - included CGM documentation update:
    - `docs/CGM_AI_ALGORITHM_EXPLAINER.md`
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Completed CGM alignment step 11 by aligning LCD/terminal semantics to the runtime CGM contract.
  - `src/gauge_render.c` updates:
    - added explicit simulation labeling in CGM UI paths (`SIM CGM`)
    - added on-screen prediction visibility (`P15`/`P30`) under glucose display
    - added terminal SQI confidence coding (`HI`/`MED`/`LOW`/`BAD`) and active sensor flag display (`Fxx`)
    - aligned terminal summary lines to contract fields (predictions + trend with simulation marker)
  - compile hygiene:
    - marked now-unused `FormatDewAltCompact()` helper with `__attribute__((unused))` to satisfy `-Werror`
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Increased on-screen simulated CGM summary text size in glucose panel.
  - `src/gauge_render.c`:
    - changed glucose-panel simulated summary text from scale `1` to scale `2`
    - updated label string from `SIM CGM ...` to `SIM ...` to preserve fit at larger size
    - build fix: marked `FormatDewAltCompact()` as `__attribute__((unused))` after prior line replacement to satisfy `-Werror`
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Adjusted simulated CGM summary text to fit within middle LCD segment.
  - `src/gauge_render.c`:
    - set center-panel `SIM P15/P30` summary render scale from `2` back to `1` to prevent overflow in middle segment
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Increased simulated CGM summary text slightly while preserving middle-segment fit.
  - `src/gauge_render.c`:
    - center `SIM P15/P30` line now uses scale-1 pseudo-1.25x render (double-draw with +1px offset)
    - keeps horizontal fit in the middle segment while improving readability
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Increased center simulated CGM summary text a little more while preserving middle-segment fit.
  - `src/gauge_render.c`:
    - `SIM P15/P30` line now uses 3-pass pseudo-scale render (base + x+1 + y+1 at scale-1)
    - improves readability relative to single-pass scale-1 without full scale-2 overflow
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Improved center simulated CGM text appearance with cleaner font rendering.
  - `src/gauge_render.c`:
    - switched `SIM P15/P30` line from pseudo-thick multi-pass draw to `DrawTextUiCrisp(...)`
    - keeps same size/fit but improves legibility and visual cleanliness
- Verification:
  - `./scripts/build_and_flash.sh` PASS
  - target: `MCXN947:FRDM-MCXN947`
  - probe: `#1` (`UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Reduced center mg/dL + SIM flicker by throttling redraw to 5-second cadence with cache invalidation on static/dashboard refresh paths.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Fixed center-text blanking: mg/dL and SIM lines now stay visible continuously while displayed values refresh every 5 seconds.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Fixed center mg/dL/SIM overdraw artifacts by restoring the center text strip every frame before drawing the two lines; retained 5-second value refresh cadence.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Moved center mg/dL + SIM lines upward to keep them fully outside the pump/elapsed clear bands; this isolates center text from y=240 region wipes.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Enabled deterministic full-frame redraw compositing each refresh to eliminate section overdraw/dirty-region flicker; center CGM text remains final overlay.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Reverted full-frame redraw mode due to whole-screen flashing and missing fields; restored incremental rendering while keeping center CGM text protections.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Adjusted center CGM text rendering to remove black bars/boxes: switched strip clear to background blit and mg/dL text to crisp draw (no shadow).
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Refined center CGM redraw to professional minimal dirty-rect behavior: only clears a few pixels around old/new text bounds before redraw; removed wide strip clearing.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Isolated center mg/dL/SIM region from activity/ball renderer by adding a protected guard rectangle in orientation ring background restore and segment draw paths.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Cleared residual ball/activity artifacts in center text zone by forcing per-frame background restore of the protected guard rectangle before overlay text redraw.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Updated rendering strategy per request: ball/ring redraws normally, and center CGM text is re-drawn as final persistent overlay each frame with minimal dirty-clear only when text changes.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Adopted permanent center-text overlay strategy: render ball/ring normally, then every frame restore a tight text-width background box and redraw mg/dL+SIM immediately (no broad clears, no guard carveouts).
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Replaced center text clear+draw flow with masked opaque glyph redraw (fg+bg per character cell) to avoid broad clears and reduce flicker/tearing.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Implemented true masked center text redraw using pump-background-per-glyph cells (no black fill box) and fixed declaration-order compile issue.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Removed center-text background-cell rewrite path; mg/dL and SIM now render as transparent final overlay only to avoid black box and bargraph masking.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Test mode: removed all center-text background restoration/masking; mg/dL and SIM are now pure transparent final overlays to isolate remaining 1 Hz flicker source.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Removed activity bargraph/orientation ring draw from the runtime frame path for test isolation.
  - disabled activity renderer invocation in `GaugeRender_DrawFrame()`
  - retained renderer function source but marked `DrawHumanOrientationPointer()` as intentionally unused for clean `-Werror` builds
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Restored activity ball/orientation ring rendering in runtime frame path.
  - re-enabled `DrawHumanOrientationPointer(style)` in `GaugeRender_DrawFrame()`
  - removed temporary `__attribute__((unused))` from `DrawHumanOrientationPointer()`
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Restored orientation ball marker rendering inside `DrawHumanOrientationPointer()`.
  - removed temporary test-disable block that suppressed `ball_x/ball_y/ball_color`
  - ball now draws as a filled marker with outline + highlight on top of the activity arc
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Stabilized MG/DL + SIM rendering with activity ball/bargraph active.
  - `DrawGlucoseIndicator()` now restores only a tight background band behind center text before redraw (prevents text smearing)
  - `DrawHumanOrientationPointer()` now skips arc segments and ball draw that intersect the center text guard zone (prevents overdraw/flicker in text rows)
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Adjusted center-text/ball interaction to address disappearing ball and persistent flashing.
  - removed orientation-layer center guard clipping so ball never disappears when crossing text region
  - changed `DrawGlucoseIndicator()` band clear policy to clear only when displayed values change (still redraws text each frame)
  - outcome goal: no text smear on value updates and reduced frame-to-frame flash in center text rows
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Switched elapsed runtime clock source to MCU hardware RTC (IRTC).
  - added `fsl_irtc` driver integration to project build
  - initialized IRTC at boot and captured RTC epoch on each elapsed-clock reset event
  - runtime elapsed display now computes `elapsed_sec` from RTC wall-time delta; timebase path remains fallback if RTC read fails
  - retained existing UI reset semantics for playback/record transitions
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Rolled back the recent MCU IRTC integration due to boot freeze and restored prior runtime/elapsed clock implementation.
  - restored `src/edgeai_medical_device_demo.c` to HEAD baseline (pre-IRTC integration)
  - restored `sdk_example/mcuxsdk_examples_overlay/demo_apps/edgeai_medical_device_demo/CMakeLists.txt` to HEAD baseline (removed explicit IRTC driver add)
  - this returns elapsed/logging flow to the previous known-good logic path
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Restored the previously working counter-read elapsed-time path (for runtime clock + logging cohesion).
  - reintroduced OSTIMER source calibration against delay window for both raw and decoded counters
  - runtime now selects the closer source (`OSTIMER_GetCurrentTimerRawValue` vs `OSTIMER_GetCurrentTimerValue`) and uses matched `s_timebase_hz`
  - no MCU IRTC integration in this change; existing runtime/logging architecture preserved
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Prevented elapsed clock display from counting up/down due small timing jitter.
  - added bounded anti-backstep guard (<=3 s) in normal, record, and playback display update paths
  - keeps existing mode-reset behavior intact (`runtime_displayed_sec = UINT32_MAX` still allows intentional resets)
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Restored device firmware to active Golden restore point.
  - flashed artifact: `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R1.bin`
  - command: `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R1.bin`
- Result: ok

## Update 2026-02-24
- Change: Restored one step back to previous Golden firmware image.
  - flashed artifact: `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R5.bin`
  - command: `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R5.bin`
- Result: ok

## Update 2026-02-24
- Change: Restored one more step back to earlier Golden firmware image.
  - flashed artifact: `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R3.bin`
  - command: `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R3.bin`
- Result: ok

## Update 2026-02-24
- Change: Restored one more step back to failsafe firmware baseline.
  - flashed artifact: `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-23-R3.bin`
  - command: `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-23-R3.bin`
- Result: ok

## Update 2026-02-24
- Change: Returned from failsafe baseline back to Golden restore track (latest Golden).
  - flashed artifact: `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R1.bin`
  - command: `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R1.bin`
- Result: ok

## Update 2026-02-24
- Change: Rolled back two more Golden restore points.
  - step 1 flashed: `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R5.bin`
  - step 2 flashed: `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R4.bin`
  - commands:
    - `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R5.bin`
    - `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R4.bin`
- Result: ok

## Update 2026-02-24
- Change: Rolled back three more restore points.
  - step 1 flashed: `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R3.bin`
  - step 2 flashed: `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-23-R4.bin`
  - step 3 flashed: `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-23-R3.bin`
  - commands:
    - `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R3.bin`
    - `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-23-R4.bin`
    - `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-23-R3.bin`
- Result: ok

## Update 2026-02-24
- Change: Moved forward to most recent Golden restore point.
  - flashed artifact: `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R1.bin`
  - command: `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R1.bin`
- Result: ok

## Update 2026-02-24
- Change: Restored firmware to Golden point `R5` (pre-rollback stable target).
  - flashed artifact: `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R5.bin`
  - command: `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-23-R5.bin`
- Result: ok

## Update 2026-02-24
- Change: Flashed most recent failsafe restore image for validation.
  - flashed artifact: `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R1.bin`
  - command: `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R1.bin`
- Result: ok

## Update 2026-02-24
- Change: Promoted current source-built runtime as new restore baseline `R2` and flashed active Golden `R2`.
  - built+flashed current source: `./scripts/build_and_flash.sh`
  - staged artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R2.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R2.bin`
  - activated on hardware:
    - `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R2.bin`
- Result: ok

## Update 2026-02-24
- Change: Restored runtime behavior path where center `mg/dL` + `SIM` lines are present while activity ball/bargraph are active by rebuilding/flashing from current source (not a saved restore artifact).
  - note: the exact historical point before ball-removal tests was a runtime iteration and was not captured as a standalone failsafe/golden `.bin`.
  - command: `./scripts/build_and_flash.sh`
- Result: ok

## Update 2026-02-24
- Change: Fixed elapsed-time counter stability in runtime, record, and playback clock paths.
  - runtime path now computes deciseconds directly from OSTIMER ticks:
    - `runtime_elapsed_ds = (dt_ticks * 10) / s_timebase_hz`
  - removed partial backstep threshold logic and now enforce strict monotonic display clocks unless explicitly reset by mode transitions.
  - applied monotonic clamp consistently in:
    - normal runtime clock update
    - record elapsed clock update
    - playback timestamp display update
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Completed/normalized Step-11 CGM LCD semantics and corrected Step-2 TODO contract naming.
  - `docs/TODO.md` step 2 corrected to `trend_mgdl_min_x100` to match `docs/CGM_RUNTIME_CONTRACT.md`.
  - `src/gauge_render.c` `DrawGlucoseIndicator()` now renders on-screen quality line:
    - `SQI <pct> <confidence> F<flags>`
    - includes confidence code via `CgmConfidenceCode(...)` and full sensor flags (`F%04X`)
  - center text redraw cache/clear conditions now include SQI and sensor flags updates.
- Command: ./scripts/build_and_flash.sh
- Result: ok

## Update 2026-02-24
- Change: Fixed elapsed-time refresh cadence and random freeze behavior in runtime clock handling.
  - `src/edgeai_medical_device_demo.c`
    - switched runtime timebase selection to decoded OSTIMER path (`s_timebase_use_raw = false`) and preferred configured 32.768 kHz clock for stable scaling
    - changed runtime display tracking from whole seconds to deciseconds (`runtime_displayed_ds`) in normal, record, and playback paths
    - `GaugeRender_SetRuntimeClock(...)` now receives computed deciseconds instead of fixed `0` tenths
  - `src/gauge_render.c`
    - updated on-screen runtime format from `HHHH:MM:SS` to `HHHH:MM:SS.d`
    - updated static placeholder to `--:--:--.-`
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS (LinkServer probe `#1`, `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Reverted runtime clock display to second-only format and corrected timebase source selection.
  - `src/gauge_render.c`
    - runtime clock format restored to `HHHH:MM:SS`
    - removed tenths placeholder from static/dynamic clock draw strings
  - `src/edgeai_medical_device_demo.c`
    - timebase source selection now prefers plausible calibrated 32.768 kHz OSTIMER values (`dec_cal` then `raw_cal` then plausible `cfg`), otherwise falls back to nominal crystal rate
    - keeps runtime monotonic decisecond tracking internally but avoids unstable frequency selection that can skew elapsed time
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Corrected elapsed-time rate by removing delay-based calibration from runtime time conversion.
  - `src/edgeai_medical_device_demo.c`
    - runtime `s_timebase_hz` now uses nominal 32.768 kHz unless `CLOCK_GetOstimerClkFreq()` is tightly within expected range (30.72k..34.816k)
    - retained `raw_hz`/`dec_hz` measurements for diagnostics only; no longer used for runtime scaling
    - prevents ~25-33% slow runtime caused by miscalibrated delay-window estimates
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Applied explicit 1:4 elapsed-rate correction by switching runtime elapsed ticks to raw OSTIMER counter mode.
  - `src/edgeai_medical_device_demo.c`
    - `s_timebase_use_raw` set to `true` in `TimebaseInit()`
    - runtime scale remains nominal/bounded 32.768 kHz (not delay-window calibrated)
    - UART `TIMEBASE` print now includes `mode=raw|dec` for immediate verification
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Removed OSTIMER elapsed-time guesswork by aligning runtime time conversion with SDK driver semantics.
  - Confirmed from `mcuxsdk_ws/mcuxsdk/drivers/ostimer/fsl_ostimer.c` that `OSTIMER_GetCurrentTimerValue()` is the valid decimal counter API (raw may be Gray-encoded)
  - `src/edgeai_medical_device_demo.c`:
    - set `s_timebase_use_raw = false`
    - runtime `s_timebase_hz` now prefers measured decimal counter rate (`dec_meas`) within `[4096..65536]`, else bounded config/nominal fallback
- Verification:
  - `./tools/build_frdmmcxn947.sh debug` PASS
  - `./tools/flash_frdmmcxn947.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Added local dataset artifact for CGM model prototyping.
  - downloaded `data/data_cgm.csv` from Stanford CGMDB host (`web.stanford.edu/group/genetics/cgmdb/data/`)
  - file shape: 7 columns (`glucose, subject, foods, mitigator, food, rep, mins_since_start`), 23521 rows
  - note: dataset does not contain insulin dosing fields
- Result: ok

## Update 2026-02-24
- Change: Downloaded an openly accessible diabetes dataset artifact from an Awesome-CGM linked source for CGM+dosing workflow development.
  - source DOI: `https://doi.org/10.5281/zenodo.1421615` (Zenodo record `5651217`, D1NAMO)
  - downloaded file: `data/d1namo_diabetes_pictures_glucose_food_insulin.zip` (~241 MB)
  - contains per-subject `glucose.csv`, `insulin.csv`, and `food.csv` (plus meal photos)
- Result: ok

## Update 2026-02-24
- Change: Added D1NAMO replay conversion pipeline and generated subject-001 replay artifacts.
  - new converter: `tools/d1namo_extract_replay.py`
  - generated normalized CGM+insulin replay: `data/d1namo_subject001_cgm_insulin_replay.csv` (1438 rows)
    - columns: `ts_iso, epoch_s, glucose_mgdl, glucose_mmol_l, glucose_type, insulin_fast_u, insulin_slow_u, insulin_total_u`
  - generated firmware replay-trace CSV: `data/replay_trace_d1namo_subject001.csv` (1438 rows)
    - columns: `current_mA, power_mW, voltage_mV, soc_pct, temp_c`
    - note: this trace is a deterministic compatibility mapping from CGM rows for replay-path testing only.
  - regenerated `src/replay_trace_generated.h` from `data/replay_trace_d1namo_subject001.csv`
- Result: ok

## Update 2026-02-24
- Change: Flashed latest debug build to FRDM-MCXN947.
  - command: `./tools/flash_frdmmcxn947.sh`
  - runner: `linkserver`
  - target detected: `MCXN947:FRDM-MCXN947`
- Result: ok

## Update 2026-02-24
- Change: Created train/test split with subject `001` held out for long demo/test playback.
  - train split: `data/d1namo_train_excl001.csv` (`6783` rows, subjects `002..009`)
  - test split: `data/d1namo_test_subject001.csv` (`1438` rows)
  - demo alias: `data/d1namo_demo_subject001.csv` (`1438` rows)
- Notes:
  - split is subject-aware and time-series safe (no random row shuffling)
  - held-out subject `001` remains the long replay candidate for demos
- Result: ok

## Update 2026-02-24
- Change: Imported best C++-exportable CGM model artifacts into project-local `model/` folder from extension compare run.
  - source compare run: `projects/microsoft/visual-studio/embedded-intelligence-layer/training_output/model_compare_smoke_20260224T045444Z`
  - selected model: `ridge` (best deployable among export-supported models by holdout MAE)
  - files added:
    - `model/cgm_best_model.hpp`
    - `model/cgm_best_model.cpp`
    - `model/cgm_best_model_metrics.json`
    - `model/cgm_best_model_training_report.md`
    - `model/README.md`
- Result: ok

## Update 2026-02-24
- Change: Updated run/playback behavior so `LIVE` mode loops test playback data from ext flash instead of disabling playback.
  - `src/edgeai_medical_device_demo.c`
    - selecting `LIVE` or `TRAIN` in settings now attempts `ExtFlashRecorder_StartPlayback()` immediately
    - removed live-banner gating that previously stopped playback while in `LIVE`
    - playback end-of-data now restarts playback (`EXT_FLASH_PLAY: loop_restart`) for continuous looping
    - startup and post-record transitions now initialize playback without requiring non-live banner state
    - when on-board training completes and app promotes to `LIVE`, playback is started instead of being forced off
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed latest debug build after LIVE-mode test-data loop update.
  - command: `./scripts/flash.sh`
  - runner: `linkserver`
  - target detected: `MCXN947:FRDM-MCXN947`
  - probe: `#1 UYLKOJI11H2B3`
- Result: ok

## Update 2026-02-24
- Change: Updated Settings so prior `MODE` row no longer shows `ADAPT/TRAINED`; it now shows `AI OFF/ON`.
  - `src/gauge_render.c`
    - row label changed from `MODE` to `AI`
    - mode-row option text changed from `ADAPT`/`TRAINED` to `OFF`/`ON`
    - selection state bound to `ai_enabled` state (`gPrevAiEnabled`)
  - `src/edgeai_medical_device_demo.c`
    - mode-row touch handler now toggles `ai_enabled` OFF/ON and calls `PowerData_SetAiAssistEnabled(...)`
    - UART log updated for this row to `AI_ENABLE,OFF|ON`
- Note: Existing `MCU/NPU` settings row was intentionally kept as requested.
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed latest debug build after Settings update (`MODE` row -> `AI OFF/ON`, `MCU/NPU` retained).
  - command: `./scripts/flash.sh`
  - runner: `linkserver`
  - target detected: `MCXN947:FRDM-MCXN947`
  - probe: `#1 UYLKOJI11H2B3`
- Result: ok

## Update 2026-02-24
- Change: Fixed AI toggle behavior and alert-panel UX issues.
  - `src/gauge_render.c`
    - added runtime AI enable gate (`gUiAiEnabled`) so prediction alert logic is disabled when AI is OFF
    - `DrawAiAlertOverlay(...)` now shows `AI OFF` state when disabled instead of continuing alert severity flow
    - added prediction accuracy scoreboard line below activity/warning box: `PRED SCORE xx%`
      - score is computed from delayed 15m/30m prediction error tracking using ring-buffered due-evaluation
    - updated AI pill styling so both `AI MCU` and `AI NPU` render as green banners
  - retained settings behavior from prior update:
    - mode-row (`AI OFF/ON`) toggles AI enable state
    - existing `MCU/NPU` row remains present
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed AI control semantics and banner coloring to match runtime intent.
  - `src/edgeai_medical_device_demo.c`
    - `AI OFF/ON` row remains the sole AI enable switch (`ai_enabled` + `PowerData_SetAiAssistEnabled`)
    - `MCU/NPU` row no longer toggles AI enable; it now selects backend label only
  - `src/gauge_render.h`
    - added `GaugeRender_SetAiBackendNpu(bool use_npu)`
  - `src/gauge_render.c`
    - added independent backend state tracking for `MCU/NPU` selection (`gUiAiBackendNpu`)
    - top AI pill label now follows backend selection (`AI MCU` / `AI NPU`)
    - top AI pill color now follows enable state:
      - AI ON -> green
      - AI OFF -> dark background
    - settings `MCU/NPU` selection highlight now follows backend selection (independent of enable)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Added boot/warmup `THINKING` status in the warning/activity box.
  - `src/gauge_render.c`
    - `DrawAiAlertOverlay(...)` now renders `THINKING` (yellow) while prediction score is not yet primed (`!gUiPredMaePrimed`), provided AI is enabled and not in record/training overlays
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Corrected prediction-score priming so startup no longer reports synthetic baseline (~67%) as a real accuracy value.
  - `src/gauge_render.c`
    - added `gUiPredEvalCount` and increment on each consumed due-time prediction evaluation
    - score priming now requires at least 6 consumed evaluations (`gUiPredEvalCount >= 6`)
    - reset prediction-eval/priming/score state at CGM preprocess initialization
- Effect:
  - warning box stays `THINKING` until real 15m/30m evaluations have actually completed
  - score transitions from thinking state only after enough real evidence exists
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed playback runtime clock freeze at replay-loop boundary.
  - Root cause: playback timestamp monotonic clamp prevented `ts_ds` from decreasing when replay restarted, so display clock stuck at last sample time (e.g., `07:47`).
  - `src/edgeai_medical_device_demo.c`
    - on successful `ExtFlashRecorder_StartPlayback()` in loop-restart path, reset clock state:
      - `runtime_displayed_ds = UINT32_MAX`
      - `GaugeRender_SetRuntimeClock(0u, 0u, 0u, 0u, true)`
- Effect:
  - playback/live-loop clock now resets and advances again each replay cycle instead of freezing at end-of-trace.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Reset `docs/TODO.md` to a new roadmap and cleared prior completed checklist from active TODO view.
  - new TODO now focuses on next-phase realism/validation items:
    - true timestamp-driven live replay
    - startup warm-up/preseed and readiness UX
    - pump/motor realism and safety interlocks
    - outcome metrics and release/restore steps
- Result: ok

## Update 2026-02-24
- Change: Fixed warmup score timeline: prediction accuracy now advances on per-sample decisecond timeline during catch-up to prevent stuck 0% after primer.
- Binary: mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin
- Command: ./scripts/build.sh
- Result: ok

## Update 2026-02-24
- Change: Prediction score now uses per-prediction evaluation with ±1% tolerance hit tracking plus MAE blend; score priming starts after first matured prediction (no 6-sample gate).
- Binary: mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin
- Command: ./scripts/build.sh
- Result: ok

## Update 2026-02-24
- Change: Score strip now shows evaluation count (E#) and no longer hides score behind primed gate after evaluations start; aids runtime diagnosis of 0% issues.
- Binary: mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin
- Command: ./scripts/build.sh
- Result: ok

## Update 2026-02-24
- Change: Adjusted prediction scoring tolerance from ±1% to ±10% per user request; rebuilt and flashed.
- Binary: mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin
- Command: ./scripts/build.sh && ./scripts/flash.sh
- Result: ok

## Update 2026-02-24
- Change: Diagnostic scoring test: prediction tolerance temporarily set to ±100% and flashed to validate score pipeline responsiveness.
- Binary: mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin
- Command: ./scripts/build.sh && ./scripts/flash.sh
- Result: ok

## Update 2026-02-24
- Change: Diagnostic scoring now uses pure tolerance-hit rate (no MAE blend) to verify score pipeline behavior; rebuilt and flashed.
- Binary: mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin
- Command: ./scripts/build.sh && ./scripts/flash.sh
- Result: ok

## Update 2026-02-24
- Change: Applied user-selected scoring profile items 1+2: tolerance set to ±10% and evaluation counter E# retained in score strip; rebuilt and flashed.
- Binary: mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin
- Command: ./scripts/build.sh && ./scripts/flash.sh
- Result: ok

## Update 2026-02-24
- Change: Added MAE (mg/dL) line below PRED SCORE in alert strip for interpretable model quality; rebuilt and flashed.
- Binary: mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin
- Command: ./scripts/build.sh && ./scripts/flash.sh
- Result: ok

## Update 2026-02-24
- Change: Fixed MAE label rendering on embedded target by removing float printf dependency; MAE now formatted with integer tenths and flashed.
- Binary: mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin
- Command: ./scripts/build.sh && ./scripts/flash.sh
- Result: ok

## Update 2026-02-24
- Change: Documentation refresh: synchronized TODO, runtime contract, traceability, and validation docs with current prediction-score/E#/MAE behavior and latest baseline findings.
- Result: ok

## Update 2026-02-24
- Change: Wired exported trained CGM model into MCXN947 firmware prediction path.
  - `src/cgm_preprocess.c`
    - embedded ridge model coefficients from project `model/cgm_best_model.cpp`
    - added feature builder for trained contract fields (`lag1/2/3`, deltas, accel, rolling means)
    - replaced placeholder linear-only predictor with trained + conservative linear blend
    - retained SQI/sensor-flag confidence derating and mg/dL clamps (`40..400`)
- Effect:
  - `CgmModel_Predict()` now uses trained model behavior for `+15m` with bounded extrapolation used for `+30m`.
- Verification:
  - `./scripts/build.sh` PASS
  - output: `mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin`
- Result: ok

## Update 2026-02-24
- Change: Flashed MCXN947 with trained-CGM-integrated firmware build.
- Verification:
  - `./scripts/flash.sh` PASS
  - runner: `west flash` with `linkserver` (probe `#1`, FRDM-MCXN947)
- Result: ok

## Update 2026-02-24
- Change: Updated LIVE replay flow to run benchmark-style through dataset and hold final prediction score.
  - `src/edgeai_medical_device_demo.c`
    - added `RECPLAY_FULLRUN_MULTIPLIER` for post-warmup fast replay stepping
    - warmup remains first 4 hours (`RECPLAY_WARMUP_TARGET_DS` unchanged)
    - after warmup, replay continues accelerated through full dataset (no realtime cadence handoff)
    - on end-of-dataset in LIVE mode:
      - stop playback (no loop restart)
      - mark run complete and hold state
      - force playhead to 100%
      - keep final `PRED SCORE`/`MAE` visible on dashboard
    - runtime clock progression now freezes when benchmark run is complete (`playback_run_complete` guard)
    - restart paths reset completion flag so user can rerun benchmark via mode/timeline interactions
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Prevented post-benchmark auto-restart that could reset/overwrite final score display.
  - `src/edgeai_medical_device_demo.c`
    - guarded `AI_TRAIN: complete_live` auto-promote playback restart with `!playback_run_complete`
- Effect:
  - after full-run completion in LIVE benchmark mode, firmware no longer re-enters playback via trained-ready auto transition
  - final timeline/score hold behavior remains latched until explicit user restart action
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Addressed `E9818` with `0%` prediction score by fixing trained feature mapping and completion restart path.
  - `src/cgm_preprocess.c`
    - set trained `epoch_s` feature to model mean (instead of runtime-relative epoch counter) to prevent large standardized bias and clipped predictions.
  - `src/edgeai_medical_device_demo.c`
    - blocked trained-ready auto-promote playback restart when benchmark run is already complete (`!playback_run_complete` guard).
- Rationale:
  - `E9818` confirms scoring path is active; persistent `0%` indicated systematic prediction mismatch, not missing evaluator wiring.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Replaced CGM predictor with glucose-only trained model (removed unconnected insulin/motor feature dependency).
  - Training dataset: `data/d1namo_train_excl001.csv`
  - Holdout dataset: `data/d1namo_test_subject001.csv`
  - Output metrics artifact: `model/cgm_glucose_only_metrics.json`
  - Feature set (9):
    - `glucose_mgdl`
    - `glucose_mgdl_lag1`
    - `glucose_mgdl_lag2`
    - `glucose_mgdl_lag3`
    - `glucose_delta1`
    - `glucose_delta2`
    - `glucose_accel`
    - `glucose_roll3`
    - `glucose_roll6`
- Holdout training metrics (glucose-only ridge):
  - MAE `7.4848`
  - RMSE `10.4997`
  - R2 `0.98567`
  - tol10 hit rate `0.84181`
- Firmware integration:
  - `src/cgm_preprocess.c` embedded model coefficients/normalization updated to 9-feature glucose-only contract.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Ensured alert overlay always shows prediction state and upcoming values while preserving prediction-driven warning/fault behavior.
  - `src/gauge_render.c`
    - removed unused `BuildAnomalyReason(...)` helper after detail-line transition to prediction-centric text
    - alert detail continues to render `NORMAL/HYPO/HYPER` with `P15` and `P30` values
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed current prediction-alert-overlay build to FRDM-MCXN947.
- Verification:
  - `./scripts/flash.sh` PASS
  - runner: `linkserver` (probe `#1`, `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Added prediction visibility in elapsed-time area so upcoming values/states are always visible independent of activity headline.
  - `src/gauge_render.c`
    - clock area now includes second line under elapsed time:
      - `PRED <NORMAL|HYPO|HYPER> P15 <mg/dL> P30 <mg/dL>`
      - shows `PRED AI OFF` when AI is disabled
    - static dashboard placeholder updated to include `PRED --`
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Increased prediction readability in elapsed-time area.
  - `src/gauge_render.c`
    - prediction line under clock now renders at scale-2 by default
    - auto-falls back to scale-1 only when text would overflow available width
    - compact format used for better legibility: `PRED <STATE> <P15>/<P30>`
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed build with enlarged elapsed-area prediction text.
- Verification:
  - `./scripts/flash.sh` PASS
  - runner: `linkserver` (probe `#1`, `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Moved prediction display from elapsed-time area to center CGM area below `mg/dL`.
  - `src/gauge_render.c`
    - elapsed-time band now shows clock only again
    - center line directly under `mg/dL` now shows:
      - `PRED <NORMAL|HYPO|HYPER> <P15>/<P30>`
      - `PRED AI OFF` when AI is disabled
    - quality line now includes source tag with SQI/flags (`DATA`/`SIM`)
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Simplified center CGM text per UI request.
  - `src/gauge_render.c`
    - removed extra text lines under center `mg/dL`
    - line directly under `mg/dL` now shows predictions only, unlabeled format: `<P15>/<P30>` (example `160/170`)
    - when AI is off, displays `--/--`
    - removed prediction content from elapsed-time row
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed build with simplified unlabeled prediction line under center `mg/dL`.
- Verification:
  - `./scripts/flash.sh` PASS
  - runner: `linkserver` (probe `#1`, `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Increased center prediction line size and switched to explicit labeled format.
  - `src/gauge_render.c`
    - under center `mg/dL`, prediction text now renders as:
      - `15M PRED: xxx 30M: xxx`
    - text renders larger (scale-2) with auto-fallback to scale-1 if width exceeds available area
    - AI-off placeholder: `15M PRED: --- 30M: ---`
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed build with large center prediction line (`15M PRED: xxx 30M: xxx`).
- Verification:
  - `./scripts/flash.sh` PASS
  - runner: `linkserver` (probe `#1`, `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Removed spaces after colons in center prediction text format.
  - `src/gauge_render.c`
    - from `15M PRED: xxx 30M: xxx`
    - to `15M PRED:xxx 30M:xxx`
    - AI-off placeholder now `15M PRED:--- 30M:---`
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed build with center prediction colon-spacing update (`15M PRED:xxx 30M:xxx`).
- Verification:
  - `./scripts/flash.sh` PASS
  - runner: `linkserver` (probe `#1`, `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Updated center prediction text format to requested ordering.
  - `src/gauge_render.c`
    - now: `PRED 15M:xxx 30M:xxx`
    - AI-off placeholder: `PRED 15M:--- 30M:---`
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed build with center prediction text `PRED 15M:xxx 30M:xxx`.
- Verification:
  - `./scripts/flash.sh` PASS
  - runner: `linkserver` (probe `#1`, `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Promoted current firmware and documentation package as restore baseline `R6` and refreshed project documentation.
  - restore tags:
    - `GOLDEN-2026-02-24-R6`
    - `FAILSAFE-2026-02-24-R6`
  - staged artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R6.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R6.bin`
  - documentation updates:
    - rewritten `README.md` with Embedded Intelligence Layer architecture, host firmware safety separation, model behavior, and full ops guidance
    - synchronized baseline references in `docs/START_HERE.md` and `docs/OPS_RUNBOOK.md` to `R6`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: active release package and restore points updated.

## Update 2026-02-24
- Change: Increased center prediction line by one font size.
  - `src/gauge_render.c`
    - center `PRED 15M:xxx 30M:xxx` line now renders at scale-2 (was medium-weight scale-1)
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed build with one-step larger center prediction text (`PRED 15M:xxx 30M:xxx`).
- Verification:
  - `./scripts/flash.sh` PASS
  - runner: `linkserver` (probe `#1`, `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Reduced center prediction text from oversized scale-2 to standard scale-1 for better balance.
  - `src/gauge_render.c`
    - `PRED 15M:xxx 30M:xxx` now renders at scale-1
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Enhanced real-world behavior mapping and documentation.
  - `README.md`
    - added Human Activity state explanation (`REST`..`HEAVY`)
    - added real-world integration guidance for prediction/dosing feature pipelines
    - documented accelerometer/gyroscope/barometric roles (including up/down elevation trend use)
    - added optional ST AI biosensor offload architecture note
  - `src/gauge_render.c`
    - motor pulse RPM now directly maps to glucose/trend/dose state instead of broad random pulse RPM
    - prediction direction/status and CGM block/hold conditions now modulate RPM target
    - preserves dose safety gating while making motor/pump behavior visibly follow mg/dL dynamics
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Flashed build with motor/pump behavior coupled to glucose/trend prediction context.
- Verification:
  - `./scripts/flash.sh` PASS
  - runner: `linkserver` (probe `#1`, `UYLKOJI11H2B3`)
- Result: ok

## Update 2026-02-24
- Change: Refined pump/motor mimic to look closer to real pump actuation behavior.
  - `src/gauge_render.c`
    - switched to quantized pulse dose sizes based on commanded U/h (0.01U / 0.02U / 0.03U)
    - pulse interval now derived from `pulse_u / target_u_h` and bounded for realistic cadence
    - minimum/maximum interval bounds updated to avoid overly rapid synthetic pulses
    - `RATE` display while pumping now follows commanded dose flow (`U/h -> mL/h`) rather than RPM-only mapping
- Verification:
  - `./scripts/build.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Refined demo realism for pump behavior: fixed 30s dose-command cadence, neutral-zone damping near 95-115 mg/dL with stable trend, and reduced pulse chatter by raising pulse interval bounds to 30s..30min.
- Command: ./scripts/build.sh
- Result: ok

## Update 2026-02-24
- Change: Flashed current realism-tuned CGM pump build to FRDM-MCXN947 for on-device validation.
- Command: ./scripts/flash.sh
- Result: ok

## Update 2026-02-24
- Change: Promoted current realism-tuned firmware as restore baseline R7 and staged new golden/failsafe binaries.
- Binary: failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R7.bin ; failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R7.bin
- Command: cp mcuxsdk_ws/build/edgeai_medical_device_demo_cm33_core0.bin -> failsafe/*R7.bin
- Result: ok

## Update 2026-02-24
- Change: README cleanup: removed date stamp line and added hardware/sensor BOM section with FRDM-MCXN947, LCD controller, touch controller, and all runtime sensor part numbers used by firmware.
- Command: edit README.md
- Result: ok

## Update 2026-02-24
- Change: README: added Vehicle And Non-Human Motion Filtering section describing transport-context suppression of false high-speed movement effects; aligned restore baseline references to R7.
- Command: edit README.md
- Result: ok

## Update 2026-02-24
- Change: Synchronized local README.md to latest remote version from origin/main via checkout of tracked file.
- Command: git fetch origin main && git checkout origin/main -- README.md
- Result: ok

## Update 2026-02-24
- Change: Created pre-change restore checkpoint before any CGM display pipeline modifications.
- Restore refs:
  - Tag: `restore-cgm-20260224-192316`
  - Branch: `restore/cgm-20260224-192316`
  - Commit: `3c62fc2`
- Recovery commands:
  - `git checkout restore/cgm-20260224-192316`
  - or `git checkout restore-cgm-20260224-192316`
- Result: ready

## Update 2026-02-24
- Change: Implemented buffered atomic redraw for high-flicker CGM text regions.
  - `src/gauge_render.c`
    - added center glucose/prediction text cache (RAM compose from pump background + text, then blit)
    - added RTC strip cache (RAM compose + blit) to avoid direct clear-then-draw flashing
    - invalidates caches when static dashboard/modal transitions force background redraw
  - `src/text5x7.c`, `src/text5x7.h`
    - added `edgeai_text5x7_draw_scaled_to_buffer(...)` for RGB565 offscreen text composition
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Added buffered atomic redraw for graph-heavy dynamic regions to further reduce visible flashing.
  - `src/gauge_render.c`
    - scope waveform plot (`SCOPE_X+6 ..`) now composes into `gScopePlotCache` (RAM) and blits once per frame
    - timeline control strip now composes into `gTimelineCache` (RAM) and blits once per frame
    - added buffer primitives (`BufFillRect`, `BufDrawLine`, `BufDrawCircleFilled`) used by the offscreen path
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Optimized LCD solid-rectangle write path to reduce visible raster during dynamic UI updates.
  - `src/par_lcd_s035.c`
    - `par_lcd_s035_fill_rect(...)` now selects the destination area once and streams RGB565 pixels in chunks (`4096` pixels/chunk)
    - removed per-row `SelectArea + WritePixels` loop for rectangle fills
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Converted terminal/status dynamic renderer to offscreen composition + atomic blit.
  - `src/gauge_render.c`
    - terminal dynamic region now composes text/header in `gTerminalCache` and blits once per frame
    - added buffer text helpers for shadowed 5x7 rendering in RAM
  - previous LCD driver fill optimization remains active (`src/par_lcd_s035.c` streamed fill_rect)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Reworked scope/timeline update behavior to reduce full-region repaint artifacts.
  - `src/gauge_render.c`
    - scope plot now uses incremental column updates in `gScopePlotCache` instead of full trace re-rasterization every frame
    - timeline strip redraw is now gated to state changes (live mode / pause state / AI mode) instead of unconditional per-frame redraw
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Extended anti-raster conversion to remaining left/middle dynamic regions.
  - `src/gauge_render.c`
    - human orientation pointer now composes in `gOrientCache` and blits once (replaces direct multi-primitive LCD writes)
    - left bar dynamic region now composes in `gLeftBarCache` and blits once on value changes
    - alert score/MAE strip redraw is now change-gated (no unconditional per-frame clear/redraw)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Notes:
  - SRAM dynamic data usage increased significantly due added region buffers (`m_data` ~76.96%).
- Result: ok

## Update 2026-02-24
- Change: Added startup scope history prefill and further left/middle anti-raster gating.
  - `src/gauge_render.c`
    - new `PrefillScopeTraceFromReplayWindow()` seeds scope traces from the first 4-hour replay window so graph is not empty at startup
    - `GaugeRender_Init()` now preloads trace buffers via prefill helper
    - `DrawScopeDynamic()` initializes first render cache from prefilled trace history before incremental updates
    - `DrawMedicalOverlayData()` now redraws motor/pump/anomaly text regions only when values change
    - `DrawHumanOrientationPointer()` now skips redraw when movement/segment change is negligible
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Notes:
  - Memory usage after changes: `m_text` ~64.00%, `m_data` ~76.97%.
- Result: ok

## Update 2026-02-24
- Change: Adjusted startup graph preload and removed several remaining unnecessary dynamic redraws.
  - `src/gauge_render.c`
    - replaced replay-window prefill behavior with first-live-sample bootstrap: on first sample, all trace buffers are initialized to that sample, creating in-range flat startup lines that transition smoothly to live data
    - center glucose text cache blit is now dirty-only (no unconditional middle-panel redraw when unchanged)
    - battery widget redraw is now gated by SOC changes (fixed SOC no longer repaints each frame)
    - AX/AY/AZ/T/GX/GY/GZ/BP legend strip now redraws only on first draw or temperature-color change
    - removed duplicate `DrawAiSideButtons()` call to avoid a second redundant repaint of the side buttons region
    - removed replay-trace include dependency from startup trace initialization path
- Verification:
  - `./scripts/build.sh` PASS (latest edit set)
  - `./scripts/flash.sh` PASS
- Notes:
  - Goal was to reduce residual flashing in mg/dL/PRED row, symbol row (`* ?`), battery, and the left/middle legend strip while keeping live updates active.
- Result: ok

## Update 2026-02-24
- Change: Fixed rendering regressions introduced by aggressive redraw gating in center and alert regions.
  - `src/gauge_render.c`
    - center CGM text cache (mg/dL + PRED row) now blits whenever cache is valid, preventing intermittent disappearance when neighboring dynamic layers repaint
    - alert score strip cache now invalidates on modal/recording/training/thinking early-return paths so the accuracy strip always restores when returning to normal view
    - warning/activity headline switched from crisp text path to standard UI text path for reliable rendering of labels such as `HUMAN REST`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed alert/text persistence regressions and reduced unnecessary static touch-marker redraws.
  - `src/gauge_render.c`
    - `DrawGlucoseIndicator()` now rebuilds center cache when cache is invalidated (not only on value deltas), then blits dirty-only to reduce sporadic mg/dL/PRED flashing while still recovering after static redraws
    - `DrawAiSideButtons()` now redraws only when settings/help visibility state changes (`*` and `?` are static unless touch-state changes)
    - `DrawAiAlertOverlay()` refactored so `RECORDING`, `TRAINING`, and `THINKING` no longer bypass score-strip rendering via early return
    - score strip redraw now triggers whenever the alert panel itself is redrawn, preventing "appeared then disappeared" behavior after panel/static invalidations
    - modal branch now clears both alert box and score-strip area together to prevent stale fragments
    - activity/warning headline rendering in normal/fault panel path uses crisp text rendering for cleaner/consistent label output
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Stabilized warning panel text rendering and score-strip persistence under static redraw transitions.
  - `src/gauge_render.c`
    - added `gUiForceAlertOverlayRefresh` flag; set when static dashboard is redrawn (`!gStaticReady` and modal-close full redraw paths)
    - `DrawAiAlertOverlay()` now consumes this flag to invalidate both alert visual cache and score-strip cache so score/MAE reliably reappear without requiring motion/activity-state changes
    - switched warning/activity headline draw path from crisp renderer back to standard `DrawTextUi(...)` to remove dithered/non-font appearance in warning box
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Artifact-cleanup pass focused on black box fragments and width mismatches.
  - `src/gauge_render.c`
    - fixed scope frame rectangle bounds to strict inclusive coordinates (`SCOPE_X + SCOPE_W - 1`, `SCOPE_Y + SCOPE_H - 1`) to eliminate +1 width mismatch against dynamic graph content
    - converted alert/warning panel paths (`RECORDING`/`TRAINING`/`THINKING` and normal warning/activity mode) to deterministic redraw each frame path (no cache-skip branch)
    - score strip now reliably repaints with the alert region (condition still cache-aware but forced by alert redraw), reducing missing center strip/side fragment artifacts under warning box
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Reworked warning + score region into a single offscreen-composited panel to remove side fragments, half-filled backgrounds, and multi-rect repaint artifacts.
  - `src/gauge_render.c`
    - added `gAlertPanelCache` (`192x80`) for alert/score composite rendering
    - `DrawAiAlertOverlay()` now composes full-width warning panel + full-width score strip in RAM and blits once to LCD
    - settings/help/limits modal path restores full alert+score region from background image (`BlitPumpBgRegion(...)`) instead of piecemeal clears
    - removed obsolete alert visual cache state fields no longer used by the new renderer
    - retained prior scope frame width-bound fix (`SCOPE_W/H - 1` inclusive bounds)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Notes:
  - SRAM usage increased due new alert panel cache: `m_data` now ~86.54%.
- Result: ok

## Update 2026-02-24
- Change: Converted center mg/dL + PRED rows to the same deterministic offscreen-composited render strategy used for warning/score.
  - `src/gauge_render.c`
    - `DrawGlucoseIndicator()` now composes a fixed-width center panel (`CENTER_TEXT_CACHE_W x 30`) into `gCenterTextCache` each frame and blits once
    - removed delta-gated center text cache invalidation logic that could leave center rows missing after overlapping redraw events
    - removed obsolete legacy center-cache coordinate globals no longer used by the deterministic panel path
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Notes:
  - SRAM remains high due panel buffers: `m_data` ~86.53%.
- Result: ok

## Update 2026-02-24
- Change: Reduced AI status pill flashing by making it state-driven.
  - `src/gauge_render.c`
    - `DrawAiPill()` now caches prior state and redraws only when either AI enable state changes or backend label changes (`AI MCU` / `AI NPU`)
    - no per-frame repaint when state is unchanged
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed center panel overlap into terminal text area.
  - `src/gauge_render.c`
    - center mg/dL/PRED offscreen panel width is now dynamic and clamped so it cannot cross into terminal region (`TERM_X` boundary)
    - preserves deterministic single-blit center rendering while preventing leading-character erasure in terminal rows (`ACC`, subsequent lines)
  - `DrawAiPill()` remains state-gated from prior update
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed slow settings/help popup rendering and restored solid black modal background.
  - `src/gauge_render.c`
    - `DrawPopupModalBase()` now paints a full black backdrop for modal views
    - added modal redraw-on-demand path in `GaugeRender_DrawFrame()` using `ModalRenderSignature()` and `gModalRedrawPending`; popups are redrawn only when modal state/content changes
    - added modal invalidation triggers in popup-related setters (`SetHelpVisible`, `SetHelpPage`, `NextHelpPage`, `SetSettingsVisible`, `SetLimitsVisible`, `SetLiveBannerMode`, `SetAiBackendNpu`, `SetLogRateHz`, `SetLimitInfo`) and static/modal transitions
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Tuned modal backdrop rendering for settings/help/limits to improve open latency while preserving black background.
  - `src/gauge_render.c`
    - `DrawPopupModalBase()` now fills expanded black regions around active popup panels instead of full-screen black fill
    - retains modal redraw-on-demand signature path from prior update
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: ok

## Update 2026-02-24
- Change: Fixed modal popup latency/regression and restored top-row modal black background coverage.
  - `src/gauge_render.c`
    - removed modal signature/pending redraw gating (`ModalRenderSignature`, `gModalRedrawPending`, `gModalLastSignature`)
    - `GaugeRender_DrawFrame()` now deterministically redraws active modal popup content every modal frame
    - `DrawPopupModalBase()` now paints a single black backdrop from top edge through popup-bottom extent, keeping `?` and `*` on black while popup is active
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: popup open/close path is now deterministic, and top `?/*` modal background coverage is restored.

## Update 2026-02-24
- Change: Added modal dirty-redraw path to reduce popup latency and keep `?`/`*` visible with black backing while modal is active.
  - `src/gauge_render.c`
    - added `gModalDirty` and switched modal rendering to redraw only when modal state/content changes
    - modal branch now redraws side buttons during modal render (`DrawAiSideButtons()`), preventing `?`/`*` disappearance
    - `DrawPopupModalBase()` now fills active popup panel region plus top button strip backgrounds (instead of broad full-screen/top-band fill)
    - modal-affecting setters (`SetHelp*`, `SetSettingsVisible`, `SetLimitsVisible`, `SetLiveBannerMode`, `SetAiBackendNpu`, `SetLogRateHz`, `SetLimitInfo`) now mark modal dirty
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: modal open/close rendering is now event-driven rather than continuous redraw; `?`/`*` are explicitly repainted in modal state.

## Update 2026-02-24
- Change: Improved popup readability and fixed missing center ball after closing popups.
  - `src/gauge_render.c`
    - modal branch now redraws active popup content every modal frame (settings/help/limits text stays readable), while modal backdrop fill remains dirty-gated
    - added one-shot orientation force-refresh flag (`gForceOrientRefresh`) to bypass no-change early-return after modal close and redraw the ball immediately
    - modal-close path now sets `gForceOrientRefresh = true`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: popup text should remain readable and center ball should reappear immediately after popup close (without requiring tilt/shake).

## Update 2026-02-24
- Change: Restored full modal black background and reduced popup draw cost.
  - `src/gauge_render.c`
    - `DrawPopupModalBase()` now performs a one-shot full-screen black fill for modal transitions
    - modal render branch now draws popup content only when `gModalDirty` is set (open/close/page/settings changes), removing per-frame popup repaint overhead
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: settings/help should show complete black modal background and open/close faster under normal touch interaction.

## Update 2026-02-25
- Change: Documented settings/help popup bug progression and promoted current UI-fix build as restore baseline `R8`.
  - popup bug progression covered in docs:
    - missing modal black background in settings/help
    - high popup open/close latency during modal redraw churn
    - post-popup orientation-ball missing until sensor motion forced redraw
  - implemented progress in code path (`src/gauge_render.c`):
    - modal redraw gating via `gModalDirty`
    - full-screen modal black backdrop on modal transitions
    - one-shot orientation force refresh after modal close (`gForceOrientRefresh`)
- Restore point staging:
  - tags:
    - `GOLDEN-2026-02-24-R8`
    - `FAILSAFE-2026-02-24-R8`
  - artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-24-R8.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-24-R8.bin`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: `R8` is the active golden/failsafe restore baseline; popup bug remains tracked in `docs/TODO.md` pending final on-device validation.

## Update 2026-02-25
- Change: Fixed graph/timeline width mismatch and reduced unnecessary LIVE banner refreshes.
  - `src/gauge_render.c`
    - corrected timeline width alignment by changing `TIMELINE_X1` from `SCOPE_X + SCOPE_W` to `SCOPE_X + SCOPE_W - 1`
    - removed timeline/LIVE strip drawing from `DrawScopeFrame()` so static scope frame no longer repaints the banner each frame
    - timeline/LIVE strip remains rendered by `DrawScopeDynamic()` timeline change gate only (mode/state change driven)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: timeline background now aligns with graph width, and LIVE blue banner redraw is no longer tied to per-frame scope frame rendering.

## Update 2026-02-25
- Change: Adjusted scope plot width alignment and removed full-trace-cycle erase behavior.
  - `src/gauge_render.c`
    - widened scope plot region to align with scope interior/timeline framing (`px0 = SCOPE_X + 2`, `pw = SCOPE_W - 4`)
    - removed full interior clear on write-head wrap; plot now overwrites old columns as head advances (continuous ring-buffer style)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: plot area should better match surrounding scope/timeline width and no longer blank on full-cycle wrap.

## Update 2026-02-25
- Change: Fixed missing scope plot introduced by width expansion.
  - `src/gauge_render.c`
    - increased `SCOPE_PLOT_CACHE_W` from `139` to `151` to match widened plot region (`pw = SCOPE_W - 4`)
    - this removes the cache-bound early-return that blanked the plot area
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Notes:
  - SRAM data usage increased to ~`87.04%` due larger scope plot cache.
- Result: plot area should render again with the widened width and continuous overwrite behavior.

## Update 2026-02-25
- Change: Cleaned up persistent black remnant under scope graph strip.
  - `src/gauge_render.c`
    - scope legend strip under graph now restores pump background each frame (`BlitPumpBgRegion(...)`) and redraws labels deterministically
    - removes stale black box remnants caused by prior legend redraw gating
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: under-graph area should no longer retain black remnant artifacts when UI layers refresh.

## Update 2026-02-25
- Change: Moved scope legend row (`AX AY AZ T GX GY GZ BP`) up to visually integrate with graph box.
  - `src/gauge_render.c`
    - legend baseline moved up by 2 px (`ly: SCOPE_Y + SCOPE_H + 1 -> SCOPE_Y + SCOPE_H - 1`)
    - legend strip background restore start moved up accordingly
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: reduced visible gap between graph box and legend row.

## Update 2026-02-25
- Change: Re-aligned scope plot width to match LIVE banner interior width after remnant cleanup.
  - `src/gauge_render.c`
    - adjusted scope plot geometry to `px0 = SCOPE_X + 1` and `pw = SCOPE_W - 2`
    - keeps plot rendering path and overwrite-on-wrap behavior unchanged
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: graph plot width should visually align with the LIVE box width again.

## Update 2026-02-25
- Change: Made AX/AY scope legend static and non-flashing with fixed black background.
  - `src/gauge_render.c`
    - added `DrawScopeLegendRow()` to render `AX AY AZ T GX GY GZ BP` with a fixed black strip
    - moved legend draw to static dashboard path (`DrawStaticDashboard`) so it renders once per static refresh
    - removed per-frame legend redraw block from `GaugeRender_DrawFrame`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: AX/AY legend row should no longer flash and keeps a stable black background.

## Update 2026-02-25
- Change: Fine-tuned static AX/AY legend position upward by an additional 2 px.
  - `src/gauge_render.c`
    - `DrawScopeLegendRow()` baseline moved from `SCOPE_Y + SCOPE_H - 1` to `SCOPE_Y + SCOPE_H - 3`
    - legend black background strip start moved to match new baseline
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: legend sits tighter to the graph box with reduced vertical gap.

## Update 2026-02-25
- Change: Fixed AX/AY legend black bar overshoot on the right side of the display.
  - `src/gauge_render.c`
    - in `DrawScopeLegendRow()`, clamped legend background fill bounds to exact scope box width:
      - from terminal bounds (`TERM_X .. TERM_X + TERM_W`)
      - to scope bounds (`SCOPE_X .. SCOPE_X + SCOPE_W - 1`)
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: AX/AY legend black background now lines up with the scope box right edge and no longer extends off-screen.

## Update 2026-02-25
- Change: Created a new pre-change restore baseline `R9` before popup flow modifications.
  - artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-25-R9.bin`
  - note:
    - failsafe baseline remains `R8` per request (`FAILSAFE-2026-02-24-R8`)
- Result: rollback point captured and available via `./tools/flash_failsafe.sh`.

## Update 2026-02-25
- Change: Modal transition behavior hardened for Settings/Help/Limits popup flow.
  - `src/gauge_render.c`
    - on modal open transition, force immediate full-screen black clear before popup render (`DrawPopupModalBase()`).
    - on modal close transition, force full-screen black clear then redraw full dashboard (`DrawStaticDashboard(...)`).
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: popup mode now explicitly freezes regular UI refresh and performs deterministic clear-to-black/open and clear-to-dashboard/close transitions while background data processing continues.

## Update 2026-02-25
- Change: Reflashed current modal-popup build on request for device verification.
- Verification:
  - `./scripts/flash.sh` PASS
- Result: board now running latest image with modal open/close clear behavior changes.

## Update 2026-02-25
- Change: Enforced strict popup display ownership while modal is open.
  - `src/gauge_render.c`
    - modal draw branch now always redraws full-screen black modal base and active popup every modal frame entry (settings/help/limits), instead of relying on dirty-state gating.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: popup interactions now consistently keep the dashboard frozen/hidden behind full black modal surface until close transition redraw.

## Update 2026-02-25
- Change: Implemented requested single-step settings modal behavior.
  - `src/gauge_render.c`
    - when settings modal is active, render full-screen black + only a touchable corner `X` (no settings panel/buttons/text).
  - `src/edgeai_medical_device_demo.c`
    - settings touch handling is now close-only: only the `X` hitbox closes settings; other settings touch targets are ignored.
  - `src/gauge_render.h`
    - added `GAUGE_RENDER_SETTINGS_CLOSE_X0..Y1` constants for shared corner-`X` hitbox geometry.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: pressing settings now freezes display updates, shows black screen with only `X`, and resumes normal dashboard redraw on close.

## Update 2026-02-25
- Change: Ensured modal blackout is actively rendered while settings modal is open.
  - `src/edgeai_medical_device_demo.c`
    - render loop now always calls `GaugeRender_DrawFrame(...)` on display ticks, including modal-active state.
    - modal content remains display-owner via early-return modal branch in renderer, so normal dashboard updates stay paused.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: settings close-only `X` overlay should no longer appear transparent over visible dashboard.

## Update 2026-02-25
- Change: Extended close-only black modal behavior to both Settings and Help.
  - `src/gauge_render.c`
    - modal branch now shows the same full-black + corner `X` overlay when either settings or help is active.
  - `src/edgeai_medical_device_demo.c`
    - help touch handling is now close-only, matching settings (only `X` closes; no next/page interactions).
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: both `*` and `?` should now enter the same black modal with only corner `X`.

## Update 2026-02-25
- Change: Switched modal blackout renderer to per-line blit path.
  - `src/gauge_render.c`
    - `DrawPopupModalBase()` now writes full-screen black using line-by-line `par_lcd_s035_blit_rect(...)` with a static black scanline buffer.
- Why:
  - addresses persistent transparent-background behavior where corner `X` appeared over visible dashboard.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: modal black background should now fully overwrite prior UI for both settings/help close-only overlays.

## Update 2026-02-25
- Change: Addressed modal close redraw regressions and X flashing.
  - `src/gauge_render.c`
    - modal branch now redraws blackout/overlay only when modal state is dirty (not every frame), removing `X` flicker.
    - `DrawAiSideButtons()` cache short-circuit removed so `*` and `?` are always redrawn after static/dashboard refreshes.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: `X` should stay stable while modal is open; `*`, `?`, and static UI elements (including battery frame) should reappear after close.

## Update 2026-02-25
- Change: Boot warmup now runs in background-only display mode until preroll completes.
  - `src/gauge_render.c`
    - `GaugeRender_DrawFrame(...)` now short-circuits to `DrawSpaceboxBackground()` when warmup-thinking is active (`gUiWarmupThinking`), with no UI overlays/graphics drawn.
    - on warmup exit, renderer forces a full static dashboard rebuild before resuming normal updates.
    - `GaugeRender_DrawGyroFast()` now also skips scope updates during warmup-thinking.
  - `src/edgeai_medical_device_demo.c`
    - if booting in LIVE mode, set warmup-thinking before first frame to avoid showing dashboard graphics during initial preroll.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: during first 4-hour preroll learning phase, only background image is displayed; full UI appears after preroll completion.

## Update 2026-02-25
- Change: Tightened boot warmup display and post-modal redraw behavior.
  - `src/gauge_render.c`
    - `GaugeRender_Init()` now draws background only (no pre-drawn dashboard graphics at boot).
    - removed per-frame `DrawAiSideButtons()` dynamic redraw path to keep `*`/`?` stable.
    - added `gForceBatteryRedraw` so battery frame/value is re-rendered after modal close and warmup transition.
  - `src/edgeai_medical_device_demo.c`
    - replay runtime clock now uses a relative timestamp origin (first playback sample) to avoid jumping elapsed display to large absolute times.
    - playback-origin reset added on playback restart/reset paths.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result:
  - no dashboard pre-draw at boot warmup,
  - stable `*`/`?` (no continuous flash),
  - battery static redraw restored after help/settings close,
  - elapsed clock no longer jumps to absolute replay day/hour values.

## Update 2026-02-25
- Change: Corrected help/settings touch-open regression and elapsed-time progression.
  - `src/edgeai_medical_device_demo.c`
    - replay display time now advances via per-sample timestamp deltas from 0 (no absolute-day hour jump).
    - added source-timestamp tracker reset on playback restart paths.
  - `src/gauge_render.c`
    - restored per-frame side-button redraw (`*`, `?`) in normal rendering path for reliable touch affordance visibility.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: help/settings buttons should respond again; elapsed time should progress from preroll handoff timeline instead of jumping to ~19h.

## Update 2026-02-25
- Change: Restored settings/help touch responsiveness with immediate-open path.
  - `src/edgeai_medical_device_demo.c`
    - if touch is inside `*` or `?` and no modal is active, modal now opens immediately (no dependency on edge-trigger latch state).
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: `*` and `?` should respond to touch and bring up the black close-only modal again.

## Update 2026-02-25
- Change: Re-enabled Help popup content and navigation.
  - `src/gauge_render.c`
    - modal branch now renders full `DrawHelpPopup()` for help mode (text + `NEXT PAGE` button).
    - settings mode remains close-only black modal.
  - `src/edgeai_medical_device_demo.c`
    - help touch routing restored for `X` close, `NEXT PAGE`, and outside-panel close.
    - help close hitbox restored to help-panel corner `X` geometry.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: Help now shows text and `NEXT`; Settings remains minimal close-only modal.

## Update 2026-02-25
- Change: Reduced help/settings popup open latency.
  - `src/gauge_render.c`
    - `DrawPopupModalBase()` now uses fast full-screen `par_lcd_s035_fill(RGB565(0,0,0))` instead of slow per-line blit loop.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: help popup should appear significantly faster (no slow serial-style text paint effect).

## Update 2026-02-25
- Change: Reverted most recent popup-base optimization to prior black-screen behavior.
  - `src/gauge_render.c`
    - `DrawPopupModalBase()` restored to line-by-line black blit implementation.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: device returned to previous modal-black rendering behavior before the last speed-only change.

## Update 2026-02-25
- Change: Fixed repeated modal redraw causing slow popup text rendering.
  - `src/gauge_render.c`
    - Added change-detection guards so `gModalDirty` is only set when values actually change in:
      - `GaugeRender_SetLimitInfo`
      - `GaugeRender_SetHelpVisible`
      - `GaugeRender_SetHelpPage`
      - `GaugeRender_SetSettingsVisible`
      - `GaugeRender_SetLimitsVisible`
      - `GaugeRender_SetLiveBannerMode`
      - `GaugeRender_SetAiBackendNpu`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Expected result: Help popup no longer repaints full text every frame; open/render latency should be substantially reduced.

## Update 2026-02-25
- Change: Switched Help popup text rendering to buffered line blits to remove slow character-by-character LCD writes.
  - `src/gauge_render.c`
    - Added `DrawPopupTextLineBuffered(...)`.
    - `DrawHelpPopup()` now renders title/page label/help text and NEXT label via buffered blits.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Notes:
  - This reduces LCD transactions during popup draw.
  - Current RAM (`m_data`) is now ~93.11% due added line buffer; monitor for stability.

## Update 2026-02-25
- Change: Restored a clearly visible Help `NEXT PAGE` button.
  - `src/gauge_render.c`
    - Increased NEXT button contrast (green fill, bright edge/text).
    - Kept existing NEXT hitbox and page-toggle behavior.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS

## Update 2026-02-25
- Change: Fixed black box overlap on Help `NEXT PAGE` button.
  - `src/gauge_render.c`
    - Moved NEXT button draw to the end of `DrawHelpPopup()` so lower help text/background blits cannot paint over it.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS

## Update 2026-02-25
- Change: Applied same buffered-popup render strategy to Settings overlay.
  - `src/gauge_render.c`
    - `DrawSettingsCloseOnlyOverlay()` now draws `SETTINGS` + close note using buffered text blits.
    - Close `X` control is drawn last to prevent overlap artifacts.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS

## Update 2026-02-25
- Change: Restored full Settings popup and re-enabled settings button actions.
  - `src/gauge_render.c`
    - Modal branch now renders `DrawSettingsPopup()` (not close-only overlay).
    - Marked `DrawSettingsCloseOnlyOverlay()` as unused helper to satisfy `-Werror`.
  - `src/edgeai_medical_device_demo.c`
    - Restored Settings touch handling for:
      - AI mode ON/OFF
      - RUN TRAIN/LIVE
      - SENS LOOSE/NORM/STRICT
      - AI backend MCU/NPU
      - LIMITS open
      - CLEAR FLASH confirm
      - LOG HZ dec/inc
      - outside-to-close
    - Saves updated settings to flash via `SaveUiSettingsIfReady(...)`.
- Verification:
  - `./scripts/build.sh` FAIL once (unused-function warning)
  - `./scripts/build.sh` PASS after fix
  - `./scripts/flash.sh` PASS

## Update 2026-02-25
- Change: Fixed Settings/Help immediate close on open (tap race).
  - `src/edgeai_medical_device_demo.c`
    - Added `opened_modal_this_touch` guard so the same press that opens modal cannot also execute modal close/outside logic in that loop.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Expected result:
  - Settings no longer disappears immediately after opening from `*` tap.

## Update 2026-02-25
- Change: Improved modal button responsiveness with dedicated touch latch.
  - `src/edgeai_medical_device_demo.c`
    - Added `s_modal_touch_consumed`.
    - Modal tap handling (Settings/Help/Limits) now processes one action per press-release cycle independent of `s_touch_was_down` edge timing.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Expected result:
  - Settings buttons should respond reliably to taps.

## Update 2026-02-25
- Change: Reworked modal touch handling to modal-specific edge detection.
  - `src/edgeai_medical_device_demo.c`
    - Replaced modal consumed-flag logic with `s_modal_touch_was_down` edge tracking.
    - Modal actions now trigger on `modal_press_edge` while overlay is visible.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Expected result:
  - Settings buttons should react on tap; no dependency on main-screen touch edge state.

## Update 2026-02-25
- Change: Settings responsiveness + render speed + UI flash fixes.
  - `src/edgeai_medical_device_demo.c`
    - Boot default now forces AI ON (`ai_enabled = true`) even if persisted OFF.
    - Settings interactions now call `GaugeRender_RequestModalRedraw()` after setting changes.
  - `src/gauge_render.h`
    - Added `GaugeRender_RequestModalRedraw()` API.
  - `src/gauge_render.c`
    - Added `GaugeRender_RequestModalRedraw()` implementation (`gModalDirty = true`).
    - Settings popup button containers switched from rounded-pill renderer to fast rectangular renderer (`DrawButtonRectFast`) to reduce load latency.
    - Added `gAiSideButtonsDirty` + state cache to avoid redrawing `*`/`?` every frame (reduces flashing).
    - Side-button dirty flag now refreshes on static redraw and settings/help/limits visibility changes.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS

## Update 2026-02-25
- Change: Promoted current build as active Golden + Failsafe restore baseline `R10`.
  - tags:
    - `GOLDEN-2026-02-25-R10`
    - `FAILSAFE-2026-02-25-R10`
  - artifacts:
    - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-25-R10.bin`
    - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-25-R10.bin`
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Result: `R10` is now the active golden/failsafe restore point set.

## Update 2026-02-25
- Change: Fixed runtime counter handoff at preroll completion.
  - `src/edgeai_medical_device_demo.c`
    - Added `SetRuntimeClockFromDs(...)` helper.
    - On warmup completion (normal and force-complete paths), runtime display now clamps to at least `RECPLAY_WARMUP_TARGET_DS` and updates clock immediately.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Expected result:
  - Counter starts from preroll boundary (~4:00:00) after warmup handoff, not from 0.

## Update 2026-02-25
- Change: Fixed post-preroll elapsed-time jump (4:00:00 -> ~23:54:00).
  - `src/edgeai_medical_device_demo.c`
    - Added `RECPLAY_POST_WARMUP_MAX_DELTA_DS` (10-minute cap).
    - After warmup handoff, replay timestamp deltas are clamped before adding to displayed runtime.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Expected result:
  - After preroll ends near `4:00:00`, elapsed time advances smoothly without large jumps.

## Update 2026-02-25
- Change: Forced exact runtime handoff at warmup completion.
  - `src/edgeai_medical_device_demo.c`
    - warmup completion now always sets runtime to `RECPLAY_WARMUP_TARGET_DS` exactly (4h), both for normal and force-complete paths.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Expected result:
  - elapsed time should remain at `0004:00:00` at handoff and then advance forward normally.

## Update 2026-02-25
- Change: Added global elapsed-time anti-jump guard.
  - `src/edgeai_medical_device_demo.c`
    - added `RUNTIME_MAX_STEP_DS` and applied it to all runtime clock update paths (fallback/runtime, live-anchor, replay timeline).
    - if any path attempts a large single-step jump, elapsed increments by one decisecond tick instead.
- Verification:
  - `./scripts/build.sh` PASS
  - `./scripts/flash.sh` PASS
- Expected result:
  - no sudden jump from preroll boundary to ~23:55; runtime advances smoothly.

## Update 2026-02-25
- Change: Fixed elapsed-time acceleration after preroll by accepting real OSTIMER frequencies (1 kHz..1 MHz) in `TimebaseInit()` instead of forcing near-32 kHz selection; this prevents ~30x runtime clock scaling when OSTIMER runs near 1 MHz.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Improved preroll UX and speed in LIVE warmup path.
  - Added on-screen preroll panel during warmup (`PREROLL LOADING`) with elapsed `TIME hh:mm:ss` and progress `%` against 4-hour target.
  - Increased replay warmup throughput by changing `RECPLAY_WARMUP_MULTIPLIER` from 120 to 300 for faster preroll completion.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Increased preroll throughput by 10x by raising `RECPLAY_WARMUP_MULTIPLIER` from 300 to 3000 in `src/edgeai_medical_device_demo.c`.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Preroll warmup panel visual polish in `src/gauge_render.c`.
  - Centered the panel on screen.
  - Updated typography hierarchy and palette (title, subtitle, time, percent).
  - Added framed card styling and refined progress bar colors.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Improved high-speed preroll robustness to protect model accuracy.
  - In LIVE playback mode, transient `ExtFlashRecorder_ReadNextSample()` failures no longer immediately force final-score completion.
  - Added retry streak and playback recovery restart path before declaring completion.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Tuned preroll speed from aggressive 25x to true 10x baseline by setting `RECPLAY_WARMUP_MULTIPLIER` to `1200` (from `3000`) to reduce warmup-induced accuracy regression risk.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Relaxed runtime anti-jump clamp from `+1 ds` creep to `+RUNTIME_MAX_STEP_DS` in key runtime/playback paths.
  - Prevents overly slow timeline catch-up that can freeze alert/activity dynamics.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Restored warmup scoring semantics to match original intent.
  - 0-2h warmup treated as pre-evaluation only.
  - 2-4h warmup treated as scoring window.
  - Added `GaugeRender_ResetPredictionMetrics()` and invoke at warmup start for clean runs.
  - Added explicit 2h boundary reset inside prediction-accuracy updater so second window scoring is isolated.
  - Score display now uses `MODEL SCORE` label and requires minimum steady eval count before showing a percentage.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Tightened score wiring to model-eligible predictions only.
  - Added model-eligibility state (`model_ok && conf>=55`) for score issuance.
  - `MODEL SCORE` display now requires current model-eligible state plus minimum steady eval count; otherwise shows `--` with eval count.
  - Prevents stale/fallback-driven score from appearing as active model quality.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Tightened MODEL SCORE error tolerance from +/-10% to +/-5% (with 3 mg/dL minimum window) in prediction evaluation.
  - Goal: avoid persistent 99% saturation and make score more discriminative/realistic.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Tuned MODEL SCORE for realistic behavior.
  - Increased minimum steady evaluation threshold from 8 to 24 samples.
  - Replaced raw hit-rate-only score with weighted realism score:
    - 50% tolerance-hit rate
    - 35% MAE quality mapping (8 mg/dL strong to 26 mg/dL poor)
    - 15% model confidence
  - Score remains bounded to 0..99.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Unstuck model metrics visibility by relaxing strict score gates.
  - Minimum steady eval threshold reduced from 24 to 12.
  - Model-eligibility confidence threshold reduced from 55 to 45.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Removed preroll popup/background-only warmup render path.
  - Boot now renders normal dashboard/data display immediately while warmup runs in background.
- Result: build PASS, flash PASS (`./scripts/build.sh`, `./scripts/flash.sh`).

## Update 2026-02-25
- Change: Finalized current firmware/docs package as restore baseline `R11` and removed preroll popup UI path.
  - boot now goes directly to live dashboard rendering while warmup runs in background
  - model-score pipeline remains model-eligible + realism-weighted with MAE/confidence integration
- Restore points promoted:
  - Golden: `GOLDEN-2026-02-25-R11`
  - Failsafe: `FAILSAFE-2026-02-25-R11`
- Staged artifacts:
  - `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-25-R11.bin`
  - `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-25-R11.bin`
- Docs synchronized:
  - `README.md`, `STATUS.md`, `docs/START_HERE.md`, `docs/OPS_RUNBOOK.md`, `docs/HARDWARE_SETUP.md`
