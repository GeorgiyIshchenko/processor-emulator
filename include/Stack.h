#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cstdint>
#include <utility>

template<class T>
class Stack {

private:
    size_t size;
    size_t top;
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
        std::copy(other.array, other.array + other.size - 1, array);
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

    Stack &operator=(Stack &&other) noexcept
    {
        this->swap(other);
        return *this;
    }

    void swap(Stack &&other)
    {
        std::swap(size, other.size);
        std::swap(top, other.top);
        std::swap(array, other);
    }

    [[nodiscard]] bool isEmpty() const { return top < 0; }

    [[nodiscard]] int32_t getSize() const { return top; }

    void pushBack(T&& object) {
        if (top + 1 == size) {
            T *resizedArray = new T[size * 2];
            for (size_t i = 0; i < size; i++) {
                resizedArray[i] = array[i];
            }
            delete array;
            array = resizedArray;
            size *= 2;
        }
        array[++top] = std::forward<T>(object);
    }

    T getTop() {
        if (this->isEmpty())
            throw std::exception();
        return array[top];
    }

    T pop() {
        if (this->isEmpty())
            throw std::exception();
        return array[top--];
    }


};


#endif