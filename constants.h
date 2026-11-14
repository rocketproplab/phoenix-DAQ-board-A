// Timing for solenoids
constexpr unsigned long OPEN_MILLIS = 500;
constexpr uint8_t OPEN_PWM = 255;
constexpr uint8_t HOLD_PWM = 77;
constexpr uint32_t PWM_FREQUENCY_HZ = 200;  // Conservative value for the linked MOSFET module

// MAC addresses
static const uint8_t MAC_GROUND_STATION[6] = {0x02, 0x47, 0x53,
                                              0x00, 0x00, 0x01}; // GS: ground station
static const uint8_t MAC_BOARD_B[6] = {0x02, 0x52, 0x56,
                                       0x00, 0x00, 0x02}; // board B (bottom, formerly vent board)
static const uint8_t MAC_BOARD_A[6] = {0x02, 0x46, 0x4C,
                                       0x00, 0x00, 0x03}; // board A (middle, formerly flow valve board)
static const uint8_t MAC_SENSOR_GIGA[6] = {0x02, 0x53, 0x49,
                                           0x00, 0x00, 0x04}; // sensor

static const uint8_t LNG_PRES_MASK = 0b1000000; // LNG Pressurant / Upstream
static const uint8_t LOX_PRES_MASK = 0b0100000; // LOX Pressurant / Upstream
static const uint8_t LNG_FLOW_MASK = 0b0001000; // LNG Flow / Downstream
static const uint8_t LNG_VENT_MASK = 0b0000100; // LNG Vent
static const uint8_t LOX_FLOW_MASK = 0b0000010; // Lox Flow / Downstream
static const uint8_t LOX_VENT_MASK = 0b0000001; // LOX Vent
