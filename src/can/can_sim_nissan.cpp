#include <Arduino.h>
#include <mcp2515_can.h>

#include "../pin_assignments.h"
#include "can_sim_nissan.h"
#include "debug_logging.h"

#define CAN_ID_NISSAN_TEMP 0x551
#define CAN_ID_NISSAN_FAKE 0x666

mcp2515_can CAN_NISSAN(CS_PIN_NISSAN);

void setupCanSimNissan() {
  if (CAN_NISSAN.begin(CAN_500KBPS) == CAN_OK) {
    DEBUG_GENERAL("[CAN_NISSAN] Init OK");
  } else {
    DEBUG_ERROR("[CAN_NISSAN] Init failed");
  }
}

void sendCanNissanEngineTemp() {
  byte     data[2];
  uint16_t temp = random(70, 110) * 10;
  data[0]       = highByte(temp);
  data[1]       = lowByte(temp);
  CAN_NISSAN.sendMsgBuf(CAN_ID_NISSAN_TEMP, 0, 2, data);
}

void sendCanNissanFakeNoise() {
  byte data[8];
  for (int i = 0; i < 8; i++)
    data[i] = random(0, 256);
  CAN_NISSAN.sendMsgBuf(CAN_ID_NISSAN_FAKE, 0, 8, data);
}