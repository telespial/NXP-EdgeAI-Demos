# EdgeAI Package Transport Anomaly Demo (FRDM-MCXN947)

Standalone embedded intelligence firmware for **FRDM-MCXN947 + LCD-PAR-S035** that layers adaptive anomaly monitoring on top of standard host firmware logic.

![package_mon](https://github.com/user-attachments/assets/32d6d706-53bc-4582-9031-dc30bee0869e)

This project is designed as a practical "AI watchover" system:
- host firmware keeps deterministic control behavior,
- the intelligence layer scores risk, detects drift/anomaly, and emits explainable reason codes,
- logs and flash recording preserve timestamped evidence for replay and tuning.

## What This Device Does

### Intelligence Layer (AI-Assisted)
- Adaptive anomaly scoring from multi-sensor channels.
- Deterministic warning/fault transitions with explicit reason codes.
- Predictive warning signals (inversion, tilt, temp approach, erratic motion).
- On-device train/record/play/live workflow (no mandatory CSV round-trip).
- Severity-priority alert policy with visibility hold:
  - higher severity always overrides lower severity,
  - warning hold: 5s minimum,
  - fault hold: 8s minimum.

### Host Firmware Layer (Deterministic)
- Sensor bus handling and decode.
- UI rendering, controls, and operator interactions.
- External flash recording/replay with timeline controls.
- Persistent settings on reboot (mode, AI on/off, limits, log rate).

## Hardware Used In This Firmware

Target platform:
- NXP FRDM-MCXN947
- LCD-PAR-S035 display
- ST sensor shield stack used by this demo firmware

### GitHub Hardware Parts List

This repository firmware is written against the following detected/used hardware parts:

- `FRDM-MCXN947` (target MCU board)
- `LCD-PAR-S035` (display + touch assembly used by UI)
- ST multi-sensor shield stack (this firmware probes/uses these ST devices):
  - `LSM6DSO16IS` IMU (accel + gyro primary path)
  - `LIS2MDL` magnetometer
  - `LPS22DF` barometer
  - `STTS22H` temperature sensor
  - `LSM6DSV16X` IMU WHOAMI fallback probe path
  - `LIS2DUXS12` probe entries for shield-bus diagnostics
- `SHT40` (shield-mounted temperature/humidity path)
- `P3T1755DP` (board temperature path)
- `W25Q64` class external flash (record/replay storage path used by firmware)
- `GT911` touch controller path used by UI input handling

ST shield components used by code:
- `LSM6DSO16IS` (primary IMU): 3-axis accelerometer + 3-axis gyroscope data source for motion channels.
- `LIS2MDL` (magnetometer): magnetic field channels (`MX/MY/MZ`) for logging and replay evidence.
- `LPS22DF` (barometer): pressure channel (`baro`) used in telemetry/log records.
- `STTS22H` (temperature): shield temperature channel used for operator display and logging.

Additional shield-mounted component used by code:
- `SHT40` (temperature + humidity): auxiliary environmental channel (`SHT temp` + `RH`) in logs/terminal telemetry.

Shield device detection/probe support present in code:
- `LSM6DSV16X` WHOAMI fallback handling on IMU probe path.
- `LIS2DUXS12` address probing entries for shield-bus diagnostics.

Board-level component used by code:
- `P3T1755DP` board temperature sensor path via I3C/I2C fallback.

## Architecture Summary

The firmware intentionally separates responsibilities:
1. Sensor and protocol complexity stays in host firmware.
2. The intelligence layer consumes normalized decoded channels.
3. Output is an explainable decision layer (`status + reason + score`) that complements host algorithms.

This keeps integration portable and makes behavior auditable.

## EIL Profile Workflow (VS Extension -> Firmware)

1. Build profile in the EIL extension (`model.config.json`).
2. Export profile package.
3. Import profile into firmware:

```bash
python3 tools/import_eil_profile.py \
  --model /path/to/model.config.json \
  --out src/eil_profile_generated.h
```

4. Build and flash firmware.

Current integration uses:
- profile alert thresholds -> firmware warning/fault boundaries,
- profile input weights -> weighted anomaly score computation.

## Planned Derivative: Medical Infusion Pump

Approved transition approach is reuse-first:
- keep current elapsed-time runtime, sensor streaming, flash rec/play, and live/train/operator control flows,
- retarget model profile + reason-code semantics to infusion safety use-cases.

Planned supervision scope:
- motor status anomaly + wear/damage prediction,
- over/under temperature plus trend-based predictive warnings,
- activity/context classification (`sleep/sit/stand/walk/run/stairs up/down`),
- inversion and drop/possible-damage detection.

Model authoring for this derivative is planned through:
- `projects/microsoft/visual-studio/embedded-intelligence-layer`
- default bundled template target:
  - `EdgeAI_Medical_Infusion_Pump_Adaptive_Reasoning_demo_NXP_FRDM-MCXN947.config.json`

## Build And Flash

```bash
./tools/bootstrap_ubuntu_user.sh
./tools/setup_mcuxsdk_ws.sh
BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/build_frdmmcxn947.sh debug
BUILD_DIR=mcuxsdk_ws/build_adaptive_reasoning ./tools/flash_frdmmcxn947.sh
```

## Operator Controls

- `MODE`: `ADAPT` / `TRAINED`
- `RUN`: `TRAIN` / `LIVE`
- Timeline: `PLAY` + `RECORD/STOP`
- Limits: `G WARN`, `G FAIL`, `TEMP LOW`, `TEMP HIGH`, `GYRO LIMIT`
- Logging: `LOG HZ` = 1/5/10/20/30/40/50 Hz
- Maintenance: `CLEAR FLASH` (confirm popup)

## Data Recording And Evidence

Each flash row stores:
- timestamp (`ts_ds`),
- accel/gyro/mag/temp/baro channels,
- anomaly score,
- alert status,
- alert reason code.

This supports replay and post-event analysis with explicit cause visibility.

## Key Documentation

- `docs/OPS_RUNBOOK.md`: canonical setup/build/flash commands.
- `docs/PROJECT_STATE.md`: detailed running change history and validation state.
- `docs/SYSTEM_DESIGN.md`: architecture and data flow.
- `docs/AI_RUNTIME_REFERENCE.md`: complete AI and non-AI function reference.
- `docs/RESTORE_POINTS.md`: active golden/failsafe metadata.
- `docs/failsafe.md`: active failsafe binary and checksum.

## Repository Layout

- `src/`: firmware source
- `tools/`: setup/build/flash/import scripts
- `docs/`: design, operations, restore points, command logs
- `data/`: replay assets
- `failsafe/`: pinned recovery binaries/checksums
