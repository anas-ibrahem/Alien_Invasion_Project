#pragma once
#include "priNode.h"
#include "../ArmiesHeaders/unit.h"

//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
    priNode<T>* head;
    int count;

public:
    priQueue() : head(nullptr) { count = 0; }

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp,p));
    }

    //insert the new node in its correct position according to its priority
    bool enqueue(const T& data, int priority) {
        count++;
        priNode<T>* newNode = new priNode<T>(data, priority);
        if (head == nullptr || priority > head->getPri()) {
            
            newNode->setNext(head);
            head = newNode;
            return true;
        }
       
        priNode<T>* current = head;        
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext( current->getNext());
        current->setNext( newNode);   
        return true;
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        count--;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int getCount() {
        return count;
    }

    bool print()const;//Unit 
    
};


template<>
inline bool priQueue<unit*>::print()const {
    if (isEmpty())
    {
        return false;
    }
    priNode<unit*>* ptr = head;
    cout << "[ ";
    while (ptr)
    {
        int pri;
        if (ptr->getItem(pri)->GetType() == unit::ES && ptr->getItem(pri)->isInfected())
            cout << ptr->getItem(pri)->getID() << "* ";
        else
            cout << ptr->getItem(pri)->getID() << " ";

        ptr = ptr->getNext();
        if (!ptr) cout << "]"; // Last Element
        else cout << ", "; // Not Last Element
    }

    return true;
}





template <>
inline priQueue<unit*>::~priQueue()
{

    //Delete All units
    unit* temp; int p;
    while (dequeue(temp,p))
     delete  temp;

}