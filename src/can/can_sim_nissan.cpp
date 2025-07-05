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
  unsigned char data[8];
  uint16_t      temp = random(70, 105);
  data[0]            = temp + 40;
  CAN_NISSAN.sendMsgBuf(CAN_ID_NISSAN_TEMP, 0, 8, data);
  DEBUG_CAN_SEND("Engine temp sent: %d C", temp - 40);
}

void sendCanNissanFakeNoise() {
  byte data[8];
  for (int i = 0; i < 8; i++)
    data[i] = random(0, 256);
  CAN_NISSAN.sendMsgBuf(CAN_ID_NISSAN_FAKE, 0, 8, data);
}