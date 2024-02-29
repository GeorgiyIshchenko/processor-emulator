#include <vector>
#include <string>
#include <regex>

#include <Commands.h>


#ifndef PROCESSOREMULATOR_COMMANDPARSER_H
#define PROCESSOREMULATOR_COMMANDPARSER_H


namespace processorEmulator::CommandParser {

    enum class Command {
        BEGIN, END,
        PUSH, POP,
        PUSHR, POPR,
        ADD, SUB, MUL, DIV,
        OUT, IN
    };

    class LineParser{



    private:

        std::string _line;

        std::map<Command, std::regex> commandRegex = {
                {Command::BEGIN, std::regex(R"(BEGIN\b)")},
                {Command::ADD, std::regex(R"(ADD\b\ [+-]?[1-9]*[0-9]+\.[0-9]*\ [+-]?[1-9]*[0-9]+\.[0-9]*)")},
                {Command::SUB, std::regex(R"(SUB\b\ [+-]?[1-9]*[0-9]+\.[0-9]*\ [+-]?[1-9]*[0-9]+\.[0-9]*)")},
                {Command::MUL, std::regex(R"(MUL\b\ [+-]?[1-9]*[0-9]+\.[0-9]*\ [+-]?[1-9]*[0-9]+\.[0-9]*)")},
                {Command::DIV, std::regex(R"(DIV\b\ [+-]?[1-9]*[0-9]+\.[0-9]*\ [+-]?[1-9]*[0-9]+\.[0-9]*)")},
        };

    };


    std::vector<BaseCommand> getCommandVector(const char* pathToExe);


}


#endif
