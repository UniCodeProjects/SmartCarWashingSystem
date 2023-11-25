#ifndef BUTTON_H
#define BUTTON_H

// Class that represents a generic button.
class Button {
    public:
        // Returns true if the button is pressed, false otherwise.
        virtual bool isPressed() = 0;
};

#endif