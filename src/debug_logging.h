#pragma once

#include <Arduino.h>

// ======================================================================
// Debug category flags (defined in main_simulator.cpp)
// ======================================================================

extern bool debugError;
extern bool debugGeneral;
extern bool debugCanSend;
extern bool debugCanReceive;

// ======================================================================
// Timestamp printer
// ======================================================================

inline void printDebugTimestamp() {
  unsigned long ms    = millis();
  unsigned long sec   = ms / 1000;
  unsigned long milli = ms % 1000;
  unsigned long mins  = sec / 60;
  unsigned long hours = mins / 60;
  sec                 = sec % 60;
  mins                = mins % 60;

  char buf[20];
  snprintf(buf, sizeof(buf), "[%02lu:%02lu:%02lu.%03lu] ", hours, mins, sec, milli);
  Serial.print(buf);
}

// ======================================================================
// Base debug print macro
// ======================================================================
#define _DEBUG_PRINTF(enabled, tag, fmt, ...)           \
  do {                                                  \
    if (enabled) {                                      \
      char _buf[256];                                   \
      snprintf(_buf, sizeof(_buf), fmt, ##__VA_ARGS__); \
      printDebugTimestamp();                            \
      Serial.print("[DEBUG ");                          \
      Serial.print(tag);                                \
      Serial.print("] ");                               \
      Serial.println(_buf);                             \
    }                                                   \
  } while (0)

// ======================================================================
// Logging category wrappers
// ======================================================================
#define DEBUG_ERROR(fmt, ...) _DEBUG_PRINTF(debugError, "ERROR", fmt, ##__VA_ARGS__)
#define DEBUG_GENERAL(fmt, ...) _DEBUG_PRINTF(debugGeneral, "GENERAL", fmt, ##__VA_ARGS__)
#define DEBUG_CAN_SEND(fmt, ...) _DEBUG_PRINTF(debugCanSend, "CAN SEND", fmt, ##__VA_ARGS__)
#define DEBUG_CAN_RECEIVE(fmt, ...) _DEBUG_PRINTF(debugCanReceive, "CAN RECEIVE", fmt, ##__VA_ARGS__)
