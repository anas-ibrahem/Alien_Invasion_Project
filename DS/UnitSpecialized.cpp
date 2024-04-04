#include"../Game/Game.h"


template<>
bool DoubleLinkedQueue<unit*>::print() const
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

template<>
bool LinkedQueue<unit*>::print() const
{
	if (isEmpty())
	{
		return false;
	}
	Node<unit*>* ptr = frontPtr;
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
template<>
bool DynamicArray<unit*>::print() const
{
	if (count==0)
		return false;
	cout << "[ ";
	for (int i = 0; i < count; i++)
	{
		cout << array[i]->getID() << " ";
		if (i==count-1) cout << "]"; // Last Element
		else cout << ", "; // Not Last Element
	}
}

template<>
bool ArrayStack<unit*>::print()const
{
	if (isEmpty())
		return false;
	cout << "[ ";
	for (int i = 0; i < top + 1; i++) {
		cout << items[i]->getID() << " ";
		if (i != top)cout << ", ";
		else
			cout << "]";
	}
	return true;
}

template<>
bool priQueue<unit*>::print()const {
	if (isEmpty())
	{
		return false;
	}
	priNode<unit*>* ptr = head;
	cout << "[ ";
	while (ptr)
	{
		int pri;
		cout << ptr->getItem(pri)->getID() << " ";
		ptr = ptr->getNext();
		if (!ptr) cout << "]"; // Last Element
		else cout << ", "; // Not Last Element
	}

	return true;
}