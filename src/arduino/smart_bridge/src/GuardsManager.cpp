/// @brief Manages the application's guard variables.
class GuardsManager {
   public:
    /// @brief Retrieves the manager's instance.
    /// @return the GuardsManager object
    static GuardsManager& getInstance() {
        static GuardsManager instance;
        return instance;
    }

    /// @brief Sets the guards variables needed for the washing task.
    void prepareForWashing() {
        openGate = false;
        vacant = false;
        washStart = true;
    }

    /// @brief Sets the guards variable needed for the check-out task.
    void prepareForCheckOut() {
        washingComplete = true;
        washStart = false;
    }

    /// @brief Sets the guards variable needed for the check-in task.
    void prepareForCheckIn() {
        openGate = false;
        vacant = true;
    }

    /// @brief Sets the value for the openGate guard variable.
    /// @param value the boolean value
    void setGateOpened(const bool value) {
        openGate = value;
    }

    /// @brief Sets the value for the vacant guard variable.
    /// @param value the boolean value
    void setVacant(const bool value) {
        vacant = value;
    }

    /// @brief Sets the value for the washStart guard variable.
    /// @param value the boolean value
    void setCanWashStart(const bool value) {
        washStart = value;
    }

    /// @brief Sets the value for the washingComplete guard variable.
    /// @param value the boolean value
    void setIsWashingComplete(const bool value) {
        washingComplete = value;
    }

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
