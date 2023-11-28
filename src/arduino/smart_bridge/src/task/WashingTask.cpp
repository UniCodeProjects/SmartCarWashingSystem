#include "task/WashingTask.h"

#include "task/TaskImpl.h"
#include <Arduino.h>

#define WASHING_DURATION_MS 15000
#define MAX_EMERGENCY_TIME 5000
#define MAX_TEMP 45.0

#define LCD_CLEAR_ROW "                    "
#define EMPTY_PROGRESS_BAR "[                  ]"
#define PROGRESS_BAR_LEN 20
/*
 * The value is 800 because of the washing time (15000 ms)
 * and the number of available lcd cells (18) for printing the progress.
 */
#define PROGRESS_BAR_STEP_MS 800

extern bool isBtnPressed;
extern bool canWashStart;

static String progressBar = EMPTY_PROGRESS_BAR;

/// @brief Updates the progress bar each PROGRESS_BAR_STEP_MS.
static void updateProgressBar(LiquidCrystal_I2C* const lcd, const int washingTime);
/// @brief Utility function that updates the progress bar.
static void nextProgressStep();

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
                // Preparing progress bar.
                lcd->clear();
                lcd->setCursor(6, 1);
                lcd->print("Washing.");
                lcd->setCursor(0, 2);
                lcd->print(progressBar);
                state = WASHING;
            }
            break;
        case WASHING:
            updateProgressBar(lcd, washingTime);
            temp = temperatureSensor->getCurrentTemperature();
            Serial.println("temp: " + String(temp));
            if (washingTime == WASHING_DURATION_MS) {
                progressBar = EMPTY_PROGRESS_BAR;
                washingComplete = true;
                blinkTask->disableBlink();
                washingTime = 0;
                lcd->clear();
                washedCars++;
                Serial.println("washed cars: " + String(washedCars)); // the pc has to know the number of washed cars
                canWashStart = false;
                state = IDLE;
                break;
            } else if (temp > MAX_TEMP) {
                state = WAITING_EMERGENCY;
            }
            washingTime += this->period;
            break;
        case WAITING_EMERGENCY:
            updateProgressBar(lcd, washingTime);
            temp = temperatureSensor->getCurrentTemperature();
            Serial.println("temp: " + String(temp));
            if (washingTime == WASHING_DURATION_MS) {
                progressBar = EMPTY_PROGRESS_BAR;
                washingComplete = true;
                blinkTask->disableBlink();
                washedCars++;
                Serial.println("washed cars: " + String(washedCars)); // the pc has to know the number of washed cars
                lcd->clear();
                washingTime = 0;
                canWashStart = false;
                elapsedEmergencyTimer = 0;
                state = IDLE;
                break;
            }
            if (temp <= MAX_TEMP) {
                elapsedEmergencyTimer = 0;
                state = WASHING;
            } else {
                elapsedEmergencyTimer += this->period;
            }
            washingTime += this->period;
            if (elapsedEmergencyTimer == MAX_EMERGENCY_TIME) {
                elapsedEmergencyTimer = 0;
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
            break;
        case REQUIRED_PC_MAINTENANCE:
            String received = Serial.readString();
            if (received.equals("Maintenance done")) {
                blinkTask->enableBlink();
                // Clearing row to print "washing" text.
                lcd->setCursor(0, 1);
                lcd->print(LCD_CLEAR_ROW);
                lcd->setCursor(6, 1);
                lcd->print("Washing.");
                state = WASHING;
                break;
            }
            break;
    }
}

static void updateProgressBar(LiquidCrystal_I2C* const lcd, const int washingTime) {
    if (washingTime % PROGRESS_BAR_STEP_MS == 0) {
        nextProgressStep();
        lcd->setCursor(0, 2);
        lcd->print(progressBar);
    }
}

static void nextProgressStep() {
    for (unsigned int i = 0; i < PROGRESS_BAR_LEN; i++) {
        if (progressBar.charAt(i) == ' ') {
            progressBar.setCharAt(i, '#');
            break;
        }
    }
}
