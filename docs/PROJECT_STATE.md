# Project State

Last updated: 2026-02-22
Project: `EdgeAI_Package_Transport_Anomaly_demo_NXP_FRDM-MCXN947`

## Current Baseline
- Lifecycle: initialized
- App target: `edgeai_package_transport_anomaly_demo`
- Build target: `frdmmcxn947` / `cm33_core0`
- Golden tag: `GOLDEN-20260222-152829`
- Lock tag: `FAILSAFE-ACTIVE`
- Failsafe binary: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`

## Update 2026-02-22 (Repo Hygiene: Hide Local Agent Instructions)
- Removed `AGENTS.md` from git tracking (`git rm --cached AGENTS.md`) while preserving local file content on disk.
- Added ignore rules in `.gitignore`:
  - `AGENTS.md`
  - `agents.md`
- Result: local agent-instruction files are no longer published to GitHub for this project repo.

## Update 2026-02-22 (README GitHub Hardware Parts Expansion)
- Expanded `README.md` with explicit GitHub-facing hardware parts list including board, display, ST shield devices, and key supporting components used in code paths.
- Added clear component inventory entries for:
  - `LSM6DSO16IS`, `LIS2MDL`, `LPS22DF`, `STTS22H`
  - `LSM6DSV16X` and `LIS2DUXS12` probe/fallback entries
  - `SHT40`, `P3T1755DP`, external flash (`W25Q64` class), and `GT911` touch path

## Update 2026-02-22 (README Hardware Section Expanded)
- Updated `README.md` to explicitly document the ST shield component stack used by firmware code:
  - `LSM6DSO16IS`, `LIS2MDL`, `LPS22DF`, `STTS22H`
  - plus shield-mounted `SHT40` auxiliary environment channel
  - plus probe/fallback references (`LSM6DSV16X`, `LIS2DUXS12`) and board temp path (`P3T1755DP`)
- Purpose: make GitHub-facing hardware coverage clear for integrators and reviewers.

## Update 2026-02-22 (Golden/Failsafe Release Cut: GOLDEN-20260222-152829)
- Cut new golden/failsafe from current validated build output:
  - golden tag: `GOLDEN-20260222-152829`
  - golden binary: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260222T152829Z.bin`
  - failsafe active: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
  - sha256: `2304af425c539cc63ddd56a6e0166c1697f43d1f1c0b744bf32be32ff8b78bd3`
- Synced restore metadata across:
  - `STATUS.md`
  - `docs/START_HERE.md`
  - `docs/RESTORE_POINTS.md`
  - `docs/failsafe.md`
  - `failsafe/README_GOLDEN.txt`

## Update 2026-02-22 (UI Text/Glyph Reliability Fixes)
- Restored visible `LOG HZ` controls in settings by switching from text `+/-` to explicit drawn up/down arrow icons.
- Fixed help popup character loss by completing font map coverage in `src/text5x7.c`:
  - added missing `J` and `Q` glyphs,
  - normalized lowercase letters to uppercase before glyph lookup so full A-Z is available.
- Verification:
  - `./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (5x7 Font Completeness Fix: Missing Q and J)
- Root cause for missing help text letters was incomplete 5x7 font mapping in `src/text5x7.c`:
  - `Q` glyph was not defined or mapped,
  - `J` glyph was not defined or mapped,
  - lowercase handling was partial (only a few letters mapped).
- Fix applied:
  - added `GLYPH_J` and `GLYPH_Q`,
  - added `J` and `Q` switch mappings,
  - normalized all lowercase letters to uppercase before glyph lookup, ensuring full A-Z coverage from a single glyph set.
- Verification:
  - `./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Help Popup Missing Character Render Fix)
- Fixed help popup text rendering where multiple characters were missing across pages on the board font:
  - rewrote help-page strings to plain uppercase ASCII wording with reduced symbol-heavy punctuation,
  - replaced slash and symbol-heavy phrasing with simple words to avoid unsupported glyph fall-through in panel text rendering.
- Updated help page header to `PAGE 1 OF 2` / `PAGE 2 OF 2` for consistent visible character set.
- Verification:
  - `./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Settings UI: LOG HZ Up/Down Icons Restored)
- Fixed missing visual controls in `LOG HZ` setting row:
  - replaced `+` / `-` text rendering with explicit drawn arrow icons (down on decrement button, up on increment button),
  - avoids font-glyph visibility issues and keeps controls consistent with touch-target semantics.
- Verification:
  - `./tools/build_frdmmcxn947.sh` (PASS)
  - `./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (LOG HZ Drives Flash Record Rate + Buffered Alert Capture)
- Implemented recorder cadence coupling to UI `LOG HZ` selection:
  - flash record/write loop now uses dynamic period from `ClampLogRateHz(s_log_rate_hz)`:
    - `1 Hz`, `5 Hz`, `10 Hz`, `20 Hz`, `30 Hz`, `40 Hz`, `50 Hz`.
  - replaced fixed-period recorder gate with dynamic catch-up loop (`while (recplay_tick_accum_us >= recplay_period_us)`).
- Improved flash evidence capture for alert context:
  - recorder now consumes buffered alert window (`ConsumeAlertCaptureWindow`) at write time,
  - persisted `anomaly_score_pct`, `alert_status`, and `alert_reason_code` represent worst/highest-priority state seen in the capture interval, not only instantaneous frame state.
- Existing buffered sensor peak capture remains active for accel/gyro/mag log+record windows.
- Verification:
  - `./tools/build_frdmmcxn947.sh` (PASS)
  - `./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Adaptive False-Positive Reduction Tuning)
- Implemented warning/fault anti-chatter logic to reduce over-triggering during ordinary handling/tilt:
  - added persistence gates before status elevation:
    - fault candidates require sustained condition (~167 ms),
    - hard-limit warnings require sustained condition (~250 ms),
    - predictive/score/watch warnings require sustained condition (~700 ms to 1 s).
  - added score hysteresis (separate enter/exit thresholds) so score warnings/faults do not chatter around threshold edges.
- Added adaptive-baseline freeze control in anomaly engine:
  - adaptive baseline updates pause during active warning/fault windows,
  - adaptation remains frozen during a stable-normal recovery window (~8 s), then resumes automatically.
- Updated generated profile score thresholds for calmer default behavior:
  - `EIL_ALERT_WARN`: `0.18`
  - `EIL_ALERT_FAIL`: `0.35`
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Tilt vs Impact Retune)
- Addressed reported behavior: tilt warnings were too eager while hard bangs could be missed.
- Runtime retune applied:
  - tilt warning now requires stronger/lower-noise posture evidence:
    - x/y tilt component >= `1000 mg`,
    - z component still present (>= `350 mg`),
    - low dynamics gate (`jerk <= 500 mg`, gyro peak <= `300 dps`).
  - erratic/impact detection now includes explicit accel peak path:
    - triggers on `jerk >= 2200 mg`, or accel axis peak >= `2800 mg`, or gyro+jerk combo.
  - added short impact latch (`~250 ms`) so transient bangs survive decision cadence.
  - impact warning persistence reduced to `~125 ms` so impact warnings can mature quickly.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Impact Warning Maturation Fix)
- Addressed issue where hard bang appeared on graph but warning did not post.
- Runtime change:
  - `ERRATIC_MOTION` warning now matures immediately once impact condition is detected (no additional persistence delay).
  - impact latch window increased to ~`800 ms` so short transients remain eligible through UI decision cadence.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Accel Spike Alert Sync + Horizon Stability Fix)
- Addressed two runtime issues:
  - accel spikes visible on graph without corresponding warning,
  - gyro-sphere horizon line disappearing/reappearing intermittently.
- Runtime fixes:
  - warning/fault accel peak path now evaluates against buffered accel peak windows (capture/log) in addition to instantaneous values, so alerting aligns with graphed spikes.
  - sphere attitude rendering now uses last valid accel attitude when a sample-validity blip occurs, preventing horizon flicker/dropout.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Raw Accel Path for Scope + Bang Alerts)
- Addressed report where gyro sphere/graph responded but accel graph + bang warnings were missing.
- Root cause:
  - accel bang/trace path was relying on low-pass filtered accel state, which can suppress short impacts.
- Runtime fix:
  - added explicit raw accel channels (`s_accel_raw_x/y/z_mg`) from IMU read path,
  - switched accel peak windows and alert accel peak evaluation to raw accel channels,
  - switched scope linear-accel feed to raw accel channels while retaining filtered accel for sphere orientation stability.
- Result target:
  - accel spikes should now appear in graph and trigger bang warning more reliably.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Post-Impact Warning Decay Fix)
- Addressed issue where `BREAK` (impact) transitioned to `SHIFT` and remained stuck instead of returning to normal.
- Runtime retune:
  - lowered anomaly-level to score mapping to reduce score-stickiness in normal/watch states:
    - `WATCH`: `12%` (was `40%`)
    - `MINOR`: `45%` (was `80%`)
    - `MAJOR`: `85%` (was `100%`)
  - tightened score warning exit hysteresis (warn exit now ~85% of enter threshold, not ~67%) so post-event score warnings decay sooner.
  - warning hold timer no longer re-extends repeatedly for same-priority same-reason warnings.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (ANOMALY_WATCH Rest-State Recovery Fix)
- Addressed issue where warning could remain in `WATCH/SHIFT` state for extended time after impact even at rest.
- Runtime change:
  - `ANOMALY_WATCH` no longer elevates to warning unless active motion evidence is present (accel/jerk/gyro activity gate).
  - at-rest watch-level noise now decays to `NORMAL` instead of perpetually reasserting warning.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Temporary Combined State Doc Added)
- Added `docs/TEMP_COMBINED_STATE.md` as a single temporary briefing document that consolidates:
  - project baseline and milestone state,
  - runtime architecture summary,
  - AI/non-AI alert behavior,
  - operator mode/settings model,
  - verified status and next recommended validation step.

## Update 2026-02-22 (Documentation Expansion: AI + System Functions)
- Updated user-facing and engineering docs to fully describe the current runtime behavior:
  - rewritten `README.md` with full architecture, operation flow, and integration instructions,
  - added `docs/AI_RUNTIME_REFERENCE.md` with complete AI/non-AI function inventory,
  - updated `docs/SYSTEM_DESIGN.md` with current alert hold/priority behavior and reference link.
- Scope of documentation now explicitly covers:
  - intelligence-layer logic and reason-code behavior,
  - host firmware responsibilities and control boundaries,
  - operator controls, modes, persistence, and logging evidence model.

## Update 2026-02-22 (Golden/Failsafe Release Cut: GOLDEN-20260222-045031)
- Cut a new timestamped golden artifact and promoted active failsafe from current validated build output:
  - golden tag: `GOLDEN-20260222-045031`
  - golden binary: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260222T045031Z.bin`
  - failsafe active: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
  - sha256: `67b7bc651ba7319196ef462834380ff40c8f30d8202ef1aab42f9715a85b087f`
