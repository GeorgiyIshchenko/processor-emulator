#ifndef PROCESSOREMULATOR_H
#define PROCESSOREMULATOR_H

#include <vector>

#include "Commands.h"

namespace processorEmulator {

    class Processor {

    public:

        explicit Processor(const std::vector<std::shared_ptr<Commands::BaseCommand>>& commands){
            _processorState.registers = new int[5];
            _processorState.stack = Stack<argType>{};
            _processorState.status = Status::NOT_STARTED;
            _processorState.commands = commands;
            _processorState.head = commands.cbegin();
        };

        ~Processor() = default;

        ProcessorState* getState() {
            return &_processorState;
        }

        void execute();

    private:

        ProcessorState _processorState{};

    };


}

#endif
