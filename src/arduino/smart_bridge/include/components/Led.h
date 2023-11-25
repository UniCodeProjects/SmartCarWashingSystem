#ifndef LED_H
#define LED_H

// Class that represents a generic led.
class Led {
    public:

        // Turns on the led.
        virtual void switchOn() = 0;

        // Turns off the led.
        virtual void switchOff() = 0;
};

#endif