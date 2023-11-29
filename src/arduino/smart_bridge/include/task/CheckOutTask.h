#ifndef CHECK_OUT_TASK_H
#define CHECK_OUT_TASK_H

#include <LiquidCrystal_I2C.h>

#include "TaskImpl.h"
#include "components/Led.h"
#include "components/Sonar.h"
#include "components/TempSensor.h"

/// @brief The task that allows the user to perform the checkout
class CheckOutTask : public TaskImpl {
   public:
    /// @brief The check-out task's default constructor.
    /// @param lcd the user display.
    /// @param led the led that has to be switched on during the check-out.
    /// @param sonar the system's sonar.
    /// @param temperatureSensor the system's temperature sensor.
    /// @param period the task period.
    CheckOutTask(LiquidCrystal_I2C* lcd, Led* const led, Sonar* const sonar, TempSensor* const temperatureSensor, const int period);

    void start();

   private:
    LiquidCrystal_I2C* lcd;
    Led* led;
    Sonar* sonar;
    TempSensor* temperatureSensor;
    int timeElapsed;
    enum { IDLE,
           GATE_HOLDING } state;
};

#endif
