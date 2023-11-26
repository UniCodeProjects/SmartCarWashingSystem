#include "task/BlinkTask.h"

BlinkTask::BlinkTask(Led* const led, const int period) : TaskImpl(period) {
    this->led = led;
    isBlinkEnabled = false;
    state = OFF;
}

bool BlinkTask::canBlink() {
    return this->isBlinkEnabled;
}

void BlinkTask::enableBlink() {
    this->isBlinkEnabled = true;
}

void BlinkTask::disableBlink() {
    this->isBlinkEnabled = false;
}

bool BlinkTask::canStart(const int schedulerPeriod) {
    /* if the blink is enabled, than the method canStart() of the superclass is called. In this way,
     * the value of the field timeElapsed is not updated when the blink is not enabled, avoiding problems.
     */
    return isBlinkEnabled ? TaskImpl::canStart(schedulerPeriod) : false;
}

Led* BlinkTask::getLed() {
    return led;
}

void BlinkTask::start() {
    switch (state) {
        case OFF:
            led->switchOn();
            state = ON;
            break;
        case ON:
            led->switchOff();
            state = OFF;
            break;
    }
}
