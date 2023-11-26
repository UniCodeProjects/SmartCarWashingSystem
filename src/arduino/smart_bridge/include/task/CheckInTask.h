#ifndef CHECK_IN_TASK_H
#define CHECK_IN_TASK_H

#include "TaskImpl.h"
#include "components/Pir.h"
#include "components/PirImpl.h"
#include "components/Sonar.h"
#include "components/SonarImpl.h"
#include "components/Led.h"
#include "components/LedImpl.h"
#include <LiquidCrystal_I2C.h>
#include "task/BlinkTask.h"

#define OPEN_GATE_TIME_MS 5000
#define CLOSE_GATE_TIME_MS 1000
#define SONAR_MIN_DIST_M 0.1

class CheckInTask : public TaskImpl {
    public:
     CheckInTask(Pir* const pir, Sonar* const sonar, LiquidCrystal_I2C* const lcd, Led* const led, BlinkTask* const blinkTask, const int period);
     void start();

    private:
     Pir* pir;
     Sonar* sonar;
     LiquidCrystal_I2C* lcd;
     Led* led;
     BlinkTask* blinkTask;
     enum { IDLE, SLEEP, DETECTED, GATE_CROSSING, GATE_HOLDING } state;
     bool detected;
     int timeElapsed;
};

#endif
