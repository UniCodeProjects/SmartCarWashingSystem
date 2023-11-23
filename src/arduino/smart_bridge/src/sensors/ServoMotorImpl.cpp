#include "../../include/sensors/ServoMotorImpl.h"

#define MOTOR_MIN_POSITION 0
#define MOTOR_MAX_POSITION 179

ServoMotorImpl::ServoMotorImpl(const int pin) {
    this->pin = pin;
}

void ServoMotorImpl::on() {
    servoMotor.attach(this->pin);
}

void ServoMotorImpl::off() {
    servoMotor.detach();
}

void ServoMotorImpl::setPosition(const int position) {
    if (position >= MOTOR_MIN_POSITION && position <= MOTOR_MAX_POSITION) {
        servoMotor.write(position);
    }
}