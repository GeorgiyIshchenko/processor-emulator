#include <gtest/gtest.h>
#include <vector>

#include <Starter.h>

using namespace processorEmulator;

TEST(Operation, Emul){
    Starter starter{"../tests/test_program"};
    starter.doit();
}

TEST(Operation, Fibonachi){
    Starter starter{"../tests/fibonachi"};
    starter.doit();
}

