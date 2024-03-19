#include <fstream>
#include <memory>

#include "BinTool.h"
#include "CommandParser.h"
#include "Exceptions.h"

namespace processorEmulator::BinTool {

    void Serializer::serialize(const std::string &programPath, const std::string& objectRegex) {
        try{
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
        catch (CommandParser::ParserException& e){
            std::cout << e.what() << std::endl;
        }
        catch (BinToolException& e){
            std::cout << e.what() << std::endl;
        }
    }

}