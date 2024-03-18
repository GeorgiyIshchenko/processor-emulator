#include <utility>
#include <vector>
#include <string>

#include <fstream>

#include "Commands.h"
#include "CommandParser.h"
#include "Exceptions.h"


namespace processorEmulator::CommandParser {

    template<class T>
    std::shared_ptr<T> _() {
        return std::make_shared<T>(T());
    }

    CommandParser::LineParser::LineParser(std::string programPath, std::string objectRegex) {
        _programPath = std::move(programPath);
        _objectRegex = std::move(objectRegex);

        _generatorVector = {_<Commands::Begin>, _<Commands::End>, _<Commands::Push>, _<Commands::Pop>,
                            _<Commands::PushR>, _<Commands::PopR>, _<Commands::Add>, _<Commands::Sub>, _<Commands::Mul>,
                            _<Commands::Div>, _<Commands::In>, _<Commands::Out>, _<Commands::Jmp>, _<Commands::Jeq>,
                            _<Commands::Jne>, _<Commands::Ja>, _<Commands::Jae>, _<Commands::Jb>, _<Commands::Jbe>,
                            _<Commands::Call>, _<Commands::Ret>};
        _commandVector = {};
        _labelsMap = {};
    }

    void LineParser::parse() {
        std::ifstream file(_programPath);
        if (!file.is_open())
            throw ParserException("Invalid Path");

        std::smatch lastMatch{};

        std::string line;
        int lineIdx = 0;
        size_t commandIdx = 0;

        while (std::getline(file, line)) {
            lineIdx++;

            if (line.empty()) continue;

            std::regex_search(line.cbegin(), line.cend(), lastMatch, std::regex("(#[^\\*]*)"));
            if (!lastMatch.empty()) continue;

            std::regex_search(line.cbegin(), line.cend(), lastMatch, std::regex("([^\\s]+:)"));
            if (!lastMatch.empty()) {
                std::string label = lastMatch[1].str();
                _labelsMap.emplace(label.substr(0, label.length() - 1), commandIdx);
                continue;
            }

            bool isInvalidCommand = true;
            for (const auto &commandGenerator: _generatorVector) {
                auto command = commandGenerator();
                std::regex_search(line.cbegin(), line.cend(), lastMatch,
                                  std::regex(command->getStringForRegex(), std::regex::icase));
                if (!lastMatch.empty()) {
                    command->setArgFromRegex(lastMatch, lineIdx);
                    _commandVector.push_back(command);
                    commandIdx++;
                    isInvalidCommand = false;
                    break;
                }
            }

            if (isInvalidCommand) {
                auto errorMessage = new std::string("Invalid Command");
                throw ParserException(errorMessage->c_str(), lineIdx);
            }
        }
        file.close();
    }

}