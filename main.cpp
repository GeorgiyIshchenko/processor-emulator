#include <iostream>

#include <Starter.h>

using namespace processorEmulator;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No path" << std::endl;
        return 1;
    }
    Starter starter{argv[1]};
    starter.doit();
    return 0;
}
