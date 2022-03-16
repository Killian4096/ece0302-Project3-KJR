//  Adapated from Frank M. Carrano and Timothy M. Henry.


/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

// TODO: Implement the constructor here
template<class ItemType>
Stack<ItemType>::Stack() 
{
	currentSize=0;
	headPtr = nullptr;
}  // end default constructor

// TODO: Implement the destructor here
template<class ItemType>
Stack<ItemType>::~Stack()
{
}  // end destructor

// TODO: Implement the isEmpty method here
template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	return currentSize==0;
}  // end isEmpty

// TODO: Implement the size method here
template<class ItemType>
int Stack<ItemType>::size() const
{
	return currentSize;
}  // end size

// TODO: Implement the push method here
template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	currentSize++;
	Node<ItemType> *addNode = new Node<ItemType>();
	addNode->setItem(newItem);
	addNode->setNext(headPtr);
	headPtr = addNode;
	return true;
}  // end push

// TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const throw(logic_error)
{
	if(isEmpty()){return NULL;}
	ItemType returnItem = headPtr->getItem();
	return returnItem;
}  // end peek

// TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	if(isEmpty()){return false;}
	currentSize--;
	Node<ItemType> *delNode = headPtr;
	headPtr = headPtr->getNext();
	return true;
}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
	while(currentSize!=0){
		pop();
	}
}  // end clear

