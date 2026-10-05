# AI Runtime Reference

Last updated: 2026-02-22
Project: `EdgeAI_Package_Transport_Anomaly_demo_NXP_FRDM-MCXN947`

## Purpose

Defines all intelligence-layer and non-intelligence runtime functions currently implemented in firmware.

## 1) AI Layer Functions

### 1.1 Model/Profile Integration
- Profile source: imported EIL `model.config.json`.
- Import tool: `tools/import_eil_profile.py`.
- Runtime usage:
  - `alertThresholds.warn/fail` -> score-based warning/fault transitions.
  - input weights (`accel_x_g`, `accel_y_g`, `accel_z_g`, `temp_c`) -> weighted anomaly score.

### 1.2 Anomaly Scoring
- Inputs:
  - channel severity levels from anomaly engine (`AX/AY/AZ/TEMP`),
  - profile weights,
  - hard-limit checks,
  - predictive motion/temperature context.
- Output:
  - `anomaly_score_pct` (0..100),
  - `ai_status` (`NORMAL`, `WARNING`, `FAULT`),
  - `alert_reason_code`.

### 1.3 Alert Reason Set (Current)
- Hard limit reasons:
  - `ACCEL WARN`, `ACCEL FAIL`
  - `TEMP WARN`, `TEMP FAIL`
  - `GYRO WARN`
- Score/watch reasons:
  - `SHIFT` (score warning)
  - `BREAK` (score fail)
  - `WATCH STATE`
- Predictive reasons:
  - `INVERTED`
  - `TILTED`
  - `TEMP LOW SOON`
  - `TEMP HIGH SOON`
  - `ERRATIC MOTION`
- Normal:
  - `NORMAL TRACKING`

### 1.4 Alert Hold and Priority Policy
- Minimum visibility hold:
  - `WARNING`: 5 seconds
  - `FAULT`: 8 seconds
- Priority behavior:
  - `FAULT` always preempts `WARNING`/`NORMAL`.
  - `WARNING` preempts `NORMAL`.
  - among warning reasons, stronger warnings preempt weaker held warnings.
- Timing source:
  - hardware timebase (`TimebaseNowTicks`) so behavior is stable across render-rate changes.

### 1.5 Adaptive/Training Runtime Modes
- `ADAPT` mode:
  - learning remains active.
- `TRAINED` mode:
  - model uses trained/frozen behavior.
- `RUN=TRAIN`:
  - enables record/playback-assisted on-board fitting workflow.
- `RUN=LIVE`:
  - live sensor-driven operation.
- Auto behavior:
  - when training reaches ready state, firmware auto-promotes to live monitoring.

## 2) AI Evidence and Logging

### 2.1 UART Log Fields
- periodic line includes:
  - `AX/AY/AZ`, `GX/GY/GZ`, `MX/MY/MZ`, `T`, `P`,
  - `AL` (anomaly level),
  - `AS` (alert status),
  - `RC` (reason code),
  - `SC` (score).

### 2.2 Flash Recorder Payload
Per row stores:
- sequence id,
- timestamp (`ts_ds`),
- accel, gyro, mag, baro, and temperature channels,
- `anomaly_score_pct`,
- `alert_status`,
- `alert_reason_code`.

### 2.3 Replay Behavior
- Playback restores recorded channels and timestamp.
- Timeline/playhead is synchronized to recorder offset/count.
- Recording and replay are suitable for model behavior validation and operator demonstrations.

## 3) Non-AI Functions (Host Firmware Responsibilities)

### 3.1 Sensor Interface Layer
- Reads and decodes IMU/aux sensors.
- Handles protocol specifics (I2C/I3C/sensor hub).
- Provides normalized channel values to AI layer.

### 3.2 UI Layer
- Dashboard, scope traces, status banner, settings/help/limits popups.
- Touch handling and modal interaction flow.
- Model/version metadata display.

### 3.3 Safety/Operator Controls
- Hard limits configurable in settings.
- AI enable/disable in settings only.
- Flash clear with confirmation.

### 3.4 Persistence
- Boot-persistent settings in external flash metadata:
  - mode, tune, AI state,
  - limits,
  - log rate.

## 4) Current Practical Positioning

This firmware is a production-oriented embedded intelligence supervisor:
- deterministic host control remains primary,
- adaptive anomaly layer adds early warning and explainable diagnostics,
- timestamped evidence is retained for replay and review.

