#include <utility>
#include <vector>
#include <string>

#include <fstream>

#include <Commands.h>
#include <CommandParser.h>


namespace processorEmulator::CommandParser {

    CommandParser::LineParser::LineParser(std::string programPath, const char *objectRegex) {
        _programPath = std::move(programPath);
        _objectRegex = objectRegex;
        _commandRegex = {
                {nullptr,                                              "(^\\s*$)"},
                {std::make_unique<Commands::Begin>(Commands::Begin{}), "(BEGIN\\b)"},
                {std::make_unique<Commands::End>(Commands::End{}),     "(END\\b)"},
                {std::make_unique<Commands::Push>(Commands::Push{}),   "(PUSH\\b\\ )" + _objectRegex},
                {std::make_unique<Commands::Pop>(Commands::Pop{}),     "(POP\\b)"},
                {std::make_unique<Commands::PushR>(Commands::PushR{}), "(PUSHR\\b\\ )([a-zA-Z]X)"},
                {std::make_unique<Commands::PopR>(Commands::PopR{}),   "(POPR\\b\\ )([a-zA-Z]X)"},
                {std::make_unique<Commands::Add>(Commands::Add{}),     "(ADD\\b)"},
                {std::make_unique<Commands::Sub>(Commands::Sub{}),     "(SUB\\b)"},
                {std::make_unique<Commands::Mul>(Commands::Mul{}),     "(MUL\\b)"},
                {std::make_unique<Commands::Div>(Commands::Div{}),     "(DIV\\b)"},
                {std::make_unique<Commands::Out>(Commands::Out{}),     "(OUT\\b)"},
                {std::make_unique<Commands::In>(Commands::In{}),       "(IN\\b)"},
        };
    }

    std::vector<std::shared_ptr<Commands::BaseCommand>> LineParser::getCommandVector() {
        std::ifstream file(_programPath);
        std::vector<std::shared_ptr<Commands::BaseCommand>> result;

        std::smatch last_match{};

        std::string line;
        int numOfLine = 1;
        bool isInvalidCommand;

        while (std::getline(file, line)) {
            isInvalidCommand = true;
            for (const auto &item: _commandRegex) {
                std::regex_search(line.cbegin(), line.cend(), last_match, std::regex(item.second));
                if (!last_match.empty()) {
                    if (item.first) {
                        std::shared_ptr<Commands::BaseCommand> commandPtr = getCommandFromString(item.first, last_match,
                                                                                                 numOfLine);
                        result.push_back(commandPtr);
                    }
                    isInvalidCommand = false;
                    break;
                }
            }
            if (isInvalidCommand) {
                auto errorMessage = new std::string("Invalid Command");
                throw ParserException(errorMessage->c_str(), numOfLine);
            }
            numOfLine++;
        }

        return result;
    }

    std::shared_ptr<Commands::BaseCommand>
    LineParser::getCommandFromString(std::shared_ptr<Commands::BaseCommand> command, const std::smatch &match,
                                     int numOfLine) {
        Commands::ArgType argType = command->getArgInfo();

        if (argType == Commands::ArgType::NONE) return command;

        if (match.length() < 3) {
            auto *errorString =
                    new std::string("Not enough arguments");
            throw ParserException(errorString->c_str(), numOfLine);
        }

        std::string arg = match[2].str();

        if (argType == Commands::ArgType::REGISTER) {
            std::map<std::string, Register> strRegisterMap{
                    {"AX", Register::AX},
                    {"BX", Register::BX},
                    {"CX", Register::CX},
                    {"DX", Register::DX}
            };
            if (!strRegisterMap.count(arg)) {
                auto *errorString =
                        new std::string("Invalid Register");
                throw ParserException(errorString->c_str(), numOfLine);
            }
            auto registerCommand = dynamic_pointer_cast<Commands::RegisterCommand>(command);
            registerCommand->setRegister(strRegisterMap[arg]);
            return registerCommand;
        } else {
            auto userArgCommand = dynamic_pointer_cast<Commands::UserArgCommand>(command);
            userArgCommand->setValue(stoi(arg));
            return command;
        };
    }
}