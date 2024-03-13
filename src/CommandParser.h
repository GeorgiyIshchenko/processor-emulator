#ifndef PROCESSOREMULATOR_COMMANDPARSER_H
#define PROCESSOREMULATOR_COMMANDPARSER_H

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <Commands.h>
#include <ProcessorEmulator.h>

namespace processorEmulator::CommandParser {

    struct ParserException : public std::exception {

        explicit ParserException(const char *message) : message(message) {};

        [[nodiscard]] const char *what() const noexcept override {
            return message;
        }

    private:

        const char *message;

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

        static Commands::BaseCommand *getCommandFromString(Token command, std::smatch match) {
            switch (command) {
                case Token::BEGIN:
                    return new Commands::Begin{};
                case Token::END:
                    return new Commands::End{};
                case Token::PUSH:
                    if (match.length() < 3)
                        throw ParserException("Exception while Parsing: Invalid PUSH command");
                    return new Commands::Push{stoi(match[2].str())};
                case Token::POP:
                    return new Commands::Pop{};
                case Token::PUSHR:
                    if (match.length() < 3)
                        throw ParserException("Exception while Parsing: Invalid PUSHR command");
                    return new Commands::PushR{RegisterMap.at(match[2].str())};
                case Token::POPR:
                    if (match.length() < 3)
                        throw ParserException("Exception while Parsing: Invalid POPR command");
                    return new Commands::PopR{RegisterMap.at(match[2].str())};
                case Token::ADD:
                    return new Commands::Add{};
                case Token::SUB:
                    return new Commands::Sub{};
                case Token::MUL:
                    return new Commands::Mul{};
                case Token::DIV:
                    return new Commands::Div{};
                case Token::OUT:
                    return new Commands::Out{};
                case Token::IN:
                    return new Commands::In{};
                default:
                    return nullptr;
            }
        }


    private:

        std::string _programPath;

        // Default is double
        std::string _objectRegex;

        std::map<Token, std::string> _commandRegex;

    };


}


#endif
