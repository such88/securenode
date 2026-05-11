#!/bin/bash
# SecureNode flash helper
# Usage: ./scripts/flash.sh [stm32|esp32]
set -e

case "${1:-stm32}" in
  stm32)
    echo "Flashing STM32F407 via OpenOCD (ST-Link)..."
    west flash --runner openocd
    ;;
  esp32)
    echo "Flashing ESP32 via esptool..."
    west flash --runner esp32
    ;;
  *)
    echo "Usage: $0 [stm32|esp32]"
    exit 1
    ;;
esac
