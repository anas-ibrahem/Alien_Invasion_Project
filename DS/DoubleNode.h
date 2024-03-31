#pragma once

#include <iostream>
using namespace std;
template <typename T>
class DoubleNode
{
private:
	T item; // A data item
	DoubleNode<T>* nextNodePtr<T>* next; // Pointer to next node
	DoubleNode<T>* nextNodePtr<T>* prev; // Pointer to Previous node

public :
	DoubleNode();
	DoubleNode(const T & r_Item);
	DoubleNode(const T & r_Item, DoubleNode<T>* nextNodePtr , DoubleNode<T>* prevNodePtr);
	void setItem(const T & r_Item);
	void setNext(DoubleNode<T>* nextNodePtr);
	void setPrev(DoubleNode<T>* prevNodePtr);

	T getItem() const ;
	DoubleNode<T>* getNext() const ;
	DoubleNode<T>* getPrev() const;

}; // end Node


template < typename T>
DoubleNode<T>::DoubleNode()
{
	next = nullptr;
	prev = nullptr;
} 

template < typename T>
DoubleNode<T>::DoubleNode( const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	prev = nullptr;
} 

template < typename T>
DoubleNode<T>::DoubleNode( const T& r_Item, DoubleNode<T>* nextNodePtr , DoubleNode<T>* prevNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	prev = prevNodePtr;
}





template < typename T>
void DoubleNode<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void DoubleNode<T>::setNext(DoubleNode<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
void DoubleNode<T>::setPrev(DoubleNode<T>* prevNodePtr)
{
	prev = prevNodePtr;
}


template < typename T>
T DoubleNode<T>::getItem() const
{
	return item;
} 

template < typename T>
DoubleNode<T>* DoubleNode<T>::getNext() const
{
	return next;
} 

template < typename T>
DoubleNode<T>* DoubleNode<T>::getPrev() const
{
	return prev;
}