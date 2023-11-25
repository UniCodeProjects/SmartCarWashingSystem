#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

#include "Task.h"
#include "components/Button.h"
#include "components/ButtonImpl.h"

class ButtonTask : public Task {
    public:
     ButtonTask(Button* const button, const int period);
     void start();

    private:
     Button* button;
};

#endif
