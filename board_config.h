#pragma once

struct Valve {
  const char *name;
  uint8_t mask;
  uint8_t pin;
  bool state;
  unsigned long lastOpened;
};

// Which board is this build for? Pick ONE.
// `make build BOARD=A|B` sets this for you. In Arduino IDE, uncomment a line:
// #define BOARD_A
// #define BOARD_B

#if !defined(BOARD_A) && !defined(BOARD_B)
#define BOARD_A  // default
#endif

#if defined(BOARD_A) && defined(BOARD_B)
#error "Define only one of BOARD_A or BOARD_B"
#endif

// Per-board setup: this board's MAC and which valve is on which channel.
#if defined(BOARD_A)
const uint8_t *const BOARD_MAC = MAC_BOARD_A;
const char *const BOARD_NAME = "A";
Valve valves[] = {
    {"LOX_PRES", LOX_PRES_MASK, DRIVER_CH1_PIN, false, 0},
    {"LOX_FLOW", LOX_FLOW_MASK, DRIVER_CH2_PIN, false, 0},
    {"LNG_VENT", LNG_VENT_MASK, DRIVER_CH3_PIN, false, 0},
};
#else  // BOARD_B
const uint8_t *const BOARD_MAC = MAC_BOARD_B;
const char *const BOARD_NAME = "B";
Valve valves[] = {
    {"LNG_PRES", LNG_PRES_MASK, DRIVER_CH1_PIN, false, 0},
    {"LNG_FLOW", LNG_FLOW_MASK, DRIVER_CH2_PIN, false, 0},
    {"LOX_VENT", LOX_VENT_MASK, DRIVER_CH3_PIN, false, 0},
};
#endif