- Synchronized restore metadata in:
  - `docs/START_HERE.md`
  - `docs/RESTORE_POINTS.md`
  - `docs/failsafe.md`
  - `failsafe/README_GOLDEN.txt`
  - `STATUS.md`

## Update 2026-02-22 (Alert Visibility Hold: Warning/Fault Persistence)
- Added explicit time-based alert hold in frame anomaly application path so transient recoveries do not immediately clear operator warnings.
- Hold behavior:
  - `WARNING` alerts are held for `5s` minimum.
  - `FAULT` alerts are held for `8s` minimum.
  - Held state preserves both status and reason code text while active.
- Severity-priority behavior:
  - higher severity always preempts lower severity (`FAULT` > `WARNING` > `NORMAL`) even if lower-severity hold time remains.
  - when both are `WARNING`, higher-priority warning reasons replace weaker held reasons (limit warnings > predictive warnings > score/watch).
- Implementation notes:
  - hold timer is timebase-driven (`TimebaseNowTicks`) rather than frame-count-driven, so behavior remains stable across UI refresh cadence changes.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (GY Root-Cause Fix: Gyro Buffer Source)
- Root cause found for incorrect/weak `GY` behavior in logs/recorded stream:
  - 100 Hz gyro peak windows (`log` and `capture`) were fed from accel-derived UI orientation fields (`s_ui_gyro_*`) instead of true gyro rate channels.
- Fix:
  - added dedicated live gyro rate channels (`s_live_gyro_x_dps`, `s_live_gyro_y_dps`, `s_live_gyro_z_dps`) sourced directly from IMU gyro registers.
  - rewired gyro peak-window update/consume paths to use those true gyro channels.
  - zeroed live gyro channels when gyro sensor is unavailable to avoid stale carryover.
- Result:
  - `GX/GY/GZ` in buffered logging and flash recording now reflect real gyro rates, independent of accel/sphere orientation mapping.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (GY Verification + Terminal Mapping Fix)
- Verified gyro data path wiring in firmware:
  - sensor read mapping is `OUTX/OUTY/OUTZ` -> `gx/gy/gz` from LSM6-family IMU registers.
  - graph traces `GX/GY/GZ` are sourced from `GaugeRender_SetGyro(gx, gy, gz, valid)`.
- Found and fixed display bug causing operator confusion:
  - terminal `GYR X/Y/Z` text was incorrectly showing accel channels (`gAccel*`) instead of gyro channels (`gGyro*`).
  - updated terminal line to show `gGyroXdps/gGyroYdps/gGyroZdps` (or zero when gyro invalid).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Flash Row Integrity: Fresh Alert/Score Snapshot Per Write)
- Verified external-flash recorder payload includes full row data:
  - timestamp: `ts_ds`
  - alert fields: `alert_status`, `alert_reason_code`, `anomaly_score_pct`
  - sensor channels: accel/gyro/temp/mag/baro/sht/stts
- Fixed stale-frame risk for persisted alert fields:
  - recorder write path now refreshes frame sample immediately before each `ExtFlashRecorder_AppendSampleEx(...)` call.
  - UART `LOG,...AS/RC/SC` line now also uses a freshly computed frame sample each emit cycle.
- Result:
  - alert status, reason code, and score written to flash are synchronized with the current anomaly snapshot at write time (not dependent on last UI redraw timing).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Elapsed Time Width + Gyro Scope + Settings Clear Flash)
- Expanded elapsed-time hour display width:
  - runtime clock now renders as `HHHH:MM:SS` (4-digit hour field),
  - hour count no longer wraps at 24 hours; it increments continuously and clamps at `9999`.
- Scope graph switched to gyro-axis plotting:
  - scope traces now render `GX/GY/GZ`,
  - legend text under scope now uses matching line colors for `GX GY GZ`.
- Added settings-driven manual flash erase with confirm popup:
  - new settings action: `CLEAR FLASH`,
  - tap opens modal confirm (`YES/NO`),
  - confirm executes `ExtFlashRecorder_ClearAll()` and resets runtime/playhead display state.
- UI layout update:
  - settings panel now includes dedicated `FLASH` row,
  - `LOG HZ` row moved down to avoid overlap with new button.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Scope Regression Fix: Restore ACCEL/TEMP + Add GYRO)
- Fixed scope regression where accel/temp traces were unintentionally replaced by gyro-only traces.
- Scope now renders all requested channels together:
  - accel: `AX`, `AY`, `AZ`
  - temperature: `T`
  - gyro: `GX`, `GY`, `GZ`
- Legend now shows gyro labels to the right of accel/temp labels, with matching trace colors.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Gyro Sphere Artifact + Axis Mapping Correction)
- Removed persistent line artifact source in gyro sphere rendering:
  - dropped static frame cross-lines that could appear as stale overdraw artifacts,
  - increased dynamic clear radius before horizon/vector redraw.
- Corrected gyro sphere axis mapping:
  - removed previous X/Y swap in UI feed (`X->X`, `Y->Y` direct mapping).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Scope Trace Feed Fix + Settings Model Text Placement)
- Fixed scope trace feed so gyro traces are driven by true live gyro channels:
  - added dedicated renderer gyro API/state (`GaugeRender_SetGyro`),
  - scope `GX/GY/GZ` no longer reuses accel channels, so accel+gyro traces are distinct.
- Removed gyro-sphere short center line to eliminate persistent white horizontal artifact.
- Moved settings model metadata upward so `MODEL / EIL EXT / MODEL V` lines stay fully inside popup bounds.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Clear-Flash Confirm Deadlock Fix)
- Fixed settings `CLEAR FLASH` flow where confirm did not appear and UI could freeze:
  - clear-flash action now closes settings before opening confirm modal,
  - confirm request force-closes any help/settings/limits popup state before activation.
- Result:
  - `CLEAR FLASH` now shows `YES/NO` confirm reliably and remains touch-responsive.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Confirm Touch Priority + Elapsed Reset on Manual Clear)
- Fixed remaining clear-confirm freeze path in `LIVE` mode:
  - record/clear confirm touch handling is now processed before live-mode timeline blocking,
  - confirms (`YES/NO`) are accepted regardless of run mode.
- Elapsed-time reset enhancement:
  - manual clear (`CLEAR FLASH` confirm YES) now also resets record elapsed counter (`rec_elapsed_ds`),
  - runtime elapsed clock reset remains in place.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Alert Pipeline Simplification + Flash Alert Logging)
- Simplified runtime status architecture to a single canonical alert pipeline:
  - UI no longer falls back to a separate non-AI rule-status path for banner/terminal status.
  - Canonical `sample->ai_status` now drives displayed system state consistently.
- Added explicit per-sample alert reason code generation in anomaly apply path:
  - `ALERT_REASON_*` codes cover accel/temp/gyro limit warnings/failures and score/watch states.
- Updated alert text generation in UI to reason-code mapping (instead of score-band heuristics):
  - examples: `ACCEL WARN`, `TEMP FAIL`, `SCORE WARN`, `WATCH STATE`.
- Extended external-flash sample payload to persist alert context with sensor row data:
  - `anomaly_score_pct`
  - `alert_status`
  - `alert_reason_code`
  - packed into recorder row reserved fields for backward-compatible footprint.
- Extended UART periodic log line fields for diagnostics:
  - added `AS` (alert status), `RC` (reason code), `SC` (score).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Predictive Warning Layer: Orientation/Temp/Motion)
- Added predictive warning conditions on top of existing hard limit checks:
  - orientation risk:
    - `INVERTED` warning when gravity vector indicates upside-down package orientation.
    - `TILTED` warning when lateral tilt is elevated but below hard shock limits.
  - temperature approach risk:
    - `TEMP LOW SOON` when approaching low limit margin.
    - `TEMP HIGH SOON` when approaching high limit margin.
  - motion instability risk:
    - `ERRATIC MOTION` warning using acceleration jerk + gyro trend logic for possible handling damage onset.
- Added new reason codes:
  - `ALERT_REASON_INVERTED_WARN`
  - `ALERT_REASON_TILT_WARN`
  - `ALERT_REASON_TEMP_APPROACH_LOW`
  - `ALERT_REASON_TEMP_APPROACH_HIGH`
  - `ALERT_REASON_ERRATIC_MOTION`
- UI alert detail text now renders these predictive causes directly.
- Predictive warnings are warning-level supervisor signals and do not replace hard fail safety checks.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (100Hz Accel Buffering + Interval Peak Capture)
- Added dedicated 100 Hz accel sampling loop (`ACCEL_BUFFER_SAMPLE_PERIOD_US = 10000`) decoupled from UI render cadence.
- Implemented dual peak windows for accel channels:
  - log window peak (`AX/AY/AZ`) consumed on each `LOG HZ` emit interval,
  - record window peak (`AX/AY/AZ`) consumed on each flash capture interval.
