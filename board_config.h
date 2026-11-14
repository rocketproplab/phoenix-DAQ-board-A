// AV is allowed to touch parts of this file specifically labeled as such

#pragma once

// DO NOT TOUCH THIS
struct Valve {
  const char *name;
  uint8_t mask;
  uint8_t pin;
  bool state;
  unsigned long lastOpened;
};

// AV can comment/uncomment as they see fit
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
// DO NOT TOUCH THESE TWO LINES
const uint8_t *const BOARD_MAC = MAC_BOARD_A;
const char *const BOARD_NAME = "A";
// AV touchable
// These are the valves for board A (the middle board)
// If a valve gets moved, change them here
Valve valves[] = {
    {"LNG_PRES",  LNG_PRES_MASK, DRIVER_CH1_PIN, false, 0},
    {"LOX_PRESS", LOX_PRES_MASK, DRIVER_CH2_PIN, false, 0},
    {"LNG_FLOW",  LNG_FLOW_MASK, DRIVER_CH3_PIN, false, 0},
    {"LOX_FLOW",  LOX_FLOW_MASK, DRIVER_CH3_PIN, false, 0},
};
#else  // BOARD_B
// DO NOT TOUCH THESE TWO LINES
const uint8_t *const BOARD_MAC = MAC_BOARD_B;
const char *const BOARD_NAME = "B";
// AV touchable
// These are the valves for board B (the bottom board)
// If a valve gets moved, change them here
Valve valves[] = {
    {"LNG_VENT", LNG_VENT_MASK, DRIVER_CH1_PIN, false, 0},
    {"LOX_VENT", LOX_VENT_MASK, DRIVER_CH2_PIN, false, 0},
};
#endif
