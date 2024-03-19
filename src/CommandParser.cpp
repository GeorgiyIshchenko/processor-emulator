#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

#include "Commands.h"
#include "CommandParser.h"
#include "Exceptions.h"


namespace processorEmulator::CommandParser {

    template<class T>
    std::shared_ptr<T> objectGenerator() {
        return std::make_shared<T>(T());
    }

    std::vector<std::function<std::shared_ptr<Commands::BaseCommand>()>> LineParser::_generatorVector = {
            objectGenerator<Commands::Begin>,
            objectGenerator<Commands::End>,
            objectGenerator<Commands::Push>,
            objectGenerator<Commands::Pop>,
            objectGenerator<Commands::PushR>,
            objectGenerator<Commands::PopR>,
            objectGenerator<Commands::Add>,
            objectGenerator<Commands::Sub>,
            objectGenerator<Commands::Mul>,
            objectGenerator<Commands::Div>,
            objectGenerator<Commands::In>,
            objectGenerator<Commands::Out>,
            objectGenerator<Commands::Jmp>,
            objectGenerator<Commands::Jeq>,
            objectGenerator<Commands::Jne>,
            objectGenerator<Commands::Ja>,
            objectGenerator<Commands::Jae>,
            objectGenerator<Commands::Jb>,
            objectGenerator<Commands::Jbe>,
            objectGenerator<Commands::Call>,
            objectGenerator<Commands::Ret>,
            objectGenerator<Commands::LabelCommand>,
            objectGenerator<Commands::BaseCommand>};

    CommandParser::LineParser::LineParser(std::string programPath, std::string objectRegex) {
        _programPath = std::move(programPath);
        _objectRegex = std::move(objectRegex);
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
        std::hash<std::string> hashMaker;


        while (std::getline(file, line)) {
            lineIdx++;

            if (line.empty()) continue;

            std::regex_search(line.cbegin(), line.cend(), lastMatch, std::regex("(#[^\\*]*)"));
            if (!lastMatch.empty()) continue;

            std::regex_search(line.cbegin(), line.cend(), lastMatch, std::regex("([^\\s]+:)"));
            if (!lastMatch.empty()) {
                std::string label = lastMatch[1].str();
                _labelsMap.emplace(hashMaker(label.substr(0, label.length() - 1)), commandIdx);
                _commandVector.push_back(objectGenerator<Commands::LabelCommand>());
                commandIdx++;
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