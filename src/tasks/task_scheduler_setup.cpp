#include "task_scheduler_setup.h"
#include "../can/can_sim_bmw.h"
#include "../can/can_sim_nissan.h"
#include "../io/rpm_simulator.h"
#include "../io/speed_simulator.h"

// Define actual scheduler task instances
ptScheduler taskBmwWheel(PT_TIME_20MS);
ptScheduler taskBmwNoise(PT_TIME_50MS);
ptScheduler taskNissanTemp(PT_TIME_100MS);
ptScheduler taskNissanNoise(PT_TIME_50MS);
ptScheduler rpmAnalogTask(PT_TIME_100MS);
ptScheduler speedAnalogTask(PT_TIME_100MS);

void runAllScheduledTasks() {
  if (taskBmwWheel.call())
    sendCanBmwWheelSpeed();
  if (taskBmwNoise.call())
    sendCanBmwFakeNoise();
  if (taskNissanTemp.call())
    sendCanNissanEngineTemp();
  if (taskNissanNoise.call())
    sendCanNissanFakeNoise();
  if (rpmAnalogTask.call())
    updateRpmFromAnalog();
  if (speedAnalogTask.call())
    updateSpeedFromAnalog();
}
