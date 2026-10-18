# Embedded Real-Time System — FreeRTOS on MSP430

A real-time embedded application running on the **MSP430F5529** microcontroller, developed in **Code Composer Studio** as a university project for the *Embedded Real-Time Systems* course at ETF.

## Target hardware

- **MCU**: Texas Instruments MSP430F5529
- **Development board**: ETF5529 (university custom board)
- **IDE**: Code Composer Studio (CCS)
- **RTOS**: FreeRTOS

## What it does

- Runs multiple concurrent FreeRTOS tasks at different priority levels
- Handles hardware button inputs (S1, S4) via interrupt-driven GPIO
- Reads analogue values through an ADC task
- Controls a 7-segment display via a dedicated HAL driver
- Uses FreeRTOS synchronisation primitives (semaphores, event groups) for inter-task communication

## Project structure

```
main.c              — Task definitions, scheduler start, hardware init
util.c              — Shared utility functions
FreeRTOSConfig.h    — RTOS kernel configuration (tick rate, heap size, priorities)
ETF5529_HAL/
  hal_7seg.c        — 7-segment display driver
  hal_ETF_5529.h    — Board-level HAL interface
FreeRTOS_source/    — FreeRTOS kernel source (tasks, queues, semaphores, event groups)
drivers/
  pmm.c/h           — Power Management Module driver
  ucs.c/h           — Unified Clock System driver
lnk_msp430f5529.cmd — Linker script for memory map
```

## Key concepts demonstrated

| Concept | Detail |
|---------|--------|
| FreeRTOS multi-tasking | Three+ tasks at priorities 1–3 running concurrently under the FreeRTOS scheduler |
| Semaphores | Binary semaphores for synchronising button-press events with processing tasks |
| Event groups | Bit-flag based signalling between tasks without queues |
| Hardware abstraction | HAL layer isolates peripheral drivers (display, clocks, power) from application logic |
| Interrupt-driven I/O | Button presses handled in ISRs; deferred processing via FreeRTOS task notification |
| Clock & power management | UCS (Unified Clock System) and PMM (Power Management Module) configured at startup |

## Building & flashing

Open the project in **Code Composer Studio**, build with the MSP430-GCC toolchain, and flash via USB-JTAG debug probe.
