#ifndef BLINK_TASK_H
#define BLINK_TASK_H

#include "TaskImpl.h"
#include "components/Led.h"

class BlinkTask : public TaskImpl {
   public:
    BlinkTask(Led* const led, int period);
    void start();
    /// @brief Determines whether the task can start.
    /// @param schedulerPeriod the period of the scheduler that manages this task.
    /// @return true if the period of this task is reached and the blink is enabled, false otherwise.
    bool canStart(const int schedulerPeriod);
    bool canBlink();
    void enableBlink();
    void disableBlink();

   private:
    Led* led;
    enum { OFF, ON } state;
    bool isBlinkEnabled;
};

#endif
