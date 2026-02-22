# Status

Last updated: 2026-02-22

- Project build target: `edgeai_package_transport_anomaly_demo` (`frdmmcxn947/cm33_core0`)
- Current build status: PASS (`mcuxsdk_ws/build_adaptive_reasoning`)
- Flash status: PASS in this session (probe `2PZWMSBKUXU22`)
- Latest hotfix: PASS (LCD/touch responsiveness mitigation in `par_lcd_s035_fill_rect`, 2026-02-22)
- Latest profile import: PASS (`package_shipping_monitor` imported and model name shown in settings page 1)
- Latest settings/logging update: PASS (model/version moved near settings footer + configurable `LOG HZ` selector/persistence, 2026-02-22)
- Latest architecture update: PASS (canonical alert status path + persisted alert status/reason/score in flash rows, 2026-02-22)
- Latest predictive warning update: PASS (inverted/tilt, temp-approach, erratic-motion warning reasons, 2026-02-22)
- Latest capture fidelity update: PASS (100Hz accel buffering with interval peak capture for logs/flash, 2026-02-22)
- Latest gyro verification update: PASS (confirmed GY pipeline mapping; fixed terminal `GYR` line to report true gyro channels instead of accel channels, 2026-02-22)
- Latest gyro source fix: PASS (gyro peak/log/record windows now use true gyro dps channels, not accel-derived UI orientation channels, 2026-02-22)
- Latest buffer extension update: PASS (gyro + magnetometer interval-peak buffering; temp/baro unchanged, 2026-02-22)
- Latest label update: PASS (`SCORE WARN/FAIL` display renamed to `SHIFT/BREAK`, 2026-02-22)
- Latest UI/runtime update: PASS (elapsed clock expanded to `HHHH:MM:SS`, scope graph switched to `GX/GY/GZ` with color legend, settings `CLEAR FLASH` confirm added, 2026-02-22)
- Latest flash-row integrity update: PASS (recorder/log path now refreshes frame sample at emit/write time so `AS/RC/SC` + timestamp rows are current even when UI redraw is paused, 2026-02-22)
- Latest scope fix: PASS (restored `AX/AY/AZ/T` plots and added `GX/GY/GZ`; gyro labels placed to right of accel/temp legend, 2026-02-22)
- Latest gyro sphere fix: PASS (artifact line cleanup + corrected direct X/Y axis mapping, 2026-02-22)
- Latest scope feed fix: PASS (gyro traces now use true gyro feed, not accel overlap; model metadata moved inside settings popup, 2026-02-22)
- Latest clear-flash fix: PASS (confirm popup now opens reliably from settings and no freeze on clear action, 2026-02-22)
- Latest confirm-priority fix: PASS (clear/record confirm works in LIVE mode; manual clear also resets record elapsed counter, 2026-02-22)
- Latest alert-hold update: PASS (warning/fault statuses now persist for a minimum visibility window: WARN=5s, FAIL=8s, 2026-02-22)
- Latest alert-priority update: PASS (higher severity preempts lower held alerts; stronger warning reasons replace weaker warning holds, 2026-02-22)
- Latest docs update: PASS (README and AI runtime reference expanded with complete AI/non-AI behavior and operator instructions, 2026-02-22)
- Latest recorder cadence update: PASS (`LOG HZ` now drives flash record cadence at `1/5/10/20/30/40/50 Hz`, 2026-02-22)
- Latest settings control fix: PASS (`LOG HZ` now shows explicit down/up arrow icons, 2026-02-22)
- Latest help/font fix: PASS (missing help characters resolved by complete 5x7 alphabet mapping including `J`/`Q`, 2026-02-22)
- Latest derivative planning update: PASS (approved infusion-pump transition plan documented with reuse-first architecture and EIL template path, 2026-02-22)

## UI Control Scope (Updated)
- AI enable/disable is settings-only.
- Main-screen AI badge is status display only and no longer accepts touch toggle.
- Settings now uses explicit options `AI ON` and `AI OFF` with direct runtime apply.
- Settings AI order: left=`AI OFF`, right=`AI ON`.
- Settings mode labels are readable: `ADAPT`, `TRAIN`, `LIVE` (not `M1/M2/M3`).
- Boot persistence enabled for mode/tune/AI via external flash metadata.
- Settings popup rows now have aligned labels and vertically centered row text.
- Selecting any mode (`ADAPT`/`TRAIN`/`LIVE`) now auto-closes settings.
- Settings now separates `MODE` (`ADAPT`/`TRAINED`) from `RUN` (`TRAIN`/`LIVE`).
- Added operator limit controls in settings: `G`, `TEMP LOW/HIGH`, `GYRO` (persistent on boot).
- Limits controls are now rendered in a readable 2x2 grid (no overlap).
- Shock limits now use separate `GW/GF` defaults: `12.0g` warning, `15.0g` fault.
- Temp low/high controls are on the same row in settings.
- Each limit button now supports direct down/up adjustment (`-` on left, `+` on right).
- Limit controls now show `v` (decrease) and `^` (increase) markers.
- Settings includes `LOG HZ` options: `1/5/10/20/30/40/50 Hz` (persistent on boot).
- Settings footer now places `MODEL`, `EIL EXT`, and `MODEL V` near the bottom of the panel.
- Modal redraw now uses popup-only dirty region updates (reduced full-screen flashing/latency).
- Compass heading display is disabled until heading tracking is validated.
- Alert display now uses a single canonical status source (`sample->ai_status`) for system-state rendering.
- Alert detail text is reason-code based (limit/score/watch causes), not score-band-only text.
- Predictive warning reasons added for package handling supervision:
  - `INVERTED`, `TILTED`, `TEMP LOW SOON`, `TEMP HIGH SOON`, `ERRATIC MOTION`
