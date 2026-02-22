# TODO

Last updated: 2026-02-22
Project: `EdgeAI_Package_Transport_Adaptive_Reasoning_demo_NXP_FRDM-MCXN947`

## Priority 0 (Derivative Scope Lock: Infusion Pump)
- [ ] Freeze reuse baseline for unchanged runtime blocks:
  - elapsed-time scheduler
  - sensor streaming pipeline
  - flash record/playback and timeline controls
  - live/train/operator flow and settings persistence
- [ ] Define infusion-pump safety state contract (`NORMAL`/`WARNING`/`FAULT`) with deterministic preemption rules.
- [ ] Freeze initial reason-code set for:
  - motor anomaly
  - predicted motor wear/damage
  - over/under temperature and thermal-trend risk
  - activity class and confidence
  - inversion and drop/damage events

## Priority 1 (Model Contract + EIL Extension Integration)
- [ ] Create infusion-pump default model template in EIL extension:
  - `EdgeAI_Medical_Infusion_Pump_Adaptive_Reasoning_demo_NXP_FRDM-MCXN947.config.json`
- [ ] Include infusion-focused inputs:
  - motor channels (`rpm`, `current`, `step_error`, `load_proxy`)
  - thermal channels (`temp_c`, `temp_slope_c_per_min`, `ambient_c`)
  - motion channels (`accel`, `gyro`, `baro_delta`, `inverted_flag`, `drop_event`)
  - activity channels (`sleep/sit/stand/walk/run/stairs_up/stairs_down`)
- [ ] Keep threshold and reason-code mapping export-compatible with existing firmware import path (`tools/import_eil_profile.py`).

## Priority 2 (Firmware Transition Plan, Reuse First)
- [ ] Add infusion-pump feature extraction layer without replacing base runtime plumbing.
- [ ] Implement motor-health logic:
  - anomaly detection
  - wear trend prediction
  - warning/fault transitions
- [ ] Implement thermal trend prediction:
  - approach-to-limit warning
  - over/under fault boundaries
- [ ] Implement wearable-context logic:
  - activity classification
  - inversion detection
  - drop/possible-damage detection

## Priority 3 (Verification + Evidence)
- [ ] Run replay validation set with expected reason-code timelines for:
  - normal infusion
  - early motor wear drift
  - motor fault event
  - temp rise/fall trend breach
  - inversion event
  - drop impact and post-impact behavior
- [ ] Capture UART + flash evidence for each scenario (`AS/RC/SC` + `ts_ds`).
- [ ] Confirm recorder cadence correctness at `1/10/50 Hz` for infusion profile.

## Priority 4 (Release Hygiene)
- [ ] Keep `STATUS.md`, `docs/PROJECT_STATE.md`, restore docs, and command log synchronized for every milestone.
- [ ] Verify active failsafe image still boots and reaches UI before release cut.
- [ ] Publish milestone notes mapping package-transport baseline to infusion-pump derivative state.
