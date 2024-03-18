#include "Starter.h"

#include <utility>
#include "CommandParser.h"
#include "Commands.h"

namespace processorEmulator {

    Starter::Starter(std::string programPath, std::string objectRegex) {
        _programPath = std::move(programPath);
        _objectRegex = std::move(objectRegex);
    }

    void Starter::doit() {
        try{
            auto commands = CommandParser::LineParser(_programPath, _objectRegex).getCommandVector();
            Processor processor{commands};
            for (const auto& command: commands) {
                command->execute(processor.getState());
            }
        }
        catch (CommandParser::ParserException& e){
            std::cout << e.what() << std::endl;
        }
        catch (StackException& e){
            std::cout << e.what() << std::endl;
        }
    }
}