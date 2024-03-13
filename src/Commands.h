#ifndef PROCESSOREMULATOR_COMMANDS_H
#define PROCESSOREMULATOR_COMMANDS_H

#include <ProcessorEmulator.h>

namespace processorEmulator::Commands {

    using argType = int;

    enum class ArgType {
        NONE,
        REGISTER,
        USER_TYPE
    };

    class BaseCommand {

    public:

        virtual void execute() {};

        virtual ArgType getArgInfo();

    };

    std::string commandToString(BaseCommand* command);

    class Begin : public BaseCommand {

    public:

        void execute() override;

    };

    class End : public BaseCommand {

    public:

        void execute() override;

    };

    class UserArgCommand : public BaseCommand {

    public:

        UserArgCommand() = default;

        explicit UserArgCommand(argType value) : _value(value) {};

        void execute() override = 0;

        ArgType getArgInfo() override;

        void setValue(argType value);

    private:

        argType _value;

    };

    class Push : public UserArgCommand {

    public:

        void execute() override;


    };

    class Pop : public BaseCommand {

    public:

        void execute() override;

    };

    class RegisterCommand : public BaseCommand {

    public:

        RegisterCommand() { _reg = Register::AX; };

        explicit RegisterCommand(Register reg) : _reg(reg) {};

        void execute() override = 0;

        ArgType getArgInfo() override;

        void setRegister(Register reg);

    private:

        Register _reg;

    };

    class PushR : public RegisterCommand {

    public:

        void execute() override;

    };

    class PopR : public RegisterCommand {

    public:

        void execute() override;

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
