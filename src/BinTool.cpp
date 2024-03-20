#include <fstream>

#include "BinTool.h"
#include "CommandParser.h"
#include "Exceptions.h"

namespace processorEmulator::BinTool {

    void Serializer::serialize(const std::string &programPath, const std::string& objectRegex) {
        auto parser = CommandParser::LineParser(programPath, objectRegex);
        parser.parse();
        auto commands = parser.getCommands();
        auto labelMap = parser.getLabels();

        std::string outputName = programPath + ".bin";
        std::ofstream writer(outputName, std::ios::binary);
        if (!writer.is_open())
            throw BinToolException("Bad Path");

        size_t commandSize = commands.size();
        writer.write(reinterpret_cast<char*>(&commandSize), sizeof(commandSize));
        for (const auto& command: commands){
            CommandData data = {.code = static_cast<char>(command->getCode()), .arg = command->getArgument()};
            writer.write(reinterpret_cast<char*>(&data), sizeof(data));
        }

        size_t labelSize = labelMap.size();
        writer.write(reinterpret_cast<char*>(&labelSize), sizeof(labelSize));
        for (const auto& label: labelMap){
            LabelData data = {.hash = label.first, .label = label.second};
            writer.write(reinterpret_cast<char*>(&data), sizeof(data));
        }

        writer.close();
    }

    DeserializerResponse Serializer::deserialize(const std::string &programPath) {
        std::map<char, std::function<std::shared_ptr<Commands::BaseCommand>()>> codeMap;
        for (const auto& commandGenerator: CommandParser::LineParser::_generatorVector){
            codeMap[static_cast<char>(commandGenerator()->getCode())] = commandGenerator;
        }

        std::ifstream reader(programPath, std::ios::binary);
        if (!reader.is_open())
            throw BinTool::BinToolException("Bad Path");

        size_t commandSize;
        reader.read(reinterpret_cast<char*>(&commandSize), sizeof(commandSize));
        std::vector<std::shared_ptr<Commands::BaseCommand>> commands = {};
        BinTool::CommandData commandData{};
        for(int i = 0; i < commandSize; i++){
            reader.read(reinterpret_cast<char*>(&commandData), sizeof(commandData));
            auto command = codeMap[commandData.code]();
            command->setArg(commandData.arg);
            commands.push_back(command);
        }

        size_t labelSize;
        reader.read(reinterpret_cast<char*>(&labelSize), sizeof(labelSize));
        std::map<size_t, size_t> labels = {};
        BinTool::LabelData labelData{};
        for(int i = 0; i < labelSize; i++){
            reader.read(reinterpret_cast<char*>(&labelData), sizeof(labelData));
            labels[labelData.hash] = labelData.label;
        }

        reader.close();
        return DeserializerResponse{.commands = commands, .labels = labels};
    }

}