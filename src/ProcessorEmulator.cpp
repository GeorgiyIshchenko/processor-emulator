#include <memory>
#include <utility>

#include "ProcessorEmulator.h"
#include "Commands.h"
#include "CommandParser.h"


namespace processorEmulator {

    Processor &processorEmulator::Processor::instance() {
        static Processor instance;
        return instance;
    }

    void Processor::execute(std::string programPath) {
        CommandParser::LineParser parser{std::move(programPath)};
        auto commands = parser.getCommandVector();
        for (const auto& command: commands) {
            command->execute();
        }
    }
}



