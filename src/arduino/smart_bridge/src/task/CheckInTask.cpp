#include "task/CheckInTask.h"

#include <avr/sleep.h>

// #define DEBUG
#ifdef DEBUG
#include <Arduino.h>
#endif

#define EI_NOTPORTC
#define EI_NOTPORTB
#define EI_NOTEXTERNAL

#include <EnableInterrupt.h>

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
    state = IDLE;
    timeElapsed = 0;
}

void handle_wake_up() {
#ifdef DEBUG
    Serial.println("WAKE UP");
#endif
}

void CheckInTask::start() {
    switch (state) {
        case IDLE:
#ifdef DEBUG
            Serial.println("IDLE");
            Serial.println(digitalRead(4));
#endif
            if (!isVacant) {
                break;
            }
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
#ifdef DEBUG
            Serial.println("SLEEP");
#endif
            // TODO: use getter for pin after it is implemented.
            enableInterrupt(4, handle_wake_up, RISING);
            set_sleep_mode(SLEEP_MODE_PWR_DOWN);
            sleep_enable();
            sleep_mode();
            sleep_disable();
            disableInterrupt(4);
#ifdef DEBUG
            Serial.println(digitalRead(4));
#endif
            led->switchOn();
            lcd->clear();
            lcd->setCursor(6, 1);
            lcd->print("Welcome!");
            state = DETECTED;
            break;
        case DETECTED:
#ifdef DEBUG
            Serial.println("DETECTED");
#endif
            timeElapsed += period;
            if (timeElapsed >= OPEN_GATE_TIME_MS) {
                openGate = true;
                led->switchOff();
                blinkTask->enableBlink();
                lcd->clear();
                lcd->setCursor(3, 1);
                lcd->print("Proceed to the");
                lcd->setCursor(4, 2);
                lcd->print("washing area");
                timeElapsed = 0;
                state = GATE_CROSSING;
            }
            break;
        case GATE_CROSSING:
#ifdef DEBUG
            Serial.println("GATE CROSS");
#endif
            carDist = sonar->getDistance((double)20);
#ifdef DEBUG
            Serial.println(carDist);
#endif
            if (carDist < SONAR_MIN_DIST_M) {
                state = GATE_HOLDING;
            }
            break;
        case GATE_HOLDING:
#ifdef DEBUG
            Serial.println("GATE HOLD");
#endif
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
