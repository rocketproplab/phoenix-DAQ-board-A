# phoenix-fc-valve-board
Phoenix Flight Computer: valve boards. One codebase builds both boards.

- **Board A** (middle board, #2): LOX - P, LOX - F, LNG - V
- **Board B** (bottom board, #3): LNG - P, LNG - F, LOX - V



## Last updated
11/14/2026

## ESP32 DevKit / ESP32-WROOM-32 — Ground-Station Actuator

### IMPORTANT NOTE:
`pins.h` contains the pinouts for the MOSFET Driver and W5500. If you change the physical pinouts, you ***MUST*** change them in `pins.h` or else it won't be reflected in code.

### MOSFET Driver

| Channel | GPIO |
|---------|------|
| CH1 | GPIO 13 |
| CH2 | GPIO 33 |
| CH3 | GPIO 12 |
| CH4 | GPIO 27 |

### W5500 Ethernet

| Signal | GPIO |
|--------|------|
| MISO | GPIO 32 |
| RST | GPIO 26 |
| MOSI | GPIO 23 |
| SCK | GPIO 18 |
| CS | GPIO 5 |

## Board A / Board B builds
One codebase serves both boards. The board select is `board_config.h`; each board's MAC and valve-to-channel list is the `#if defined(BOARD_A)` block in the `.ino`.

- `make build BOARD=A` / `make build BOARD=B`
- `make flash BOARD=B PORT=/dev/cu.usbserial-XXXX`
- Arduino IDE: uncomment `#define BOARD_A` or `#define BOARD_B` in `board_config.h`.
