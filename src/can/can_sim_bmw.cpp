#include <Arduino.h>
#include <mcp2515_can.h>

#include "../io/speed_simulator.h"
#include "../pin_assignments.h"
#include "can_sim_bmw.h"
#include "debug_logging.h"

#define CAN_ID_BMW_WHEEL_SPEED 0x1F0
#define CAN_ID_BMW_FAKE 0x300

mcp2515_can CAN_BMW(CS_PIN_BMW);

void setupCanSimBmw() {
  if (CAN_BMW.begin(CAN_500KBPS) == CAN_OK) {
    DEBUG_GENERAL("[CAN_BMW] Init OK");
  } else {
    DEBUG_ERROR("[CAN_BMW] Init failed");
  }
}

void sendCanBmwWheelSpeed() {
  byte data[8];
  int  speedKph = getSimulatedVehicleSpeed();
  int  speedRaw = speedKph * 20; // Assuming 0.05 km/h resolution like OEM

  data[0] = highByte(speedRaw);
  data[1] = lowByte(speedRaw);

  uint16_t speed = speedKph * 10;
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
