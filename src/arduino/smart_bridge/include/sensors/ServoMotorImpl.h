#ifndef SERVO_MOTOR_IMPL_H
#define SERVO_MOTOR_IMPL_H

#include "ServoMotor.h"
#include <Arduino.h>
#include <ServoTimer2.h>

// Implementation of a servo motor.
class ServoMotorImpl: public ServoMotor {

    public:

        /*
         * Default constructor.
         * 
         * Parameters:
         * - pin: the Arduino pin in which the motor is plugged in. The pin must support PWM.
         */
        ServoMotorImpl(const int pin);

        void on();
        void off();
        void setPosition(const int position);

    private:

        int pin;
        ServoTimer2 servoMotor;
};

#endif