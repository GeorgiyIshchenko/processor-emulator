#ifndef PROCESSOREMULATOR_EXCEPTIONS_H
#define PROCESSOREMULATOR_EXCEPTIONS_H

#include <string>

namespace processorEmulator {

    namespace CommandParser {

        struct ParserException : public std::exception {

            explicit ParserException(const char *message, int line = 0) : message(message), line(line) {};

            [[nodiscard]] const char *what() const noexcept override {
                return (new std::string("Exception while Parsing: line " + std::to_string(line) + ". " + message))->c_str();
            }

        private:

            const char *message;
            int line;

        };

    }

    namespace Commands {

        //TODO: Commands Exceptions

    }

}

#endif
