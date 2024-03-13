#include <Commands.h>

namespace processorEmulator {

    std::string Commands::commandToString(Commands::BaseCommand *command) {
        std::map<ArgType, std::string> argTypeStrMap = {
                {ArgType::NONE, "NONE"},
                {ArgType::USER_TYPE, "USER_TYPE"},
                {ArgType::REGISTER, "REGISTER"}
        };
        std::string repr = std::string(typeid(command).name()) + " ArgType: " + argTypeStrMap[command->getArgInfo()];
        return repr;
    }


    void Commands::Begin::execute() {
        BaseCommand::execute();
    }

    void Commands::End::execute() {
        BaseCommand::execute();
    }

    void Commands::Push::execute() {
        BaseCommand::execute();
    }

    void Commands::Pop::execute() {
        BaseCommand::execute();
    }

    void Commands::PushR::execute() {
        BaseCommand::execute();
    }

    void Commands::PopR::execute() {
        BaseCommand::execute();
    }

    void Commands::Add::execute() {
        BaseCommand::execute();
    }

    void Commands::Sub::execute() {
        BaseCommand::execute();
    }

    void Commands::Mul::execute() {
        BaseCommand::execute();
    }

    void Commands::Div::execute() {
        BaseCommand::execute();
    }

    void Commands::In::execute() {
        BaseCommand::execute();
    }

    void Commands::Out::execute() {
        BaseCommand::execute();
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

    void Commands::UserArgCommand::setValue(Commands::argType value) {
        _value = value;
    }
}
