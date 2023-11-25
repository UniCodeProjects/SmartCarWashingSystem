#ifndef TASK_H
#define TASK_H

class Task {
    public:
    
    Task(const int period) {
        taskPeriod = period;
        timeElapsed = 0;
    }

    virtual void start() = 0;

    bool canStart(const int schedulerPeriod) {
        timeElapsed += schedulerPeriod;
        if (timeElapsed >= taskPeriod) {
            timeElapsed = 0;
            return true;
        } else {
            return false;
        }
    }

    private:
    int taskPeriod;
    int timeElapsed;
};

#endif