#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task/Task.h"

#define MAX_TASKS 10

class Scheduler {
    public:

    void initialize(const int period);
    virtual bool addTask(Task* const task);
    virtual void tick();

    private:
    int schedulerPeriod;
    int actualTasksNum;
    Task* tasks[MAX_TASKS];
    void init();
};

#endif