#include <vector>


#ifndef PROCESSOREMULATOR_H
#define PROCESSOREMULATOR_H

#include "Stack.h"

namespace processorEmulator {

    enum class Register{
        AX, BX, CX, DX
    };

    template<class T>
    class Processor{

    public:

        Processor(const Processor<T>&) = delete;
        Processor(Processor&&) = delete;
        Processor& operator=(const Processor&) = delete;
        Processor& operator=(Processor&&) = delete;

        static Processor<T>& instance() {
            static Processor<T> instance;
            return instance;
        }

        void loadProgram(std::string programPath) {

        }


    private:

        T registers[4];
        Stack<T> stack{};

        Processor() = default;
        ~Processor() = default;

    };


}

#endif
