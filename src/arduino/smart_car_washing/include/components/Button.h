#ifndef BUTTON_H
#define BUTTON_H

/// @brief Class that represents a generic button.
class Button {
    public:
     /// @brief Retrieves if a button is pressed.
     /// @return true if pressed, false otherwise.
     virtual bool isPressed() = 0;
};

#endif
