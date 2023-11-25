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

#define SERIAL_BAUD_RATE 9600
#define NUM_LEDS 3

Led* leds[NUM_LEDS] = {new LedImpl(13), new LedImpl(12), new LedImpl(11)};
Button* const button = new ButtonImpl(7);
Pir* const pir = new PirImpl(4);
TempSensor* const tempSensor = new TempSensorImpl(A2);
Sonar* const sonar = new SonarImpl(2, 3);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
ServoMotor* const motor = new ServoMotorImpl(9);

Scheduler scheduler;

bool openGate = true;
extern bool isBtnPressed;

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    scheduler.initialize(100);
    scheduler.addTask(new BlinkTask(leds[0], 100));
    scheduler.addTask(new BlinkTask(leds[1], 500));
    scheduler.addTask(new GateTask(motor, 500));
    scheduler.addTask(new ButtonTask(button, 100));
}

void loop() {
    openGate = isBtnPressed;
    scheduler.tick();
}
