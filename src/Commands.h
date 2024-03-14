#ifndef PROCESSOREMULATOR_COMMANDS_H
#define PROCESSOREMULATOR_COMMANDS_H

#include <regex>

#include "ProcessorEmulator.h"

namespace processorEmulator::Commands {


    class BaseCommand {

    public:

        virtual void execute() {};

        virtual void setArgFromRegex(const std::smatch &match, int numOfLine) {};

    };
    
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

        void execute() override = 0;

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

    protected:

        argType _value{};

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

        void execute() override = 0;

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

    protected:

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
