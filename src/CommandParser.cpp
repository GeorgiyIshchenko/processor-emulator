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
                {Token::_EMPTY, "(\\n)"},
                {Token::BEGIN,  "(BEGIN\\b)"},
                {Token::END,    "(END\\b)"},
                {Token::PUSH,   "(PUSH\\b\\ )" + _objectRegex},
                {Token::POP,    "(POP\\b)"},
                {Token::PUSHR,  "(PUSHR\\b\\ )([a-dA-D])"},
                {Token::POPR,   "(POPR\\b\\ )([a-dA-D])"},
                {Token::ADD,    "(ADD\\b)"},
                {Token::SUB,    "(SUB\\b)"},
                {Token::MUL,    "(MUL\\b)"},
                {Token::DIV,    "(DIV\\b)"},
                {Token::OUT,    "(OUT\\b)"},
                {Token::IN,    "(IN\\b)"},
        };
    }

    std::vector<Commands::BaseCommand> LineParser::getCommandVector() {
        std::ifstream file(_programPath);
        std::vector<Commands::BaseCommand> result;

        std::smatch last_match{};

        std::string line;
        while (std::getline(file, line)) {
            for (const auto &item: _commandRegex) {
                unsigned int regexLength = item.second.length();
                std::regex_search(line.cbegin(), line.cend(), last_match, std::regex(item.second));
                if (!last_match.empty()) {
                    Commands::BaseCommand* commandPtr = getCommandFromString(item.first, last_match);
                    if (commandPtr){
                        result.push_back(std::move(*commandPtr));
                    }
                    break;
                }
            }
        }

        return result;
    }

}