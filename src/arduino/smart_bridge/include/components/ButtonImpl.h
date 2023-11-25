#ifndef BUTTON_IMPL_H
#define BUTTON_IMPL_H

#include "Button.h"

// Implementation of a button.
class ButtonImpl: public Button {
    public:
        
        /* Default constructor.
         *
         * Parameters: 
         * 
         * - pin: the Arduino pin in which the button is plugged in.
         */
        ButtonImpl(const int pin);

        bool isPressed();

    private:
        int pin;
};

#endif