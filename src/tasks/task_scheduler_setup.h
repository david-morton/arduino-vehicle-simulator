#pragma once

#include <ptScheduler.h>

// Declare task instances so they are visible to main_simulator.cpp
extern ptScheduler taskBmwWheel;
extern ptScheduler taskBmwNoise;
extern ptScheduler taskNissanTemp;
extern ptScheduler taskNissanNoise;

// Setup (currently empty but reserved for future use)
void setupTaskScheduler();

// Call all scheduled tasks
void runAllScheduledTasks();
