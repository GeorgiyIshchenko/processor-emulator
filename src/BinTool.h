#ifndef PROCESSOREMULATOR_BINTOOL_H
#define PROCESSOREMULATOR_BINTOOL_H

#include <string>
#include <map>
#include <functional>
#include <memory>

#include "Starter.h"
#include "Commands.h"

namespace processorEmulator::BinTool {


    struct CommandData {
        char code;
        size_t arg;
    };

    struct LabelData {
        size_t hash;
        size_t label;
    };

    struct DeserializerResponse {
        std::vector<std::shared_ptr<Commands::BaseCommand>> commands = {};
        std::map<size_t, size_t> labels = {};
    };

    class Serializer {

    public:

        static void serialize(const std::string& programPath, const std::string& objectRegex = "([+-]?[1-9]*[0-9]*)");

        static DeserializerResponse deserialize(const std::string& programPath);

    };

}

#endif
