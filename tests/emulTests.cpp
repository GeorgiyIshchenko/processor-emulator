#include <gtest/gtest.h>
#include <vector>

#include <ProcessorEmulator.h>
#include <CommandParser.h>
#include <Commands.h>

using namespace processorEmulator;

TEST(Operation, Parsing){
    try {
        std::vector<Commands::BaseCommand> commands;
        CommandParser::LineParser parser{"/home/gosha/CLionProjects/ProcessorEmulator/tests/test_program"};
        commands = parser.getCommandVector();
    }
    catch (CommandParser::ParserException& e){
        std::cout << e.what() << std::endl;
    }
}