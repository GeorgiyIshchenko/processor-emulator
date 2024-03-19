#include <iostream>
#include <regex>
#include <unordered_map>

#include "Commands.h"
#include "CommandParser.h"
#include "Exceptions.h"

namespace processorEmulator {

    void Commands::BaseCommand::printCommandName(ProcessorState &processorState) {
        if (processorState.isRunning())
            std::cout << _parseName << std::endl;
    }

    void Commands::Begin::execute(ProcessorState &processorState) {
        processorState.status = Status::RUNNING;
    }

    void Commands::End::execute(ProcessorState &processorState) {
        processorState.status = Status::ENDED;
    }

    void Commands::Push::execute(ProcessorState &processorState) {
        if (processorState.isRunning())
            processorState.stack.push(_value);
    }

    void Commands::Pop::execute(ProcessorState &processorState) {
        if (processorState.isRunning())
            processorState.stack.pop();
    }

    void Commands::PushR::execute(ProcessorState &processorState) {
        if (processorState.isRunning())
            processorState.stack.push(processorState.registers[static_cast<int>(_reg)]);
    }

    void Commands::PopR::execute(ProcessorState &processorState) {
        if (processorState.isRunning())
            processorState.registers[static_cast<int>(_reg)] = processorState.stack.pop();
    }

    void Commands::Add::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            processorState.stack.push(processorState.stack.pop() + processorState.stack.pop());
        }
    }

    void Commands::Sub::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            processorState.stack.push(processorState.stack.pop() - processorState.stack.pop());
        }
    }

    void Commands::Mul::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            processorState.stack.push(processorState.stack.pop() * processorState.stack.pop());
        }
    }

    void Commands::Div::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            processorState.stack.push(processorState.stack.pop() / processorState.stack.pop());

        }
    }

    void Commands::In::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            argType input;
            std::cin >> input;
            processorState.stack.push(input);
        }
    }

    void Commands::Out::execute(ProcessorState &processorState) {
        if (processorState.isRunning())
            std::cout << processorState.stack.getTop() << std::endl;
    }

    struct DoubleTop {
        argType higher;
        argType lower;
    };

    DoubleTop getTwoTopValues(Stack<argType> *stack) {
        DoubleTop result = {.higher = stack->pop(), .lower=stack->getTop()};
        stack->push(result.higher);
        return result;
    }

    void jump(ProcessorState &processorState, size_t label) {
        processorState.head = processorState.commands.cbegin() + processorState.labels[label];
    }

    void Commands::Jmp::execute(ProcessorState &processorState) {
        if (processorState.isRunning())
            jump(processorState, _labelHash);
    }

    void Commands::Jeq::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            DoubleTop top = getTwoTopValues(&processorState.stack);
            if (top.lower == top.higher)
                jump(processorState, _labelHash);
        }
    }

    void Commands::Jne::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            DoubleTop top = getTwoTopValues(&processorState.stack);
            if (top.lower != top.higher)
                jump(processorState, _labelHash);
        }
    }

    void Commands::Ja::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            DoubleTop top = getTwoTopValues(&processorState.stack);
            if (top.lower < top.higher)
                jump(processorState, _labelHash);
        }
    }

    void Commands::Jae::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            DoubleTop top = getTwoTopValues(&processorState.stack);
            if (top.lower <= top.higher)
                jump(processorState, _labelHash);
        }
    }

    void Commands::Jb::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            DoubleTop top = getTwoTopValues(&processorState.stack);
            if (top.lower > top.higher)
                jump(processorState, _labelHash);
        }
    }

    void Commands::Jbe::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            DoubleTop top = getTwoTopValues(&processorState.stack);
            if (top.lower >= top.higher)
                jump(processorState, _labelHash);
        }
    }

    void Commands::Call::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            processorState.callStack.push(
                    std::make_pair(std::distance(processorState.commands.cbegin(), processorState.head),
                                   processorState.stack.getSize()));
            jump(processorState, _labelHash);
        }
    }

    void Commands::Ret::execute(ProcessorState &processorState) {
        if (processorState.isRunning()) {
            auto callStackItemState = processorState.callStack.pop();
            processorState.head = processorState.commands.cbegin() + callStackItemState.first;
            while (processorState.callStack.getSize() > callStackItemState.second)
                processorState.stack.pop();
        }
    }

    void checkArguments(const std::smatch &match, int numOfLine) {
        if (match.length() < 3) {
            auto *errorString = new std::string("Not enough arguments");
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
                {"DX", Register::DX},
        };
        std::transform(arg.begin(), arg.end(), arg.begin(), [](unsigned char c) { return std::toupper(c); });
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
        std::hash<std::string> hashMaker;
        _labelHash = hashMaker(match[2].str());
    }

    std::string Commands::BaseCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)";
    }

    std::string Commands::UserArgCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)\\ " + _objectRegex;
    }

    std::string Commands::RegisterCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)\\ ([A-Z]X)";
    }

    std::string Commands::LabelCommand::getStringForRegex() {
        return "(" + _parseName + "\\b)\\ ([^\\s]+)";
    }

}
