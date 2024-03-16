#include <iostream>
#include <regex>

#include "Commands.h"
#include "CommandParser.h"

namespace processorEmulator {

    void Commands::Begin::execute(Processor::ProcessorState* processorState) {
        processorState->status =  Processor::Status::RUNNING;
    }

    void Commands::End::execute(Processor::ProcessorState* processorState) {
        processorState->status =  Processor::Status::ENDED;
    }

    void Commands::Push::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING)
            processorState->stack.push(_value);
    }

    void Commands::Pop::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING)
            processorState->stack.pop();
    }

    void Commands::PushR::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING)
            processorState->stack.push(processorState->registers[static_cast<int>(_reg)]);
    }

    void Commands::PopR::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING)
            processorState->registers[static_cast<int>(_reg)] = processorState->stack.pop();
    }

    void Commands::Add::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING) {
            processorState->stack.push(processorState->stack.pop() + processorState->stack.pop());
        }
    }

    void Commands::Sub::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING) {
            processorState->stack.push(processorState->stack.pop() - processorState->stack.pop());

        }
    }

    void Commands::Mul::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING) {
            processorState->stack.push(processorState->stack.pop() * processorState->stack.pop());

        }
    }

    void Commands::Div::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING) {
            processorState->stack.push(processorState->stack.pop() / processorState->stack.pop());

        }
    }

    void Commands::In::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING) {
            argType input;
            std::cin >> input;
            processorState->stack.push(input);
        }
    }

    void Commands::Out::execute(Processor::ProcessorState* processorState) {
        if (processorState->status == Processor::Status::RUNNING)
            std::cout << processorState->stack.getTop() << std::endl;
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
