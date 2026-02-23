#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

echo "[flash_safe] project=edgeai_package_transport_anomaly_demo"
"$ROOT_DIR/tools/flash_frdmmcxn947.sh"
