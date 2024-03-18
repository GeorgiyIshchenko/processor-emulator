#include <gtest/gtest.h>
#include <vector>

#include <Starter.h>


TEST(Operation, Test){
    auto path = "../tests/test_program";
    processorEmulator::Starter starter{path, "([+-]?[1-9]*[0-9]*)"};
    starter.doit();
}

TEST(Operation, Fibonachi){
    auto path = "../tests/fibonachi";
    processorEmulator::Starter starter{path};
    starter.doit();
}

TEST(Operation, Factorial){
    auto path = "../tests/factorial";
    processorEmulator::Starter starter{path};
    starter.doit();
}

