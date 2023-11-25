#ifndef TASK_H
#define TASK_H

class Task {
   public:
    Task(const int period) {
        this->period = period;
        this->timeElapsed = 0;
    }

    virtual void start() = 0;

    bool canStart(const int schedulerPeriod) {
        timeElapsed += schedulerPeriod;
        if (timeElapsed >= period) {
            timeElapsed = 0;
            return true;
        } else {
            return false;
        }
    }

   private:
    int period;
    int timeElapsed;
};

#endif