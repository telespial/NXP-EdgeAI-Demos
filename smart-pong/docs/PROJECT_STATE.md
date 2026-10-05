# Project State

Last updated: 2026-03-24

## Current Status
- Target board: `FRDM-MCXN947`
- Demo: 3D-look Smart Pong with optional EdgeAI assist layer
- Working workspace: `mcuxsdk_ws/`
- Most recent validated binary:
  - `mcuxsdk_ws/mcuxsdk_ws/build_default_algo_left_edgeai_right_20260324/edgeai_smart_pong_demo_cm33_core0.bin`

## Last Verified Change
- Date: 2026-03-24
- Result: build/flash PASS
- Summary:
  - Changed boot default SKILL mode to `ALGO/AI` so startup assigns left side `ALGO` and right side `EdgeAI`.
  - Existing gameplay logic and side-role mapping are unchanged; this is a default-selection update.
  - Verified with build/flash:
    - `BUILD_DIR=mcuxsdk_ws/build_default_algo_left_edgeai_right_20260324 ./tools/build_frdmmcxn947.sh`
    - `BUILD_DIR=mcuxsdk_ws/build_default_algo_left_edgeai_right_20260324 ./tools/flash_frdmmcxn947.sh`

## Active Restore Point
- Pointer file: `docs/failsafe.md`
- Artifact folder: `failsafe/`
- Active artifact:
  - `failsafe/edgeai_smart_pong_demo_cm33_core0_20260324_073456_ui_dx_spacing_golden.elf`
- Flash command:
  - `FAILSAFE_CONFIRM="$(sed -n '1p' docs/failsafe.md)" ./tools/flash_failsafe.sh`

## Default Build / Flash
- Build:
  - `./tools/build_frdmmcxn947.sh`
- Flash:
  - `./tools/flash_frdmmcxn947.sh`

## Notes
- Keep release documentation synchronized in:
  - `STATUS.md`
  - `docs/PROJECT_STATE.md`
  - `docs/failsafe.md`
