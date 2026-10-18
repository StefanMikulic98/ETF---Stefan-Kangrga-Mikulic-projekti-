# Real-Time Programming — Mine Safety Monitoring System (Ada)

A concurrent real-time simulation of a mine water-pump and gas-monitoring system, written in **Ada** using tasks, protected objects, and rendezvous-based synchronisation, as a university project for the *Real-Time Programming* course at ETF.

## What it does

The system simulates and controls a mine shaft environment:

- **Nature** simulates an observed physical phenomenon (e.g. water level) as a periodically-updated random walk, which can be "controlled" (increased/decreased) by signals from the pump.
- **PumpControlStation** monitors water level (high/low boundary detector) and water flow, and drives a water pump through a protected interrupt handler (`WaterPumpInterruptHandler`) that reacts to high/low level events.
- **EnvironmentMonitoringStation** periodically polls CO, methane (CH4), and airflow sensors, raises an alarm when any value exceeds its critical boundary, and logs status to file.
- **ControlRoom** ties the stations together: an automatic monitoring task enforces the safety interlock — the pump is forced off whenever the methane level is critical, even if the water level would otherwise call for pumping (to avoid igniting gas) — plus a `UserInput` task for manual pump commands from the operator.
- **Sensor / RegularSensor** are reusable task types representing generic and periodic (with explicit period and deadline) sensors, used to model CO, methane, and airflow sensors.

## Project structure

```
main.adb                           — Program entry point
nature.ads / nature.adb            — Simulated environment phenomenon (random walk task)
sensor.ads / sensor.adb            — Generic sensor task type
regularsensor.ads / regularsensor.adb — Periodic sensor task type (period + deadline)
pumpcontrolstation.ads / .adb      — Water level/flow sensors, pump task, interrupt handler
environmentmonitoringstation.ads / .adb — CO / methane / airflow monitoring & alarms
controlroom.ads / controlroom.adb  — Operator input + automatic safety-interlock logic
```

## Key concepts demonstrated

| Concept | Detail |
|---------|--------|
| Ada tasking | Multiple concurrent task types (`NatureTask`, `Sensor`, `RegularSensor`, `HighLowWaterDetector`, `WaterFlowSensor`, `WaterPump`, `EnvironmentMonitoringStationTask`, `UserInput`, `ControlRoom`) |
| Rendezvous | Task entries (`accept`) used for synchronous data exchange between tasks (`SetValue`, `GetValueDataRegister`, …) |
| `select` statements | Non-deterministic selection between multiple entry calls and a periodic `delay until` branch |
| Protected objects | `WaterPumpInterruptHandler` models an interrupt handler with guarded entries (`entry ... when evenOccurred`) |
| Periodic tasks | `Ada.Real_Time` clocks (`delay until nextActivationSensor`) with fixed periods; `RegularSensor` additionally tracks explicit deadlines |
| Safety interlock | Automatic shutdown of the pump when a critical gas (CH4) level is detected, overriding the water-level-driven control logic |
| File logging | Each station periodically appends timestamped status lines to a log file (`Ada.Calendar`, `Ada.Text_IO`) |

## Building & running

Compile with GNAT (GNU Ada compiler):

```bash
gnatmake main.adb
./main
```
