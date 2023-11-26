#include "task/CheckInTask.h"

#include <Arduino.h>

bool openGate = false;
bool isVacant = true;
bool canWashStart = false;
extern bool isBtnPressed;
extern double carDist;

CheckInTask::CheckInTask(Pir* const pir, Sonar* const sonar, LiquidCrystal_I2C* const lcd, Led* const led, BlinkTask* const blinkTask, const int period) : TaskImpl(period) {
    this->pir = pir;
    this->sonar = sonar;
    this->lcd = lcd;
    this->led = led;
    this->blinkTask = blinkTask;
    detected = false;
    washedCars = 0;
    state = IDLE;
    timeElapsed = 0;
}

void CheckInTask::start() {
    switch (state) {
        case IDLE:
            Serial.println("IDLE");
            if (!isVacant) {
                break;
            }
            if (detected) {
                led->switchOn();
                lcd->print("Welcome");
                lcd->flush();
                state = DETECTED;
            } else {
                state = SLEEP;
            }
            break;
        case SLEEP:
            Serial.println("SLEEP");
            // TODO: sleep
            led->switchOn();
            state = DETECTED;
            break;
        case DETECTED:
            Serial.println("DETECTED");
            timeElapsed += period;
            if (timeElapsed >= OPEN_GATE_TIME_MS) {
                openGate = true;
                led->switchOff();
                blinkTask->enableBlink();
                lcd->print("Proceed to the washing area");
                lcd->flush();
                timeElapsed = 0;
                state = GATE_CROSSING;
            }
            break;
        case GATE_CROSSING:
            Serial.println("GATE CROSS");
            if (carDist < SONAR_MIN_DIST_M) {
                state = GATE_HOLDING;
            }
            break;
        case GATE_HOLDING:
            Serial.println("GATE HOLD");
            timeElapsed += period;
            if (timeElapsed >= CLOSE_GATE_TIME_MS) {
                openGate = false;
                isVacant = false;
                canWashStart = true;
                blinkTask->disableBlink();
                timeElapsed = 0;
                state = IDLE;
            }
            break;
    }
}
