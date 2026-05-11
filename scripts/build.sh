#!/bin/bash
# SecureNode build helper
# Usage: ./scripts/build.sh [stm32|esp32|qemu]
set -e

BOARD=${1:-qemu}
APP_DIR=$(cd "$(dirname "$0")/.." && pwd)

case "$BOARD" in
  stm32) BOARD_NAME="stm32f4_disco" ;;
  esp32) BOARD_NAME="esp32_devkitc_wroom/esp32/procpu" ;;
  qemu)  BOARD_NAME="qemu_cortex_m3" ;;
  *)
    echo "Usage: $0 [stm32|esp32|qemu]"
    exit 1
    ;;
esac

echo "======================================="
echo " Building SecureNode → $BOARD_NAME"
echo "======================================="
west build -p auto -b "$BOARD_NAME" "$APP_DIR"
echo ""
echo "Done → build/zephyr/zephyr.elf"
