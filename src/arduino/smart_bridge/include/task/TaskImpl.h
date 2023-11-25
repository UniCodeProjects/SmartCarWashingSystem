#ifndef TASK_IMPL_H
#define TASK_IMPL_H

#include "Task.h"

class TaskImpl : public Task {
   public:
    TaskImpl(const int period);

    virtual void start() = 0;

    virtual bool canStart(const int schedulerPeriod);

   private:
    int period;
    int timeElapsed;
};

#endif