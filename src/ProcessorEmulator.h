#ifndef PROCESSOREMULATOR_H
#define PROCESSOREMULATOR_H

#include <vector>
#include <map>

#include <Stack.h>

namespace processorEmulator {

    enum class Register{
        AX, BX, CX, DX
    };

//    std::map<std::string, Register> RegisterMap{
//            {"AX", Register::AX},
//            {"BX", Register::BX},
//            {"CX", Register::CX},
//            {"DX", Register::DX},
//    };

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
