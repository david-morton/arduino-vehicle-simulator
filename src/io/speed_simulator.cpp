#include "../debug_logging.h"
#include "../pin_assignments.h"
#include <Arduino.h>

#define SPEED_KPH_MIN 0
#define SPEED_KPH_MAX 200

static int lastSpeedKph    = -1;
static int currentSpeedKph = 0;

void setupSpeedOutputSimulator() {
  pinMode(SPEED_ANALOG_PIN, INPUT);
  DEBUG_GENERAL("Vehicle speed simulator initialized");
}

void updateSpeedFromAnalog() {
  int raw   = analogRead(SPEED_ANALOG_PIN);
  int speed = map(raw, 0, 1023, SPEED_KPH_MIN, SPEED_KPH_MAX);

  if (abs(speed - lastSpeedKph) >= 2) {
    DEBUG_CAN_SEND("Vehicle speed analog=%d mapped=%d kph", raw, speed);
    currentSpeedKph = speed;
    lastSpeedKph    = speed;
  }
}

int getSimulatedVehicleSpeed() {
  return currentSpeedKph;
}
