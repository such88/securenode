# SecureNode — Zephyr Multi-Board Template

> Zephyr RTOS template supporting **STM32F407 Discovery** and **ESP32 DevKitC** out of the box.

[![Zephyr CI](https://github.com/yourusername/securenode/actions/workflows/ci.yml/badge.svg)](https://github.com/yourusername/securenode/actions)

---

## Compatibility

| Component   | Version |
|-------------|---------|
| Zephyr RTOS | v3.5.0  |
| Zephyr SDK  | 0.17.0  |
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
├── not_shipped_LR_GD/
│   ├── Linear_regression/              ← CGPA vs Package prediction models
│   ├── matrix/                         ← Matrix operations (inversion)
│   ├── matrix_mul_perf/                ← Matrix multiplication performance analysis
│   └── cache_info.txt                  ← Caching details
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

---

## Not Shipped – Research & Experimental Code

The `not_shipped_LR_GD/` directory contains experimental and research-phase code not integrated into the main SecureNode runtime. These modules explore ML prediction models and performance optimization techniques for embedded systems.

### Linear Regression (CGPA vs Package Prediction)

**Location:** `not_shipped_LR_GD/Linear_regression/`

Machine learning module for predicting job package offers based on academic CGPA.

| File                 | Purpose                                          |
|----------------------|--------------------------------------------------|
| `gen_cgpa_pkg_data.c` | Generates synthetic CGPA vs package training data with realistic correlation |
| `gen_cgpa_pkg_data.h` | Data structure definitions (ROW_COUNT, COL_COUNT)            |
| `single_lr.c`        | Linear regression implementation (slope/intercept calculation) |
| `placement.csv`      | Sample dataset: CGPA and corresponding package offers         |
| `Makefile`           | Standalone compilation target                              |

**How it works:**
- Generates random CGPA values (6.0–10.0) with probabilistic package correlations
- Calculates mean CGPA and package across dataset
- Computes linear regression coefficients (slope `m`, intercept `b`)
- Predicts package = `m × CGPA + b`

**Compile standalone:**
```bash
cd not_shipped_LR_GD/Linear_regression
make
./single_lr
```

---

### Matrix Operations

**Location:** `not_shipped_LR_GD/matrix/`

Matrix algebra utilities for linear algebra computations.

| File               | Purpose                          |
|--------------------|----------------------------------|
| `matrix_inverse.c` | Matrix inversion implementation  |

Used as a foundation for advanced ML algorithms and numerical methods.

---

### Matrix Multiplication Performance Analysis

**Location:** `not_shipped_LR_GD/matrix_mul_perf/`

Benchmarking and optimization exploration for matrix multiplication on embedded platforms.

| File                  | Purpose                                          |
|-----------------------|--------------------------------------------------|
| `matrix_mul_perf.cpp` | C++ performance test harness                     |
| `matrix_mul.py`       | Python reference implementation for validation   |
| `types.h`             | Data type definitions for matrices               |
| `performance_log`     | Logged benchmarks from previous test runs        |

**Use cases:**
- Benchmarking matrix operations on STM32F407 vs ESP32
- Evaluating optimization techniques (SIMD, cache locality)
- Predicting runtime overhead for ML inference

---

### Caching Information

**Location:** `not_shipped_LR_GD/cache_info.txt`

Documents CPU cache characteristics and optimization notes for both target platforms (STM32F407 and ESP32).

---

## Status

These modules are **research-phase** and **not shipped** with the production SecureNode build. They serve as:
- **Reference implementations** for ML and numerical algorithms
- **Performance benchmarks** for embedded systems capability assessment
- **Development sandbox** for future feature prototyping

To integrate components, copy relevant source files to `src/` and update `CMakeLists.txt`.

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
