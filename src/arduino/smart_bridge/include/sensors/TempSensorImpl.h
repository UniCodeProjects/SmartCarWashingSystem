#ifndef TEMP_SENSOR_IMPL_H
#define TEMP_SENSOR_IMPL_H

#include "TempSensor.h"

// Implementation of a temperature sensor.
class TempSensorImpl: public TempSensor {
    public:
    
        /* 
         * Default constuctor.
         *
         * Parameters:
         * 
         * - pin: the Arduino pin in which the sensor is plugged in.
         */
        TempSensorImpl(const int pin);

        double getCurrentTemperature();
    
    private:
        int pin;
};

#endif