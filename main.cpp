#include <iostream>

#include <Starter.h>
#include <BinTool.h>

using namespace processorEmulator;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No path" << std::endl;
        return 1;
    }
    else if (argc == 2){
        Starter starter{argv[1]};
        starter.run();
    }
    else if (argc == 3){
        std::string flag = argv[1];

        if (flag == "-s")
            BinTool::Serializer::serialize(argv[2]);

        else if (flag == "-b")
        {
            Starter starter{argv[2]};
            starter.runBinary();
        }

    }
    return 0;
}
