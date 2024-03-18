#include "Starter.h"

#include "ProcessorEmulator.h"
#include "CommandParser.h"
#include "Exceptions.h"

namespace processorEmulator {

    Starter::Starter(const std::string& programPath, const std::string& objectRegex) {
        _programPath = programPath;
        _objectRegex = objectRegex;
    }

    void Starter::doit() {
        try{
            auto parser = CommandParser::LineParser(_programPath, _objectRegex);
            parser.parse();
            auto commands = parser.getCommands();
            auto labels = parser.getLabels();
            Processor processor{commands, labels};
            processor.execute();
        }
        catch (CommandParser::ParserException& e){
            std::cout << e.what() << std::endl;
        }
        catch (StackException& e){
            std::cout << e.what() << std::endl;
        }
    }
}