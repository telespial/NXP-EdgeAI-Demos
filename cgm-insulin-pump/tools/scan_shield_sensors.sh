#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${BUILD_DIR:-mcuxsdk_ws/build_sensor_scan}"
UART_DEV="${UART_DEV:-/dev/ttyACM0}"
CAPTURE_SEC="${CAPTURE_SEC:-30}"

if [[ "$BUILD_DIR" != /* ]]; then
  BUILD_DIR="$ROOT_DIR/$BUILD_DIR"
fi

echo "[scan] Cleaning build dir: $BUILD_DIR"
rm -rf "$BUILD_DIR"

echo "[scan] Building sensor-scan firmware..."
(
  cd "$ROOT_DIR"
  EDGEAI_WEST_BUILD_ARGS="-DEDGEAI_SENSOR_SCAN_MODE=OFF -DEDGEAI_SHIELD_SCAN_DIAG=ON -DEDGEAI_SHIELD_SENSOR_SCAN_LOG=ON" \
    BUILD_DIR="$BUILD_DIR" ./tools/build_frdmmcxn947.sh debug
)

echo "[scan] Flashing..."
(
  cd "$ROOT_DIR"
  BUILD_DIR="$BUILD_DIR" ./tools/flash_frdmmcxn947.sh
)

TS="$(date +%Y%m%d_%H%M%S)"
RAW="$ROOT_DIR/captures/uart_raw_${TS}_sensor_scan.log"
CLEAN="$ROOT_DIR/captures/uart_raw_${TS}_sensor_scan_clean.log"

echo "[scan] Capturing UART from $UART_DEV for ${CAPTURE_SEC}s..."
stty -F "$UART_DEV" 115200 cs8 -cstopb -parenb -ixon -ixoff -echo raw
timeout "${CAPTURE_SEC}s" cat "$UART_DEV" > "$RAW" || true
tr -d '\000' < "$RAW" > "$CLEAN"

echo "[scan] Capture: $CLEAN"
echo "[scan] Summary:"
PATTERN="SENSOR_SCAN_MODE|SHIELD scan|SHIELD probe|SHIELD_SHUB|SHIELD_(GYRO|MAG|BARO|SHT|STTS)"
if command -v rg >/dev/null 2>&1; then
  rg -n "$PATTERN" "$CLEAN" -S || true
else
  grep -En "$PATTERN" "$CLEAN" || true
fi
