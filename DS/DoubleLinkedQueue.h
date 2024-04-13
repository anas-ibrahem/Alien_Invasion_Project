#ifndef DBL_LINKED_QUEUE_
#define DBL_LINKED_QUEUE_


#include "DoubleNode.h"
#include "QueueADT.h"
#include "unit.h"

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
	return (frontPtr == nullptr);
}



template <typename T>
bool DoubleLinkedQueue<T>::enqueue(const T& newEntry)
{
	count++;
	DoubleNode<T>* newNodePtr = new DoubleNode<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue



template <typename T>
bool DoubleLinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	DoubleNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;
}




template <typename T>
bool DoubleLinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

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
	while (dequeue(temp));

	cout << "\n Is DoubleLinkedQueue Empty now?? ==> " << boolalpha << isEmpty();
	cout << "\nEnding DoubleLinkedQueue destructor..." << endl;
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

	if (nodeToDeletePtr == frontPtr)	 // Special case: last node in the queue
		frontPtr = nullptr;

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
	while (dequeue(temp))
	delete  temp;

}




#endif