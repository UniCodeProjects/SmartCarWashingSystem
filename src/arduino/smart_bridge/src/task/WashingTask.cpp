#include "task/WashingTask.h"

#include "task/TaskImpl.h"
#include <Arduino.h>

#define WASHING_DURATION_MS 15000
#define MAX_EMERGENCY_TIME 5000
#define MAX_TEMP 25.0

extern bool isBtnPressed;
extern bool canWashStart;

WashingTask::WashingTask(TempSensor* const tempSensor, LiquidCrystal_I2C* const lcd, BlinkTask* const blinkTask, const int period) : TaskImpl(period) {
    temperatureSensor = tempSensor;
    this->lcd = lcd;
    this->blinkTask = blinkTask;
    state = IDLE;
    washingComplete = false;
    washedCars = 0;
    temp = 0.0;
    washingTime = 0;
    elapsedEmergencyTimer = 0;
    performedMaintenance = false;
}

void WashingTask::start() {
    switch (state) {
        case IDLE:
            if (canWashStart) {
                lcd->setCursor(3, 1);
                lcd->print("Ready to wash");
                blinkTask->getLed()->switchOn();
                state = READY;
            }
            break;
        case READY:
            if (isBtnPressed) {
                blinkTask->getLed()->switchOff();
                blinkTask->enableBlink();
                // TODO: print empty progress bar on lcd
                state = WASHING;
            }
            break;
        case WASHING:
            // TODO: update progress bar instead of printing the washing time on the lcd
            lcd->clear();
            lcd->print(String(washingTime));
            temp = temperatureSensor->getCurrentTemperature();
            Serial.println(temp);
            if (washingTime == WASHING_DURATION_MS) {
                washingComplete = true;
                blinkTask->disableBlink();
                washingTime = 0;
                lcd->clear();
                washedCars++;
                Serial.println(washedCars); // the pc has to know the number of washed cars
                canWashStart = false;
                state = IDLE;
                break;
            } else if (temp > MAX_TEMP) {
                state = WAITING_EMERGENCY;
                break;
            }
            washingTime += this->period;
            break;
        case WAITING_EMERGENCY:
            // TODO: update progress bar instead of printing the washing time on the lcd
            lcd->clear();
            lcd->print(String(washingTime));
            temp = temperatureSensor->getCurrentTemperature();
            Serial.println(temp);
            if (temp <= MAX_TEMP) {
                elapsedEmergencyTimer = 0;
                state = WASHING;
                break;
            } else {
                elapsedEmergencyTimer += this->period;
            }
            if (washingTime == WASHING_DURATION_MS) {
                washingComplete = true;
                blinkTask->disableBlink();
                washedCars++;
                Serial.println(washedCars); // the pc has to know the number of washed cars
                lcd->clear();
                washingTime = 0;
                canWashStart = false;
                elapsedEmergencyTimer = 0;
                state = IDLE;
                break;
            }
            if (elapsedEmergencyTimer == MAX_EMERGENCY_TIME) {
                blinkTask->disableBlink();
                Serial.println("Maintenance required");
                lcd->clear();
                lcd->setCursor(1, 1);
                lcd->print("Detected a problem");
                lcd->setCursor(4, 2);
                lcd->print("please wait");
                state = REQUIRED_PC_MAINTENANCE;
                break;
            }
            washingTime += this->period;
            break;
        case REQUIRED_PC_MAINTENANCE:
            Serial.println("Waiting for maintainer...");
            break;
    }
}

// TODO: implement progress bar like "[#####]"
