#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "../include/sensors/Button.h"
#include "../include/sensors/ButtonImpl.h"
#include "../include/sensors/Led.h"
#include "../include/sensors/LedImpl.h"
#include "../include/sensors/Pir.h"
#include "../include/sensors/PirImpl.h"
#include "../include/sensors/ServoMotor.h"
#include "../include/sensors/ServoMotorImpl.h"
#include "../include/sensors/Sonar.h"
#include "../include/sensors/SonarImpl.h"
#include "../include/sensors/TempSensorImpl.h"
#include "scheduler/Scheduler.h"
#include "task/BlinkTask.h"
#include "task/GateTask.h"

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

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    scheduler.initialize(100);
    scheduler.addTask(new BlinkTask(leds[0], 100));
    scheduler.addTask(new BlinkTask(leds[1], 500));
    scheduler.addTask(new GateTask(motor, 500));
}

void loop() {
    scheduler.tick();
}
