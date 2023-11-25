#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

// Class that represents a generic servo motor.
class ServoMotor {

    public:

        // Turns on the motor.
        virtual void on() = 0;
        
        // Turns off the motor.
        virtual void off() = 0;

        /* Sets the current angle of the motor with the provided one.
         * 
         * Parameters:
         * - angle: The new angle of the motor. Its value must be between 0 and 179. Otherwise, the
         *          angle is not set.
         */
        virtual void setAngle(int angle) = 0;
};

#endif