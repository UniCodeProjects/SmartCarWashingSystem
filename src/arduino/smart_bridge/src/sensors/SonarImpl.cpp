#include <Arduino.h>
#include "../../include/sensors/SonarImpl.h"

#define ZERO_CELSIUS_IN_KELVIN 273.15
#define AIR_ADIABATIC_INDEX 1.4
#define AIR_MOLAR_CONSTANT 287.057
#define ONE_SECOND_IN_MICROSECONDS 1000000.0

SonarImpl::SonarImpl(const int trigPin, const int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

double SonarImpl::getKelvinFromCelsius(const double celsiusTemp) {
    return celsiusTemp + ZERO_CELSIUS_IN_KELVIN;
}

double SonarImpl::getSoundSpeed(const double kelvinTemp) {
    return sqrt(AIR_ADIABATIC_INDEX * AIR_MOLAR_CONSTANT * kelvinTemp);
}

double SonarImpl::getDistance(const double currentTemperature) {
    digitalWrite(this->trigPin, LOW),
    delayMicroseconds(5);
    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin, LOW);

    // pulseIn() returns time in microseconds, so it is converted in seconds.
    double t = pulseIn(this->echoPin, HIGH) / (ONE_SECOND_IN_MICROSECONDS * 2);
    return getSoundSpeed(getKelvinFromCelsius(currentTemperature)) * t;
}