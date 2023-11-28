#include "task/CheckOutTask.h"

#include "task/TaskImpl.h"

#define SONAR_MIN_DIST_METERS 1.0
#define CLOSE_GATE_TIME_MS 1000

extern bool washingComplete;
extern bool openGate;
extern bool isVacant;

CheckOutTask::CheckOutTask(LiquidCrystal_I2C* const lcd, Led* const led, Sonar* const sonar, TempSensor* const temperatureSensor, const int period) : TaskImpl(period) {
    this->lcd = lcd;
    this->led = led;
    this->sonar = sonar;
    this->temperatureSensor = temperatureSensor;
    timeElapsed = 0;
    state = IDLE;
}

void CheckOutTask::start() {
    double carDist;
    switch (state) {
        case IDLE:
            if (washingComplete) {
                openGate = true;
                led->switchOn();
                lcd->setCursor(1, 1);
                lcd->print("Washing complete,");
                lcd->setCursor(3, 2);
                lcd->print("you can leave");
                lcd->setCursor(5, 3);
                lcd->print("the area");
                washingComplete = false;
                state = PREPARATION;
            }
            break;
        case PREPARATION:
            carDist = sonar->getDistance(20);  // TODO: pass to the method the current temperature measured by the temperature sensor.
            if (carDist > SONAR_MIN_DIST_METERS) {
                state = GATE_HOLDING;
            }
            break;
        case GATE_HOLDING:
            timeElapsed += this->period;
            if (timeElapsed >= CLOSE_GATE_TIME_MS) {
                openGate = false;
                lcd->clear();
                led->switchOff();
                isVacant = false;
                timeElapsed = 0;
                state = IDLE;
            }
            break;
    }
}
