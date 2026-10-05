#!/usr/bin/env bash
set -euo pipefail

# Create/update a local MCUX SDK west workspace under ./mcuxsdk_ws.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
WS_DIR="${WS_DIR:-$ROOT_DIR/mcuxsdk_ws}"

# Pin to a known-good MCUX manifest revision.
MCUX_MANIFEST_URL="${MCUX_MANIFEST_URL:-https://github.com/nxp-mcuxpresso/mcuxsdk-manifests.git}"
MCUX_MANIFEST_REV="${MCUX_MANIFEST_REV:-a2a4de055a35e20ea7de66f3afe4303f6fdc0934}"

# Some MCUX manifest revisions reference SHAs which are no longer reachable in
# upstream remotes. Exclude those projects so `west update` can complete for
# typical demo builds.
DEFAULT_MCUX_PROJECT_FILTER="-metering,-touch,-canopennode,-qcbor,-g2d_dpu,-mcux-sdk-middleware-mpp"
MCUX_PROJECT_FILTER="${MCUX_PROJECT_FILTER:-$DEFAULT_MCUX_PROJECT_FILTER}"

echo "[setup] repo: $ROOT_DIR"
echo "[setup] ws:   $WS_DIR"

mkdir -p "$WS_DIR"

if [[ ! -d "$WS_DIR/.west" ]]; then
  echo "[setup] west init"
  (
    cd "$WS_DIR"
    west init -m "$MCUX_MANIFEST_URL"
  )
fi

echo "[setup] ensuring manifest revision: $MCUX_MANIFEST_REV"
(
  cd "$WS_DIR"
  if ! git -C manifests cat-file -e "$MCUX_MANIFEST_REV^{commit}" 2>/dev/null; then
    git -C manifests fetch -q origin
  fi
  git -C manifests checkout -q "$MCUX_MANIFEST_REV"
)

echo "[setup] west config: manifest.project-filter"
(
  cd "$WS_DIR"
  if ! west config manifest.project-filter >/dev/null 2>&1; then
    echo "[setup] setting manifest.project-filter: $MCUX_PROJECT_FILTER"
    west config manifest.project-filter -- "$MCUX_PROJECT_FILTER"
  else
    echo "[setup] manifest.project-filter already set; leaving as-is"
  fi
)

echo "[setup] west update (this can take a while)"
(
  cd "$WS_DIR"
  for i in 1 2 3; do
    echo "[setup] west update attempt $i/3"
    if west update --fetch-opt=--depth=1; then
      exit 0
    fi
    sleep 2
  done
  echo "[setup] shallow west update failed; retrying without --depth=1 (can be slower, but avoids missing pinned commits)" >&2
  if west update; then
    exit 0
  fi
  echo "[setup] west update failed after retries; re-run this script." >&2
  exit 1
)

echo "[setup] installing edgeai_smart_pong_demo wrapper into mcuxsdk/examples"
(
  cd "$ROOT_DIR"
  MCUX_EXAMPLES_DIR="$WS_DIR/mcuxsdk/examples" ./sdk_example/install_mcux_overlay.sh
)

echo "[setup] applying workspace patches"
"$ROOT_DIR/tools/patch_mcuxsdk.sh" "$WS_DIR"

echo "[setup] done"
