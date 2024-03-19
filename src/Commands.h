#ifndef PROCESSOREMULATOR_COMMANDS_H
#define PROCESSOREMULATOR_COMMANDS_H

#include <regex>
#include <utility>

#include "ProcessorState.h"

namespace processorEmulator::Commands {


    enum class Code : char {
        Begin,
        End,
        Push,
        Pop,
        Pushr,
        Popr,
        Add,
        Sub,
        Mul,
        Div,
        Out,
        In,
        Jmp,
        Jeq,
        Jne,
        Ja,
        Jae,
        Jb,
        Jbe,
        Call,
        Ret,
        Label,
        Base
    };


    class BaseCommand {

    public:

        explicit BaseCommand(std::string parseName = "BASE_COMMAND", Code code = Code::Base) : _parseName(
                std::move(parseName)), _code(code) {};

        virtual void execute(ProcessorState &processorState) {};

        virtual void setArgFromRegex(const std::smatch &match, int numOfLine) {};

        virtual void setArg(size_t arg) {};

        virtual std::string getStringForRegex();

        virtual void printCommandName(ProcessorState &processorState);

        virtual Code getCode() { return _code; };

        virtual size_t getArgument() { return 0; };

    protected:

        std::string _parseName;

        Code _code;

    };

    class Begin : public BaseCommand {

    public:

        explicit Begin(std::string parseName = "BEGIN") : BaseCommand(std::move(parseName), Code::Begin) {};

        void execute(ProcessorState &processorState) override;

    };

    class End : public BaseCommand {

    public:

        explicit End(std::string parseName = "END") : BaseCommand(std::move(parseName), Code::End) {};

        void execute(ProcessorState &processorState) override;

    };

    class UserArgCommand : public BaseCommand {

    public:

        explicit UserArgCommand(std::string parseName, std::string objectRegex, argType value = 0,
                                Code code = Code::Base) :
                BaseCommand(std::move(parseName), code) {
            _value = value;
            _objectRegex = std::move(objectRegex);
        };

        void execute(ProcessorState &processorState) override = 0;

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

        void setArg(size_t arg) override { _value = static_cast<argType>(arg); };

        std::string getStringForRegex() override;

        size_t getArgument() override { return _value; };

    protected:

        argType _value{};

        std::string _objectRegex;

    };

    class Push : public UserArgCommand {

    public:

        explicit Push(std::string parseName = "PUSH", std::string objectRegex = "([+-]?[1-9]*[0-9]*)",
                      argType value = 0) : UserArgCommand(std::move(parseName), std::move(objectRegex), value, Code::Push) {};

        void execute(ProcessorState &processorState) override;

    };

    class Pop : public BaseCommand {

    public:

        explicit Pop(std::string parseName = "POP") : BaseCommand(std::move(parseName), Code::Pop) {};

        void execute(ProcessorState &processorState) override;

    };

    class RegisterCommand : public BaseCommand {

    public:

        explicit RegisterCommand(std::string parseName = "REGISTER", Code code = Code::Base, Register reg = Register::AX) : BaseCommand(
                std::move(parseName), code) { _reg = reg; };

        void execute(ProcessorState &processorState) override = 0;

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

        void setArg(size_t arg) override { _reg = static_cast<Register>(arg); };

        std::string getStringForRegex() override;


        size_t getArgument() override { return static_cast<size_t>(_reg); };

    protected:

        Register _reg;

    };

    class PushR : public RegisterCommand {

    public:

        explicit PushR(std::string parseName = "PUSHR") : RegisterCommand(std::move(parseName), Code::Pushr) {};

        void execute(ProcessorState &processorState) override;

    };

    class PopR : public RegisterCommand {

    public:

        explicit PopR(std::string parseName = "POPR") : RegisterCommand(std::move(parseName), Code::Popr) {};

        void execute(ProcessorState &processorState) override;

    };

    class Add : public BaseCommand {

    public:

        explicit Add(std::string parseName = "ADD") : BaseCommand(std::move(parseName), Code::Add) {};

        void execute(ProcessorState &processorState) override;

    };

    class Sub : public BaseCommand {

    public:

        explicit Sub(std::string parseName = "SUB") : BaseCommand(std::move(parseName), Code::Sub) {};

        void execute(ProcessorState &processorState) override;

    };

    class Mul : public BaseCommand {

    public:

        explicit Mul(std::string parseName = "MUL") : BaseCommand(std::move(parseName), Code::Mul) {};

        void execute(ProcessorState &processorState) override;

    };

    class Div : public BaseCommand {

    public:

        explicit Div(std::string parseName = "DIV") : BaseCommand(std::move(parseName), Code::Div) {};

        void execute(ProcessorState &processorState) override;

    };

    class In : public BaseCommand {

    public:

        explicit In(std::string parseName = "IN") : BaseCommand(std::move(parseName), Code::In) {};

        void execute(ProcessorState &processorState) override;

    };

    class Out : public BaseCommand {

    public:

        explicit Out(std::string parseName = "OUT") : BaseCommand(std::move(parseName), Code::Out) {};

        void execute(ProcessorState &processorState) override;

    };

    class LabelCommand : public BaseCommand {

    public:

        explicit LabelCommand(std::string parseName = "LABEL", Code code = Code::Label) : BaseCommand(std::move(parseName), code) {};

        void execute(ProcessorState &processorState) override {};

        void setArgFromRegex(const std::smatch &match, int numOfLine) override;

        void setArg(size_t arg) override { _labelHash = arg; };

        std::string getStringForRegex() override;

        size_t getArgument() override { return _labelHash; };

    protected:

        size_t _labelHash;

    };

    class Jmp : public LabelCommand {

    public:

        explicit Jmp(std::string parseName = "JMP") : LabelCommand(std::move(parseName), Code::Jmp) {};

        void execute(ProcessorState &processorState) override;

    };

    class Jeq : public LabelCommand {

    public:

        explicit Jeq(std::string parseName = "JEQ") : LabelCommand(std::move(parseName), Code::Jeq) {};

        void execute(ProcessorState &processorState) override;

    };

    class Jne : public LabelCommand {

    public:

        explicit Jne(std::string parseName = "JNE") : LabelCommand(std::move(parseName), Code::Jne) {};

        void execute(ProcessorState &processorState) override;

    };

    class Ja : public LabelCommand {

    public:

        explicit Ja(std::string parseName = "JA") : LabelCommand(std::move(parseName), Code::Ja) {};

        void execute(ProcessorState &processorState) override;

    };

    class Jae : public LabelCommand {

    public:

        explicit Jae(std::string parseName = "JAE") : LabelCommand(std::move(parseName), Code::Jae) {};

        void execute(ProcessorState &processorState) override;

    };

    class Jb : public LabelCommand {

    public:

        explicit Jb(std::string parseName = "JB") : LabelCommand(std::move(parseName), Code::Jb) {};

        void execute(ProcessorState &processorState) override;

    };

    class Jbe : public LabelCommand {

    public:

        explicit Jbe(std::string parseName = "JBE") : LabelCommand(std::move(parseName), Code::Jbe) {};

        void execute(ProcessorState &processorState) override;

    };

    class Call : public LabelCommand {

    public:

        explicit Call(std::string parseName = "CALL") : LabelCommand(std::move(parseName), Code::Call) {};

        void execute(ProcessorState &processorState) override;

    };

    class Ret : public BaseCommand {

    public:

        explicit Ret(std::string parseName = "RET") : BaseCommand(std::move(parseName), Code::Ret) {};

        void execute(ProcessorState &processorState) override;

    };

}


#endif
