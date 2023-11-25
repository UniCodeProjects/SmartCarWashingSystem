#include "task/ButtonTask.h"

bool isBtnPressed;

ButtonTask::ButtonTask(Button* const button, const int period) : TaskImpl(period) {
    this->button = button;
}

void ButtonTask::start() {
    isBtnPressed = button->isPressed();
}
