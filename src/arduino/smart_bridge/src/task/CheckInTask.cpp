#include "task/CheckInTask.h"
#include "GuardsManager.h"
#include <avr/sleep.h>

#include "pins.h"

#define EI_NOTPORTC
#define EI_NOTPORTB
#define EI_NOTEXTERNAL

#include <EnableInterrupt.h>

CheckInTask::CheckInTask(Pir* const pir, Sonar* const sonar, TempSensor* const tempSensor, LiquidCrystal_I2C* const lcd, Led* const led, BlinkTask* const blinkTask, const int period) : TaskImpl(period) {
    this->pir = pir;
    this->sonar = sonar;
    this->tempSensor = tempSensor;
    this->lcd = lcd;
    this->led = led;
    this->blinkTask = blinkTask;
    timeElapsed = 0;
    state = IDLE;
}

void handle_wake_up() {
}

void CheckInTask::start() {
    GuardsManager& guards = GuardsManager::getInstance();
    bool detected;
    double carDist;
    switch (state) {
        case IDLE:
            if (!guards.isVacant()) {
                break;
            }
            detected = pir->isDetected();
            if (detected) {
                led->switchOn();
                lcd->clear();
                lcd->setCursor(6, 1);
                lcd->print("Welcome!");
                state = DETECTED;
            } else {
                state = SLEEP;
            }
            break;
        case SLEEP:
            lcd->noBacklight();
            enableInterrupt(P_PIR, handle_wake_up, RISING);
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();
            sleep_disable();
            disableInterrupt(P_PIR);
            lcd->backlight();
            led->switchOn();
            lcd->clear();
            lcd->setCursor(6, 1);
            lcd->print("Welcome!");
            state = DETECTED;
            break;
        case DETECTED:
            timeElapsed += period;
            if (timeElapsed >= OPEN_GATE_TIME_MS) {
                guards.setGateOpened(true);
                led->switchOff();
                blinkTask->enableBlink();
                lcd->clear();
                lcd->setCursor(3, 1);
                lcd->print("Proceed to the");
                lcd->setCursor(4, 2);
                lcd->print("washing area");
                timeElapsed = 0;
                state = GATE_HOLDING;
            }
            break;
        case GATE_HOLDING:
            carDist = sonar->getDistance(tempSensor->getCurrentTemperature());
            if (carDist != 0) {
                if (carDist < SONAR_MIN_DIST_M) {
                    timeElapsed += period;
                } else {
                    timeElapsed = 0;
                    break;
                }
            }
            if (timeElapsed >= CLOSE_GATE_TIME_MS) {
                guards.prepareForWashing();
                blinkTask->disableBlink();
                state = IDLE;
            }
            break;
    }
}
