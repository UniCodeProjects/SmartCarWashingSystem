#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

// Class that represents a temperature sensor.
class TempSensor {
    public:

        // Retrieves the current temperature in °C.
        virtual double getCurrentTemperature() = 0;
};

#endif