#ifndef SERVO_MOTOR_IMPL_H
#define SERVO_MOTOR_IMPL_H

#include <Servo.h>
#include "ServoMotor.h"

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
        Servo servoMotor;
};

#endif