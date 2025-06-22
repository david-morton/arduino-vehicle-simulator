#include "can/can_helpers.h"
#include "can/can_sim_bmw.h"
#include "can/can_sim_nissan.h"
#include "tasks/task_scheduler_setup.h"
#include <Arduino.h>

void setup() {
  Serial.begin(500000);
  while (!Serial)
    ;

  setupCanSimBmw();
  setupCanSimNissan();
  setupTaskScheduler();
}

void loop() {
  runAllScheduledTasks();
  checkIncomingCan();
}
