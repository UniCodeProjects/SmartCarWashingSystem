#include "task/ButtonTask.h"
#include "GuardsManager.h"

ButtonTask::ButtonTask(Button* const button, const int period) : TaskImpl(period) {
    this->button = button;
}

void ButtonTask::start() {
    GuardsManager::getInstance().setBtnPressed(button->isPressed());
}
