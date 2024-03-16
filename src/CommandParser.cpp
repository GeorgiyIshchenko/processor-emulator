#include <utility>
#include <vector>
#include <string>

#include <fstream>

#include <Commands.h>
#include <CommandParser.h>


namespace processorEmulator::CommandParser {

    template<class T>
    std::shared_ptr<T> _() {
        return std::make_shared<T>(T());
    }

    CommandParser::LineParser::LineParser(std::string programPath, const char *objectRegex) {
        _programPath = std::move(programPath);
        _objectRegex = objectRegex;

        _commandVector = {_<Commands::Begin>, _<Commands::End>, _<Commands::Push>, _<Commands::Pop>, _<Commands::PushR>,
                          _<Commands::PopR>, _<Commands::Add>, _<Commands::Sub>, _<Commands::Mul>, _<Commands::Div>,
                          _<Commands::In>, _<Commands::Out>};
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
            if (line.empty()) continue;
            isInvalidCommand = true;
            for (const auto &commandGenerator: _commandVector) {
                auto command = commandGenerator();
                std::regex_search(line.cbegin(), line.cend(), last_match, std::regex(command->getStringForRegex()));
                if (!last_match.empty()) {
                    command->setArgFromRegex(last_match, numOfLine);
                    result.push_back(command);
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
        file.close();
        return result;
    }

}