#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <cstdint>
#include <utility>
#include <exception>

namespace processorEmulator {
    struct StackException : public std::exception {

        explicit StackException(const char *message) : message(message) {};

        [[nodiscard]] const char *what() const noexcept override {
            return message;
        }

    private:

        const char *message;

    };


    template<class T>
    class Stack {

        using sizeType = size_t;

    private:
        static constexpr sizeType defaultCapacity{16};

        sizeType capacity{defaultCapacity};
        sizeType size{0};
        T *array;

    public:


        Stack() {
            capacity = defaultCapacity;
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
            swap(*this, other);
        }

        Stack &operator=(const Stack &other) noexcept {
            *this = Stack(other);
            return *this;
        }

        Stack &operator=(Stack &&other) noexcept {
            swap(*this, other);
            return *this;
        }


        ~Stack() {
            delete[] array;
        }


    public:

        [[nodiscard]] bool isEmpty() const { return size == 0; }

        [[nodiscard]] int32_t getSize() const { return size; }

        T getTop() {
            if (this->isEmpty())
                throw StackException("getTop() from empty stack");
            return array[size - 1];
        }

    public:

        void push(T &&object) {
            if (size + 1 == capacity)
                increaseCapacity();
            array[size++] = object;
        }

        void push(const T &object) {
            T copy{object};
            push(std::move(copy));
        }

        T pop() {
            if (this->isEmpty())
                throw StackException("pop() from empty stack");
            size--;
            return array[size];
        }

        size_t getSize(){
            return size;
        }

    private:

        friend void swap(Stack &s1, Stack &s2) noexcept {
            std::swap(s1.size, s2.size);
            std::swap(s1.capacity, s2.capacity);
            std::swap(s1.array, s2.array);
        }

        void increaseCapacity() {
            T *resizedArray = new T[capacity * 2];
            for (sizeType i = 0; i < capacity; i++) {
                resizedArray[i] = array[i];
            }
            delete[] array;
            array = resizedArray;
            capacity *= 2;
        }

    };

}


#endif