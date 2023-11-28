#include "task/ButtonTask.h"

/// @brief The global variable to determine whether the button is pressed or not.
bool isBtnPressed;

ButtonTask::ButtonTask(Button* const button, const int period) : TaskImpl(period) {
    this->button = button;
}

void ButtonTask::start() {
    isBtnPressed = button->isPressed();
}
