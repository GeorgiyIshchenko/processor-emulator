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
                {"(^\\s*$)",                    []() { return nullptr; }},
                {"(BEGIN\\b)",                  []() { return std::make_shared<Commands::Begin>(Commands::Begin{}); }},
                {"(END\\b)",                    []() { return std::make_shared<Commands::End>(Commands::End{}); }},
                {"(PUSH\\b\\ )" + _objectRegex, []() { return std::make_shared<Commands::Push>(Commands::Push{}); }},
                {"(POP\\b)",                    []() { return std::make_shared<Commands::Pop>(Commands::Pop{}); },},
                {"(PUSHR\\b\\ )([a-zA-Z]X)",    []() { return std::make_shared<Commands::PushR>(Commands::PushR{}); }},
                {"(POPR\\b\\ )([a-zA-Z]X)",     []() { return std::make_shared<Commands::PopR>(Commands::PopR{}); }},
                {"(ADD\\b)",                    []() { return std::make_shared<Commands::Add>(Commands::Add{}); }},
                {"(SUB\\b)",                    []() { return std::make_shared<Commands::Sub>(Commands::Sub{}); }},
                {"(MUL\\b)",                    []() { return std::make_shared<Commands::Mul>(Commands::Mul{}); }},
                {"(DIV\\b)",                    []() { return std::make_shared<Commands::Div>(Commands::Div{}); }},
                {"(OUT\\b)",                    []() { return std::make_shared<Commands::Out>(Commands::Out{}); }},
                {"(IN\\b)",                     []() { return std::make_shared<Commands::In>(Commands::In{}); }},
        };
    }

    std::vector<std::shared_ptr<Commands::BaseCommand>> LineParser::getCommandVector() {
        std::ifstream file(_programPath);
        if (file.bad())
            throw ParserException("Invalid Path");
        std::vector<std::shared_ptr<Commands::BaseCommand>> result;

        std::smatch last_match{};

        std::string line;
        int numOfLine = 1;
        bool isInvalidCommand;

        while (std::getline(file, line)) {
            isInvalidCommand = true;
            for (const auto &item: _commandRegex) {
                std::regex_search(line.cbegin(), line.cend(), last_match, std::regex(item.first));
                if (!last_match.empty()) {
                    auto command = item.second();
                    if (command) {
                        getCommandFromString(command,last_match,numOfLine);
                        result.push_back(command);
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