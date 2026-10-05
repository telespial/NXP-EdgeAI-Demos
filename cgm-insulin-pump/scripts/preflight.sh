#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

required=(
  "docs/START_HERE.md"
  "docs/PROJECT_STATE.md"
  "docs/OPS_RUNBOOK.md"
  "docs/COMMAND_LOG.md"
)

for f in "${required[@]}"; do
  if [[ ! -f "$f" ]]; then
    echo "missing required file: $f" >&2
    exit 1
  fi
done

echo "preflight ok"
