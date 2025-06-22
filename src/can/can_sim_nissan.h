#pragma once

#include "mcp2515_can.h"

void setupCanSimNissan();
void sendCanNissanEngineTemp();
void sendCanNissanFakeNoise();

extern mcp2515_can CAN_NISSAN;
