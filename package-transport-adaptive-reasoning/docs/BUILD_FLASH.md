# Build And Flash

## Prerequisites
- Ubuntu host with user-local bootstrap complete
- NXP LinkServer installed and available on `PATH`

## Setup
```bash
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

## Expected Artifact
- `mcuxsdk_ws/build_anomaly/edgeai_package_transport_anomaly_demo_cm33_core0.bin`
