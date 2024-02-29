#include <vector>
#include <string>

#include <sstream>
#include <fstream>

#include <Commands.h>

namespace processorEmulator::CommandParser {

    std::vector<BaseCommand> getCommandVector(const char* pathToExe){
        std::ifstream input(pathToExe);
        std::vector<BaseCommand> result;

        std::string line;
        while(std::getline(input, line)){

        }

        return result;
    }


}