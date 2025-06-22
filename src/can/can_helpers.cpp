#include <Arduino.h>
#include <mcp2515_can.h>
#include "can_sim_bmw.h"
#include "can_sim_nissan.h"

#include "can_sim_bmw.h"
#include "can_sim_nissan.h"

void checkIncomingCan() {
  struct Bus {
    const char* label;
    mcp2515_can* bus;
  };

  Bus buses[] = {
    { "BMW", &CAN_BMW },
    { "NISSAN", &CAN_NISSAN }
  };

  for (auto& b : buses) {
    while (b.bus->checkReceive() == CAN_MSGAVAIL) {
      unsigned long id;
      byte len;
      byte buf[8];
      b.bus->readMsgBuf(&len, buf);
      id = b.bus->getCanId();

      Serial.print("[");
      Serial.print(b.label);
      Serial.print(" RX] ID 0x");
      Serial.print(id, HEX);
      Serial.print(": ");
      for (byte i = 0; i < len; i++) {
        Serial.print(buf[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
}
