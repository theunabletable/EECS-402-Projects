#ifndef _LIFOSTACKCLASS_INL
#define _LIFOSTACKCLASS_INL

#include <iostream>
#include "LinkedNodeClass.h"
#include "LIFOStackClass.h"

/*
Andrew Jones
November 16th, 2024
This class encompasses a last-in-first-out stack of LinkedNodeClass objects.
*/

using namespace std;

//default constructor creates an empty stack.
template < class T >
LIFOStackClass< T >::LIFOStackClass()
{
  head = NULL;
  tail = NULL;
}

//destructor clears out any dynamic memory associated with this stack.
template < class T >
LIFOStackClass< T >::~LIFOStackClass()
{
  clear();
}

//clear() traverses the queue and deletes all nodes in the stack
template < class T >
void LIFOStackClass< T >::clear()
{
  //temp is a pointer that traverses the list
  LinkedNodeClass< T >* temp = head;
  if (temp != NULL)
  {
    //check if we are at the end of a nonempty stack
    while (temp->getNext() != NULL)
    {
      temp = temp->getNext();
      delete temp->getPrev();
    }
    delete temp;
  }
  head = NULL;
  tail = NULL;
}

//pushes newItem to the top of the stack, at the tail.
template < class T >
void LIFOStackClass< T >::push(
  const T &newItem
  )
{
  //if list is currently empty
  if (head == NULL)
  {
    LinkedNodeClass< T >* newNode = new LinkedNodeClass(NULL, newItem, NULL);
    head = newNode;
    tail = newNode;
  }
  //if the list is nonempty, put new node at tail
  else
  {
    LinkedNodeClass< T >* newNode = new LinkedNodeClass(tail, newItem, NULL);
    newNode->setBeforeAndAfterPointers();
    tail = newNode;
  }
}

//pops the next item off the stack's tail, setting outItem to its value.
//returns true if successful, returns false if the stack is empty.
template < class T >
bool LIFOStackClass< T >::pop(
  T &outItem
  )
{
  //if stack is empty
  if (head == NULL)
  {
    return false;
  }

  //if the stack is nonempty, pop node from tail
  else
  {
    //temp lags behind tail to make sure data is cleared
    LinkedNodeClass< T >* temp = tail;
    outItem = tail->getValue();
    tail = tail->getPrev();

    //if the stack has only one element
    if (tail == NULL)
    {
      head = NULL;
      delete temp;
      return true;
    }

    //stack has more than one element
    tail->setNextPointerToNull();
    delete temp;
    return true;
  }
}

//Prints the contents of the stack from top(tail) to bottom.
template < class T >
void LIFOStackClass< T >::print() const
{
  //temp is a pointer for traversing the list
  LinkedNodeClass< T >* temp = tail;
  while (temp!= NULL)
  {
    cout << temp->getValue();
    temp = temp->getPrev();

    //the last element doesn't have a space after it
    if (temp != NULL)
    {
      cout << " ";
    }
  }
  cout << endl;
}

//returns the number of elements in the stack
template < class T >
int LIFOStackClass< T >::getNumElems() const
{
  int numElems = 0;

  //temp traverses the stack
  LinkedNodeClass< T >* temp = head;
  while (temp != NULL)
  {
    temp = temp->getNext();
    numElems += 1;
  }

  return numElems;
}

#endif