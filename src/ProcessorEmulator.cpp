#include "ProcessorEmulator.h"
#include "Commands.h"

namespace processorEmulator {

    void Processor::execute() {
        while (_processorState.status != Status::ENDED) {
            _processorState.head->get()->execute(&_processorState);
            _processorState.head++;
        }
    }
}



