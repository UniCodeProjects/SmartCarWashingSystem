#ifndef PIR_IMPL_H
#define PIR_IMPL_H

#include "Pir.h"

/// @brief Implementation of a generic PIR.
class PirImpl : public Pir {
   public:
    /// @brief Default constructor.
    /// @param pin the Arduino pin in which the PIR is plugged in.
    PirImpl(const int pin);

    bool isDetected();

   private:
    int pin;
};

#endif
