#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
WS_DIR="${WS_DIR:-$ROOT_DIR/mcuxsdk_ws}"
BUILD_DIR="${BUILD_DIR:-$WS_DIR/build}"

# Normalize relative BUILD_DIR values from repo-root context.
if [[ "$BUILD_DIR" != /* ]]; then
  BUILD_DIR="$ROOT_DIR/$BUILD_DIR"
fi

source "$ROOT_DIR/tools/mcux_env.sh"

if [[ ! -d "$WS_DIR/.west" ]]; then
  echo "MCUX workspace missing at: $WS_DIR" >&2
  echo "Run: ./tools/setup_mcuxsdk_ws.sh" >&2
  exit 1
fi

if ! command -v LinkServer >/dev/null 2>&1; then
  echo "LinkServer not found on PATH." >&2
  exit 1
fi

EXPECTED_APP_NAME="edgeai_medical_device_demo"
EXPECTED_BIN_NAME="${EXPECTED_APP_NAME}_cm33_core0.bin"
EXPECTED_APP_PATH_FRAGMENT="demo_apps/${EXPECTED_APP_NAME}"

# Fail-fast safety gate: block flash when build artifacts do not match this project.
if [[ "${EDGEAI_FLASH_SAFETY_BYPASS:-0}" != "1" ]]; then
  if [[ ! -f "$BUILD_DIR/$EXPECTED_BIN_NAME" ]]; then
    echo "Flash blocked: expected artifact missing: $BUILD_DIR/$EXPECTED_BIN_NAME" >&2
    echo "Build this project first, then flash again." >&2
    exit 1
  fi

  if [[ -f "$BUILD_DIR/CMakeCache.txt" ]]; then
    if ! grep -q "$EXPECTED_APP_PATH_FRAGMENT" "$BUILD_DIR/CMakeCache.txt"; then
      echo "Flash blocked: build directory app does not match project (${EXPECTED_APP_NAME})." >&2
      echo "Hint: run a pristine build for this project before flashing." >&2
      exit 1
    fi
  fi
fi

(cd "$WS_DIR" && west flash -d "$BUILD_DIR" -r linkserver)
