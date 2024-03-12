#ifndef PROCESSOREMULATOR_COMMANDS_H
#define PROCESSOREMULATOR_COMMANDS_H

#include <ProcessorEmulator.h>

namespace processorEmulator::Commands {

    using argType = int;

    class BaseCommand {

    public:

        virtual void execute() {};

    };

    class Begin : public BaseCommand {

        void execute() override;

    };

    class End : public BaseCommand {

        void execute() override;

    };

    class Push : public BaseCommand {

    public:

        explicit Push(argType value) : _value(value) {}

        void execute() override;

    private:

        argType _value;

    };

    class Pop : public BaseCommand {

        void execute() override;

    };

    class PushR : public BaseCommand {

    public:

        explicit PushR(Register reg) : _reg(reg) {};

        void execute() override;

    private:

        Register _reg;

    };

    class PopR : public BaseCommand {

    public:

        explicit PopR(Register reg) : _reg(reg) {};

        void execute() override;

    private:

        Register _reg;

    };

    class Add : public BaseCommand {

    public:

        void execute() override;

    };

    class Sub : public BaseCommand {

    public:

        void execute() override;

    };

    class Mul : public BaseCommand {

    public:

        void execute() override;

    };

    class Div : public BaseCommand {

    public:

        void execute() override;

    };

    class In : public BaseCommand {

    public:

        void execute() override;

    };

    class Out : public BaseCommand {

    public:

        void execute() override;

    };


}


#endif
