#ifndef LED_IMPL_H
#define LED_IMPL_H

#include "Led.h"

// Implementation of a led.
class LedImpl: public Led {

    public:
    
        /* Default constructor.
         *
         * Parameters:
         * 
         * - pin: the Arduino pin in which the led is plugged in.
         */
        LedImpl(const int pin);
        
        void switchOn();
        void switchOff();

    private:
        
        int pin;
};

#endif