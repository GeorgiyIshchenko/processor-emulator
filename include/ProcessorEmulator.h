#ifndef PROCESSOREMULATOR_H
#define PROCESSOREMULATOR_H

#include <Stack.h>

namespace processorEmulator {

    enum class Register{
        AX, BX, CX, DX
    };

    template<class T>
    class ProcessorEmulator{

        T registers[4];
        Stack<T> stack{};

    };


}

#endif
