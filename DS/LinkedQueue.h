#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_


#include "Node.h"
#include "QueueADT.h"
#include "../ArmiesHeaders/unit.h"

template <typename T>
class LinkedQueue:public QueueADT<T>
{
private :
	int count;
	Node<T>* backPtr;
	Node<T>* frontPtr;
public :
	LinkedQueue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);  
	bool peek(T& frntEntry)  const;	
	int getCount() const;
	~LinkedQueue();

	bool print() const; // Specialized for unit* type // returns false if empty

};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;
	count = 0;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr==nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue( const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	count++;
	return true ;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;


	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr ;	
		
	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

template <typename T>
bool LinkedQueue<T>:: peek(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template<typename T>
inline int LinkedQueue<T>::getCount() const
{
	return count;
}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	//Note that the cout statements here is just for learning purpose
	//They should be normally removed from the destructor
	//cout<<"\nStarting LinkedQueue destructor...";
	//cout<<"\nFreeing all nodes in the queue...";

	//Free all nodes in the queue
	T temp;
	while(dequeue(temp));
	
	//cout<<"\n Is LinkedQueue Empty now?? ==> "<<boolalpha<<isEmpty();
	//cout<<"\nEnding LinkedQueue destructor..."<<endl;
}


template<>
inline bool LinkedQueue<unit*>::print() const
{
	if (isEmpty())
	{
		return false;
	}
	Node<unit*>* ptr = frontPtr;
	cout << "[ ";
	while (ptr)
	{
		if (ptr->getItem()->GetType() == unit::ES && ptr->getItem()->isInfected())
			cout << ptr->getItem()->getID() << "* ";
		else 
			cout << ptr->getItem()->getID() << " ";


		ptr = ptr->getNext();
		if (!ptr) cout << "]"; // Last Element
		else cout << ", "; // Not Last Element
	}

	return true;

}





template <>
inline LinkedQueue<unit*>::~LinkedQueue()
{

	//Delete All units
	unit* temp;
	while (dequeue(temp))
	delete  temp;

}



#endif