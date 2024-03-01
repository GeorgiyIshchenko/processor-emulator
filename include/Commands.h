#include <ProcessorEmulator.h>

#ifndef PROCESSOREMULATOR_COMMANDS_H
#define PROCESSOREMULATOR_COMMANDS_H

namespace processorEmulator {

    namespace Commands {

        using argType = int;

        class BaseCommand {

        public:

            virtual argType execute() { return argType{}; };

        };

        class Begin : public BaseCommand {

            argType execute() override;

        };

        class End : public BaseCommand {

            argType execute() override;

        };

        class Push : public BaseCommand {

        public:

            explicit Push(argType value) : _value(value) {}

            argType execute() override;

        private:

            argType _value;

        };

        class Pop : public BaseCommand {

            argType execute() override;

        };

        class PushR : public BaseCommand {

        public:

            explicit PushR(Register reg) : _reg(reg) {};

            argType execute() override;

        private:

            Register _reg;

        };

        class PopR : public BaseCommand {

            argType execute() override;

        };

        class MathCommand : public BaseCommand {

        public:

            explicit MathCommand(argType arg1, argType arg2) : _arg1(arg1), _arg2(arg2) {};

        private:

            argType _arg1;
            argType _arg2;

        };

        class Add : public MathCommand {

        public:

            Add(argType arg1, argType arg2) : MathCommand(arg1, arg2) {};

            argType execute() override;

        };

        class Sub : public MathCommand {

        public:

            Sub(argType arg1, argType arg2) : MathCommand(arg1, arg2) {};

            argType execute() override;

        };

        class Mul : public MathCommand {

        public:

            Mul(argType arg1, argType arg2) : MathCommand(arg1, arg2) {};

            argType execute() override;

        };

        class Div : public MathCommand {

        public:

            Div(argType arg1, argType arg2) : MathCommand(arg1, arg2) {};

            argType execute() override;

        };

        class In : public BaseCommand {

        public:

            explicit In(argType arg) : _arg(arg) {};

            argType execute() override;

        private:

            argType _arg;

        };

        class Out : public BaseCommand {

        public:

            explicit Out(argType arg) : _arg(arg) {};

            argType execute() override;

        private:

            argType _arg;

        };


    }

}

#endif
