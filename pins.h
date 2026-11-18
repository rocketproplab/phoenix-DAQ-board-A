// AV is explicitly allowed to modify this file and required to do so when updating pinouts
//
// Again, if you change the board pinouts change this file
// Historically that wasn't communicated and you can imagine how poorly that could go
// So make sure to do it and double check with ESP wiring

// W5500 pins
constexpr uint8_t W5500_MISO = 32;
constexpr uint8_t W5500_RST  = 26;
constexpr uint8_t W5500_MOSI = 23;
constexpr uint8_t W5500_SCK  = 18;
constexpr uint8_t W5500_CS   = 5;

// Four MOSFET-driver inputs
constexpr uint8_t DRIVER_CH1_PIN = 13;
constexpr uint8_t DRIVER_CH2_PIN = 33;
constexpr uint8_t DRIVER_CH3_PIN = 12;
constexpr uint8_t DRIVER_CH4_PIN = 27;
