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


    class LineParser {

    public:
        explicit LineParser(std::string programPath, const char *objectRegex = "([+-]?[1-9]*[0-9]*)");

        std::vector<std::shared_ptr<Commands::BaseCommand>> getCommandVector();

        static std::shared_ptr<Commands::BaseCommand>
        getCommandFromString(std::shared_ptr<Commands::BaseCommand> command, const std::smatch& match, int numOfLine);


    private:

        std::string _programPath;

        // Default is int
        // Regex for double: "([+-]?[1-9]*[0-9]+\\.[0-9]*)"
        std::string _objectRegex;

        std::map<std::shared_ptr<Commands::BaseCommand>, std::string> _commandRegex;

    };


}


#endif
