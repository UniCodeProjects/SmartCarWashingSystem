#ifndef SONAR_H
#define SONAR_H

// Class that represents a generic sonar.
class Sonar {

    public:
        // Retrieves the distance in meters of the nearest object.
        virtual double getDistance(double currentTemperature) = 0;
};

#endif