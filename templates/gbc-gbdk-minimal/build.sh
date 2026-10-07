#!/usr/bin/env bash
# Build Harbor Lights (or a copied project) with GBDK-2020.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT"

export GBDK_DIR="${GBDK_DIR:-/opt/gbdk}"
if [[ ! -x "${GBDK_DIR}/bin/lcc" ]]; then
  echo "ERROR: lcc not found at ${GBDK_DIR}/bin/lcc" >&2
  echo "Run scripts/setup.sh from the handheld-forge plugin root." >&2
  exit 1
fi

SLUG="${SLUG:-harbor_lights}"
VERSION="${VERSION:-0.1}"
CLEAN=0
while [[ $# -gt 0 ]]; do
  case "$1" in
    --clean) CLEAN=1; shift ;;
    --version) VERSION="$2"; shift 2 ;;
    --slug) SLUG="$2"; shift 2 ;;
    *) echo "Unknown arg: $1" >&2; exit 2 ;;
  esac
done

if [[ "$CLEAN" -eq 1 ]]; then
  make clean GBDK_DIR="$GBDK_DIR"
fi

make all GBDK_DIR="$GBDK_DIR" SLUG="$SLUG" VERSION="$VERSION"
ROM="build/${SLUG}_v${VERSION}.gbc"
test -f "$ROM"
SIZE=$(wc -c < "$ROM" | tr -d ' ')
HASH=$(sha256sum "$ROM" | awk '{print $1}')
echo "ROM=$ROM"
echo "SIZE=$SIZE"
echo "SHA256=$HASH"
