#ifndef CHECK_OUT_TASK_H
#define CHECK_OUT_TASK_H

#include <LiquidCrystal_I2C.h>

#include "components/Led.h"
#include "TaskImpl.h"
#include "components/Sonar.h"
#include "components/TempSensor.h"

class CheckOutTask : public TaskImpl {
   public:
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
