#pragma once

#include <ptScheduler.h>

// Declare task instances so they are visible to main_simulator.cpp
extern ptScheduler taskBmwWheel;
extern ptScheduler taskBmwNoise;
extern ptScheduler taskNissanTemp;
extern ptScheduler taskNissanNoise;
extern ptScheduler rpmAnalogTask;
extern ptScheduler speedAnalogTask;

// Call all scheduled tasks
void runAllScheduledTasks();
