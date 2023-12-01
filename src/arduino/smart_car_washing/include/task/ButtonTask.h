#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

#include "TaskImpl.h"
#include "components/Button.h"
#include "components/ButtonImpl.h"

/// @brief The button task.
class ButtonTask : public TaskImpl {
    public:
     /// @brief The button task constructor.
     /// @param button the button linked to this task
     /// @param period the task period in ms
     ButtonTask(Button* const button, const int period);

     /// @brief Starts the task and set the isBtnPressed global variable.
     void start();

    private:
     Button* button;
};

#endif