- Accel capture now samples at 100 Hz and records interval-max peaks for `AX/AY/AZ` at the configured log/capture output cadence.
- Gyro and magnetometer now use the same interval-max buffering model for `GX/GY/GZ` and `MX/MY/MZ`.
- Temp and barometer remain direct sampled channels (no peak window buffering).
- Runtime clock now shows 4-digit non-wrapping hours (`HHHH:MM:SS`, clamped at `9999`).
- Settings now includes a dedicated `CLEAR FLASH` action with `YES/NO` confirmation popup.

## EIL Model Integration (In Progress)
- Added EIL profile adapter (`src/eil_profile.h/.c`) with generated constants (`src/eil_profile_generated.h`).
- Added importer tool:
  - `python3 tools/import_eil_profile.py --model <path-to-model.config.json> --out src/eil_profile_generated.h`
- Runtime scoring/status now consumes imported model values:
  - weighted anomaly score from AX/AY/AZ/TEMP input weights
  - `WARNING`/`FAULT` transitions from `alertThresholds.warn/fail`

## On-Board Training Flow (Current)
- Train can now complete entirely on board from record/replay/live controls:
  - `RECORD` captures training samples with training path active.
  - `PLAY` can continue fitting from recorded timeline if training window is not yet complete.
  - replay auto-restarts while training remains incomplete.
  - once trained-ready is reached, firmware auto-switches to live monitoring mode.
  - selecting `TRAIN` alone does not auto-start recording.
  - recording start requires confirmation.
  - during recording, left timeline button shows `STOP` and stop action requires confirmation.
  - while train mode is armed (not recording), alert banner shows `TRAINING`.
  - touch responsiveness improved by faster poll cadence (`2000 us`).
  - while train mode is armed, motion/sensor progression is frozen until `RECORD` confirm.
  - while recording, timeline left button (`STOP`) is blue for clearer state visibility.
  - alert banner now shows `NORMAL TRACKING` without the `WARNING` prefix when that detail is active.

## Golden Baseline (Active)
- Golden tag: `GOLDEN-20260222-152829`
- Active failsafe: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_failsafe_active.bin`
- Golden image: `failsafe/edgeai_package_transport_anomaly_demo_cm33_core0_golden_20260222T152829Z.bin`
- sha256: `2304af425c539cc63ddd56a6e0166c1697f43d1f1c0b744bf32be32ff8b78bd3`

## Frozen Features in Golden
- Accelerometer sphere gauge with fast redraw.
- Scope UI with PLAY (left) and RECORD (right) controls.
- Persistent AX/AY/AZ/TEMP traces.
- Board digital temperature sensor wired to temp gauge + trace.

## Current Runtime Validation
- On-board temperature sensor U6 (`P3T1755DP`) is now reading via I3C1 dynamic address flow.
- UART boot log confirms:
  - `TEMP ready dyn=0x08 bus=i3c T=24C`
- Prior stuck `99C` behavior was traced to a decode scale bug and is fixed.
- Temperature display now shows both units side-by-side (`C` and `F`) in terminal and left bar label.
- Boot-time raw-byte validation:
  - `TEMP init raw=0x18 0xf0 -> 24C/75F`
- Temperature display now supports one decimal place in both units (live sensor path uses raw-byte-derived tenths).
- Accelerometer sphere and `ACCEL VECTOR` title are now re-centered together after right shift (+5% screen width).
- Latest layout tweak: sphere/text moved left by 2.5% of screen width from that prior position.
- Horizon line roll response is calibrated to track sphere movement more accurately, reducing perceived mismatch.
- Gyro fast path is dynamic-only for responsive refresh; dynamic overlays are circle-clipped to keep all moving pixels inside the sphere and remove square-edge artifacts.
- Battery indicator is pinned to demo value `82%`.
- External-flash recorder is a robust one-record-per-page FIFO with gyro-ready sample fields (`gx/gy/gz`) and decimal temperature (`temp_c10`).
- External-flash recorder rows now also persist:
  - alert status
  - alert reason code
  - anomaly score
- External-flash recorder uses the upper half of NOR for recording, reserving one sector for metadata/generation.
- Current retention (FRDM-MCXN947 W25Q64 geometry, 10 Hz): ~27.3 minutes before FIFO overwrite.
- Recorder state now reconstructs from flash on boot (recordings persist across reboot).
- Timeline mode now defaults to PLAY on boot and auto-starts external-flash playback when recorded data is available.
- PLAY button now rewinds playback to beginning of current recording window on each press.
- RECORD now requires confirmation; YES clears recorder flash region first, then recording starts.
- RECORD confirm YES is non-blocking (fast logical clear), and confirm popup is forced topmost during fast refresh with close-transition cleanup redraw.
- Scope graph now includes a vertical playhead line tied to recorder state (green in PLAY, red in RECORD) for REC/PLAY verification.
- Battery fill/text and temp-related dynamic visuals are now forced to redraw reliably after modal transitions.
- REC/PLAY stepping now runs at 10 Hz; display refresh also runs at 10 Hz for smoother playback.
- Scope graph sampling cadence is now aligned to 10 Hz (`SCOPE_FAST_STEP_US=100000`) to keep plotted timeline pace matched to recorded/playback data pace.
- PLAY mode scope plotting now advances on playhead movement (timeline-relative), preventing rapid full-window cycling that looked faster than recorded timeline pace.
- Added shield auxiliary sensor terminal telemetry integration:
  - `MAG X/Y/Z` (LIS2MDL),
  - compact environmental line for `BARO` (LPS22DF), `RH` + `SHT` temp (SHT40).
- Terminal TEMP + left temperature bargraph now prioritize shield temperature (`STTS22H`, fallback `SHT40`, fallback board sensor).
