# STM32 Bare-Metal Traffic Light Controller

A bare-metal traffic light controller developed for the STM32F407 Discovery board without using STM32CubeIDE, HAL, or any RTOS.

This project was built from scratch using Embedded C, custom startup code, a custom linker script, GNU Make, OpenOCD, and GDB. The traffic controller is implemented as a finite state machine and uses the SysTick timer for non-blocking timing.

---

## Features

- Bare-metal Embedded C implementation
- Custom ARM Cortex-M4 startup code
- Custom linker script
- GNU Make build system
- SysTick interrupt configured for 1 ms system tick
- Non-blocking timing (no delay loops)
- Modular LED driver
- Traffic light finite state machine
- Pedestrian crossing mode
- Emergency override mode with highest priority
- Event-driven state transitions
- OpenOCD flashing support
- GDB debugging support

---

## Hardware

- STM32F407G Discovery Board
- ARM Cortex-M4 MCU
- On-board LEDs

| LED | Function |
|-----|----------|
| Green | Traffic Green |
| Orange | Traffic Yellow |
| Red | Traffic Red |
| Blue | Pedestrian / Emergency Indicator |

---

## Project Structure

```
.
├── main.c
├── main.h
├── traffic.c
├── traffic.h
├── led.c
├── led.h
├── stm32_startup.c
├── stm32_ls.ld
├── Makefile
└── README.md
```

---

## Traffic Light Sequence

```
GREEN (5 s)
      ↓
YELLOW (2 s)
      ↓
RED (5 s)
      ↓
GREEN
```

---

## Pedestrian Mode

When a pedestrian request is received:

```
GREEN
      ↓
YELLOW
      ↓
RED
      ↓
PEDESTRIAN
      ↓
GREEN
```

During pedestrian mode:

- Vehicle signal remains RED
- Blue LED blinks every 500 ms
- After the pedestrian timer expires, the controller returns to GREEN

---

## Emergency Mode

Emergency requests have the highest priority.

```
ANY STATE
      ↓
EMERGENCY
      ↓
GREEN
```

During emergency mode:

- Vehicle signal remains RED
- Blue LED blinks rapidly
- After the emergency timer expires, the controller returns to GREEN

---

## Software Architecture

```
                SysTick Interrupt (1 ms)
                        │
                        ▼
                traffic_update()
                        │
                        ▼
              Traffic State Machine
                        │
                        ▼
                 LED Driver Layer
                        │
                        ▼
               STM32 GPIO Registers
```

---

## Finite State Machine

```
             +---------+
             | GREEN   |
             +---------+
                  |
                  v
             +---------+
             | YELLOW  |
             +---------+
                  |
                  v
             +---------+
             |  RED    |
             +---------+
             /         \
            /           \
           v             v
 +----------------+   +--------+
 | PEDESTRIAN     |   | GREEN  |
 +----------------+   +--------+
          |
          v
      +--------+
      | GREEN  |
      +--------+

Emergency request from any state

        ANY STATE
             |
             v
      +--------------+
      | EMERGENCY    |
      +--------------+
             |
             v
         GREEN
```

---

## Building

```bash
make
```

---

## Flashing

Start OpenOCD:

```bash
make download
```

In another terminal:

```bash
arm-none-eabi-gdb final.elf
```

Connect to OpenOCD:

```gdb
target remote localhost:3333
load
monitor reset init
continue
```

---

## Debugging

The project was debugged using:

- OpenOCD
- ARM GDB
- Hardware breakpoints
- Register inspection
- Step-by-step debugging

---

## Concepts Practiced

- Embedded C
- Bare-metal firmware development
- ARM Cortex-M4 architecture
- Startup code
- Linker script writing
- Vector table
- Interrupt handling
- SysTick timer
- GPIO programming
- Finite State Machines (FSM)
- Event-driven programming
- Driver abstraction
- GNU Make
- OpenOCD
- GDB debugging
- Git & GitHub

---

## Future Improvements

- Push-button support using EXTI interrupts
- UART-based command interface
- LCD/OLED display
- Countdown timer display
- Buzzer for pedestrian crossing
- Configurable traffic timings
- Multiple traffic junction support

---

## Author

**Amalraj K**


