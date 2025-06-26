#include <Arduino.h>
#include <mcp2515_can.h>

#include "../io/speed_simulator.h"
#include "../pin_assignments.h"
#include "can_sim_bmw.h"
#include "debug_logging.h"

#define CAN_ID_BMW_WHEEL_SPEED 0x1F0
#define CAN_ID_BMW_FAKE 0x300

mcp2515_can CAN_BMW(CS_PIN_BMW);

// Initializes the BMW CAN simulator by setting up the CAN bus at 500 kbps.
void setupCanSimBmw() {
  if (CAN_BMW.begin(CAN_500KBPS) == CAN_OK) {
    DEBUG_GENERAL("[CAN_BMW] Init OK");
  } else {
    DEBUG_ERROR("[CAN_BMW] Init failed");
  }
}

// Send simulated BMW wheel speed data over CAN.
void sendCanBmwWheelSpeed() {
  byte data[8];
  int  speedKph = getSimulatedVehicleSpeed();
  int  rawSpeed = speedKph * 16; // Match receiver's decoding scale

  for (int i = 0; i < 4; i++) {
    data[i * 2]     = rawSpeed & 0xFF;        // Lower 8 bits
    data[i * 2 + 1] = (rawSpeed >> 8) & 0x0F; // Upper 4 bits in low nibble
  }

  CAN_BMW.sendMsgBuf(CAN_ID_BMW_WHEEL_SPEED, 0, 8, data);
  DEBUG_CAN_SEND("Wheel speed sent: %d kph", speedKph);
}

// Send fake noise data over BMW CAN bus.
void sendCanBmwFakeNoise() {
  byte data[8];
  for (int i = 0; i < 8; i++)
    data[i] = random(0, 256);
  CAN_BMW.sendMsgBuf(CAN_ID_BMW_FAKE, 0, 8, data);
}
