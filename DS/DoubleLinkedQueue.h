#ifndef DBL_LINKED_QUEUE_
#define DBL_LINKED_QUEUE_


#include "DoubleNode.h"
#include "QueueADT.h"
#include "../ArmiesHeaders/unit.h"

template <typename T>
class DoubleLinkedQueue :public QueueADT<T>
{
private:
	int count;
	DoubleNode<T>* backPtr;
	DoubleNode<T>* frontPtr;
public:
	DoubleLinkedQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	int getCount() const;
	~DoubleLinkedQueue();
	
	// Added Functions of Double 

	bool enqueue_front(const T& newEntry);
	bool dequeue_front(T& frntEntry);
	bool peek_front(T& frntEntry)  const;

	bool enqueue_rear(const T& newEntry);
	bool dequeue_rear(T& rearEntry);
	bool peek_rear(T& rearEntry)  const;

	bool print() const; // Specialized for unit* type // returns false if empty

};


template <typename T>
DoubleLinkedQueue<T>::DoubleLinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;

}



template <typename T>
bool DoubleLinkedQueue<T>::isEmpty() const
{
	return (count == 0);
}





template <typename T>
bool DoubleLinkedQueue<T>::enqueue_rear(const T& newEntry) // enqueue from back
{
	DoubleNode<T>* newNodePtr = new DoubleNode<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
	{
		frontPtr = newNodePtr;
	}// The queue is empty
	else
	{
		newNodePtr->setPrev(backPtr);
		backPtr->setNext(newNodePtr); // The queue was not empty
	}
	backPtr = newNodePtr; // New node is the last node now
	count++;
	return true;
} // end enqueue



template <typename T> // enqueue front
bool DoubleLinkedQueue<T>::enqueue_front(const T& newEntry)
{
	DoubleNode<T>* newNodePtr = new DoubleNode<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
	{
		backPtr = newNodePtr;
	}// The queue is empty
	else
	{
		newNodePtr->setNext(frontPtr);
		frontPtr->setPrev(newNodePtr); // The queue was not empty
	}
	frontPtr = newNodePtr; // New node is the last node now
	count++;
	return true;
} // end enqueue




template <typename T>
bool DoubleLinkedQueue<T>::dequeue_front(T& frntEntry)
{
	if (isEmpty())
		return false;

	DoubleNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();

	// Queue is not empty; remove front
	if (count == 1)	 // Special case: last node in the queue
		backPtr = nullptr;
	else
		frontPtr->setPrev(nullptr);

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;
}


// Dequeue From Rear //
template<typename T>
bool DoubleLinkedQueue<T>::dequeue_rear(T& rearEntry)
{


	if (isEmpty())
		return false;

	DoubleNode<T>* nodeToDeletePtr = backPtr;
	rearEntry = backPtr->getItem();
	backPtr = backPtr->getPrev();

	if (count == 1)	 // Special case: last node in the queue
		frontPtr = nullptr;
	else
		backPtr->setNext(nullptr);


	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;


}

template<typename T>
bool DoubleLinkedQueue<T>::peek_rear(T& rearEntry) const
{
	if (isEmpty())
		return false;

	rearEntry = backPtr->getItem();
	return true;
}


template <typename T>
bool DoubleLinkedQueue<T>::peek_front(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}


template<typename T>
bool DoubleLinkedQueue<T>::enqueue(const T& newEntry)
{
	return enqueue_rear(newEntry);
}

template<typename T>
bool DoubleLinkedQueue<T>::dequeue(T& frntEntry)
{
	return dequeue_front(frntEntry);
}

template<typename T>
bool DoubleLinkedQueue<T>::peek(T& frntEntry) const
{
	return peek_front(frntEntry);
}

template<typename T>
inline int DoubleLinkedQueue<T>::getCount() const
{
	return count;
}



template <typename T>
DoubleLinkedQueue<T>::~DoubleLinkedQueue()
{
	//Note that the cout statements here is just for learning purpose
	//They should be normally removed from the destructor
	cout << "\nStarting DoubleLinkedQueue destructor...";
	cout << "\nFreeing all nodes in the queue...";

	//Free all nodes in the queue
	T temp;
	while (dequeue_rear(temp));

	cout << "\n Is DoubleLinkedQueue Empty now?? ==> " << boolalpha << isEmpty();
	cout << "\nEnding DoubleLinkedQueue destructor..." << endl;
}








template<>
inline bool DoubleLinkedQueue<unit*>::print() const
{
	if (isEmpty())
	{
		return false;
	}
	DoubleNode<unit*>* ptr = frontPtr;
	cout << "[ ";
	while (ptr)
	{
		cout << ptr->getItem()->getID() << " ";
		ptr = ptr->getNext();
		if (!ptr) cout << "]"; // Last Element
		else cout << ", "; // Not Last Element
	}

	return true;

}


template <>
inline DoubleLinkedQueue<unit*>::~DoubleLinkedQueue()
{

	//Delete All units
	unit* temp;
	while (dequeue_rear(temp))
	delete  temp;

}




#endif