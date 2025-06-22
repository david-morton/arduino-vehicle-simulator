#include "can_sim_bmw.h"
#include <Arduino.h>
#include <mcp2515_can.h>

#define CS_PIN_BMW 10
#define CAN_ID_BMW_WHEEL_SPEED 0x1F0
#define CAN_ID_BMW_FAKE 0x300

mcp2515_can CAN_BMW(CS_PIN_BMW);

void setupCanSimBmw() {
  if (CAN_BMW.begin(CAN_500KBPS) == CAN_OK) {
    Serial.println("[CAN_BMW] Ready");
  } else {
    Serial.println("[CAN_BMW] Init failed");
  }
}

void sendCanBmwWheelSpeed() {
  byte     data[8];
  int      speedKph = random(0, 200);
  uint16_t speed    = speedKph * 10;
  for (int i = 0; i < 4; i++) {
    data[i * 2 + 0] = highByte(speed);
    data[i * 2 + 1] = lowByte(speed);
  }
  CAN_BMW.sendMsgBuf(CAN_ID_BMW_WHEEL_SPEED, 0, 8, data);
}

void sendCanBmwFakeNoise() {
  byte data[8];
  for (int i = 0; i < 8; i++)
    data[i] = random(0, 256);
  CAN_BMW.sendMsgBuf(CAN_ID_BMW_FAKE, 0, 8, data);
}