#include <gtest/gtest.h>
#include <Stack.h>

using namespace processorEmulator;

TEST(Operation, Base) {
    Stack<int> stack{};
    stack.push(1);
    stack.push(2);
    stack.push(3);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.pop(), 2);
    stack.push(4);
    EXPECT_EQ(stack.pop(), 4);
    EXPECT_EQ(stack.pop(), 1);
    EXPECT_ANY_THROW(stack.pop());
}

struct Person {
    uint64_t id;
    const char *name;
};

TEST(Operation, CustomType) {
    Stack<Person> stack{};
    Person p1{.id = 0, .name = "Gosha"};
    stack.push(p1);
    EXPECT_EQ(stack.getTop().id, 0);
    EXPECT_STREQ(stack.getTop().name, "Gosha");
    stack.push({.id = 1, .name = "Misha"});
    stack.push({.id = 2, .name = "Grisha"});
    EXPECT_EQ(stack.getSize(), 3);
}

TEST(Operation, RuleOfFive) {
    Stack<uint32_t> st{};
    st.push(1);
    Stack<uint32_t> copy{st};
    EXPECT_EQ(copy.getTop(), 1);
    Stack<uint32_t> &&rvalue = Stack<uint32_t>{};
    rvalue.push(1);
    rvalue.push(2);
    Stack<uint32_t> rvalueCopy{rvalue};
    EXPECT_EQ(rvalueCopy.pop(), 2);
    EXPECT_EQ(rvalue.pop(), 2);
}

TEST(Operation, PopEmpty){
    Stack<std::vector<int>> stack{};
    try{
        stack.pop();
    }
    catch(const StackException &e){
        EXPECT_EQ(e.what(), "pop() from empty stack");
    }
}
