#ifndef CHECK_IN_TASK_H
#define CHECK_IN_TASK_H

#include "TaskImpl.h"
#include "components/Pir.h"
#include "components/PirImpl.h"
#include "components/Sonar.h"
#include "components/SonarImpl.h"
#include "components/Led.h"
#include "components/LedImpl.h"
#include "components/TempSensor.h"
#include "components/TempSensorImpl.h"
#include <LiquidCrystal_I2C.h>
#include "task/BlinkTask.h"

/// @brief The required time to wait before the gate can be opened.
#define OPEN_GATE_TIME_MS 5000
/// @brief The required time to wait before the gate can be closed.
#define CLOSE_GATE_TIME_MS 1000
/// @brief The minimum distance from the sonar that is required to close the gate.
#define SONAR_MIN_DIST_M 0.1

/// @brief The check-in task performed at the gate entrance.
class CheckInTask : public TaskImpl {
    public:
     /// @brief The check-in constructor.
     /// @param pir the passive infrared sensor before the gate
     /// @param sonar the sonar in the washing area
     /// @param tempSensor the temperature sensor
     /// @param lcd the lcd screen
     /// @param led the first green led
     /// @param blinkTask the first green led blinking task
     /// @param period the task period in ms
     CheckInTask(Pir* const pir, Sonar* const sonar, TempSensor* const tempSensor, LiquidCrystal_I2C* const lcd, Led* const led, BlinkTask* const blinkTask, const int period);

     /// @brief Starts the task.
     void start();

    private:
     Pir* pir;
     Sonar* sonar;
     TempSensor* tempSensor;
     LiquidCrystal_I2C* lcd;
     Led* led;
     BlinkTask* blinkTask;
     enum { IDLE, SLEEP, DETECTED, GATE_HOLDING } state;
     bool detected;
     int timeElapsed;
};

#endif
