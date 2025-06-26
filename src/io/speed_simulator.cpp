#include "../debug_logging.h"
#include "../pin_assignments.h"
#include <Arduino.h>

#define SPEED_KPH_MIN 0
#define SPEED_KPH_MAX 200

static int currentSpeedKph = 0;

// Initializes the speed output simulator by setting the analog pin mode.
void setupSpeedOutputSimulator() {
  pinMode(SPEED_ANALOG_PIN, INPUT);
  DEBUG_GENERAL("Vehicle speed simulator initialized");
}

// Reads the analog value from the speed sensor and maps it to a speed in kph.
void updateSpeedFromAnalog() {
  static unsigned long lastDebugMillis = 0;

  int raw   = analogRead(SPEED_ANALOG_PIN);
  int speed = map(raw, 0, 1023, SPEED_KPH_MAX, SPEED_KPH_MIN);

  currentSpeedKph = speed;

  unsigned long now = millis();
  if (now - lastDebugMillis >= 1000) {
    DEBUG_SENSORS("Vehicle speed analog=%d mapped=%d kph", raw, speed);
    lastDebugMillis = now;
  }
}

// This function should be called periodically to update the speed
int getSimulatedVehicleSpeed() {
  return currentSpeedKph;
}
