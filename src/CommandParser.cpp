#include <vector>
#include <string>

#include <fstream>

#include <Commands.h>
#include <CommandParser.h>


namespace processorEmulator::CommandParser {

    CommandParser::LineParser::LineParser(const char *programPath, const char *objectRegex) {
        _programPath = programPath;
        _objectRegex = objectRegex;
        _commandRegex = {
                {nullptr,               "(\\n)"},
                {new Commands::Begin{}, "(BEGIN\\b)"},
                {new Commands::End{},   "(END\\b)"},
                {new Commands::Push{},  "(PUSH\\b\\ )" + _objectRegex},
                {new Commands::Pop{},   "(POP\\b)"},
                {new Commands::PushR{}, "(PUSHR\\b\\ )([a-zA-Z]X)"},
                {new Commands::PopR{},  "(POPR\\b\\ )([a-zA-Z]X)"},
                {new Commands::Add{},   "(ADD\\b)"},
                {new Commands::Sub{},   "(SUB\\b)"},
                {new Commands::Mul{},   "(MUL\\b)"},
                {new Commands::Div{},   "(DIV\\b)"},
                {new Commands::Out{},   "(OUT\\b)"},
                {new Commands::In{},    "(IN\\b)"},
        };
    }

    std::vector<Commands::BaseCommand> LineParser::getCommandVector() {
        std::ifstream file(_programPath);
        std::vector<Commands::BaseCommand> result;

        std::smatch last_match{};

        std::string line;

        int numOfLine = 1;
        while (std::getline(file, line)) {
            for (const auto &item: _commandRegex) {
                std::regex_search(line.cbegin(), line.cend(), last_match, std::regex(item.second));
                if (!last_match.empty()) {
                    Commands::BaseCommand *commandPtr = getCommandFromString(item.first, last_match, numOfLine);
                    if (commandPtr) {
                        result.push_back(std::move(*commandPtr));
                    }
                    break;
                }
            }
            numOfLine++;
        }

        return result;
    }

}