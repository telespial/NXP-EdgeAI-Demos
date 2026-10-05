#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

state_file="docs/PROJECT_STATE.md"
build_cmd="${BUILD_CMD:-}"

if [[ -z "$build_cmd" && -f "$state_file" ]]; then
  build_cmd="$(sed -n 's/^- Build Command:[[:space:]]*//p' "$state_file" | head -n1)"
fi

if [[ -z "$build_cmd" ]]; then
  echo "Build Command is empty. Set BUILD_CMD or docs/PROJECT_STATE.md" >&2
  exit 1
fi

echo "running: $build_cmd"
bash -lc "$build_cmd"
