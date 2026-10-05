# Ops Runbook

## Purpose
Canonical setup, build, and flash workflow for this repository.

## Environment Setup
```bash
./tools/bootstrap_ubuntu_user.sh
./tools/setup_mcuxsdk_ws.sh
```

## Build
```bash
BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/build_frdmmcxn947.sh debug
```

## Flash
```bash
BUILD_DIR=mcuxsdk_ws/build_anomaly ./tools/flash_frdmmcxn947.sh
```

## Logging Requirements
- After command execution, append an entry in `docs/COMMAND_LOG.md`.
- After code/config/build/flash/release changes, update:
  - `docs/PROJECT_STATE.md`
  - `STATUS.md`

## Active Debug Target (UI Popups)
- Before modifying popup code, read `docs/CODER_HANDOFF.md`.
- Repro sequence to validate fix:
  1. Tap `*` (settings open).
  2. Tap `X` to close.
  3. Tap `?` (help open).
  4. Tap `X` to close.
  5. Repeat 10+ cycles and confirm no freeze and popups always topmost.
