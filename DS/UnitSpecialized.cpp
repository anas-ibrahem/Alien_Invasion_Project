#include"../Game/Game.h"


template<>
bool DoubleLinkedQueue<unit*>::print() const
{
	if (isEmpty())
	{
		return false;
	}
	DoubleNode<unit*>* ptr = frontPtr;
	cout << "[";
	while (ptr)
	{
		cout << ptr->getItem()->getID() << " ";
		ptr = ptr->getNext();
		if (!ptr) cout << "]"; // Last Element
		else cout << ","; // Not Last Element
	}

	return true;

}

template<>
bool LinkedQueue<unit*>::print() const
{
	if (isEmpty())
	{
		return false;
	}
	Node<unit*>* ptr = frontPtr;
	cout << "[";
	while (ptr)
	{
		cout << ptr->getItem()->getID() << " ";
		ptr = ptr->getNext();
		if (!ptr) cout << "]"; // Last Element
		else cout << ","; // Not Last Element
	}

	return true;

}