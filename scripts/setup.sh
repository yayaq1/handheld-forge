#!/usr/bin/env bash
# Install GBDK-2020 and a PyBoy venv for Handheld Game Forge agents/devs.
set -euo pipefail

PLUGIN_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
GBDK_DIR="${GBDK_DIR:-/opt/gbdk}"
GBDK_VERSION="${GBDK_VERSION:-4.3.0}"
VENV="${HANDHELD_FORGE_VENV:-$PLUGIN_ROOT/.venv-pyboy}"

echo "==> GBDK-2020 → ${GBDK_DIR}"
if [[ -x "${GBDK_DIR}/bin/lcc" ]]; then
  echo "    already present"
else
  TMP="$(mktemp -d)"
  URL="https://github.com/gbdk-2020/gbdk-2020/releases/download/${GBDK_VERSION}/gbdk-linux64.tar.gz"
  echo "    downloading ${URL}"
  curl -fsSL "$URL" -o "$TMP/gbdk.tgz"
  tar -xzf "$TMP/gbdk.tgz" -C "$TMP"
  if [[ -d /opt ]] && [[ -w /opt || "$(id -u)" -eq 0 ]]; then
    sudo mkdir -p "$(dirname "$GBDK_DIR")"
    sudo rm -rf "$GBDK_DIR"
    sudo mv "$TMP/gbdk" "$GBDK_DIR"
  else
    LOCAL="$PLUGIN_ROOT/tools/gbdk"
    mkdir -p "$(dirname "$LOCAL")"
    rm -rf "$LOCAL"
    mv "$TMP/gbdk" "$LOCAL"
    GBDK_DIR="$LOCAL"
    echo "    installed to ${GBDK_DIR} (no /opt write access)"
  fi
  rm -rf "$TMP"
fi
"${GBDK_DIR}/bin/lcc" -v 2>&1 | head -1 || true
echo "GBDK_DIR=${GBDK_DIR}"

echo "==> PyBoy venv → ${VENV}"
if [[ ! -d "$VENV" ]]; then
  python3 -m venv "$VENV"
fi
# shellcheck disable=SC1091
source "$VENV/bin/activate"
pip install -q --upgrade pip
pip install -q pyboy pillow mido
python -c "from pyboy import PyBoy; print('PyBoy import OK')"
echo "VENV=${VENV}"
echo "Setup complete."
