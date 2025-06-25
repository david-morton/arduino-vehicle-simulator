#include <Arduino.h>

#include "../debug_logging.h"
#include "../pin_assignments.h"

// RPM range
const int RPM_MIN = 0;
const int RPM_MAX = 8000;

// Pulses per revolution for this engine
const float PULSES_PER_REV = 3.0;

void setupRpmOutputSimulator() {
  pinMode(RPM_OUTPUT_PIN, OUTPUT);
  digitalWrite(RPM_OUTPUT_PIN, LOW);
  DEBUG_GENERAL("RPM simulator initialized");
}

// Update RPM output based on analog input
void updateRpmFromAnalog() {
  static int lastRpm = -9999; // Start far out of range to ensure first log

  int potValue = analogRead(RPM_ANALOG_PIN);
  int rpm      = map(potValue, 0, 1023, RPM_MIN, RPM_MAX);

  if (rpm <= 0) {
    if (lastRpm != 0) {
      noTone(RPM_OUTPUT_PIN);
      DEBUG_SENSORS("RPM output disabled (0 RPM)");
      lastRpm = 0;
    }
    return;
  }

  // Skip update if change is too small
  if (abs(rpm - lastRpm) < 10)
    return;

  float freq   = rpm * (PULSES_PER_REV / 60.0); // Hz
  int   freqHz = (int)(freq + 0.5);

  tone(RPM_OUTPUT_PIN, freq);
  DEBUG_SENSORS("RPM analog=%d mapped=%d -> freq=%d Hz", potValue, rpm, freqHz);
  lastRpm = rpm;
}
