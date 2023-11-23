#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "../include/sensors/Led.h"
#include "../include/sensors/LedImpl.h"
#include "../include/sensors/Button.h"
#include "../include/sensors/ButtonImpl.h"
#include "../include/sensors/Pir.h"
#include "../include/sensors/PirImpl.h"
#include "../include/sensors/TempSensorImpl.h"
#include "../include/sensors/Sonar.h"
#include "../include/sensors/SonarImpl.h"
#include "../include/sensors/ServoMotor.h"
#include "../include/sensors/ServoMotorImpl.h"

#define SERIAL_BAUD_RATE 9600
#define NUM_LEDS 3
#define PIR_CALIBRATION_TIME_SEC 60

// #define LEDS
// #define BUTTON
// #define PIR
// #define TEMP
// #define SONAR
// #define LCD_MONITOR
// #define SERVO_MOTOR

enum buttonStatus {NOT_PRESSED, PRESSED} buttonStatus;
int buttonCurrentStatus = NOT_PRESSED;
int pirCurrentStatus = NOT_PRESSED;
boolean isButtonPressed = false;

Led* leds[NUM_LEDS] = {new LedImpl(13), new LedImpl(12), new LedImpl(11)};
Button* const button = new ButtonImpl(7);
Pir* const pir = new PirImpl(4);
TempSensor* const tempSensor = new TempSensorImpl(A2);
Sonar* const sonar = new SonarImpl(2, 3);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
ServoMotor* const motor = new ServoMotorImpl(9);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  #ifdef PIR
  Serial.println("Calibrating sensor... ");
  for(int i = 0; i < PIR_CALIBRATION_TIME_SEC; i++){
    Serial.println(".");
    delay(1000);
  }
  Serial.println("Calibration terminated.");
  #endif
  #ifdef LCD_MONITOR
  lcd.init();
  lcd.backlight();
  #endif
  #ifdef SERVO_MOTOR
  motor->on();
  #endif
}

void loop() {

  #ifdef LEDS
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    leds[i]->switchOn();
    delay(500);
    leds[i]->switchOff();
    delay(500);
  }
  #endif

  #ifdef BUTTON
  bool actualButtonStatus = button->isPressed();
  if (actualButtonStatus != isButtonPressed) {
    Serial.println(actualButtonStatus == true ? "pressed" : "not pressed");
    isButtonPressed = actualButtonStatus;
  }
  // Serial.println(button->isPressed());
  // delay(200);
  #endif

  #ifdef PIR
  bool actualPirStatus = pir->isDetected();
  if (actualPirStatus != pirCurrentStatus) {
    Serial.println(actualPirStatus == true ? "detected" : "not detected");
    pirCurrentStatus = actualPirStatus;
  }
  #endif

  #ifdef TEMP
  Serial.println(tempSensor->getCurrentTemperature());
  delay(1000);
  #endif

  #ifdef SONAR
  Serial.println("Nearest object's distance: " + String(sonar->getDistance(tempSensor->getCurrentTemperature())));
  delay(1000);
  #endif

  #ifdef LCD_MONITOR
  lcd.setCursor(3, 1);
  lcd.print("Hello, world!");
  #endif

  #ifdef SERVO_MOTOR
  motor->setPosition(0);
  delay(1000);
  motor->setPosition(179);
  delay(1000);
  motor->setPosition(0);
  Serial.println("Trying to set an illegal position...");
  delay(500);
  motor->setPosition(250);
  #endif

}
