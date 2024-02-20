#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cstdint>
#include <utility>

template<class T>
class Stack {

private:
    int32_t capacity;
    int32_t size;
    T *array;

public:
    

    Stack() {
        capacity = 10;
        size = 0;
        array = new T[capacity];
    }

    Stack(const Stack &other) {
        capacity = other.capacity;
        size = other.size;
        array = new T[other.capacity];
        std::copy(other.array, other.array + other.capacity - 1, array);
    }

    Stack(Stack &&other) noexcept {
        capacity = other.capacity;
        size = other.size;
        array = std::move(other);
    }

    Stack &operator=(const Stack &other) noexcept {
        *this = Stack(other);
        return *this;
    }

    Stack &operator=(Stack &&other) noexcept {
        *this = Stack(other);
        return *this;
    }

    ~Stack() {
        capacity = 0;
        size = 0;
        delete[] array;
        array = nullptr;
    }


    [[nodiscard]] bool isEmpty() const { return size == 0; }

    [[nodiscard]] int32_t getSize() const { return size; }

    void push(const T &object) {
        if (size + 1 == capacity) {
            T *resizedArray = new T[capacity * 2];
            for (int32_t i = 0; i < capacity; i++) {
                resizedArray[i] = array[i];
            }
            std::free(array);
            array = resizedArray;
            capacity *= 2;
        }
        size++;
        array[size - 1] = object;
    }

    void push(T &&object) {
        T temp = std::move(object);
        this->push(temp);
    }

    T getTop() {
        if (this->isEmpty())
            throw std::exception();
        return array[size - 1];
    }

    T pop() {
        if (this->isEmpty())
            throw std::exception();
        size--;
        return array[size];
    }


};


#endif