/// @brief Manages the application's guard variables.
class GuardsManager {
    public:
     /// @brief Retrieves the manager's instance.
     /// @return the GuardsManager object
     static GuardsManager& getInstance() {
        static GuardsManager instance;
        return instance;
     }

     // TODO: add setters.

     /// @brief Sets if the button is pressed or not.
     /// @param value the boolean value
     void setBtnPressed(const bool value) {
        btnPressed = value;
     }

     /// @brief Checks if the gate can be opened.
     /// @return true if opening allowed
     bool isGateOpen() {
        return openGate;
     }

     /// @brief Checks if the washing area is vacant.
     /// @return true if vacant
     bool isVacant() {
        return vacant;
     }
     
     /// @brief Checks if the washing phase can start.
     /// @return true if ready to wash
     bool canWashStart() {
        return washStart;
     }

     /// @brief Checks if the washing is completed.
     /// @return true if completed
     bool isWashingComplete() {
        return washingComplete;
     }

     /// @brief Checks if the button is pressed.
     /// @return true if pressed
     bool isBtnPressed() {
        return btnPressed;
     }

    private:
     bool openGate = false;
     bool vacant = true;
     bool washStart = false;
     bool washingComplete = false;
     bool btnPressed = false;

     GuardsManager() {}
};
