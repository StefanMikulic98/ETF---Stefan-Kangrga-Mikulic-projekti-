# Microelectronic Circuits — EFM32 Display Drivers

Embedded firmware for the **EFM32 STK3700** development board, written in C as a university project for the *Microelectronic Circuits* course at ETF.

## Target hardware

- **MCU**: Silicon Labs EFM32 Giant Gecko (ARM Cortex-M3)
- **Board**: EFM32 STK3700
- **IDE**: Simplicity Studio
- **Toolchain**: GNU ARM Embedded

## What it does

- Drives the on-board **LCD display** (segment-based)
- Drives an external **OLED display** over **I2C**
- Manages interrupts for button or peripheral events
- Provides virtual UART retargeting for debug output

## Project structure

```
Main/
  lcd.c / lcd.h         — Segment LCD driver
  OLED_I2C.c / .h       — OLED display driver (I2C protocol)
  em_int.c / .h         — Interrupt enable/disable helpers
  retargetvirtual.c/.h  — Virtual COM port retargeting for printf
config/
  pin_config.h          — GPIO pin assignments for the STK3700 board
GNU ARM/                — ARM GCC build artefacts and linker output
```

## Key concepts demonstrated

| Concept | Detail |
|---------|--------|
| I2C communication | Bit-banged or hardware I2C to drive the OLED at the correct address and register map |
| LCD segment driver | Direct register writes to EFM32 LCD controller to display characters/numbers |
| GPIO configuration | Pin mode, drive strength, and pull-up/down settings via EFM32 CMSIS |
| Interrupt management | `em_int` wrappers for critical-section entry and exit |
| Embedded C best practices | HAL-style separation between platform drivers (`lcd.c`) and application |

## Building & flashing

Open the project in **Simplicity Studio**, select the EFM32 STK3700 target, build with the GNU ARM toolchain, and flash via the on-board J-Link debug probe.
