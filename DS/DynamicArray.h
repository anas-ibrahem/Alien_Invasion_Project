#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T>
class DynamicArray
{
private:
    T* array;
    int capacity;
    int size;

public:
    DynamicArray() {
        capacity = 1000;
        size = 0;
        array = new T[capacity];
    }
    bool insert(T element)
    {
        if (size == capacity)
            return false;
        array[size++] = element;
        return true;
    }

    bool remove(int index)
    {
        if (index < 0 || index >= size)
        {
            return false;
        }
        array[index] = array[--size];
        return true;
    }
    T Pick() {
        if (isEmpty()) {
            return NULL;
        }
        srand(time(0)); // Seed for random number generator
        int randomIndex = rand() % size; // Generate random index
        return array[randomIndex];
    }
    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }
    void display() {
        std::cout << "[ ";
        for (int i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << "]" << std::endl;
    }
    int search(T element) {
        for (int i = 0; i < size; ++i) {
            if (array[i] == element) {
                return i; // Return index if element is found
            }
        }
        return -1; // Return -1 if element is not found
    }
    ~DynamicArray() {
        delete[] array;
    }
};
