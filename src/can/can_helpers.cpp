#include <Arduino.h>
#include <mcp2515_can.h>

#include "can_sim_bmw.h"
#include "can_sim_nissan.h"
#include "debug_logging.h"

void checkIncomingCan() {
  struct Bus {
    const char  *label;
    mcp2515_can *bus;
  };

  Bus buses[] = {
      {"BMW", &CAN_BMW},
      {"NISSAN", &CAN_NISSAN}};

  for (auto &b : buses) {
    while (b.bus->checkReceive() == CAN_MSGAVAIL) {
      unsigned long id;
      byte          len;
      byte          buf[8];
      b.bus->readMsgBuf(&len, buf);
      id = b.bus->getCanId();

      char  payload[64] = {0};
      char *p           = payload;
      for (byte i = 0; i < len; i++) {
        p += sprintf(p, "%02X ", buf[i]);
      }

      DEBUG_CAN_RECEIVE("CAN RX on %s ID 0x%lX: %s", b.label, id, payload);
    }
  }
}
