# SecureNode — Zephyr Multi-Board Template

> Zephyr RTOS template supporting **STM32F407 Discovery** and **ESP32 DevKitC** out of the box.

[![Zephyr CI](https://github.com/yourusername/securenode/actions/workflows/ci.yml/badge.svg)](https://github.com/yourusername/securenode/actions)

---

## Compatibility

| Component   | Version |
|-------------|---------|
| Zephyr RTOS | v3.5.0  |
| Zephyr SDK  | 0.16.5  |
| Python      | 3.12+   |

---

## Project Structure

```
securenode/
├── src/
│   └── main.c                          ← app entry point
├── include/
│   └── securenode.h                    ← shared headers
├── overlays/
│   ├── stm32f4_disco.overlay           ← STM32 pins / UART / LED
│   └── esp32_devkitc_wroom.overlay     ← ESP32 pins / UART / LED
├── config/
│   ├── stm32f4_disco.conf              ← STM32 Kconfig
│   └── esp32_devkitc_wroom.conf        ← ESP32 Kconfig
├── scripts/
│   ├── build.sh                        ← build helper
│   └── flash.sh                        ← flash helper
├── .github/workflows/ci.yml            ← GitHub Actions (3 boards)
├── CMakeLists.txt                      ← auto-loads overlay + conf
├── prj.conf                            ← common Kconfig
└── Kconfig                             ← app Kconfig symbols
```

---

## Quick Start

```bash
# 1. Clone
git clone https://github.com/yourusername/securenode
cd securenode

# 2. Build for QEMU (no hardware needed)
./scripts/build.sh qemu
west build -t run
# Press Ctrl+A then X to exit

# 3. Build for STM32F407
./scripts/build.sh stm32

# 4. Build for ESP32
./scripts/build.sh esp32
```

---

## Flash

```bash
# STM32F407 via ST-Link (OpenOCD)
./scripts/flash.sh stm32

# ESP32 via USB (esptool)
./scripts/flash.sh esp32
```

---

## Serial Output

```bash
# STM32F407 Discovery → ST-Link virtual COM port
minicom -D /dev/ttyACM0 -b 115200

# ESP32 DevKitC → CP210x USB-UART bridge
minicom -D /dev/ttyUSB0 -b 115200
```

> Tip: Inside minicom press Ctrl+A → O → Serial port setup → set Hardware flow = No

---

## Board Pin Reference

### STM32F407 Discovery

| Signal  | Pin  | Notes                        |
|---------|------|------------------------------|
| LED0    | PD12 | Green onboard LED            |
| UART TX | PA2  | USART2, routed via ST-Link   |
| UART RX | PA3  | USART2, routed via ST-Link   |

### ESP32 DevKitC WROOM

| Signal  | GPIO  | Notes                        |
|---------|-------|------------------------------|
| LED0    | GPIO2 | Blue onboard LED             |
| UART TX | GPIO1 | UART0, USB-UART bridge       |
| UART RX | GPIO3 | UART0, USB-UART bridge       |

---

## How Board Auto-Detection Works

`CMakeLists.txt` automatically loads the right overlay and conf for the selected board:

```
west build -b stm32f4_disco .
                │
                ├── overlays/stm32f4_disco.overlay  ← pins, UART, LED
                └── config/stm32f4_disco.conf       ← Kconfig options

west build -b esp32_devkitc_wroom/esp32/procpu .
                │
                ├── overlays/esp32_devkitc_wroom.overlay
                └── config/esp32_devkitc_wroom.conf
```

No manual switching required — just change `-b`.

---

## Adding a New Board

1. Create `overlays/<new_board>.overlay` with LED and UART nodes
2. Create `config/<new_board>.conf` with board Kconfig
3. Add a case to `scripts/build.sh`
4. Add a matrix entry to `.github/workflows/ci.yml`

---

## CI/CD

GitHub Actions builds all 3 targets on every push and pull request.
ELF + MAP files are uploaded as downloadable artifacts per board.
