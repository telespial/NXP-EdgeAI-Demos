# Temporary Combined State

Last updated: 2026-02-22
Scope: consolidated view of `docs/PROJECT_STATE.md`, `docs/SYSTEM_DESIGN.md`, `docs/AI_RUNTIME_REFERENCE.md`, and `STATUS.md`.

## Executive Snapshot
- Build: PASS (`frdmmcxn947/cm33_core0`, app `edgeai_package_transport_anomaly_demo`)
- Flash: PASS in current session (probe `2PZWMSBKUXU22`)
- Golden baseline: `GOLDEN-20260222-152829`
- Active failsafe: `FAILSAFE-ACTIVE`
- Key output: stable live/train workflow with persistent settings, alert prioritization, and flash-backed event logging.

## Current Runtime Intent
This firmware implements an embedded intelligence supervisor on top of deterministic host sensing logic:
- Host firmware remains the source of truth for sensor acquisition and safety-critical baseline rules.
- AI/anomaly layer adds predictive/watchover behavior (drift, trend, anomaly score, reasoned alerts).
- Operator-facing states and logs are explainable (`NORMAL`, `WARNING`, `FAULT` + reason code + score).

## Architecture (Condensed)
- Sensor ingest: accel/gyro/mag/temp/baro inputs sampled in host firmware.
- Preprocess:
  - accel/gyro/mag buffered at 100 Hz and reduced by interval peak for log cadence.
  - temp/baro sampled directly (no peak buffering).
- Decision paths:
  - deterministic limit checks (G, gyro, temp high/low)
  - anomaly score and predictive checks (tilt/inversion, temperature approach, erratic motion)
- Arbitration:
  - canonical `ai_status` drives displayed/recorded status.
  - severity priority: `FAULT` > `WARNING` > `NORMAL`.
  - visibility hold: warning ~5s, fault ~8s.
- Persistence/logging:
  - settings persisted to external flash metadata.
  - event rows persist timestamp + sensor snapshot + status/reason/score.

## Operator Workflow (Current)
- `ADAPT` / `TRAINED` selects adaptation policy behavior.
- `TRAIN` / `LIVE` selects run mode.
- Recording behavior:
  - train mode no longer auto-records.
  - `RECORD` starts capture after confirmation.
  - during recording, timeline control switches to blue `STOP` with confirmation.
- Settings include:
  - AI ON/OFF (settings-only control, not main-screen touch)
  - limits (G warn/fail, gyro warn/fail, temp low/high)
  - log rate (`1/5/10/20/30/40/50 Hz`)
  - clear flash with confirmation

## Alert Model (AI + Non-AI)
- Non-AI (deterministic):
  - threshold/range limit warnings and faults from configured limits.
- AI/predictive layer:
  - anomaly score based escalation (configured warn/fail thresholds)
  - predictive warning reasons:
    - `INVERTED`
    - `TILTED`
    - `TEMP LOW SOON`
    - `TEMP HIGH SOON`
    - `ERRATIC MOTION`
- Screen behavior:
  - severe alerts preempt lower severity even while hold timers are active.
  - normal-tracking state shown clearly when no active warning/fault override exists.

## Integration with Generated Model Profile
- EIL profile import path exists in firmware (`src/eil_profile.*` + generated header).
- Imported profile constants can drive weighted score and alert thresholds.
- Current project state is integration-ready and already using profile-driven knobs for anomaly status logic.

## What Is Verified
- Build and flash pass.
- UI/settings persistence pass.
- Recorder/playback path pass.
- Alert hold/priority behavior pass.
- Gyro mapping and telemetry source path fixed and verified in latest notes.
- Help popup and font path now render full alphabet (`J`/`Q` added and lowercase normalized in 5x7 map).
- `LOG HZ` controls now use explicit arrow icons and flash record cadence is tied to selected `LOG HZ`.

## Open Validation Item (Recommended Next)
- Add a dedicated UART flash-dump line containing explicit signed values + timestamp fields for one-click post-run integrity checks, then capture a short train/live session and archive as a validation artifact.