- Peak algorithm:
  - signed value with maximum absolute magnitude per axis is retained for each interval window.
  - windows reset on consume, then refill from subsequent 100 Hz samples.
- Result:
  - short impact spikes between 10/20/50 Hz logging and 10 Hz recording intervals are preserved in emitted/logged samples.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Gyro + Magnetometer Interval Peak Buffering)
- Extended interval-peak capture windows to include:
  - gyro channels (`GX/GY/GZ`)
  - magnetometer channels (`MX/MY/MZ`)
- Buffering behavior:
  - 100 Hz sampling loop updates accel/gyro/mag peak windows.
  - log path consumes log-window peaks at configured `LOG HZ` cadence.
  - flash record path consumes capture-window peaks at record cadence.
- Updated UART telemetry line to emit buffered magnetometer values:
  - now includes `MX`, `MY`, `MZ`.
- Confirmed scope limitation retained by design:
  - temperature and barometer are not interval-peak buffered (kept as direct sampled values).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Reason Label Rename: SHIFT/BREAK)
- Updated score-driven alert labels for clearer operator language:
  - `ALERT_REASON_SCORE_WARN` text: `SHIFT`
  - `ALERT_REASON_SCORE_FAIL` text: `BREAK`
- Underlying reason codes and trigger logic are unchanged; only displayed labels were updated.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Golden/Failsafe Refresh Before Alert-Pipeline Simplification)
- Cut fresh local golden and promoted active failsafe from current build output:
  - golden tag: `GOLDEN-20260222-032039`
  - golden binary: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260222T032039Z.bin`
  - failsafe active: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
  - sha256: `a27524b891f037aa1c4602cd0d5635b49deae15d221cd619b1e35381abaefc8d`
- Purpose: lock an operator-verified restore point before consolidating alert/status architecture.

## Update 2026-02-22 (LCD Fill Chunk Buffer + Golden/Failsafe Refresh)
- Implemented RAM chunk-buffered LCD rectangle fill path in `src/par_lcd_s035.c`:
  - added `EDGEAI_LCD_FILL_CHUNK_PIXELS` static chunk buffer
  - switched full-screen fill to use rectangle fill path
  - reduced per-line area-select overhead by selecting area once and streaming pixels in chunks
- Build and flash verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)
- New restore point cut from buffered build:
  - golden tag: `GOLDEN-20260222-020527`
  - golden binary: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260222T020527Z.bin`
  - failsafe active: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
  - sha256: `ba344ca335e1c67cbc842425b7bf017d9432ad2ae8ca8b61fc7833d94683fc87`

## Update 2026-02-22 (LCD Responsiveness Hotfix)
- User-reported regression: slower display updates and touch response after buffered fill rollout.
- Root cause: `par_lcd_s035_fill_rect()` repopulated a large color chunk buffer on every call, including many tiny UI rectangles each frame.
- Fix in `src/par_lcd_s035.c`:
  - reduced `EDGEAI_LCD_FILL_CHUNK_PIXELS` from `2048` to `512` (shorter DMA bursts),
  - added cached-color chunk reuse so fill buffer is repopulated only when color changes.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Timeline Layout + Scope Density Cleanup)
- User-reported UX regression:
  - timeline controls looked squished/stacked,
  - live vs play/record states were visually confusing,
  - scope graph was over-dense with too many overlapping traces.
- Fixes in `src/gauge_render.c`:
  - removed timeline/scope overlap by setting `TIMELINE_Y1 = SCOPE_Y - 2`,
  - shortened record button label from `RECORD` to `REC`,
  - simplified scope rendering to core channels only: `AX`, `AY`, `AZ`, and `T`.
- Legend text under scope now matches plotted channels (`AX AY AZ T`).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (LCD Ghosting/Touch Regression Recovery)
- User-reported regression after previous buffer optimization iterations:
  - duplicate/ghost UI elements (`AI ON/OFF`, timeline controls, traces),
  - reduced/unstable touch interaction.
- Root cause: rectangle fill path used multi-chunk writes against a single selected area, which is not stable for this LCD/controller flow in this firmware path.
- Fix in `src/par_lcd_s035.c`:
  - removed chunk-stream rectangle fill path,
  - restored deterministic line-by-line rectangle fill (one `ST7796S_WritePixels` per row with explicit area select).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Import `package_shipping_monitor` + Settings Model Name)
- Imported latest exported EIL profile package into firmware:
  - source: `.../embedded-intelligence-layer/.tmp_export_validation/package_shipping_monitor_export_2026-02-22T02-52-35-052Z/model.config.json`
  - command: `python3 tools/import_eil_profile.py --model <...>/model.config.json --out src/eil_profile_generated.h`
  - active imported model name: `package_shipping_monitor`
- Added model-name propagation from profile to UI:
  - new API: `EilProfile_GetModelName()` in `src/eil_profile.h` / `src/eil_profile.c`
  - new API: `GaugeRender_SetModelName(const char *model_name)` in `src/gauge_render.h` / `src/gauge_render.c`
  - called from startup in `src/edgeai_package_transport_anomaly_demo.c` after LCD init
- Settings popup now shows active model name on first page (under `SETTINGS` title).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Settings Header Visibility Fix + Extension Version)
- User feedback: model name still not visible in settings.
- Root cause: settings header used raw lowercase/underscore text, which can render poorly with current small UI font.
- Fixes:
  - settings header now uses labeled, uppercase-safe strings:
    - `MODEL: <MODEL_NAME>`
    - `EIL EXT: <EXT_VERSION>`
    - `MODEL V: <MODEL_VERSION>`
  - added sanitization in renderer to normalize model/version strings for reliable glyph rendering.
  - extended generated/imported profile metadata to include:
    - `EIL_MODEL_VERSION`
    - `EIL_EXTENSION_VERSION`
  - added getters:
    - `EilProfile_GetModelVersion()`
    - `EilProfile_GetExtensionVersion()`
  - startup now passes all three profile fields into UI via:
    - `GaugeRender_SetProfileInfo(...)`
- Files changed:
  - `tools/import_eil_profile.py`
  - `src/eil_profile_generated.h`
  - `src/eil_profile.h`
  - `src/eil_profile.c`
  - `src/gauge_render.h`
  - `src/gauge_render.c`
  - `src/edgeai_package_transport_anomaly_demo.c`
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (AI Toggle Settings-Only)
- Updated UI/control flow so AI enable/disable is no longer touch-toggleable from the main screen.
- AI mode is now controlled only from Settings:
  - settings row labels updated to `AI ON` and `AI OFF` in `src/gauge_render.c`
  - settings selection state remains in sync with current AI enable state
  - settings actions map to explicit runtime calls:
    - `AI ON` -> `PowerData_SetAiAssistEnabled(true)` and `AI_SET,ON`
    - `AI OFF` -> `PowerData_SetAiAssistEnabled(false)` and `AI_SET,OFF`
- Removed now-unused main-screen AI touch helper from:
  - `src/edgeai_package_transport_anomaly_demo.c` (`TouchInAiPill`)
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Settings AI Button Order)
- Reordered settings AI controls for operator preference:
  - left button is now `AI OFF`
  - right button is now `AI ON`
- Selection highlight and runtime action mapping were updated to match this layout.
- Files changed:
  - `src/gauge_render.c`
  - `src/edgeai_package_transport_anomaly_demo.c`
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Train/Live Labels + Persistent Boot Settings)
- Restored readable settings mode labels in popup:
  - `ADAPT`, `TRAIN`, `LIVE` (replacing `M1`, `M2`, `M3`)
  - help text updated to `SET MODE: ADAPT/TRAIN/LIVE`
- Added persistent UI settings storage in external flash metadata sector:
  - saved fields: anomaly mode, sensitivity tune, AI on/off
  - values now reload and apply at boot (`UI_CFG_LOAD` log on restore)
- Save-on-change wiring added for:
  - mode changes
  - sensitivity changes
  - AI OFF/ON changes
- Files changed:
  - `src/gauge_render.c`
  - `src/ext_flash_recorder.h`
  - `src/ext_flash_recorder.c`
  - `src/edgeai_package_transport_anomaly_demo.c`
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Settings Label/Selection Alignment)
- Refined settings popup row alignment in `src/gauge_render.c`:
  - row labels (`MODE`, `SENS`, `AI`) now share a fixed label column
  - each label is vertically centered with its corresponding selection row
- This improves readability and makes label-to-control association explicit.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Mode Select Close Behavior)
- Updated settings mode selection behavior in `src/edgeai_package_transport_anomaly_demo.c`:
  - choosing `ADAPT`, `TRAIN`, or `LIVE` now closes the settings popup immediately.
- This avoids the follow-up close interaction issue observed after selecting `LIVE`.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Settings UX + Limits Controls)
- Reworked settings popup to reduce crowding and improve readability:
  - split rows into `MODE` (`ADAPT` / `TRAINED`) and `RUN` (`TRAIN` / `LIVE`)
  - kept `SENS` and `AI` rows with cleaner alignment
  - added `LIMIT` row with tappable controls:
    - `G` max limit
    - `TEMP LOW`
    - `TEMP HIGH`
    - `GYRO` limit
- Added persistent storage/load for expanded UI settings:
  - mode, tune, run state, ai state
  - g/temp/gyro limits
- Added runtime limit gating in anomaly output path:
  - exceeding one configured limit forces `WARNING`
  - exceeding multiple limits forces `FAULT`
- Files changed:
  - `src/gauge_render.h`
  - `src/gauge_render.c`
  - `src/ext_flash_recorder.h`
  - `src/ext_flash_recorder.c`
  - `src/edgeai_package_transport_anomaly_demo.c`
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Limits Layout Readability Fix)
- Fixed limits-row overlap/crowding in settings popup:
  - moved limits controls into a 2x2 grid (`G`, `TL`, `TH`, `GY`)
  - widened limit buttons and increased spacing
  - increased settings panel height so bottom hint text no longer collides
