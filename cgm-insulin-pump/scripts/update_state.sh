#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

state_file="docs/PROJECT_STATE.md"
change=""
binary=""
command=""
result="ok"

while [[ $# -gt 0 ]]; do
  case "$1" in
    --change)
      change="$2"; shift 2 ;;
    --binary)
      binary="$2"; shift 2 ;;
    --command)
      command="$2"; shift 2 ;;
    --result)
      result="$2"; shift 2 ;;
    *)
      echo "unknown arg: $1" >&2; exit 1 ;;
  esac
done

if [[ -z "$change" ]]; then
  echo "--change is required" >&2
  exit 1
fi

date_iso="$(date -u +%Y-%m-%d)"
{
  echo
  echo "## Update ${date_iso}"
  echo "- Change: ${change}"
  [[ -n "$binary" ]] && echo "- Binary: ${binary}"
  [[ -n "$command" ]] && echo "- Command: ${command}"
  echo "- Result: ${result}"
} >> "$state_file"

echo "updated $state_file"
