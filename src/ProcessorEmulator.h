#ifndef PROCESSOREMULATOR_H
#define PROCESSOREMULATOR_H

#include <vector>

#include "Commands.h"

namespace processorEmulator {

    class Processor {

    public:

        explicit Processor(const std::vector<std::shared_ptr<Commands::BaseCommand>>& commands,
                           const std::map<std::string, size_t>& labels){
            _processorState.registers = new int[5];
            _processorState.stack = Stack<argType>{};
            _processorState.status = Status::NOT_STARTED;
            _processorState.commands = commands;
            _processorState.head = _processorState.commands.cbegin();
            _processorState.labels = labels;
            _processorState.callStack = {};
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
