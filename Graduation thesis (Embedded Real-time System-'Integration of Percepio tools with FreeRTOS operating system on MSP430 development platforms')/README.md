# Graduation Thesis — Integration of Percepio Tools with FreeRTOS on MSP430

**Thesis title**: *Integration of Percepio Tools with FreeRTOS Operating System on MSP430 Development Platforms*

**Level**: Bachelor graduation thesis, ETF (Faculty of Electrical Engineering)

---

## Overview

This project investigates and demonstrates the integration of **Percepio Tracealyzer** — a real-time trace visualisation tool — with the **FreeRTOS** operating system running on the **MSP430F5529** microcontroller.

The motivation is to bridge the gap between low-level embedded development and professional RTOS observability: Tracealyzer captures a live trace of the FreeRTOS scheduler, task states, and inter-task communication, and renders it as an interactive timeline that greatly simplifies debugging of timing and synchronisation issues.

---

## What it does

- Runs a FreeRTOS application (multiple tasks, semaphores, event groups) on the MSP430F5529
- Integrates the **Percepio TraceRecorder** library into the FreeRTOS build
- Streams or snapshots the runtime trace buffer
- Enables visualisation of:
  - Task execution timeline (which task ran, for how long)
  - Context-switch events and preemptions
  - Semaphore/event-group operations
  - CPU load per task

---

## Repository contents

```
Project code/
  SRV_Template/         — FreeRTOS application with Percepio TraceRecorder integrated
    main.c              — Task definitions and scheduler entry
    FreeRTOSConfig.h    — RTOS + trace configuration
    ETF5529_HAL/        — Board HAL (7-segment display, GPIO)
    FreeRTOS_source/    — FreeRTOS kernel
    drivers/            — MSP430 peripheral drivers (PMM, UCS)
```

---

## Key concepts demonstrated

| Concept | Detail |
|---------|--------|
| FreeRTOS internals | Deep understanding of the task scheduler, tick ISR, and context-switch hooks |
| Percepio TraceRecorder | Library integration — hook functions called by FreeRTOS on every scheduler event |
| RTOS observability | Capturing and exporting trace data for Tracealyzer desktop analysis |
| MSP430 platform | Linker script, memory map, clock system, and debug probe configuration |
| Embedded debugging | Using trace-based tools instead of printf or breakpoints for timing-sensitive bugs |

---

## Tools

- **Code Composer Studio (CCS)** — IDE and debugger
- **FreeRTOS** — Real-time operating system
- **Percepio Tracealyzer** — Trace visualisation desktop application
- **MSP430-GCC** — Compiler toolchain
