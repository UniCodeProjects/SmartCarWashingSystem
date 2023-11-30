#ifndef BLINK_TASK_H
#define BLINK_TASK_H

#include "TaskImpl.h"
#include "components/Led.h"

/// @brief The task that allows the blinking of a led.
class BlinkTask : public TaskImpl {
   public:
    /// @brief The blink task's default constructor.
    /// @param led The led that has to blink.
    /// @param period The task period.
    BlinkTask(Led* const led, int period);

    /// @brief Starts the task.
    void start();

    /// @brief Determines whether the task can start.
    /// @param schedulerPeriod the period of the scheduler that manages this task.
    /// @return true if the period of this task is reached and the blink is enabled, false otherwise.
    bool canStart(const int schedulerPeriod);

    /// @brief Returns whether the blinking is enabled.
    /// @return true if the led blinking is enabled, false otherwise.
    bool canBlink();

    /// @brief Enables the led blinking.
    void enableBlink();

    /// @brief Disables the led blinking.
    void disableBlink();

    /// @brief Retrieves the led managed by this blink task.
    /// @return The led managed by this blink task.
    Led* getLed();

   private:
    Led* led;
    enum { OFF, ON } state;
    bool isBlinkEnabled;
};

#endif
