#include <iostream>
#include <Commands.h>

namespace processorEmulator {

    Processor &processor = Processor::instance();

    std::string Commands::commandToString(Commands::BaseCommand *command) {
        std::map<ArgType, std::string> argTypeStrMap = {
                {ArgType::NONE,      "NONE"},
                {ArgType::USER_TYPE, "USER_TYPE"},
                {ArgType::REGISTER,  "REGISTER"}
        };
        std::string repr = std::string(typeid(command).name()) + " ArgType: " + argTypeStrMap[command->getArgInfo()];
        return repr;
    }


    void Commands::Begin::execute() {
        processor.setStatus(Processor::Status::RUNNING);
    }

    void Commands::End::execute() {
        processor.setStatus(Processor::Status::ENDED);
    }

    void Commands::Push::execute() {
        if (processor.isRunning())
            processor.getStack().push(_value);
    }

    void Commands::Pop::execute() {
        if (processor.isRunning())
            processor.getStack().pop();
    }

    void Commands::PushR::execute() {
        if (processor.isRunning())
            processor.getStack().push(processor.getRegisters()[static_cast<int>(_reg)]);
    }

    void Commands::PopR::execute() {
        if (processor.isRunning())
            processor.getRegisters()[static_cast<int>(_reg)] = processor.getStack().pop();
    }

    void Commands::Add::execute() {
        if (processor.isRunning()) {
            Stack<argType> stack = processor.getStack();
            argType sum = stack.pop() + stack.pop();
            stack.push(sum);
        }
    }

    void Commands::Sub::execute() {
        if (processor.isRunning()) {
            Stack<argType> stack = processor.getStack();
            argType sum = stack.pop() - stack.pop();
            stack.push(sum);
        }
    }

    void Commands::Mul::execute() {
        if (processor.isRunning()) {
            Stack<argType> stack = processor.getStack();
            argType sum = stack.pop() * stack.pop();
            stack.push(sum);
        }
    }

    void Commands::Div::execute() {
        if (processor.isRunning()) {
            Stack<argType> stack = processor.getStack();
            argType sum = stack.pop() / stack.pop();
            stack.push(sum);
        }
    }

    void Commands::In::execute() {
        if (processor.isRunning()) {
            argType input;
            std::cin >> input;
            processor.getStack().push(input);
        }
    }

    void Commands::Out::execute() {
        if (processor.isRunning())
            std::cout << processor.getStack().getTop() << std::endl;
    }

    Commands::ArgType Commands::BaseCommand::getArgInfo() {
        return Commands::ArgType::NONE;
    }

    Commands::ArgType Commands::RegisterCommand::getArgInfo() {
        return Commands::ArgType::REGISTER;
    }

    void Commands::RegisterCommand::setRegister(Register reg) {
        _reg = reg;
    }

    Commands::ArgType Commands::UserArgCommand::getArgInfo() {
        return ArgType::USER_TYPE;
    }

    void Commands::UserArgCommand::setValue(argType value) {
        _value = value;
    }
}
