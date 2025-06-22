# CAN Simulator Project

This project simulates BMW and Nissan CAN traffic using two MCP2515 CAN bus modules and an Arduino Uno R4 (or compatible). It is structured for scalability and is compatible with the architecture of the main "Arduino CAN Plus Boost Control" project.

## Features

- Dual CAN bus support (BMW and Nissan)
- Sends:
  - BMW wheel speed data on CAN ID `0x1F0`
  - Nissan engine coolant temp on CAN ID `0x545`
- Injects noise traffic:
  - BMW: CAN ID `0x300`
  - Nissan: CAN ID `0x666`
- Structured with ptScheduler for clean task timing
- Modular design for extending to:
  - Simulated digital I/O (e.g., clutch, neutral switch)
  - RPM trigger simulation (via digital interrupt)
  - Scenario-based simulation logic

## Wiring (MCP2515 modules)

| Signal | BMW CAN Module | Nissan CAN Module |
|--------|----------------|-------------------|
| CS     | D10            | D9                |
| INT    | (not used)     | (not used)        |
| SPI    | Shared (MOSI/MISO/SCK)

## File Structure

- `src/main_simulator.cpp` — Entry point
- `src/can/` — CAN message simulation logic
- `src/tasks/` — Scheduler setup
- `src/io/` — Future expansion for simulated inputs

## PlatformIO

This project uses PlatformIO for building and flashing:
```bash
pio run
pio upload
pio monitor
```

Ensure `ptScheduler` and `mcp2515_can` libraries are included via `platformio.ini`.

## Extending

To add new simulation behaviors, define new functions in the appropriate module (e.g., `io/` for digital pins, `can/` for traffic). Register the function in `task_scheduler_setup.cpp`.

---