- Files changed:
  - `src/gauge_render.h`
  - `src/gauge_render.c`
  - `src/edgeai_package_transport_anomaly_demo.c` (touch hit-map aligned to new 2x2 layout)
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (G Warn/Fail + Temp Row Fix)
- Implemented separate acceleration thresholds for package shock detection:
  - `GW` (g-warn) default: `12.0 g`
  - `GF` (g-fail) default: `15.0 g`
- Limits controls updated and stabilized:
  - first row: `GW` and `GF`
  - second row: `TL` and `TH` (temp low/high now on the same row)
  - third row: `GY` (gyro limit)
- Runtime alert mapping now uses warn/fail semantics:
  - accel >= `GF` => `FAULT`
  - accel >= `GW` => `WARNING`
  - temp out-of-range/gyro threshold continue to contribute warning/fault behavior
- Updated persistence format to store/reload:
  - mode, tune, run state, ai state
  - `GW`, `GF`, `TL`, `TH`, `GY`
- Files changed:
  - `src/gauge_render.h`
  - `src/gauge_render.c`
  - `src/edgeai_package_transport_anomaly_demo.c`
  - `src/ext_flash_recorder.h`
  - `src/ext_flash_recorder.c`
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Per-Limit Up/Down Controls)
- Added explicit decrement/increment behavior for every settings limit control:
  - left side of each limit button = decrease (`-`)
  - right side of each limit button = increase (`+`)
- Controls now support:
  - `GW` (g warn)
  - `GF` (g fail)
  - `TL` (temp low)
  - `TH` (temp high)
  - `GY` (gyro)
- Range clamps enforced (no wraparound) and threshold consistency is maintained (`GF > GW`, `TH > TL`).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Arrow Markers For Limit Controls)
- Updated settings limit controls visual markers from `- / +` to `v / ^` for clearer directional intent.
- File changed:
  - `src/gauge_render.c`
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Settings Responsiveness + Real Arrow Icons)
- Replaced text-based arrow markers with geometric arrow primitives (line-drawn icons), eliminating dependency on font glyph support.
- Reduced modal redraw cost by changing popup modal base from full-screen repaint to popup-region dirty redraw only.
- Result: improved touch responsiveness and reduced visible flashing while interacting with Settings.
- Files changed:
  - `src/gauge_render.c`
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Compass Disabled)
- Removed compass heading presentation from UI due unreliable heading tracking.
- Compass widget draw path is now disabled and MAG terminal line no longer prints heading (`HDG`).
- Magnetometer sensor acquisition remains available for future validated heading implementation.
- Files changed:
  - `src/gauge_render.c`
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-21 (EIL Adaptive Model Integration Slice 1)
- Added first EIL model-profile integration path in firmware:
  - `src/eil_profile_generated.h`
  - `src/eil_profile.h`
  - `src/eil_profile.c`
- Added project-local importer script to map EIL `model.config.json` into firmware constants:
  - `tools/import_eil_profile.py`
- Integrated profile-based anomaly scoring in runtime:
  - `src/edgeai_package_transport_anomaly_demo.c`
  - anomaly score now uses weighted channel aggregation (`AX/AY/AZ/TEMP`) driven by imported model weights
  - alert `WARNING`/`FAULT` now use imported `alertThresholds.warn/fail` from EIL profile
- Build verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-21 (On-Board Train/Record/Play/Live Closed Loop)
- Updated runtime workflow in `src/edgeai_package_transport_anomaly_demo.c` so training can complete on-device without CSV export/import:
  - Entering `RECORD` now forces non-live training capture path.
  - Exiting `RECORD` in trained-monitor mode no longer clears training if fit is incomplete.
  - If replay ends before training completes, playback auto-restarts to continue fitting from recorded data.
  - When training reaches ready state, runtime auto-promotes to `LIVE` monitoring (`AI_TRAIN: complete_live`).
  - `LIVE` action in settings now avoids resetting trained model when already in trained-monitor mode.
- Build verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-21 (Record/Stop Confirmation UX Tightening)
- Updated timeline control behavior to match operator flow requirements:
  - Selecting `TRAIN` in settings no longer starts recording immediately.
  - `RECORD` now always requires explicit confirmation before starting and erasing stored data.
  - While recording, the left timeline button label changes from `PLAY` to `STOP`.
  - Pressing `STOP` opens a dedicated stop-confirm popup before exiting record mode.
- Runtime integration:
  - added `GaugeRender_ConsumeRecordStopRequest()` and stop-confirm action routing from renderer to app loop.
  - maintained existing replay restart behavior for `PLAY` when already paused.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-21 (Touch + Training State Responsiveness)
- Addressed operator feedback on slow touch/training-state visibility:
  - Reduced touch poll delay from `5000 us` to `2000 us` in `src/edgeai_package_transport_anomaly_demo.c`.
  - `TRAIN` selection now remains visibly selected in settings even before recording starts.
  - Alert banner now shows `TRAINING` when train mode is armed and not yet recording.
  - Terminal mode line now reports `TRAIN` in this armed state (instead of `PLAY`).
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-21 (Train-Armed Idle Freeze Until Record)
- Added explicit train-armed idle behavior in `src/edgeai_package_transport_anomaly_demo.c`:
  - when `TRAIN` is selected and `RECORD` is not active, runtime remains idle.
  - no auto-playback restart in this state.
  - gyro/aux/temp live updates are held until `RECORD` is confirmed.
  - entering `RECORD` clears idle freeze and starts capture/training as expected.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-21 (STOP Visual State Color)
- Updated timeline left button styling in `src/gauge_render.c`:
  - `PLAY` keeps green background.
  - `STOP` now renders with blue background and blue-tinted text for clearer active-record indication.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-21 (Suppress Warning Prefix For Normal Tracking)
- Updated alert banner rendering in `src/gauge_render.c`:
  - when detail text is `NORMAL TRACKING`, the `WARNING` title is suppressed.
  - banner now shows only `NORMAL TRACKING` text in that case.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-18 (Golden/Failsafe Refresh - 20:12:05Z)
- Added an explicit README notice that this project is work-in-progress and not complete code.
- Cut a new timestamped golden artifact and promoted active failsafe from current build output:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260218T201205Z.bin`
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- sha256 (golden + failsafe + current build):
  - `ef3eb2e77a8f8c30974f11ac4aec578da059722a1bce267713a9abfaf3d40167`
- Documentation synchronized in:
  - `README.md`
  - `docs/START_HERE.md`
  - `docs/PROJECT_STATE.md`
  - `docs/RESTORE_POINTS.md`
  - `docs/failsafe.md`
  - `failsafe/README_GOLDEN.txt`
  - `STATUS.md`
  - `docs/COMMAND_LOG.md`

## Update 2026-02-18 (Golden/Failsafe Refresh - 20:03:35Z)
- Validated runtime reported working and cut new golden/failsafe artifacts from current build output:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260218T200335Z.bin`
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- sha256 (golden + failsafe + current build):
  - `fddffba4f9f21f96227b834fe4a7564fabe6fbed3df874082265ef3162cfe5b7`
- Documentation synchronized in:
  - `docs/START_HERE.md`
  - `docs/PROJECT_STATE.md`
  - `docs/RESTORE_POINTS.md`
  - `docs/failsafe.md`
  - `failsafe/README_GOLDEN.txt`
  - `STATUS.md`
  - `docs/COMMAND_LOG.md`

## Update 2026-02-18 (Golden/Failsafe Refresh - 17:27:44Z)
- Cut a new timestamped golden artifact and promoted active failsafe from current validated build output:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260218T172744Z.bin`
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- sha256 (golden + failsafe + current build):
  - `0e8432b5879efefe2977907e3ac6ec5f778e641f4f3f2d7b79b584eee059f25c`
- Documentation synchronized in:
  - `docs/START_HERE.md`
  - `docs/PROJECT_STATE.md`
  - `docs/RESTORE_POINTS.md`
  - `docs/failsafe.md`
  - `failsafe/README_GOLDEN.txt`
  - `STATUS.md`
  - `docs/COMMAND_LOG.md`

## Update 2026-02-17 (System Design + New Golden/Failsafe Baseline - 23:30:44Z)
- Added comprehensive architecture/process/sensor design documentation:
  - `docs/SYSTEM_DESIGN.md`
- Wired shield sensor-hub runtime support and UI integration status finalized:
  - `LIS2MDL` (mag), `LPS22DF` (baro), `SHT40` (humidity + temp), `STTS22H` (temp)
  - terminal compact environment line now `B H S` only
  - terminal `TEMP` and left temp bargraph now prioritize shield temperature (`STTS22H -> SHT40 -> board temp`)
- Cut a new timestamped golden artifact and promoted active failsafe from current validated build output:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260218T172744Z.bin`
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- sha256 (golden + failsafe + current build):
  - `33398a0634891d6346019d018a01e99f9361b9d765e5b81752451489e5f23f9a`
- Documentation synchronized in:
  - `docs/START_HERE.md`
  - `docs/SYSTEM_DESIGN.md`
  - `docs/RESTORE_POINTS.md`
  - `docs/failsafe.md`
  - `failsafe/README_GOLDEN.txt`
  - `STATUS.md`
  - `docs/TODO.md`
  - `docs/COMMAND_LOG.md`

## Update 2026-02-17 (Shield Aux Sensors Integrated)
- Added shield auxiliary sensor pipeline on shared shield I2C bus:
  - LIS2MDL magnetometer
  - LPS22DF barometer
  - SHT40 humidity + temperature
  - STTS22H temperature (address probe set)
- Wired new terminal telemetry lines:
  - `MAG X/Y/Z`
  - compact environmental line (`BARO`, `RH`, `SHT`, `STTS`)
- Added new renderer setters and app-side periodic auxiliary sensor polling (`500 ms`).
- Build/flash verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `UYLKOJI11H2B3`)

