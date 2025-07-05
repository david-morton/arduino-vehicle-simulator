#include <Arduino.h>
#include <ptScheduler.h>

#include "can/can_helpers.h"
#include "can/can_sim_bmw.h"
#include "can/can_sim_nissan.h"
#include "debug_logging.h"
#include "io/rpm_simulator.h"
#include "io/speed_simulator.h"
#include "tasks/task_scheduler_setup.h"

/* ======================================================================
    DEBUG FLAGS
   ====================================================================== */

bool debugError       = true;
bool debugGeneral     = false;
bool debugCanSend     = false;
bool debugCanReceive  = false;
bool debugSensors     = false;
bool debugPerformance = true;

/* ======================================================================
   VARIABLES: General use / functional
   ====================================================================== */

unsigned long arduinoLoopExecutionCount = 0;

/* ======================================================================
   SCHEDULER TASKS
   ====================================================================== */

ptScheduler ptReportArduinoPerformanceStats = ptScheduler(PT_TIME_10S);

/* ======================================================================
   SETUP
   ====================================================================== */

void setup() {
  Serial.begin(500000);
  while (!Serial)
    ;

  setupCanSimBmw();
  setupCanSimNissan();
  setupRpmOutputSimulator();
  setupSpeedOutputSimulator();
}

/* ======================================================================
   MAIN LOOP
   ====================================================================== */

void loop() {
  runAllScheduledTasks();
  checkIncomingCan();

  // Increment loop counter and report on performance stats if needed
  if (debugPerformance && millis() > 10000) {
    if (ptReportArduinoPerformanceStats.call()) {
      reportArduinoLoopRate(&arduinoLoopExecutionCount);
    }
  }
  arduinoLoopExecutionCount++;
}
