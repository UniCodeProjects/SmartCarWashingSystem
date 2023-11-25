#ifndef GATE_TASK_H
#define GATE_TASK_H

#include "Task.h"
#include "sensors/ServoMotor.h"
#include "sensors/ServoMotorImpl.h"

class GateTask : public Task {
    public:
     GateTask(ServoMotor* const motor, const int period);
     void start();
    
    private:
     ServoMotor* motor;
     enum { CLOSE, OPEN } state;
};

#endif
