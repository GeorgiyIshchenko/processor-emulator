#ifndef PROCESSOREMULATOR_PROCESSORSTATE_H
#define PROCESSOREMULATOR_PROCESSORSTATE_H

#include "vector"
#include "utility"

#include "Stack.h"

namespace processorEmulator {

    namespace Commands {
        class BaseCommand;
    }

    using argType = int;

    enum class Register : int {
        AX, BX, CX, DX, BP
    };

    enum class Status {
        NOT_STARTED,
        RUNNING,
        ENDED
    };


    struct ProcessorState {
        argType *registers;
        Stack<argType> stack;
        Status status;
        std::vector<std::shared_ptr<Commands::BaseCommand>> commands;
        std::vector<std::shared_ptr<Commands::BaseCommand>>::const_iterator head;
    };


}

#endif
