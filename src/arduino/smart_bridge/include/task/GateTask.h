#ifndef GATE_TASK_H
#define GATE_TASK_H

#include "TaskImpl.h"
#include "components/ServoMotor.h"
#include "components/ServoMotorImpl.h"

class GateTask : public TaskImpl {
    public:
     GateTask(ServoMotor* const motor, const int period);
     void start();
    
    private:
     ServoMotor* motor;
     enum { CLOSE, OPEN } state;
};

#endif
