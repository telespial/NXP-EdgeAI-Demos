# System Design

Last updated: 2026-02-22
Project: `EdgeAI_Package_Transport_Anomaly_demo_NXP_FRDM-MCXN947`

## 1) Firmware Runtime Processes

### 1.1 Main Loop Scheduling
- The app runs a cooperative loop with elapsed-time accumulation and periodic task ticks.
- Key periodic processes:
  - touch polling + UI interaction handling
  - gyro/accel fast render updates
  - recorder/playback tick
  - board/shield sensor refresh
  - anomaly inference update
  - full-frame UI refresh

### 1.2 UI Rendering Pipeline
- Static dashboard composition is drawn once and reused.
- Dynamic redraw paths update:
  - gyro sphere widget
  - scope traces
  - terminal lines
  - left temperature bargraph
  - alert and modal overlays
- Modal path (settings/help/record-confirm) blocks conflicting fast-path draws to avoid layer contention.

### 1.3 Data/Replay Pipeline
- `power_data_source` provides frame samples.
- `ext_flash_recorder` provides persistent record/playback over external flash.
- Runtime supports:
  - REC mode: sample and store frames
  - PLAY mode: replay stored timeline with playhead

### 1.4 Anomaly Pipeline
- `anomaly_engine` computes per-channel levels and overall level.
- Levels feed:
  - alert banner status/color
  - terminal anomaly tags (`AX/AY/AZ/T`)
  - risk-channel percentages in the sample frame
- Runtime adds severity-prioritized alert hold behavior:
  - warning hold: 5s
  - fault hold: 8s
  - higher severity always overrides lower held severity.

## 2) Sensor Architecture

### 2.1 Sensor Buses
- FC2 (`LPI2C2`): shared touch + shield path.
- FC3 (`LPI2C3`): secondary I2C path (not currently hosting active shield sensors in this setup).
- I3C1: board on-die temp device path (`P3T1755` flow).

### 2.2 IMU Source (Primary Motion)
- Device: `LSM6DSO16IS` on shield (`0x6A/0x6B`, active at `0x6A` in current setup).
- Data used:
  - gyro rates
  - accel axes
- UI use:
  - sphere motion/orientation rendering
  - terminal `GYR ...` line
  - terminal `ACC ...` line (linear accel formatting path)

### 2.3 Shield Auxiliary Sensors

#### A) LIS2MDL (Magnetometer)
- Role: magnetic field vector.
- Output:
  - terminal `MAG X/Y/Z`

#### B) LPS22DF (Barometer)
- Role: pressure.
- Output:
  - compact terminal environment line (`B ... h`)

#### C) SHT40 (Humidity + Temperature)
- Role: RH + secondary temperature.
- Output:
  - compact line: `H` and `S` fields

#### D) STTS22H (Temperature)
- Role: dedicated shield temperature sensor.
- Output:
  - primary temperature source for terminal `TEMP ...` and left TEMP bargraph.

### 2.4 Shield Sensor Transport Strategy
- Direct I2C probe/read is attempted first.
- If not directly visible, firmware uses `LSM6DSO16IS` sensor-hub transport:
  - read path through `SENSOR_HUB_1`
  - write/config path through `DATAWRITE_SLV0`
  - per-transaction hub reset/cleanup to avoid stale transactions.

## 3) Temperature Design

### 3.1 Display Priority (Current)
- `TEMP` terminal line and left bargraph:
  1. `STTS22H`
  2. `SHT40` temperature
  3. board temp (`P3T1755`)
  4. replay/sample fallback

### 3.2 Why `S` Can Differ From `TEMP`
- `S` in the compact env line is `SHT40` temp.
- `TEMP` line/bargraph prioritize `STTS22H`.
- Small differences are expected due to sensor placement and characteristics.

## 4) Terminal Line Definitions

- `TEMP ...`: primary temp readout (priority path above).
- `GYR X/Y/Z`: gyro-driven motion values.
- `ACC ...`: accel in `g` formatted line.
- `MAG X/Y/Z`: magnetometer.
- `B ... H ... S ...`:
  - `B`: barometric pressure (`hPa`)
  - `H`: humidity (`%RH`)
  - `S`: SHT40 temperature (`C`)

## 5) Restore-Point Policy

- Golden and active failsafe artifacts are cut from the current validated build output.
- Files are stored in `failsafe/` with timestamped golden and pinned active failsafe.
- `docs/RESTORE_POINTS.md`, `docs/failsafe.md`, `failsafe/README_GOLDEN.txt`, `STATUS.md`, and `docs/COMMAND_LOG.md` are updated together for each restore-point cut.

## 6) Function Reference

- Full runtime function inventory (AI and non-AI): `docs/AI_RUNTIME_REFERENCE.md`.

## 7) Planned Derivative Architecture: Infusion Pump

### 7.1 Reused Runtime Blocks (No Redesign Planned)
- Main loop scheduling and elapsed-time accumulators.
- Sensor capture/streaming and frame assembly pipeline.
- External flash recorder/replay timeline pipeline.
- UI control model for `TRAIN/LIVE`, `PLAY/RECORD`, modal arbitration, and settings persistence.

### 7.2 New Domain Semantics (Planned)
- Replace package-domain alert semantics with infusion-device semantics:
  - motor status anomaly and wear/damage prediction.
  - thermal limit and trend forecasting (`high soon` / `low soon`).
  - wearer activity class and confidence.
  - inversion and drop/impact damage signals.

### 7.3 Model Contract Path (Planned)
- Profile generation remains extension-driven (`embedded-intelligence-layer`).
- New default infusion template will be bundled in the extension and imported through existing firmware profile importer.
- Runtime still enforces deterministic safety gates while model outputs provide predictive watchover and explainable reason codes.
