#include "../../include/sensors/ServoMotorImpl.h"
#include <ServoTimer2.h>

#define MOTOR_MIN_POSITION 0
#define MOTOR_MAX_POSITION 179
#define ANGLE_COEFFICIENT 8.33
#define ZERO_DEGREE_VALUE 750.0

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
        servoMotor.write(ZERO_DEGREE_VALUE + (ANGLE_COEFFICIENT * position));
    }
}