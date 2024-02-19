#include <gtest/gtest.h>
#include <Stack.h>

TEST(Operation, Base)
{
    Stack<int> stack{};
    stack.pushBack(1);
    stack.pushBack(2);
    stack.pushBack(3);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.pop(), 2);
    stack.pushBack(4);
    EXPECT_EQ(stack.pop(), 4);
    EXPECT_EQ(stack.pop(), 1);
    EXPECT_ANY_THROW(stack.pop());
}

struct Person{
    uint64_t id;
    const char* name;
};

TEST(Operation, CustomType)
{
    /*Stack<Person> stack{};
    Person p1{.id = 0, .name = "Gosha"};
    stack.pushBack(p1);
    EXPECT_EQ(stack.getTop().id, 0);
    EXPECT_STREQ(stack.getTop().name, "Gosha");
    stack.pushBack({.id = 1, .name = "Misha"});
    stack.pushBack({.id = 2, .name = "Grisha"});
    EXPECT_EQ(stack.getSize(), 3);*/
}