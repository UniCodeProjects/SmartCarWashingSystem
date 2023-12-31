#include "task/CheckOutTask.h"
#include "GuardsManager.h"
#include "task/TaskImpl.h"

/// @brief The minimum distance from the sonar that is required to close the gate.
#define SONAR_MIN_DIST_METERS 1.0
/// @brief The required time to wait before the gate can be closed.
#define CLOSE_GATE_TIME_MS 2000

CheckOutTask::CheckOutTask(LiquidCrystal_I2C* const lcd, Led* const led, Sonar* const sonar, TempSensor* const temperatureSensor, const int period) : TaskImpl(period) {
    this->lcd = lcd;
    this->led = led;
    this->sonar = sonar;
    this->temperatureSensor = temperatureSensor;
    timeElapsed = 0;
    state = IDLE;
}

void CheckOutTask::start() {
    GuardsManager& guards = GuardsManager::getInstance();
    double carDist;
    switch (state) {
        case IDLE:
            if (guards.isWashingComplete()) {
                guards.setGateOpened(true);
                led->switchOn();
                lcd->setCursor(1, 1);
                lcd->print("Washing complete,");
                lcd->setCursor(3, 2);
                lcd->print("you can leave");
                lcd->setCursor(5, 3);
                lcd->print("the area");
                guards.setIsWashingComplete(false);
                state = GATE_HOLDING;
            }
            break;
        case GATE_HOLDING:
            carDist = sonar->getDistance(temperatureSensor->getCurrentTemperature());
            if (carDist != 0) {
                if (carDist > SONAR_MIN_DIST_METERS) {
                    timeElapsed += this->period;
                } else {
                    timeElapsed = 0;
                    break;
                }
            }
            if (timeElapsed >= CLOSE_GATE_TIME_MS) {
                lcd->clear();
                led->switchOff();
                timeElapsed = 0;
                guards.prepareForCheckIn();
                state = IDLE;
            }
            break;
    }
}
