#!/usr/bin/env bash
# Build a GBDK project (defaults to the bundled template).
set -euo pipefail
PLUGIN_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
PROJECT="${1:-$PLUGIN_ROOT/templates/gbc-gbdk-minimal}"
shift || true

if [[ ! -f "$PROJECT/build.sh" && ! -f "$PROJECT/Makefile" ]]; then
  echo "ERROR: not a GBDK project: $PROJECT" >&2
  exit 1
fi

export GBDK_DIR="${GBDK_DIR:-/opt/gbdk}"
if [[ ! -x "${GBDK_DIR}/bin/lcc" && -x "$PLUGIN_ROOT/tools/gbdk/bin/lcc" ]]; then
  export GBDK_DIR="$PLUGIN_ROOT/tools/gbdk"
fi

if [[ -x "$PROJECT/build.sh" ]]; then
  exec "$PROJECT/build.sh" "$@"
fi

# Fallback: bare Makefile
make -C "$PROJECT" all GBDK_DIR="$GBDK_DIR" "$@"
