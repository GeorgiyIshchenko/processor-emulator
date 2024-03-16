#ifndef PROCESSOREMULATOR_COMMANDS_H
#define PROCESSOREMULATOR_COMMANDS_H

#include <regex>
#include <utility>

#include "ProcessorEmulator.h"

namespace processorEmulator::Commands {


    class BaseCommand {

    public:

        explicit BaseCommand(std::string parseName = "BASE_COMMAND") : _parseName(std::move(parseName)) {};

        virtual void execute() {};

        virtual void setArgFromRegex(const std::smatch &match, int numOfLine) {};

    private:

        std::string _parseName;

    };

    class Begin : public BaseCommand {

    public:

        explicit Begin(std::string parseName = "BEGIN") : BaseCommand(std::move(parseName)) {};

        void execute() override;

    };

    class End : public BaseCommand {

    public:

        explicit End(std::string parseName = "END") : BaseCommand(std::move(parseName)) {};

        void execute() override;

    };

    class UserArgCommand : public BaseCommand {

    public:

        explicit UserArgCommand(std::string parseName, argType value = 0) : BaseCommand(
                std::move(parseName)) { _value = value; };

        void execute() override = 0;

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

    protected:

        argType _value{};

    };

    class Push : public UserArgCommand {

    public:

        explicit Push(std::string parseName = "PUSH", argType value = 0) : UserArgCommand(std::move(parseName),
                                                                                          value) {};

        void execute() override;

    };

    class Pop : public BaseCommand {

    public:

        explicit Pop(std::string parseName = "POP") : BaseCommand(std::move(parseName)) {};

        void execute() override;

    };

    class RegisterCommand : public BaseCommand {

    public:

        explicit RegisterCommand(std::string parseName = "REGISTER", Register reg = Register::AX) : BaseCommand(
                std::move(parseName)) { _reg = reg; };

        void execute() override = 0;

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

    protected:

        Register _reg;

    };

    class PushR : public RegisterCommand {

    public:

        explicit PushR(std::string parseName = "PUSHR") : RegisterCommand(std::move(parseName)) {};

        void execute() override;

    };

    class PopR : public RegisterCommand {

    public:

        explicit PopR(std::string parseName = "POPR") : RegisterCommand(std::move(parseName)) {};

        void execute() override;

    };

    class Add : public BaseCommand {

    public:

        explicit Add(std::string parseName = "ADD") : BaseCommand(std::move(parseName)) {};

        void execute() override;

    };

    class Sub : public BaseCommand {

    public:

        explicit Sub(std::string parseName = "SUB") : BaseCommand(std::move(parseName)) {};

        void execute() override;

    };

    class Mul : public BaseCommand {

    public:

        explicit Mul(std::string parseName = "MUL") : BaseCommand(std::move(parseName)) {};

        void execute() override;

    };

    class Div : public BaseCommand {

    public:

        explicit Div(std::string parseName = "DIV") : BaseCommand(std::move(parseName)) {};

        void execute() override;

    };

    class In : public BaseCommand {

    public:

        explicit In(std::string parseName = "IN") : BaseCommand(std::move(parseName)) {};

        void execute() override;

    };

    class Out : public BaseCommand {

    public:

        explicit Out(std::string parseName = "OUT") : BaseCommand(std::move(parseName)) {};

        void execute() override;

    };


}


#endif