## Update 2026-02-17 (Golden/Failsafe Refresh From Current Code - 22:23:44Z)
- Rebuilt current source from:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
- Cut a new timestamped golden artifact and promoted active failsafe from the same built binary:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260218T172744Z.bin`
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- sha256 (golden + failsafe + current build):
  - `e480f4d64645d3b60d78e2463ae0e3e602f41db7388285d405e2d7f086d17e9f`
- Documentation synchronized in:
  - `docs/START_HERE.md`
  - `docs/PROJECT_STATE.md`
  - `docs/RESTORE_POINTS.md`
  - `docs/failsafe.md`
  - `failsafe/README_GOLDEN.txt`
  - `STATUS.md`
  - `docs/COMMAND_LOG.md`

## Update 2026-02-17 (Golden/Failsafe Refresh From Current Code)
- Rebuilt current source from:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
- Cut a new timestamped golden artifact and promoted active failsafe from the same built binary:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260218T172744Z.bin`
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- sha256 (golden + failsafe + current build):
  - `408422db46e4caf20212f61ffda9e28629ed10a09ee85cd9220dfdf771ec13e4`
- Documentation synchronized in:
  - `docs/START_HERE.md`
  - `docs/RESTORE_POINTS.md`
  - `docs/failsafe.md`
  - `failsafe/README_GOLDEN.txt`
  - `docs/COMMAND_LOG.md`

## Current Runtime Handoff
- Detailed behavior and open-defect handoff is maintained in:
  - `docs/CODER_HANDOFF.md`
- Current blocker:
  - settings/help popup close path still intermittently freezes board on hardware.
- Current UX defect:
  - popup layering can desync during transitions and appear behind graph/terminal/sphere.

## Update 2026-02-17 (Popup/Replay Reliability Fix Pass)
- Applied three targeted fixes:
  - `src/gauge_render.c`: blocked timeline/record touch handling while help/settings popup is visible.
  - `src/power_data_source.c`: on replay profile switch, reseed derived AI state when in replay mode; avoid forcing replay sample into live-override mode.
  - `src/real_telemetry.c`: aligned `TELEMETRY_OPAMP_GAIN` with actual configured OPAMP gain (1x) to fix current scaling math if live telemetry path is enabled.
- Build verification:
  - stale-cache build dir mismatch observed for old `mcuxsdk_ws/build_anomaly` path after project rename.
  - compile verification passed with fresh build dir:
    - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
- Flash verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh`
  - PASS on probe `2PZWMSBKUXU22`.
- Hardware popup stress validation is still pending for final close-cycle confirmation.

## Update 2026-02-17 (Modal Freeze Mitigation Pass)
- Added additional modal-stability hardening for popup close/open transitions:
  - `src/gauge_render.c`
    - fast gyro path now exits immediately while any modal is active (`help/settings/record-confirm`), preventing mixed-layer draw contention.
    - modal-close cleanup now uses unified modal state transition logic, so closing help/settings also triggers static dashboard recompose before returning to dynamic layers.
  - `src/edgeai_package_transport_anomaly_demo.c`
    - main loop now skips `GaugeRender_DrawGyroFast()` when modal is active.
- Build/flash verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-17 (Clock Priority Isolation During Modal)
- Incorporated additional modal isolation based on hardware report that runtime clock redraw remained active over help/settings:
  - `src/gauge_render.c`: moved runtime clock redraw block to execute only after help/settings modal early-return.
- Effect:
  - No periodic clock layer writes while help/settings popup is visible.
  - Popup composition is now modal-only during help/settings display.
- Build/flash verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh` (PASS, probe `2PZWMSBKUXU22`)

## Expected Build Output
- `mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-16
- Created standalone project scaffold from proven FRDM-MCXN947 anomaly demo structure.
- Renamed SDK overlay/build target and app entrypoint to `edgeai_package_transport_anomaly_demo`.
- Initialized runbook/state/restore docs for first bring-up and future golden release.

## Update 2026-02-17 (Golden Restore Point Refresh - Local Only)
- Created a new timestamped golden artifact from the current build output:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260218T172744Z.bin`
- Refreshed active failsafe image to the same binary:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- sha256 (golden + failsafe + current build):
  - `e40c8416da2f125814aaf4ad886aad484b5ecbe879b0fb1e5f54a11275d7a1d2`
- Documentation synchronized in:
  - `docs/START_HERE.md`
  - `docs/RESTORE_POINTS.md`
  - `docs/failsafe.md`
  - `docs/TODO.md`
  - `docs/COMMAND_LOG.md`
- Source control note:
  - No push requested; no remote operations performed.

## Update 2026-02-16 (Workspace + Build Validation)
- Ran `./tools/setup_mcuxsdk_ws.sh` to initialize the local west workspace.
- Workspace sync reported non-blocking failures for optional repos (`canopennode`, `mcux-sdk-middleware-mpp`, `metering`, `g2d_dpu`, `qcbor`, `touch`).
- Verified project build succeeded with:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
- Produced binary:
  - `mcuxsdk_ws/build_anomaly/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-16 (Build Path Normalization)
- Fixed `tools/build_frdmmcxn947.sh` and `tools/flash_frdmmcxn947.sh` to normalize relative `BUILD_DIR` values.
- This prevents accidental nested paths like `mcuxsdk_ws/mcuxsdk_ws/build_anomaly`.
- Re-ran build successfully; binary output is now at:
  - `mcuxsdk_ws/build_anomaly/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-16 (Spacebox Background + Flash)
- Added full-screen LCD background image generated from `docs/spacebox.jpg`.
- Generated RGB565 asset header:
  - `src/spacebox_bg.h`
- Integrated background draw into static dashboard render:
  - `src/gauge_render.c`
- Rebuilt and flashed successfully:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Scope Enforcement Rebuild/Flash)
- Re-verified repository scope and found no cross-project path references in this repo.
- Rebuilt and reflashed using only project-local paths and artifact:
  - `mcuxsdk_ws/build_anomaly/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-16 (User Requested Rebuild + Flash)
- Executed fresh rebuild and flash from project-local workflow.
- Commands:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`
- Result: build PASS, flash PASS.

## Update 2026-02-16 (Removed Big Gauge + Text)
- Removed center/main gauge graphics and the associated center `VAC` text rendering path in `src/gauge_render.c`.
- First rebuild attempt failed under `-Werror` due an unused helper left after removal; helper was deleted and rebuild succeeded.
- Flashed successful build from project-local path using:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Removed Elapsed + Profile Boxes)
- Removed elapsed-time box/text render path from dashboard UI (`src/gauge_render.c`).
- Removed wired/outlet profile switch box/text render path from dashboard UI (`src/gauge_render.c`).
- Rebuilt and flashed from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Right Column Edge Alignment)
- Shifted far-right column UI blocks further right to align with screen edge by updating layout constants in `src/gauge_render.c`:
  - `SCOPE_X: 324 -> 351`
  - `TERM_X: 324 -> 351`
- Updated associated right-side connector guide lines to match new column position.
- Rebuild result: PASS.

## Update 2026-02-16 (Flash Right-Column Alignment Build)
- Flashed latest build after right-column edge alignment update using project-local flash script.

## Update 2026-02-16 (Left Column Edge Alignment)
- Shifted first-column UI further left to align with screen edge in `src/gauge_render.c`:
  - `BAR_X0: 22 -> 0`, `BAR_X1: 47 -> 25`
  - `MID_TOP_CX: 98 -> 76`, `MID_BOT_CX: 98 -> 76`
  - `BATT_X: 48 -> 26`
- Updated left-side connector guide lines to match the new positions.
- Updated temperature-strip right bound to be relative (`BAR_X0 + 96`) so it follows column shifts.
- Rebuild result: PASS.

## Update 2026-02-16 (Flash Edge-Aligned Layout Build)
- Flashed latest edge-aligned dashboard layout build (left and right column shifts) via project-local flash script.

## Update 2026-02-16 (Removed Upper-Button Horizontal Bar)
- Removed the horizontal dark bar layer behind the upper timeline buttons in `src/gauge_render.c`.
- Left/right timeline buttons remain rendered.
- Rebuild result: PASS.

## Update 2026-02-16 (Flash Upper-Bar Removal Build)
- Flashed latest build after removing the horizontal dark bar behind upper timeline buttons via project-local flash script.

## Update 2026-02-16 (Rollback To Previous Build State)
- Reverted the last UI removal by restoring the timeline background bar behind upper buttons.
- Rebuilt and flashed to return hardware behavior to the prior build state.


