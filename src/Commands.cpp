#include <iostream>
#include <regex>

#include "Commands.h"
#include "CommandParser.h"

namespace processorEmulator {

    Processor &processor = Processor::instance();

    void Commands::Begin::execute() {
        Processor::instance().setStatus(Processor::Status::RUNNING);
    }

    void Commands::End::execute() {
        processor.setStatus(Processor::Status::ENDED);
    }

    void Commands::Push::execute() {
        if (processor.isRunning())
            processor.getStack()->push(_value);
    }

    void Commands::Pop::execute() {
        if (processor.isRunning())
            processor.getStack()->pop();
    }

    void Commands::PushR::execute() {
        if (processor.isRunning())
            processor.getStack()->push(processor.getRegisters()[static_cast<int>(_reg)]);
    }

    void Commands::PopR::execute() {
        if (processor.isRunning())
            processor.getRegisters()[static_cast<int>(_reg)] = processor.getStack()->pop();
    }

    void Commands::Add::execute() {
        if (processor.isRunning()) {
            Stack<argType>* stack = processor.getStack();
            argType sum = stack->pop() + stack->pop();
            stack->push(sum);
        }
    }

    void Commands::Sub::execute() {
        if (processor.isRunning()) {
            Stack<argType>* stack = processor.getStack();
            argType sub = stack->pop() - stack->pop();
            stack->push(sub);
        }
    }

    void Commands::Mul::execute() {
        if (processor.isRunning()) {
            Stack<argType>* stack = processor.getStack();
            argType mul = stack->pop() * stack->pop();
            stack->push(mul);
        }
    }

    void Commands::Div::execute() {
        if (processor.isRunning()) {
            Stack<argType>* stack = processor.getStack();
            argType div = stack->pop() / stack->pop();
            stack->push(div);
        }
    }

    void Commands::In::execute() {
        if (processor.isRunning()) {
            argType input;
            std::cin >> input;
            processor.getStack()->push(input);
        }
    }

    void Commands::Out::execute() {
        if (processor.isRunning())
            std::cout << processor.getStack()->getTop() << std::endl;
    }

    void Commands::RegisterCommand::setArgFromRegex(const std::smatch &match, int numOfLine) {
        if (match.length() < 3) {
            auto *errorString =
                    new std::string("Not enough arguments");
            throw CommandParser::ParserException(errorString->c_str(), numOfLine);
        }
        std::string arg = match[2].str();
        std::map<std::string, Register> strRegisterMap{
                {"AX", Register::AX},
                {"BX", Register::BX},
                {"CX", Register::CX},
                {"DX", Register::DX}
        };
        if (!strRegisterMap.count(arg)) {
            auto *errorString =
                    new std::string("Invalid Register");
            throw CommandParser::ParserException(errorString->c_str(), numOfLine);
        }
        _reg = strRegisterMap[arg];
    }

    void Commands::UserArgCommand::setArgFromRegex(const std::smatch &match, int numOfLine) {
        if (match.length() < 3) {
            auto *errorString =
                    new std::string("Not enough arguments");
            throw CommandParser::ParserException(errorString->c_str(), numOfLine);
        }
        _value = stoi(match[2].str());
    }

    std::string Commands::UserArgCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)\\ " + _objectRegex;
    }

    std::string Commands::RegisterCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)\\ ([a-zA-Z]X)";
    }

    std::string Commands::BaseCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)";
    }
}
