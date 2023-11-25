#include "task/ButtonTask.h"

bool isBtnPressed;

ButtonTask::ButtonTask(Button* const button, const int period) : Task(period) {
    this->button = button;
}

void ButtonTask::start() {
    isBtnPressed = button->isPressed();
}
