#ifndef PIR_H
#define PIR_H

/// @brief Class that represents a Passive Infra-Red (PIR) sensor.
class Pir {
   public:
    /// @brief Retrieves if the sensor detects something in his detection field.
    /// @return true on detection, false otherwise
    virtual bool isDetected() = 0;
};

#endif
