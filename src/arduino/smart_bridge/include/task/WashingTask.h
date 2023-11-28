#ifndef WASHING_TASK_H
#define WASHING_TASK_H

#include <LiquidCrystal_I2C.h>

#include "components/TempSensor.h"
#include "task/BlinkTask.h"
#include "task/TaskImpl.h"

class WashingTask : public TaskImpl {
   public:
    WashingTask(TempSensor* const tempSensor, LiquidCrystal_I2C* lcd, BlinkTask* const blinkTask, const int period);
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
};

#endif
