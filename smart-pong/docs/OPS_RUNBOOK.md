# Operations Runbook

## Bootstrap (fresh machine, no sudo)
```bash
./tools/bootstrap_ubuntu_user.sh
```

## Workspace Setup / Sync
```bash
./tools/setup_mcuxsdk_ws.sh
```

## Build
```bash
./tools/build_frdmmcxn947.sh
```

Build to a custom directory (recommended for release candidates):
```bash
BUILD_DIR=mcuxsdk_ws/build_rc ./tools/build_frdmmcxn947.sh
```

## Flash (normal)
```bash
./tools/flash_frdmmcxn947.sh
```

Flash from a custom build directory:
```bash
BUILD_DIR=mcuxsdk_ws/build_rc ./tools/flash_frdmmcxn947.sh
```

## Flash (failsafe restore)
```bash
FAILSAFE_CONFIRM="$(sed -n '1p' docs/failsafe.md)" ./tools/flash_failsafe.sh
```

## Release / Restore-Point Procedure
1. Build release candidate in a dedicated `BUILD_DIR`.
2. Flash candidate and confirm board boots correctly.
3. Copy `.elf` into `failsafe/` with timestamped release name.
4. Update `docs/failsafe.md` to point to the new artifact.
5. Update `STATUS.md` and `docs/PROJECT_STATE.md`.
6. Commit and push to GitHub.
7. Move `golden` and `failsafe` git tags to the release commit and push tags.

## Logging Requirements
- After each command execution, append to `docs/COMMAND_LOG.md`.
- After each code/build/flash/release change, update:
  - `STATUS.md`
  - `docs/PROJECT_STATE.md`
