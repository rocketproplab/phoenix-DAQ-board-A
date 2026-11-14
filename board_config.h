#pragma once

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
