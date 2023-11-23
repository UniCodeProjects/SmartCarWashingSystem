#ifndef PIR_H
#define PIR_H

// Class that represents a Passive Infra-Red (PIR) sensor.
class Pir {
    public:

        // Returns true if the sensor detects something in his detection field, false otherwise. 
        virtual bool isDetected() = 0;
};

#endif