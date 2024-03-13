#include <gtest/gtest.h>
#include <vector>

#include <ProcessorEmulator.h>
#include <CommandParser.h>
#include <Commands.h>

using namespace processorEmulator;

TEST(Operation, Parsing){
    try {
        std::vector<std::shared_ptr<Commands::BaseCommand>> commands;
        CommandParser::LineParser parser{"../tests/test_program"};
        commands = parser.getCommandVector();
    }
    catch (CommandParser::ParserException& e){
        std::cout << e.what() << std::endl;
    }
}

TEST(Operation, Emul){
    try {
        Processor::instance().execute("../tests/test_program");
    }
    catch (CommandParser::ParserException& e){
        std::cout << e.what() << std::endl;
    }
}

TEST(Operation, Fibonachi){
    try {
        Processor::instance().execute("../tests/fibonachi");
    }
    catch (CommandParser::ParserException& e){
        std::cout << e.what() << std::endl;
    }
}

