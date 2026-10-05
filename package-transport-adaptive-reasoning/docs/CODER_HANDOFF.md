# Coder Handoff (Current Runtime + Open Defects)

Last updated: 2026-02-17

## 1) What The Device Currently Does

- Board: FRDM-MCXN947 + LCD-PAR-S035 + GT911 touch + FXLS8974 accel click + on-board P3T1755 temp over I3C1.
- Main loop runs with fixed polling at `TOUCH_POLL_DELAY_US=10000` (10 ms).
- Runtime cadences in `src/edgeai_package_transport_anomaly_demo.c`:
  - `GYRO_REFRESH_PERIOD_US=40000` (25 Hz fast sphere redraw)
  - `DISPLAY_REFRESH_PERIOD_US=100000` (10 Hz full frame)
  - `RECPLAY_TICK_PERIOD_US=100000` (10 Hz record/play sample step)
  - `ACCEL_LIVE_PERIOD_US=200000` (5 Hz live accel update when not in playback)
  - `TEMP_REFRESH_PERIOD_US=100000` (10 Hz temp update in record mode)
  - `POWER_TICK_PERIOD_US=1000000` (1 Hz synthetic power source tick)

## 2) Data Path Summary

- Accel (`FXLS8974`) is read in `AccelUpdate()` and axis-swapped intentionally:
  - `s_accel_x_mg = filt_y`
  - `s_accel_y_mg = filt_x`
  - `s_accel_z_mg = filt_z`
- Temp (`P3T1755`) uses I3C dynamic address assignment:
  - static `0x48` -> dynamic `0x08` via `RSTDAA + SETDASA`
  - decoded as 12-bit signed, 0.0625 C/LSB.
- Recording/playback:
  - At 10 Hz, append to ext flash with `ExtFlashRecorder_AppendSampleEx(...)`.
  - Playback reads with `ExtFlashRecorder_ReadNextSample(...)`.
  - Each sample includes timestamp deciseconds (`ts_ds`), accel, temp.

## 3) UI/Layer Model In Code

- Full frame: `GaugeRender_DrawFrame(...)`.
- Fast sphere path: `GaugeRender_DrawGyroFast(...)`.
- Popup visibility flags:
  - `gSettingsVisible`
  - `gHelpVisible`
  - record confirm `gRecordConfirmActive`.
- Intended behavior:
  - If help/settings visible, renderer draws modal base + popup and returns early from normal frame path.
  - Fast gyro path also checks popup flags and draws popup instead of sphere.

## 4) Known Open Defects (Current)

1. Settings/help close can freeze the board.
   - Repro: open settings or help, close using `X` or outside tap.
   - Observed by user repeatedly on hardware.

2. Popup layering is unstable across transitions.
   - Repro: open/close popup while graph/sphere are updating.
   - User reports popup occasionally appears behind graph/terminal/sphere.

3. Top `*` and `?` controls are visually/touch unstable.
   - Repro: repeated open/close cycles then attempt to open help/settings.
   - User reports controls are sometimes obscured by oval fill or not visible.

## 5) Most Relevant Files For Next Debug Pass

- `src/edgeai_package_transport_anomaly_demo.c`
  - touch routing and popup state machine (`help_visible`, `settings_visible`, `ui_block_touch`)
  - scheduling (`gyro_tick_accum_us`, `render_tick_accum_us`, modal interactions)
- `src/gauge_render.c`
  - popup drawing and modal base
  - early-return path in `GaugeRender_DrawFrame(...)`
  - fast redraw path in `GaugeRender_DrawGyroFast(...)`
- `src/gauge_render.h`
  - all AI strip/popup geometry constants and hit regions

## 6) Suggested Immediate Fix Strategy

1. Make popup state single-source-of-truth in renderer only.
   - Avoid duplicated app-side gating logic for modal draw decisions.

2. Add lightweight UART traces around popup transitions.
   - Log on open/close entry and after each `GaugeRender_DrawFrame(...)` call.
   - Confirm no re-entrant close/open edge on same touch frame.

3. Freeze dynamic widgets while popup open by design.
   - Keep 10 Hz frame calls, but force popup-only frame composition.
   - Skip all non-popup draw subcalls while popup visible.

4. Unify `*`/`?` visual and hit geometry.
   - Make visible glyph draw independent from pill fill.
   - Keep touch boxes slightly larger than glyph bounds.

