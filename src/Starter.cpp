#include <fstream>

#include "Starter.h"
#include "ProcessorEmulator.h"
#include "CommandParser.h"
#include "Exceptions.h"
#include "BinTool.h"

namespace processorEmulator {

    Starter::Starter(const std::string& programPath, const std::string& objectRegex) {
        _programPath = programPath;
        _objectRegex = objectRegex;
    }

    void Starter::run() {
        auto parser = CommandParser::LineParser(_programPath, _objectRegex);
        parser.parse();
        auto commands = parser.getCommands();
        auto labels = parser.getLabels();
        Processor processor{commands, labels};
        processor.execute();
    }

    void Starter::runBinary() {
        BinTool::DeserializerResponse response = BinTool::Serializer::deserialize(_programPath);
        Processor processor{response.commands, response.labels};
        processor.execute();
    }

}