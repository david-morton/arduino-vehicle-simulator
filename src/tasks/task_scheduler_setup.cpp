#include "task_scheduler_setup.h"
#include "../can/can_sim_bmw.h"
#include "../can/can_sim_nissan.h"

// Define actual scheduler task instances
ptScheduler taskBmwWheel(100000);   // 100 ms
ptScheduler taskBmwNoise(50000);    // 50 ms
ptScheduler taskNissanTemp(200000); // 200 ms
ptScheduler taskNissanNoise(50000); // 50 ms

void setupTaskScheduler() {
  // Reserved for future config if needed
}

void runAllScheduledTasks() {
  if (taskBmwWheel.call())
    sendCanBmwWheelSpeed();
  if (taskBmwNoise.call())
    sendCanBmwFakeNoise();
  if (taskNissanTemp.call())
    sendCanNissanEngineTemp();
  if (taskNissanNoise.call())
    sendCanNissanFakeNoise();
}
