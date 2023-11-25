#include "scheduler/Scheduler.h"
#include <TimerOne.h>

#define ONE_MILLISEC_IN_MICROSEC 1000

volatile bool canLaunchTasks;

void reachPeriod() {
    canLaunchTasks = true;
}

void Scheduler::initialize(const int period) {
    schedulerPeriod = period;
    canLaunchTasks = false;
    actualTasksNum = 0;
    Scheduler::init();
}

void Scheduler::init() {
    Timer1.initialize(ONE_MILLISEC_IN_MICROSEC * schedulerPeriod);
    Timer1.attachInterrupt(reachPeriod);
}

bool Scheduler::addTask(Task* const task) {
    if (actualTasksNum < MAX_TASKS - 1) {
        tasks[actualTasksNum] = task;
        actualTasksNum++;
        return true;
    } else {
        return false;
    }
}

void Scheduler::tick() {
    if (canLaunchTasks) {
        canLaunchTasks = false;
        for (int i = 0; i < actualTasksNum; i++) {
            if (tasks[i]->canStart(schedulerPeriod)) {
                tasks[i]->start();
            }
        }
    }
}
