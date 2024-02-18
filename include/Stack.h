#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cstdint>
#include <utility>

template<class T>
class Stack {

private:
    int32_t size;
    int32_t top;
    T *array;

public:

    Stack() {
        size = 1;
        top = -1;
        array = new T[size];
    }

    ~Stack() {
        delete array;
    }

    Stack(const Stack &other) {
        size = other.size;
        top = other.top;
        array = new T;
        for (int32_t i = 0; i < size; i++)
            array[i] = other.array[i];
    }

    Stack(Stack &&other) noexcept {
        size = other.size;
        top = other.top;
        array = std::exchange(other.array, nullptr);
    }

    Stack &operator=(const Stack &other) {
        *this = Stack(other);
        return *this;
    }

    bool is_empty() { return top < 0; }

    int32_t get_size() { return size; }

    void pushBack(T &&object) {
        if (top == size) {
            T *resizedArray = new T[size * 2];
            for (int32_t i = 0; i < size; i++) {
                resizedArray[i] = array[i];
            }
            delete array;
            array = resizedArray;
            size *= 2;
        }
        array[++top] = object;
    }

    T get_top() {
        if (this->is_empty())
            throw std::exception();
        return array[top];
    }

    T pop() {
        if (this->is_empty())
            throw std::exception();
        return array[top--];
    }


};


#endif