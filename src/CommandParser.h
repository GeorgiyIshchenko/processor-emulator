#ifndef PROCESSOREMULATOR_COMMANDPARSER_H
#define PROCESSOREMULATOR_COMMANDPARSER_H

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <memory>
#include <Commands.h>
#include <ProcessorEmulator.h>

namespace processorEmulator::CommandParser {

    struct ParserException : public std::exception {

        explicit ParserException(const char *message, int line = 0) : message(message), line(line) {};

        [[nodiscard]] const char *what() const noexcept override {
            return (new std::string("Exception while Parsing: line " + std::to_string(line) + ". " + message))->c_str();
        }

    private:

        const char *message;
        int line;

    };

    enum class Token {
        BEGIN, END,
        PUSH, POP,
        PUSHR, POPR,
        ADD, SUB, MUL, DIV,
        OUT, IN,
        _EMPTY,
    };


    class LineParser {

    public:
        explicit LineParser(const char *programPath, const char *objectRegex = "([+-]?[1-9]*[0-9]+\\.[0-9]*)");

        std::vector<Commands::BaseCommand> getCommandVector();

        static Commands::BaseCommand *
        getCommandFromString(Commands::BaseCommand *command, std::smatch match, int numOfLine) {
            Commands::ArgType argType = command->getArgInfo();

            std::cout << Commands::commandToString(command) << std::endl;

            if (argType == Commands::ArgType::NONE) return command;

            if (match.length() < 3) {
                auto *errorString =
                new std::string("Not enough arguments");
                throw ParserException(errorString->c_str(), numOfLine);
            }

            std::string arg = match[2].str();

            std::cout << arg << std::endl;
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
                auto *registerCommand = dynamic_cast<Commands::RegisterCommand *>(command);
                registerCommand->setRegister(strRegisterMap[arg]);
                return registerCommand;
            } else {
                auto *userArgCommand = dynamic_cast<Commands::UserArgCommand *>(command);
                userArgCommand->setValue(stoi(arg));
                return command;
            };
        }


    private:

        std::string _programPath;

        // Default is double
        std::string _objectRegex;

        std::map<Commands::BaseCommand *, std::string> _commandRegex;

    };


}


#endif