## Update 2026-02-16 (Golden Restore + Failsafe Freeze)
- Published first golden restore point and promoted it to active failsafe.
- Golden binary:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260218T172744Z.bin`
- Active failsafe binary:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- sha256:
  - `955da19d95a17fc8b0635e4923feea63873b67065eeaa5cb3f8cc73d51ade3e6`
- Runtime baseline frozen:
  - sphere accelerometer gauge + fast redraw
  - PLAY/RECORD controls
  - AX/AY/AZ/TEMP scope traces with persistent FIFO
  - board digital temp sensor wired into temp gauge and trace

## Update 2026-02-16 (Golden Restore Re-Cut for Git Checkpoint)
- Created a new timestamped golden artifact for this exact Git restore point:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260218T172744Z.bin`
- Kept active failsafe image unchanged and locked:
  - `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- sha256 (golden + failsafe):
  - `955da19d95a17fc8b0635e4923feea63873b67065eeaa5cb3f8cc73d51ade3e6`

## Update 2026-02-16 (On-board Temp Sensor Fix: P3T1755 on I3C1)
- Investigated local MCUX examples and confirmed official flow:
  - `driver_examples/i3c/master_read_sensor_p3t1755`
  - dynamic assignment by `RSTDAA + SETDASA` (static `0x48` -> dynamic `0x08`), then SDR read.
- Updated `src/edgeai_package_transport_anomaly_demo.c` temp path to match that flow:
  - added explicit dynamic-address assignment on I3C1
  - aligned I3C master config with SDK example (`enableOpenDrainStop=false`, `disableTimeout=true`)
  - retained legacy `0x48..0x4B` fallback probe only if dynamic path fails
- Root cause found and fixed:
  - temperature decode math used a 10x-too-large scale
  - corrected conversion to 12-bit `1/16 C` (`raw12 / 16`)
- Runtime UART validation after flash:
  - `TEMP ready dyn=0x08 bus=i3c T=24C`
  - confirms real on-board U6 (`P3T1755DP`) data path is active.

## Update 2026-02-16 (Display C/F + Real Data Proof)
- Updated temperature UI formatting to show Celsius and Fahrenheit together:
  - right terminal line now renders `TEMP XXC YYYF`
  - left temperature bar label now renders `TEMP:XXC/YYYF`
- Added one-time boot validation print from the same I3C read path:
  - `TEMP init raw=0x18 0xf0 -> 24C/75F`
- Rebuilt and flashed successfully; confirms conversion and display are tied to real U6 sensor bytes.

## Update 2026-02-16 (One-Decimal Temp Display)
- Extended temp rendering path to carry tenths-of-degree (`C x10`) from sensor raw bytes.
- Added `GaugeRender_SetBoardTempC10(...)` and wired it from:
  - temp init/update read path
  - playback path (uses `.0` from recorded integer samples)
- Terminal and left bar now render one decimal for both units:
  - terminal: `TEMP 25.5C 77.9F` (example)
  - left bar: `T:25.5C/77.9F`
- Hardware validation after flash showed fresh raw value:
  - `TEMP init raw=0x19 0x90 -> 25C/77F`
  - raw `0x199` implies ~`25.5C`, matching new decimal conversion path.

## Update 2026-02-16 (Sphere + Label Recenter)
- Shifted accelerometer sphere center right by 5% of screen width (`+24 px`).
  - Gyro frame center `cx: 76 -> 100`
  - Gyro dynamic center `cx: 76 -> 100`
- Recentered `ACCEL VECTOR` label using measured text width so it stays aligned with sphere center.
- Rebuilt and flashed successfully.

## Update 2026-02-16 (Sphere Nudge Left by 2.5%)
- Shifted accelerometer sphere center left by 2.5% of screen width (`-12 px`) from prior position.
  - Gyro frame center `cx: 100 -> 88`
  - Gyro dynamic center `cx: 100 -> 88`
- `ACCEL VECTOR` label remains centered to sphere center via text-width centering logic.
- Rebuilt and flashed successfully.

## Update 2026-02-16 (Horizon Tilt Calibration)
- Adjusted gyro horizon-line tilt math to track roll more like an aircraft attitude indicator.
- Previous line tilt used a shallow scale (`nx * span / 3000`) that under-rotated relative to sphere vector movement.
- New line tilt derives from `roll_px` (same roll signal as the marker), scaled by line span:
  - `tilt_long = (roll_px * span) / (r - 18)`
  - `tilt_short = (roll_px * span_short) / (r - 18)`
- Keeps pitch center shift (`y_mid`) unchanged while making horizon rotation visually consistent with board tilt.
- Rebuilt and flashed successfully.

## Update 2026-02-16 (Gyro Edge Artifact Cleanup)
- Fixed residual edge trails around moving horizon/marker by expanding dynamic clear radius in the gyro fast redraw path:
  - dynamic clear fill changed from `r - 11` to `r - 6`
- This ensures prior line/marker pixels near the inner boundary are fully erased each frame.
- Rebuilt and flashed successfully.

## Update 2026-02-16 (Square-Edge Artifact Elimination)
- Addressed remaining square-edge artifacts by changing fast gyro redraw strategy:
  - `GaugeRender_DrawGyroFast()` now redraws the full sphere widget frame plus dynamic overlay each fast cycle.
- This removes stale pixels outside the prior partial redraw mask that could appear as square-edge remnants.
- Rebuilt and flashed successfully.

## Update 2026-02-16 (Refresh Blanking + Battery Demo Lock)
- User reported visible slow blanking during gyro refresh after full-frame fast redraw.
- Updated `src/gauge_render.c` to restore dynamic-only fast redraw in `GaugeRender_DrawGyroFast()` for responsive updates.
- Added line clipping against the sphere circle in dynamic rendering to keep horizon/vector/crosshair pixels inside the round gauge and prevent square-edge artifacts.
- Demo battery indicator is now intentionally pinned to `82%` fill for stable showcase behavior.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (External Flash Packed FIFO + Gyro Headroom)
- Replaced one-sample-per-page recorder with packed page format in `src/ext_flash_recorder.c`:
  - Added page header (`magic`, `count`, `first_seq`) and multiple sample records per page.
  - Implemented circular FIFO write pointer across pages/slots.
  - Kept sector-erase rotation behavior for safe overwrite on wrap.
- Extended stored sample schema to include future gyro channels (`gx/gy/gz`) and `temp_c10`:
  - `src/ext_flash_recorder.h` `ext_flash_sample_t` now carries accel + gyro-ready fields + decimal temp.
  - Added `ExtFlashRecorder_AppendSampleEx(...)` for explicit extended writes.
- Updated runtime loop in `src/edgeai_package_transport_anomaly_demo.c` to record using:
  - `ExtFlashRecorder_AppendSampleEx(s_accel_x_mg, s_accel_y_mg, s_accel_z_mg, 0, 0, 0, s_temp_c10)`
  - Playback now restores `temp_c10` directly for decimal-accurate temp rendering.
- Retention with current flash geometry (512 KiB region, 256-byte pages) is now:
  - 12 samples/page, 2048 pages, 24,576 samples total.
  - At 10 Hz: ~2,457.6 s (~40.96 minutes) in FIFO loop.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (External Flash Max-Depth FIFO Region)
- Removed fixed `512 KiB` cap in `src/ext_flash_recorder.c`; recorder now uses the upper half of detected external NOR:
  - `regionSize = totalSize / 2`
- This keeps separation from lower flash space while maximizing retention depth.
- With FRDM-MCXN947 W25Q64 geometry (8 MiB total, 256-byte pages), FIFO capacity is:
  - recording region: 4 MiB
  - samples/page: 12 (gyro-ready record format)
  - pages: 16,384
  - total samples: 196,608
  - at 10 Hz: 19,660.8 s (~327.68 minutes, ~5.46 hours)
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Default PLAY on Boot)
- Set timeline mode default to PLAY at startup:
  - `src/gauge_render.c`: `gScopePaused` now defaults to `true` and is initialized to `true` in `GaugeRender_Init()`.
- Updated app startup flow to immediately attempt playback when booting in PLAY mode:
  - `src/edgeai_package_transport_anomaly_demo.c`: after initial draw, if `GaugeRender_IsRecordMode()` is false, call `ExtFlashRecorder_StartPlayback()`.
  - Logs `EXT_FLASH_PLAY: ready` when data exists, otherwise `EXT_FLASH_PLAY: no_data`.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (PLAY Press Rewinds Playback)
- Updated timeline touch handling so pressing PLAY while already in PLAY mode generates a playback restart request.
  - `src/gauge_render.c`: `GaugeRender_HandleTouch(...)` now returns `changed=true` for `in_left && gScopePaused`.
- Updated main loop to treat any PLAY timeline event as a rewind action:
  - `src/edgeai_package_transport_anomaly_demo.c`: on timeline change with PLAY mode active, call `ExtFlashRecorder_StartPlayback()` and restart from the oldest sample in current FIFO window.
- Result: each PLAY tap starts playback from beginning of recording window (not current playback position).
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Confirm Before Record + Clear On Start)
- Added a modal confirmation popup when RECORD is pressed from PLAY mode:
  - `src/gauge_render.c` draws `START NEW RECORDING?` with `YES`/`NO` buttons.
  - While popup is active, touch handling is routed to popup buttons.
- RECORD start is now a two-step action:
  - User taps RECORD -> popup opens.
  - User taps YES -> main loop receives record-start request.
- On YES, firmware clears recorder memory before enabling record mode:
  - Added `ExtFlashRecorder_ClearAll()` in `src/ext_flash_recorder.c` and declaration in `src/ext_flash_recorder.h`.
  - Clear path erases the full recorder region (sector-by-sector) and resets FIFO pointers/counters.
  - Record mode starts only on successful clear; on clear failure, firmware stays in PLAY.
- Main loop integration (`src/edgeai_package_transport_anomaly_demo.c`):
  - Blocks AI/profile touch toggles while popup is active.
  - Consumes popup YES request, runs clear, then sets record/play mode explicitly via new gauge-render API.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Record Confirm Freeze + Layer Fix)
- Addressed reported freeze when pressing YES in record-confirm popup:
  - `src/ext_flash_recorder.c`: changed `ExtFlashRecorder_ClearAll()` from full blocking sector erase to fast logical FIFO reset (metadata/pointers/counters reset).
  - This preserves clear semantics for runtime use (old data invalidated immediately) while avoiding long blocking latency on UI thread.
- Addressed popup layer ordering issue:
  - `src/gauge_render.c`: `GaugeRender_DrawGyroFast()` now checks confirm-modal state and redraws popup directly, skipping gyro dynamic draws while modal is active.
  - Ensures confirmation popup remains topmost and not overdrawn by fast refresh.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Recorder Logging/Playback Reliability Fix)
- Root-cause found for short/invalid playback:
  - prior packed-page recorder path rewrote mutable page metadata on NOR flash, causing invalid bit-transition behavior over time and unreliable readback.
- Replaced recorder backend with robust one-record-per-page FIFO format (`REC2`) in `src/ext_flash_recorder.c`:
  - each sample is written once to a fresh page slot;
  - no in-place mutable page metadata updates are required;
  - playback reads now map directly to one sample record per page.
- Kept fast logical clear semantics for record-confirm YES (`ExtFlashRecorder_ClearAll`) to avoid UI freeze.
- Added modal close cleanup in `src/gauge_render.c`:
  - when confirm popup transitions active->inactive, force one static dashboard redraw to clear any stale overlay remnants.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Graph Playhead + REC/PLAY Diagnostics)
- Added vertical scope playhead rendering:
  - `src/gauge_render.c`: draws a vertical head line over the graph (`record=red`, `play=green`).
  - `src/gauge_render.h`: new API `GaugeRender_SetPlayhead(uint8_t position_0_to_99, bool valid)`.
- Wired playhead to real recorder playback state:
  - `src/ext_flash_recorder.h/.c`: added `ExtFlashRecorder_GetPlaybackInfo(...)` and `ExtFlashRecorder_GetRecordInfo(...)`.
  - `src/edgeai_package_transport_anomaly_demo.c`: maps playback offset/count to `0..99` and updates playhead each playback sample.
  - In record mode, playhead is pinned at right edge to indicate write head.
- Added debug logs to verify REC/PLAY internals:
  - `EXT_FLASH_PLAY_INFO: offset=<n> count=<n>`
  - `EXT_FLASH_REC_INFO: count=<n>`
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Battery/Temp Redraw Reliability)
- Addressed missing battery and temperature-related visuals after popup/modal transitions.
- `src/gauge_render.c` changes:
  - force `DrawBatteryIndicatorDynamic(...)` every frame (eliminates stale cache skip cases).
  - on modal-close static redraw, invalidate key cached dynamic state (`gPrevSoc`, bar caches, alert cache) so dependent widgets redraw correctly.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (10 Hz Playback Timing)
- Updated REC/PLAY stepping path to 10 Hz:
  - `src/edgeai_package_transport_anomaly_demo.c`: added dedicated `RECPLAY_TICK_PERIOD_US=100000` branch for recorder append and playback reads.
  - Power-model tick remains at 1 Hz (`POWER_TICK_PERIOD_US=1000000`).
- Increased UI frame refresh to 10 Hz:
  - `DISPLAY_REFRESH_PERIOD_US=100000` for smoother graph and terminal updates during playback.
- Increased scope sample ingestion cadence in fast path:
  - `src/gauge_render.c`: `SCOPE_SAMPLE_TICKS` reduced to `3` (~8.3 Hz at 40 ms fast loop), improving plotted motion smoothness.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (NV Recorder Persistence Across Reboot)
- Implemented durable recorder state recovery on boot in `src/ext_flash_recorder.c`.
- Added a reserved metadata sector at start of recorder region:
  - stores `generation` marker (`META`) for durable clear semantics.
  - `ExtFlashRecorder_ClearAll()` now increments generation and commits metadata so clear state persists across power cycle.
- Boot-time recovery now scans recorder pages for current generation records and reconstructs:
  - `s_sampleCount`
  - `s_oldestIndex`
  - `s_writeIndex`
  - `s_seq`
- Result: recordings are now expected to survive reboot (non-volatile behavior restored in firmware path).
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Playback Timeline Pace Alignment)
- Fixed playback graph/timeline pacing mismatch by aligning scope graph ingestion cadence with 10 Hz REC/PLAY tick.
- `src/gauge_render.c` change:
  - `SCOPE_FAST_STEP_US` updated from `40000` to `100000` so `PushScopeSample()` emits points at the same effective 10 Hz rate as recorder append/read.
- Effect: playback no longer appears to skip ahead of plotted timeline due to UI-side under-sampling.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Playback Graph Follows Timeline)
- Refined scope behavior in PLAY mode to prevent rapid full-window cycling.
- `src/gauge_render.c` changes:
  - PLAY mode sampling now appends only when playback playhead position changes, tying trace progression to timeline progress instead of fast redraw cadence.
  - Restored REC path sampling step to `SCOPE_FAST_STEP_US=40000` with `SCOPE_SAMPLE_PERIOD_US=100000` accumulator behavior for stable average 10 Hz sample ingestion.
- Effect: during playback, graph progression now follows recorded timeline progression and no longer sweeps the full graph window in ~10 seconds unless the recording itself is only ~10 seconds long.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (Timebase Normalization: Record + Playback)
- Normalized core timing domains to a single 10 Hz base (`100000 us`) to keep acquisition, record, playback, graphing, and render pacing aligned.
- `src/edgeai_package_transport_anomaly_demo.c`:
  - `GYRO_REFRESH_PERIOD_US`: `40000 -> 100000` (sphere update + accel acquisition now 10 Hz in RECORD and PLAY modes).
  - `TEMP_REFRESH_PERIOD_US`: `1000000 -> 100000` (board temp capture in RECORD now 10 Hz to match recorder cadence).
- `src/gauge_render.c`:
  - `SCOPE_FAST_STEP_US`: `40000 -> 100000`.
  - Removed playhead-gated sampling path and restored direct time-accumulator-based scope sampling at 10 Hz in both modes.
- Net effect:
  - sensor capture path (for recorded channels), external-flash write/read, graph sample ingestion, and display frame cadence are all synchronized at 10 Hz.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-16 (AI Anomaly Modes Integrated)
- Implemented anomaly-mode core with per-channel classification for `AX`, `AY`, `AZ`, and `TEMP`:
  - `ANOMALY_MODE_ADAPTIVE_BASELINE`
  - `ANOMALY_MODE_TRAINED_MONITOR`
  - `ANOMALY_MODE_STATIC_LIMITS`
- Added new engine module:
  - `src/anomaly_engine.h`
  - `src/anomaly_engine.c`
- Integrated engine into app loop:
  - mode init/set/get wiring
  - training start/stop on record-mode transitions
  - per-tick update from live accel/temp samples
  - mapped anomaly output into runtime frame state for UI/flags
- Integrated terminal rendering for anomaly telemetry:
  - mode/training status line
  - per-channel severity tags for AX/AY/AZ/TEMP
- Build integration:
  - `sdk_example/mcuxsdk_examples_overlay/demo_apps/edgeai_package_transport_anomaly_demo/CMakeLists.txt` now compiles `src/anomaly_engine.c`.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-17 (AI Side `?` Icon Legibility)
- User-reported issue: AI help-side `?` icon pixels appeared garbled after prior icon visibility changes.
- `src/gauge_render.c`:
  - Updated `DrawAiSideButtons(...)` to draw a bold vector-style `?` (line segments + filled dot) instead of a tiny per-pixel bitmap glyph.
- Effect: icon shape is now stable/legible on the LCD and no longer depends on bitmap sampling artifacts.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-17 (Font Upgrade for `*`, `?`, and `AI ON/OFF`)
- User request: use a better font appearance for side icons and AI state label.
- `src/text5x7.c`:
  - Added explicit glyph definitions and mapping for `?` and `*` in the built-in 5x7 font table.
- `src/gauge_render.c`:
  - Added `DrawTextUiCrisp(...)` (no shadow pass) for cleaner high-contrast labels.
  - Updated `DrawAiSideButtons(...)` to render `*` and `?` using font glyphs at scale 2.
  - Updated `DrawAiPill(...)` to render `AI ON/OFF` with scale-aware crisp text (prefers scale 2, falls back to scale 1 if needed).
- Effect: side glyphs and AI label now use consistent font rendering with improved legibility and stable shape.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-17 (Normal Banner Label by Mode)
- User request: while recording, the center normal-status banner should display `RECORDING` instead of `SYSTEM NORMAL`.
- `src/gauge_render.c`:
  - Updated `DrawAiAlertOverlay(...)` so normal-status text resolves to:
    - `RECORDING` when in record mode (`!gScopePaused`)
    - `SYSTEM NORMAL` when in play mode.
  - Added mode (`recording`) to alert visual cache key so toggling play/record forces banner text redraw even when status stays normal.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-17 (Record/Playback Timebase Drift Fix)
- User-reported defect: decisecond clock and rec/play pacing were running effectively ~10x slow under heavier frame workload (decisecond digit advancing at ~1Hz, playback at ~0.1x).
- Root cause:
  - Main-loop periodic schedulers (`recplay`, `power`, `render`, etc.) were advanced using a fixed `TOUCH_POLL_DELAY_US` assumption per loop instead of actual elapsed wall time.
  - As loop work increased, real iteration time exceeded 10ms but scheduler time did not, causing systematic undercount and slow-motion behavior.
- `src/edgeai_package_transport_anomaly_demo.c`:
  - Switched scheduler accumulator updates to measured elapsed loop time from DWT cycle counter conversion.
  - Kept fallback to fixed delay only when cycle timing is unavailable.
  - Converted periodic `if (accum >= period)` blocks to `while` catch-up loops for:
    - power tick
    - rec/play tick
    - board-temp tick
    - accel test log tick
    - render tick
- Effect:
  - Record timestamp (`ts_ds`) and playback stepping now track real elapsed time, restoring expected 10Hz rec/play cadence and correct `hh:mm:ss:ds` progression.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-17 (Post-Timebase-Fix Freeze Guard)
- User-reported regression: raster visible but display appeared frozen after elapsed-time scheduler change.
- `src/edgeai_package_transport_anomaly_demo.c`:
  - Added DWT timing validity guard: if cycle delta is zero/invalid, runtime falls back to fixed loop timing.
  - Added elapsed-loop clamp (`<= 250000 us`) so bad timing input cannot cause runaway catch-up loops and UI starvation.
  - Preserved measured-time scheduling when valid.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-17 (Scheduler Smoothing for Jitter/Slowness)
- User feedback after freeze guard: UI no longer froze but updates became jumpy/slow.
- `src/edgeai_package_transport_anomaly_demo.c`:
  - Kept measured elapsed-time scheduler source.
  - Changed DWT zero-delta handling to one-iteration fallback only (does not permanently disable measured timing).
  - Limited per-loop accumulator backlog to 2 periods for major tasks.
  - Restored single-step periodic dispatch (`if` not `while`) for heavy tasks to prevent burst catch-up stalls:
    - power tick
    - rec/play tick
    - temp tick
    - accel test tick
    - render tick
- Intent/effect:
  - Reduce bursty catch-up behavior that caused visible stutter while preserving corrected timing scale.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-17 (1-Second Cadence Jitter Mitigation)
- User-reported symptom: display response still jittery with uneven pulse roughly once per second.
- `src/edgeai_package_transport_anomaly_demo.c`:
  - Added compile-time switch `EDGEAI_ENABLE_ACCEL_TEST_LOG` (default `0`).
  - Disabled `AccelAxisSelfTestLog()` UART prints by default.
  - Removed periodic `ACCEL_TEST,NOT_READY` print path from the 1-second tick.
- Effect:
  - Eliminates intentional once-per-second blocking `PRINTF` work in the main render loop.
  - Reduces periodic UI cadence disturbance caused by serial output latency.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-17 (STM Shield Gyro Routed To Sphere)
- User request: use STM shield gyro datastream for the sphere widget and rename label to `GYRO`.
- `src/edgeai_package_transport_anomaly_demo.c`:
  - Added shield gyro support on Arduino I2C bus (FLEXCOMM2), probing `0x6A/0x6B` and reading LSM6-family gyro registers.
  - Configured gyro ODR/FS (`CTRL2_G`, `CTRL3_C`) and mapped gyro rates to sphere UI range.
  - Sphere update now uses shield gyro stream when available, with existing accel path as fallback.
- `src/gauge_render.c`:
  - Updated sphere title text from `ACCEL VECTOR` to `GYRO`.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh`

