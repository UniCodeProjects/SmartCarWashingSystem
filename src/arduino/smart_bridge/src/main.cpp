#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "../include/components/Button.h"
#include "../include/components/ButtonImpl.h"
#include "../include/components/Led.h"
#include "../include/components/LedImpl.h"
#include "../include/components/Pir.h"
#include "../include/components/PirImpl.h"
#include "../include/components/ServoMotor.h"
#include "../include/components/ServoMotorImpl.h"
#include "../include/components/Sonar.h"
#include "../include/components/SonarImpl.h"
#include "../include/components/TempSensorImpl.h"
#include "scheduler/Scheduler.h"
#include "task/BlinkTask.h"
#include "task/GateTask.h"
#include "task/ButtonTask.h"
#include "task/CheckInTask.h"
#include "task/WashingTask.h"

#define SERIAL_BAUD_RATE 9600
#define NUM_LEDS 3

Led* leds[NUM_LEDS] = {new LedImpl(13), new LedImpl(12), new LedImpl(11)};
Button* const button = new ButtonImpl(7);
Pir* const pir = new PirImpl(4);
TempSensor* const tempSensor = new TempSensorImpl(A2);
Sonar* const sonar = new SonarImpl(2, 3);
LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27, 20, 4);
ServoMotor* const motor = new ServoMotorImpl(9);

Scheduler scheduler;
BlinkTask* t0 = new BlinkTask(leds[0], 100);
BlinkTask* t1 = new BlinkTask(leds[1], 500);

extern bool openGate;
extern bool isBtnPressed;
unsigned long prev_ms = 0;

// TODO: remove
double carDist = 0;

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    lcd->init();
    lcd->backlight();
    lcd->setCursor(3, 1);
    scheduler.initialize(100);
    lcd->init();
    lcd->backlight();
    lcd->setCursor(3, 1);
    scheduler.addTask(t0);
    scheduler.addTask(t1);
    scheduler.addTask(new WashingTask(tempSensor, lcd, t1, 200));
    scheduler.addTask(new GateTask(motor, 100));
    scheduler.addTask(new ButtonTask(button, 100));
    scheduler.addTask(new CheckInTask(pir, sonar, lcd, leds[0], t0, 200));
}

void loop() {
    scheduler.tick();
}
