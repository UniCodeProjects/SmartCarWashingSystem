#include "../../include/components/PirImpl.h"
#include <Arduino.h>

PirImpl::PirImpl(const int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

bool PirImpl::isDetected() {
    return digitalRead(pin) == HIGH;
};