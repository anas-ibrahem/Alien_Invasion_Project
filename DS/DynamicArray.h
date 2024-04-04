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
    int count;

public:
    DynamicArray() {
        capacity = 1000;
        count = 0;
        array = new T[capacity];
    }
    bool insert(T element)
    {
        if (count == capacity)
            return false;
        array[count++] = element;
        return true;
    }

    bool remove(int index)
    {
        if (index < 0 || index >= count)
        {
            return false;
        }
        array[index] = array[--count];
        return true;
    }
    T Pick() {
        if (isEmpty()) {
            return NULL;
        }
        srand(time(0)); // Seed for random number generator
        int randomIndex = rand() % count; // Generate random index
        return array[randomIndex];
    }
    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }
    void display() {
        std::cout << "[ ";
        for (int i = 0; i < count; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << "]" << std::endl;
    }
    int search(T element) {
        for (int i = 0; i < count; ++i) {
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
