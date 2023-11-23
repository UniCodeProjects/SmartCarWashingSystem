#ifndef SONAR_IMPL_H
#define SONAR_IMPL_H

#include "Sonar.h"

// Implementation of a sonar.
class SonarImpl: public Sonar {
    public:

        /*
         * Default constructor.
         *
         * Parameters:
         * 
         * - trigPin: the Arduino pin in which the sonar's "trig" pin is plugged in.
         * - echoPin: the Arduino pin in which the sonar's "echo" pin is plugged in.
         */
        SonarImpl(const int trigPin, const int echoPin);

        double getDistance(const double currentTemperature);

    private:

        int trigPin;
        int echoPin;

        static double getKelvinFromCelsius(const double celsiusTemp);
        static double getSoundSpeed(const double kelvinTemp);
};

#endif