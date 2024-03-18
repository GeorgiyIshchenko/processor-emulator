#ifndef PROCESSOREMULATOR_COMMANDS_H
#define PROCESSOREMULATOR_COMMANDS_H

#include <regex>
#include <utility>

#include "ProcessorState.h"

namespace processorEmulator::Commands {


    class BaseCommand {

    public:

        explicit BaseCommand(std::string parseName = "BASE_COMMAND") : _parseName(std::move(parseName)) {};

        virtual void execute(ProcessorState* processorState) {};

        virtual void setArgFromRegex(const std::smatch &match, int numOfLine) {};

        virtual std::string getStringForRegex();

    protected:

        std::string _parseName;

    };

    class Begin : public BaseCommand {

    public:

        explicit Begin(std::string parseName = "BEGIN") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class End : public BaseCommand {

    public:

        explicit End(std::string parseName = "END") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class UserArgCommand : public BaseCommand {

    public:

        explicit UserArgCommand(std::string parseName, std::string objectRegex, argType value = 0) :
        BaseCommand(std::move(parseName)) {
            _value = value;
            _objectRegex = std::move(objectRegex);
        };

        void execute(ProcessorState* processorState) override = 0;

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

        std::string getStringForRegex() override;

    protected:

        argType _value{};

        std::string _objectRegex;

    };

    class Push : public UserArgCommand {

    public:

        explicit Push(std::string parseName = "PUSH", std::string objectRegex = "([+-]?[1-9]*[0-9]*)",
                      argType value = 0) : UserArgCommand(std::move(parseName), std::move(objectRegex), value) {};

        void execute(ProcessorState* processorState) override;

    };

    class Pop : public BaseCommand {

    public:

        explicit Pop(std::string parseName = "POP") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class RegisterCommand : public BaseCommand {

    public:

        explicit RegisterCommand(std::string parseName = "REGISTER", Register reg = Register::AX) : BaseCommand(
                std::move(parseName)) { _reg = reg; };

        void execute(ProcessorState* processorState) override = 0;

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

        std::string getStringForRegex() override;

    protected:

        Register _reg;

    };

    class PushR : public RegisterCommand {

    public:

        explicit PushR(std::string parseName = "PUSHR") : RegisterCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class PopR : public RegisterCommand {

    public:

        explicit PopR(std::string parseName = "POPR") : RegisterCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Add : public BaseCommand {

    public:

        explicit Add(std::string parseName = "ADD") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Sub : public BaseCommand {

    public:

        explicit Sub(std::string parseName = "SUB") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Mul : public BaseCommand {

    public:

        explicit Mul(std::string parseName = "MUL") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Div : public BaseCommand {

    public:

        explicit Div(std::string parseName = "DIV") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class In : public BaseCommand {

    public:

        explicit In(std::string parseName = "IN") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Out : public BaseCommand {

    public:

        explicit Out(std::string parseName = "OUT") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class LabelCommand: public BaseCommand {

    public:

        explicit LabelCommand(std::string parseName = "LABEL") : BaseCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override = 0;

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

        std::string getStringForRegex() override;

    protected:

        std::string _label;

    };

    class Jmp: public LabelCommand {

        explicit Jmp(std::string parseName = "JMP"): LabelCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Jeq: public LabelCommand {

        explicit Jeq(std::string parseName = "JEQ"): LabelCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Jne: public LabelCommand {

        explicit Jne(std::string parseName = "JNE"): LabelCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Ja: public LabelCommand {

        explicit Ja(std::string parseName = "JA"): LabelCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Jae: public LabelCommand {

        explicit Jae(std::string parseName = "JAE"): LabelCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Jb: public LabelCommand {

        explicit Jb(std::string parseName = "JB"): LabelCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

    class Jbe: public LabelCommand {

        explicit Jbe(std::string parseName = "JBE"): LabelCommand(std::move(parseName)) {};

        void execute(ProcessorState* processorState) override;

    };

}


#endif
