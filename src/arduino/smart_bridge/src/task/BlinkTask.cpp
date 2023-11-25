#include "task/BlinkTask.h"

BlinkTask::BlinkTask(Led* const led, const int period): Task(period) {
    this->led = led;
    state = OFF;
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