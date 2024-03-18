#include <iostream>
#include <regex>

#include "Commands.h"
#include "CommandParser.h"

namespace processorEmulator {

    void Commands::Begin::execute(ProcessorState* processorState) {
        processorState->status =  Status::RUNNING;
    }

    void Commands::End::execute(ProcessorState* processorState) {
        processorState->status =  Status::ENDED;
    }

    void Commands::Push::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING)
            processorState->stack.push(_value);
    }

    void Commands::Pop::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING)
            processorState->stack.pop();
    }

    void Commands::PushR::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING)
            processorState->stack.push(processorState->registers[static_cast<int>(_reg)]);
    }

    void Commands::PopR::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING)
            processorState->registers[static_cast<int>(_reg)] = processorState->stack.pop();
    }

    void Commands::Add::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING) {
            processorState->stack.push(processorState->stack.pop() + processorState->stack.pop());
        }
    }

    void Commands::Sub::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING) {
            processorState->stack.push(processorState->stack.pop() - processorState->stack.pop());

        }
    }

    void Commands::Mul::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING) {
            processorState->stack.push(processorState->stack.pop() * processorState->stack.pop());

        }
    }

    void Commands::Div::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING) {
            processorState->stack.push(processorState->stack.pop() / processorState->stack.pop());

        }
    }

    void Commands::In::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING) {
            argType input;
            std::cin >> input;
            processorState->stack.push(input);
        }
    }

    void Commands::Out::execute(ProcessorState* processorState) {
        if (processorState->status == Status::RUNNING)
            std::cout << processorState->stack.getTop() << std::endl;
    }

    void checkArguments(const std::smatch &match, int numOfLine){
        if (match.length() < 3) {
            auto *errorString =
                    new std::string("Not enough arguments");
            throw CommandParser::ParserException(errorString->c_str(), numOfLine);
        }
    }

    void Commands::RegisterCommand::setArgFromRegex(const std::smatch &match, int numOfLine) {
        checkArguments(match, numOfLine);
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
        checkArguments(match, numOfLine);
        _value = stoi(match[2].str());
    }

    void Commands::LabelCommand::setArgFromRegex(const std::smatch &match, int numOfLine) {
        checkArguments(match, numOfLine);
        _label = match[2].str();
    }

    std::string Commands::BaseCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)";
    }

    std::string Commands::UserArgCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)\\ " + _objectRegex;
    }

    std::string Commands::RegisterCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)\\ ([a-zA-Z]X)";
    }

    std::string Commands::LabelCommand::getStringForRegex() {
        return BaseCommand::getStringForRegex();
    }
}
