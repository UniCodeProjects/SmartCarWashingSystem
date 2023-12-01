#ifndef GUARDS_MANAGER_H
#define GUARDS_MANAGER_H

/// @brief Manages the application's guard variables.
class GuardsManager {
   public:
    /// @brief Retrieves the manager's instance.
    /// @return the GuardsManager object
    static GuardsManager& getInstance();
    /// @brief Sets the guards variables needed for the washing task.
    void prepareForWashing();
    /// @brief Sets the guards variable needed for the check-out task.
    void prepareForCheckOut();
    /// @brief Sets the guards variable needed for the check-in task.
    void prepareForCheckIn();
    /// @brief Sets the value for the openGate guard variable.
    /// @param value the boolean value
    void setGateOpened(const bool value);
    /// @brief Sets the value for the vacant guard variable.
    /// @param value the boolean value
    void setVacant(const bool value);
    /// @brief Sets the value for the washStart guard variable.
    /// @param value the boolean value
    void setCanWashStart(const bool value);
    /// @brief Sets the value for the washingComplete guard variable.
    /// @param value the boolean value
    void setIsWashingComplete(const bool value);
    /// @brief Sets if the button is pressed or not.
    /// @param value the boolean value
    void setBtnPressed(const bool value);
    /// @brief Checks if the gate can be opened.
    /// @return true if opening allowed
    bool isGateOpen();
    /// @brief Checks if the washing area is vacant.
    /// @return true if vacant
    bool isVacant();
    /// @brief Checks if the washing phase can start.
    /// @return true if ready to wash
    bool canWashStart();
    /// @brief Checks if the washing is completed.
    /// @return true if completed
    bool isWashingComplete();
    /// @brief Checks if the button is pressed.
    /// @return true if pressed
    bool isBtnPressed();

   private:
    bool openGate = false;
    bool vacant = true;
    bool washStart = false;
    bool washingComplete = false;
    bool btnPressed = false;

    GuardsManager() {}
};

#endif
