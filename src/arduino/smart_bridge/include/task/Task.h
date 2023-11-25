#ifndef TASK_H
#define TASK_H

class Task {
   public:
    virtual void start() = 0;

    virtual bool canStart(const int schedulerPeriod) = 0;
};

#endif