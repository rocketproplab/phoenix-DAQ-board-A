// UNLESS YOU ARE IN SOFTWARE, DO NOT TOUCH THIS FILE

#include <SPI.h>
#include "w5500.h"
#include "constants.h"
// Again, UPDATE pins.h IF YOU CHANGE PHYSICAL PINOUTS
#include "pins.h"
#include "board_config.h"

constexpr size_t NUM_VALVES = sizeof(valves) / sizeof(valves[0]);

uint8_t buffer[256];
uint8_t rocketState = 0;
bool ethernetReady = false;

// Explicit custom SPI routing: CS, SCK, MISO, MOSI.
Wiznet5500 w5500(W5500_CS, W5500_SCK, W5500_MISO, W5500_MOSI);

void setAllValvesOff() {
  for (size_t i = 0; i < NUM_VALVES; i++) {
    valves[i].state = false;
    analogWrite(valves[i].pin, 0);
  }
}

void resetW5500() {
  // W5500 RSTn is active low. Datasheet minimum low time is 500 us.
  pinMode(W5500_RST, OUTPUT);
  digitalWrite(W5500_RST, HIGH);
  delay(1);
  digitalWrite(W5500_RST, LOW);
  delay(1);
  digitalWrite(W5500_RST, HIGH);
  delay(2);
}

void setup() {
  Serial.begin(115200);
  delay(100);

  // Put actuator outputs in their safe OFF state before bringing up Ethernet.
  for (size_t i = 0; i < NUM_VALVES; i++) {
    pinMode(valves[i].pin, OUTPUT);
    digitalWrite(valves[i].pin, LOW);
    analogWriteFrequency(valves[i].pin, PWM_FREQUENCY_HZ);
  }

  // Keep W5500 deselected during reset/startup.
  pinMode(W5500_CS, OUTPUT);
  digitalWrite(W5500_CS, HIGH);
  resetW5500();

  ethernetReady = w5500.begin(BOARD_MAC);

  if (!ethernetReady) {
    Serial.println("ERROR: W5500 failed to enter MACRAW mode. Outputs remain OFF.");
    setAllValvesOff();
    return;
  }

  Serial.print("ESP32 actuator initialized, board ");
  Serial.println(BOARD_NAME);
  Serial.printf("W5500: MISO=%u RST=%u MOSI=%u SCK=%u CS=%u\n",
                W5500_MISO, W5500_RST, W5500_MOSI, W5500_SCK, W5500_CS);
  Serial.printf("MOSFET inputs: CH1=%u CH2=%u CH3=%u CH4=%u\n",
                DRIVER_CH1_PIN, DRIVER_CH2_PIN, DRIVER_CH3_PIN, DRIVER_CH4_PIN);
}

void receiveRocketState() {
  if (!ethernetReady) {
    return;
  }

  uint16_t len;
  while ((len = w5500.readFrame(buffer, sizeof(buffer))) > 0) {
    // Destination MAC (6) + source MAC (6) + EtherType (2) + state byte (1)
    if (len < 15) {
      continue;
    }

    // Custom EtherType 0x63E4 from the original project.
    if (buffer[12] != 0x63 || buffer[13] != 0xE4) {
      continue;
    }

    const uint8_t newState = buffer[14] & 0x7F;
    if (newState != rocketState) {
      rocketState = newState;
      Serial.println("----------");
      Serial.print("Received Rocket State: ");
      Serial.println(rocketState, BIN);
    }
  }
}

void updateValveStates() {
  for (size_t i = 0; i < NUM_VALVES; i++) {
    const bool shouldBeOpen = (rocketState & valves[i].mask) != 0;

    if (shouldBeOpen && !valves[i].state) {
      Serial.print(valves[i].name);
      Serial.println(": OPENING");
      valves[i].state = true;
      valves[i].lastOpened = millis();
    } else if (!shouldBeOpen && valves[i].state) {
      Serial.print(valves[i].name);
      Serial.println(": CLOSING");
      valves[i].state = false;
    }
  }
}

void applyValveVoltages() {
  for (size_t i = 0; i < NUM_VALVES; i++) {
    if (valves[i].state) {
      const unsigned long elapsed = millis() - valves[i].lastOpened;
      const uint8_t pwm = (elapsed > OPEN_MILLIS) ? HOLD_PWM : OPEN_PWM;
      analogWrite(valves[i].pin, pwm);
    } else {
      analogWrite(valves[i].pin, 0);
    }
  }
}

void loop() {
  if (!ethernetReady) {
    setAllValvesOff();
    delay(100);
    return;
  }

  receiveRocketState();
  updateValveStates();
  applyValveVoltages();
}