## Update 2026-02-22 (Gyro Sphere Vertically Centered)
- User request: move gyro sphere so it is centered top-to-bottom on the display.
- `src/gauge_render.c`:
  - Changed `GYRO_WIDGET_CY` from a lower-offset expression to `SPACEBOX_BG_HEIGHT / 2` for exact vertical centering.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-22 (Dedicated Limits Popup In Settings)
- User request: add a `LIMITS` button in Settings and move limit edits to a separate larger popup with easier touch targets.
- `src/gauge_render.h`:
  - Added settings limits-button geometry and dedicated limits-popup geometry constants.
  - Added `GaugeRender_SetLimitsVisible(bool)` / `GaugeRender_IsLimitsVisible(void)` APIs.
- `src/gauge_render.c`:
  - Added limits modal state and rendering path (`DrawLimitsPopup`).
  - Replaced inline limits controls in Settings with a single `OPEN LIMITS` button.
  - Added large per-row +/- controls for `G WARN`, `G FAIL`, `TEMP LOW`, `TEMP HIGH`, and `GYRO LIMIT`.
  - Updated modal gating so limits popup blocks fast-path/background interactions consistently.
- `src/edgeai_package_transport_anomaly_demo.c`:
  - Added limits-popup touch handlers (open button, close button, row +/- hit zones).
  - Added `ApplyLimitAdjustment(...)` helper and moved limit edits into limits-popup flow.
  - Updated UI modal arbitration so settings/help/limits are mutually exclusive and persistent settings save still applies after limit changes.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-22 (Limits Popup Freeze Fix + Visible Up/Down Labels)
