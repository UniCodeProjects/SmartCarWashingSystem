#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

/// @brief Class that represents a temperature sensor.
class TempSensor {
   public:
    /// @brief Retrieves the current temperature in °C.
    /// @return the current temperature
    virtual double getCurrentTemperature() = 0;
};

#endif
