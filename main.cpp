#include <iostream>

#include <ProcessorEmulator.h>
#include <CommandParser.h>

using namespace processorEmulator;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No path" << std::endl;
        return 1;
    }
    try {
        Processor::instance().execute(argv[1]);
    }
    catch (CommandParser::ParserException &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
