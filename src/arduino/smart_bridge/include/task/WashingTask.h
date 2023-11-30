#ifndef WASHING_TASK_H
#define WASHING_TASK_H

#include <LiquidCrystal_I2C.h>

#include "components/TempSensor.h"
#include "task/BlinkTask.h"
#include "task/TaskImpl.h"

class WashingTask : public TaskImpl {
   public:
    /// @brief WashingTask's default constructor.
    /// @param tempSensor The system's temperature sensor.
    /// @param lcd The user display.
    /// @param blinkTask The blink task of the led used during the washing phase.
    /// @param period The task period.
    WashingTask(TempSensor* const tempSensor, LiquidCrystal_I2C* lcd, BlinkTask* const blinkTask, const int period);

    /// @brief Starts the task.
    void start();

   private:
    TempSensor* temperatureSensor;
    LiquidCrystal_I2C* lcd;
    BlinkTask* blinkTask;
    enum { IDLE,
           READY,
           WASHING,
           WAITING_EMERGENCY,
           REQUIRED_PC_MAINTENANCE } state;
    bool washingComplete;  // TODO: this variable should be used to start the check-out task, so it must be exposed by the main task
    int washedCars; // TODO: remove this field and let the pc application updating the number of washed cars by himself thanks to a message sent by Arduino
    double temp;
    int washingTime;
    int elapsedEmergencyTimer;
    // Performs all the actions that need to be done during the washing phase.
    void wash();
    // Performs all the actions that need to be done at the end of the washing phase.
    void endWashing();
};

#endif
