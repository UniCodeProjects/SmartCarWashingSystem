#include "../../include/components/TempSensorImpl.h"
#include <Arduino.h>

#define MV_PER_ANALOG_VALUE 4.8876
#define ONE_CELSIUS_IN_MV 0.1

TempSensorImpl::TempSensorImpl(const int pin) {
    this->pin = pin;
}

double TempSensorImpl::getCurrentTemperature() {
    int sensorValue = analogRead(this->pin);
    int mV = MV_PER_ANALOG_VALUE * sensorValue;
    return mV * ONE_CELSIUS_IN_MV;
}
