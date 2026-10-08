# Elevator Simulator — Embedded Systems Project (SWB)

Coursework project for the **Embedded Systems (SWB)** course — a distributed elevator control system built on multiple **8052** microcontrollers, designed in **Keil µVision** and simulated in **Proteus (ISIS)**. Grade: **5** (highest).

## Project overview

The system simulates an elevator controlled by several independent microcontrollers connected over a shared **RS485** communication bus. The user selects a floor via a keypad, and the system drives the motors accordingly, displays the current floor, and logs executed commands on an LCD screen.

### Architecture (microcontrollers)

The project consists of four 8052 microcontrollers, each responsible for a different subsystem and communicating with the rest of the system over the RS485 bus (transceivers U2/U4/U6/U9):

| Microcontroller | File | Role |
|---|---|---|
| **U1** | `U1_Master.c` | Master unit — keypad input, overall system coordination |
| **U3** | `U3_7SEG.c` | Seven-segment display driver — shows the elevator's current floor |
| **U5** | `U5_Motor.c` | Motor control (elevator movement) via motor driver, plus indicator lights |
| **U8** | `U8_LCD.c` | LCD driver — prints executed commands/system messages |

### Other components

- **Keypad** (4×3 matrix) — floor selection / command input
- **Seven-segment display** — current elevator floor
- **LCD display** — log of commands/system messages
- **Motors + driver (U7)** — drive simulating the elevator cabin's movement
- **RS485/RS422 bus** — communication between microcontrollers

## Environment and tools

- **Keil µVision 4** — writing and compiling microcontroller code (C)
- **Proteus (ISIS)** — schematic design and full system simulation
- Microcontroller: **8052** family (e.g. AT89C52)

## Repository structure

```
.
├── src/
│   ├── U1_Master.c       # Master unit / keypad
│   ├── U3_7SEG.c         # Floor display
│   ├── U5_Motor.c        # Motor control
│   └── U8_LCD.c          # LCD display / command log
├── proteus/
│   └── PROJ2.pdsprj      # Proteus schematic and simulation project
├── keil/
│   └── Zadanie_projektowe.uvproj   # µVision project
├── docs/
│   └── schemat.png       # Schematic screenshot from Proteus
└── README.md
```

## How to run the simulation

1. Open `Zadanie_projektowe.uvproj` in **Keil µVision** and compile the project to a `.hex` file
2. Open `PROJ2.pdsprj` in **Proteus**
3. Load the compiled `.hex` file into the respective microcontrollers in the simulation
4. Run the simulation — select a floor on the keypad and observe the elevator moving, the floor display updating, and the log on the LCD

## Author

Szymon Trzaskowski

The base schematic for this project was partially provided by the course instructor, mgr inż. Marcin Goluch. The project code and schematic corrections were done independently. The project was defended with a grade of 5 (highest possible).
