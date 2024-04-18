#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../ArmiesHeaders/unit.h"

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


    T remove(int index)
    {
        if (index < 0 || index >= count)
        {
            return 0;
        }

        T temp = array[index];
        array[index] = array[--count];
        return temp;
    }



    int getCount() const {
        return count;
    }


    ~DynamicArray() {
        delete[] array;
    }


    bool print() const; // Specialized for unit* type // returns false if empty



    T PickRand() {
        if (isEmpty()) {
            return nullptr ;
        }
        int randomIndex = rand() % count; // Generate random index
        return remove(randomIndex) ;
    }



};





template<>
inline bool DynamicArray<unit*>::print() const
{
    if (count == 0)
        return false;
    cout << "[ ";
    for (int i = 0; i < count; i++)
    {
        cout << array[i]->getID() << " ";
        if (i == count - 1) cout << "]"; // Last Element
        else cout << ", "; // Not Last Element
    }
    return true;
}

template <>
inline DynamicArray<unit*>::~DynamicArray()
{

    //Delete All units

    for (int i = 0; i < count; i++)
    {
        delete array[i];
    }

    delete []array;

}