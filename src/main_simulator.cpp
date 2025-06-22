#include "can/can_helpers.h"
#include "can/can_sim_bmw.h"
#include "can/can_sim_nissan.h"
#include "debug_logging.h"
#include "tasks/task_scheduler_setup.h"
#include <Arduino.h>

// Debug flag definitions
bool debugError      = true;
bool debugGeneral    = true;
bool debugCanSend    = true;
bool debugCanReceive = true;

/* ======================================================================
   SETUP
   ====================================================================== */
void setup() {
  Serial.begin(500000);
  while (!Serial)
    ;

  setupCanSimBmw();
  setupCanSimNissan();
  setupTaskScheduler();
}

/* ======================================================================
   MAIN LOOP
   ====================================================================== */
void loop() {
  runAllScheduledTasks();
  checkIncomingCan();
}
