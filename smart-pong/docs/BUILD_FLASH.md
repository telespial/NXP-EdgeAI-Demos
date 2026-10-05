# Build / Flash (FRDM-MCXN947)

This repo is self-contained. It does not require any external build system repo.

## 1) Bootstrap Tooling (No sudo)

```bash
./tools/bootstrap_ubuntu_user.sh
```

This installs user-local:
- `pip`, `west`, `cmake`, `ninja`
- `git-lfs`
- `arm-none-eabi-gcc` (xPack)

## 2) Create/Update MCUX SDK Workspace

```bash
./tools/setup_mcuxsdk_ws.sh
```

This creates `./mcuxsdk_ws/`, runs `west init` + `west update`, then installs the
`edgeai_smart_pong_demo` wrapper into `mcuxsdk/examples/`.

## 3) Build

```bash
./tools/build_frdmmcxn947.sh
```

Build output:
- `mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.bin`

Notes:
- Relative `BUILD_DIR` values are resolved under `WS_DIR` (default: `./mcuxsdk_ws`).
- Set `BUILD_DIR` to use a non-default build directory (for example, `BUILD_DIR=build_alt ./tools/build_frdmmcxn947.sh debug`).
- Current known-good run uses the default build directory (`mcuxsdk_ws/build`).
- For a clean rebuild, use a fresh `BUILD_DIR` or remove the existing build directory contents.

## 4) Flash

Flashing uses NXP LinkServer (x86_64) via `west flash -r linkserver`.

Install LinkServer (user-local, no sudo):

```bash
ACCEPT_NXP_LINKSERVER_LICENSE=1 ./tools/install_linkserver_user.sh
```

If flashing fails with `No probes detected`, install udev rules (requires sudo), then unplug/replug the board:

```bash
./tools/install_mculink_udev_rules.sh
```

Then flash:

```bash
./tools/flash_frdmmcxn947.sh
```

## Failsafe Flash (Last Resort)
The active failsafe artifact is recorded in `docs/failsafe.md`.
Current active failsafe artifact:
- `failsafe/edgeai_smart_pong_demo_cm33_core0_20260324_065426_style_edgeai_fairness_speedup_golden.elf`

Flashing requires explicit confirmation via the exact filename listed in line 1 of `docs/failsafe.md`:
```bash
FAILSAFE_CONFIRM="$(sed -n '1p' docs/failsafe.md)" ./tools/flash_failsafe.sh
```

## Serial (Optional)
The MCU-Link VCOM interface typically enumerates as `/dev/ttyACM0`:
```bash
timeout 10 cat /dev/ttyACM0
```
