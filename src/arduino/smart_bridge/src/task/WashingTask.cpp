#include "task/WashingTask.h"

#include "task/TaskImpl.h"

#define WASHING_DURATION_MS 15000

extern bool isBtnPressed;
extern bool canWashStart;
extern bool isVacant;

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
            if (!isVacant && canWashStart) {
                lcd->clear();
                lcd->print("Ready to wash");
                blinkTask->getLed()->switchOn();
                state = READY;
            }
            break;
        case READY:
            // printStringOnceOnLCD("Ready to wash");
            // blinkTask->getLed()->switchOn();
            if (isBtnPressed) {
                blinkTask->getLed()->switchOff();
                state = WASHING;
                blinkTask->enableBlink();
                // TODO: print empty progress bar on lcd
            }
            break;
        case WASHING:
            lcd->clear();
            lcd->print(String(washingTime));
            // TODO: update progress bar
            if (washingTime == WASHING_DURATION_MS) {
                washingComplete = true;
                blinkTask->disableBlink();
                washingTime = 0;
                lcd->clear();
                washedCars++;
                canWashStart = false;
                state = IDLE;
                break;
            }
            washingTime += this->period;
            break;
        case WAITING_EMERGENCY:
            break;
        case REQUIRED_PC_MAINTENANCE:
            break;
    }
}

// void WashingTask::printStringOnceOnLCD(const String string) {
//     if (!isStringPrintedOnLCD) {
//         lcd->print(string);
//         isStringPrintedOnLCD = true;
//     }
// } // TODO: see if this method is useful

// TODO: implement progress bar like "[#####]"