- User-reported issue after limits-popup rollout: popup opened but adjustment labels were missing and UI appeared frozen.
- Root cause:
  - Main-loop touch gate treated limits popup as a blocking modal in the pre-touch condition, preventing limits-popup touch handlers from running.
- `src/edgeai_package_transport_anomaly_demo.c`:
  - Restored `modal_active` gating to record-confirm only so limits popup remains interactive.
- `src/gauge_render.c`:
  - Updated limits adjustment button text from symbol-only controls to explicit labels:
    - left button: `DOWN`
    - right button: `UP`
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-22 (G WARN/G FAIL Value Rendering Fix + Persistence Confirmation)
- User-reported issue: `G WARN` and `G FAIL` values were blank in limits popup.
- Root cause:
  - Limits popup used floating-point `snprintf("%.1f")` formatting, which is not available in the embedded `nano.specs` printf configuration.
- `src/gauge_render.c`:
  - Replaced float formatting with integer fixed-point formatting for mg->g display (`X.Yg`) for both `G WARN` and `G FAIL`.
- Persistence status:
  - All limit edits (`G WARN`, `G FAIL`, `TEMP LOW`, `TEMP HIGH`, `GYRO LIMIT`) are saved immediately after each change through `SaveUiSettingsIfReady(...)` -> `ExtFlashRecorder_SaveUiSettings(...)`.
  - On boot, values are reloaded via `ExtFlashRecorder_GetUiSettings(...)` and applied to runtime/UI state.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-22 (Detailed On-Device Help Popup)
- User request: expand help popup with detailed, practical guidance so users understand how to operate the system.
- `src/gauge_render.h`:
  - Increased help panel height (`GAUGE_RENDER_HELP_PANEL_Y1`) to fit expanded content.
- `src/gauge_render.c` (`DrawHelpPopup`):
  - Replaced short checklist with detailed sections:
    - Quick start and control mapping (`*` settings / `?` help)
    - Mode and run-state intent (`ADAPT`/`TRAINED`, `TRAIN`/`LIVE`)
    - Limits workflow (open limits and adjust thresholds)
    - Main screen controls (play/stop, record flow)
    - Alert meaning (green/yellow/red semantics)
    - Persistence behavior (settings auto-save and restore on reboot)
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-22 (Two-Page Deep Help Popup)
- User request: add deeper help information beyond the operator quick-start content.
- `src/gauge_render.c`:
  - Added help page state (`gHelpPage`) and page-aware rendering in `DrawHelpPopup`.
  - Added page indicator (`PAGE 1/2`, `PAGE 2/2`) in the popup header.
  - Page 1 remains operations-oriented quick usage guidance.
  - Page 2 adds deeper engineering guidance:
    - Adapt vs trained behavior
    - Train vs live runtime semantics
    - Threshold intent for G/temp/gyro
    - Host-firmware + AI-layer integration notes
  - Added APIs:
    - `GaugeRender_SetHelpPage(uint8_t page)`
    - `GaugeRender_NextHelpPage(void)`
- `src/gauge_render.h`:
  - Declared new help-page APIs.
- `src/edgeai_package_transport_anomaly_demo.c`:
  - While help popup is open, tapping `?` now switches between page 1 and page 2 instead of closing help.
  - Opening help from main screen always starts at page 1 (`GaugeRender_SetHelpPage(0u)`).
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-22 (Help Popup Interaction Reliability Fix)
- User-reported issues after deep-help rollout:
  - Could not switch to page 2 reliably.
  - Footer note appeared too low.
  - `X` close action could fail.
- Root causes and fixes:
  - `ui_block_touch` could suppress modal popup interactions:
    - In main loop, modal-visible states now clear `ui_block_touch` and allow modal tap handling.
  - Reliance on top-level `?` icon while help popup is open was ambiguous:
    - Added explicit in-popup `NEXT PAGE` button and touch hitbox.
  - Footer close note placement adjusted upward so it remains clearly inside help panel.
- Files updated:
  - `src/gauge_render.h` (help next-button geometry constants)
  - `src/gauge_render.c` (draw next-page button + footer alignment)
  - `src/edgeai_package_transport_anomaly_demo.c` (help-next touch handler + modal touch unblock)
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-22 (Help Next Button Geometry Tweak)
- User request: move help `NEXT PAGE` button to the right and reduce its width by ~20%.
- `src/gauge_render.h`:
  - Updated `GAUGE_RENDER_HELP_NEXT_X0` from `314` to `339`.
  - Kept `GAUGE_RENDER_HELP_NEXT_X1=438`, shrinking width from 125px to 100px (~20% smaller) while right-aligning the control.
- Rebuilt and flashed successfully from project-local workflow:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug`
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin`

## Update 2026-02-22 (Settings Footer Placement + Configurable Logging Rate)
- User request:
  - move model/version info near the bottom of settings popup,
  - add configurable log output rate options (`1/5/10/20/30/40/50 Hz`).
- Implemented UI changes in `src/gauge_render.c` / `src/gauge_render.h`:
  - added `LOG HZ` row with decrement/increment controls and current value display,
  - moved settings profile footer to lower panel area:
    - `MODEL:`
    - `EIL EXT:`
    - `MODEL V:`
- Implemented runtime + persistence wiring:
  - `src/edgeai_package_transport_anomaly_demo.c`:
    - added allowed-rate table and clamp/step helpers,
    - added touch handlers for `LOG HZ` decrement/increment,
    - added rate-based telemetry scheduler (`LOG,...`) without changing inference cadence.
  - `src/ext_flash_recorder.h` / `src/ext_flash_recorder.c`:
    - extended UI settings save/load to include `log_rate_hz`,
    - persisted `log_rate_hz` in metadata and restored at boot.
- Reliability note:
  - this change affects log emission cadence only,
  - anomaly/adaptive model update cadence and thresholds are unchanged.
- Verification:
  - `BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug` (PASS)
  - `./tools/flash_frdmmcxn947.sh mcuxsdk_ws/build_adaptive_reasoning/edgeai_package_transport_anomaly_demo_cm33_core0.bin` (PASS, probe `2PZWMSBKUXU22`)

## Update 2026-02-22 (Infusion Pump Derivative Planning Baseline)
- Added approved transition plan to reuse validated runtime infrastructure from package transport demo:
  - elapsed-time scheduler
  - sensor stream/frame pipeline
  - flash record/playback/live workflow
  - operator-state and settings persistence model
- Documented new derivative scope for medical infusion supervision:
  - motor anomaly + wear/damage prediction
  - over/under temperature with trend prediction
  - wearer activity class and confidence
  - inversion and drop/possible-damage events
- Aligned model-authoring path to extension workflow in `embedded-intelligence-layer` and planned default infusion template integration.
- Updated documentation artifacts:
  - `docs/TODO.md`
  - `docs/TEMP_COMBINED_STATE.md`
  - `docs/SYSTEM_DESIGN.md`
  - `README.md`
- Result: planning baseline approved and documented.
