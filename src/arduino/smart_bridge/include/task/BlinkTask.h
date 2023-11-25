#ifndef BLINK_TASK_H
#define BLINK_TASK_H

#include "Task.h"
#include "components/Led.h"

class BlinkTask : public Task {
   public:
    BlinkTask(Led* const led, int period);
    void start();

   private:
    Led* led;
    enum { OFF, ON } state;
};

#endif