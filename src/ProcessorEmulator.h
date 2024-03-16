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

        Processor(const Processor &) = delete;

        Processor(Processor &&) = delete;

        Processor &operator=(const Processor &) = delete;

        Processor &operator=(Processor &&) = delete;

        static Processor &instance();

        void execute(std::string programPath);

        void setStatus(Status newStatus) { _status = newStatus; }

        Status getStatus() { return _status; }

        bool isRunning() { return getStatus() == Status::RUNNING; }

        Stack<argType>* getStack() { return _stack; }

        argType *getRegisters() { return _registers; }


    private:

        argType* _registers;
        Stack<argType>* _stack;

        Status _status;

        Processor(){
            _registers = new int[5];
            _stack = new Stack<argType>{};
            _status = Status::NOT_STARTED;
        };

        ~Processor() = default;

    };


}

#endif
