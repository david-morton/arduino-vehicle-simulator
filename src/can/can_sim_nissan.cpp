#include "can_sim_nissan.h"
#include <Arduino.h>
#include <mcp2515_can.h>

#define CS_PIN_NISSAN 9
#define CAN_ID_NISSAN_TEMP 0x545
#define CAN_ID_NISSAN_FAKE 0x666

mcp2515_can CAN_NISSAN(CS_PIN_NISSAN);

void setupCanSimNissan() {
  if (CAN_NISSAN.begin(CAN_500KBPS) == CAN_OK) {
    Serial.println("[CAN_NISSAN] Ready");
  } else {
    Serial.println("[CAN_NISSAN] Init failed");
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