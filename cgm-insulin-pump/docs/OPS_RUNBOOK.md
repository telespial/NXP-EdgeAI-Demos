# Operations Runbook

Last updated: 2026-02-25

## One-Time Bootstrap (Ubuntu User-Local)

`./tools/bootstrap_ubuntu_user.sh`

## Preflight

`./scripts/preflight.sh`

## Build

`./scripts/build.sh`

## Flash

`./scripts/flash.sh`

Safe direct flash:

`./scripts/flash_safe.sh`

## Build + Flash

`./scripts/build_and_flash.sh`

## Restore Points

Current baseline:
- Golden: `GOLDEN-2026-02-25-R11`
- Failsafe: `FAILSAFE-2026-02-25-R11`

Artifacts:
- `failsafe/edgeai_medical_device_demo_cm33_core0_golden_2026-02-25-R11.bin`
- `failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-25-R11.bin`

Restore command (direct):
- `./tools/flash_failsafe.sh failsafe/edgeai_medical_device_demo_cm33_core0_failsafe_2026-02-25-R11.bin`

## State Updates

`./scripts/update_state.sh --change "<summary>" [--binary <path>] [--command "<cmd>"] [--result <ok|fail>]`

## Probe Check

`/usr/local/LinkServer/LinkServer probe '#1' dapinfo`

## Documentation Hygiene

- After any code/config/build/flash action, update:
  - `docs/PROJECT_STATE.md`
  - `docs/COMMAND_LOG.md`
