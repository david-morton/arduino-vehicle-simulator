#pragma once

#include "mcp2515_can.h"

void setupCanSimBmw();
void sendCanBmwWheelSpeed();
void sendCanBmwFakeNoise();

extern mcp2515_can CAN_BMW;
