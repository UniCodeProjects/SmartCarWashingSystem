#ifndef GATE_TASK_H
#define GATE_TASK_H

#include "TaskImpl.h"
#include "components/ServoMotor.h"
#include "components/ServoMotorImpl.h"

/// @brief The gate task that operates the opening and closing of the servo motor.
class GateTask : public TaskImpl {
    public:
     /// @brief The gate task constructor.
     /// @param motor the servo motor that acts as a gate
     /// @param period the task period in ms
     GateTask(ServoMotor* const motor, const int period);

     /// @brief Starts the task.
     void start();
    
    private:
     ServoMotor* motor;
     enum { CLOSE, OPEN } state;
};

#endif
