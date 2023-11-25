#include "task/GateTask.h"

extern bool openGate;

GateTask::GateTask(ServoMotor* const motor, const int period) : Task(period) {
    this->motor = motor;
    this->motor->on();
    this->motor->setAngle(0);
    state = CLOSE;
}

void GateTask::start() {
    switch (state) {
        case CLOSE:
            motor->setAngle(0);
            break;
        case OPEN:
            motor->setAngle(90);
            break;
    }
    state = openGate ? OPEN : CLOSE;
}
