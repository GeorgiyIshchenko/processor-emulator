#ifndef PROCESSOREMULATOR_H
#define PROCESSOREMULATOR_H

#include <vector>
#include <map>

#include "Stack.h"


namespace processorEmulator {

    using argType = int;

    enum class Register : int {
        AX, BX, CX, DX, BP
    };

    class Processor {

    public:

        enum class Status {
            NOT_STARTED,
            RUNNING,
            ENDED
        };

        struct ProcessorState {
            argType* registers;
            Stack<argType> stack;
            Status status;
        };

        Processor(){
            _processorState.registers = new int[5];
            _processorState.stack = Stack<argType>{};
            _processorState.status = Status::NOT_STARTED;
        };

        ~Processor() = default;

        ProcessorState* getState() {
            return &_processorState;
        }

    private:

        ProcessorState _processorState{};

    };


}

#endif
