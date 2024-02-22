#ifndef PROCESSOREMULATOR_COMMANDPARSER_H
#define PROCESSOREMULATOR_COMMANDPARSER_H

namespace processorEmulator {

    enum class Commands {
        BEGIN, END,
        PUSH, POP,
        PUSHR, POPR,
        ADD, SUB, MUL, DIV,
        OUT, IN
    };

}

#endif
