#include <fstream>

#include "Starter.h"
#include "ProcessorEmulator.h"
#include "CommandParser.h"
#include "Exceptions.h"
#include "BinTool.h"

namespace processorEmulator {

    Starter::Starter(const std::string& programPath, const std::string& objectRegex) {
        _programPath = programPath;
        _objectRegex = objectRegex;
    }

    void Starter::run() {
        try{
            auto parser = CommandParser::LineParser(_programPath, _objectRegex);
            parser.parse();
            auto commands = parser.getCommands();
            auto labels = parser.getLabels();
            Processor processor{commands, labels};
            processor.execute();
        }
        catch (CommandParser::ParserException& e){
            std::cout << e.what() << std::endl;
        }
        catch (StackException& e){
            std::cout << e.what() << std::endl;
        }
    }

    void Starter::runBinary() {
        try{
            std::map<char, std::function<std::shared_ptr<Commands::BaseCommand>()>> codeMap;
            for (const auto& commandGenerator: CommandParser::LineParser::_generatorVector){
                codeMap[static_cast<char>(commandGenerator()->getCode())] = commandGenerator;
            }

            std::ifstream reader(_programPath, std::ios::binary);
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

            Processor processor{commands, labels};
            processor.execute();

            reader.close();
        }
        catch (CommandParser::ParserException& e){
            std::cout << e.what() << std::endl;
        }
        catch (BinTool::BinToolException& e){
            std::cout << e.what() << std::endl;
        }
    }

}