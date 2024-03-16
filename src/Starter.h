#ifndef PROCESSOREMULATOR_STARTER_H
#define PROCESSOREMULATOR_STARTER_H

#include <string>
#include <vector>

namespace processorEmulator {

    class Starter final {

    public:

        explicit Starter(std::string programPath, std::string objectRegex = "([+-]?[1-9]*[0-9]*)");

        void doit();

    private:

        std::string _programPath;
        std::string _objectRegex;

    };
}

#endif
