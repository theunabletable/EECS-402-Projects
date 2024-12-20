#ifndef _SORTEDLISTCLASS_INL
#define _SORTEDLISTCLASS_INL

#include <iostream>
#include "SortedListClass.h"
#include "LinkedNodeClass.h"

/*
Andrew Jones
November 13th, 2024
This class encompasses a sorted doubly linked list of LinkedNodeClass objects.
*/

using namespace std;

//default constructor creates an empty list.
template < class T >
SortedListClass< T >::SortedListClass()
{
  head = NULL;
  tail = NULL;
}

//Copy constructor which makes a deep copy of the list.
template < class T >
SortedListClass< T >::SortedListClass(
  const SortedListClass< T > &rhs
  )
{
  head = NULL;
  tail = NULL;
  //temp is a pointer which traverses the rhs list
  LinkedNodeClass< T >* temp = rhs.head;

  //if rhs is empty, make this an empty list
  if (temp == NULL)
  {
    clear();
  }
  //
  else
  {
    //lastNode tracks the last node that we've made
    LinkedNodeClass< T >* lastNode = NULL;
    while (temp != NULL)
    {
      T newVal = temp->getValue();

      //the newNodes are what populate our list
      LinkedNodeClass< T >* newNode = 
            new LinkedNodeClass< T >(lastNode, newVal, NULL);

      //make sure newNode is pointed to by lastNode
      newNode->setBeforeAndAfterPointers();

      //check if newNode is the first node in list.
      if (lastNode == NULL)
      {
        head = newNode;
      }
      lastNode = newNode;
      temp = temp->getNext();
    }
    //loop is finished, set tail correctly.
    tail = lastNode;
  }
}

//clear() traverses and deletes all of the nodes in the list,
//and leaves it empty.
template < class T >
void SortedListClass< T >::clear()
{
  //temp is a pointer used for traversing the list
  LinkedNodeClass< T >* temp = head;
  if (temp != NULL)
  {
    //this loop checks if we are at the end of the non-empty list
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

template < class T >
SortedListClass< T >::~SortedListClass()
{
  clear();
}

//overloaded assignment operator sets this list to have a deep copy
//of all of the data inside of the rhs list.
template < class T >
SortedListClass< T >& SortedListClass< T >:: operator=(
  const SortedListClass< T > &rhs
  )
{
  //temp is a pointer which traverses the rhs list
  LinkedNodeClass< T >* temp = rhs.head;
  if (this != &rhs)
  {
    //empty this list
    clear();

    //lastnode tracks the last node that we've made
    LinkedNodeClass< T >* lastNode = NULL;
    while (temp != NULL)
    {
      T newVal = temp->getValue();
      
      //newNodes populate the list
      LinkedNodeClass< T >* newNode = 
            new LinkedNodeClass< T >(lastNode, newVal, NULL);

      //make sure newNode is pointed to by lastNode
      newNode->setBeforeAndAfterPointers();
      
      //check if newNode is the first node in list
      if (lastNode == NULL)
      {
        head = newNode;
      }
      //progress the traversal
      lastNode = newNode;
      temp = temp->getNext();
    }
    //loop is finished, have to set the tail
    tail = lastNode;
  }
  return *this;
}


//this inserts valToInsert into this list at its proper, sorted location.
//If there are other nodes in the list with the same value as valToInsert,
//it will put valToInsert last among them.
template < class T >
void SortedListClass< T >::insertValue(
  const T &valToInsert
  )
{
  LinkedNodeClass< T >* newNode;
  //temp is a pointer used for traversing the list
  LinkedNodeClass< T >* temp = head;
  //check if the list is empty
  if (head == NULL)
  {
    newNode = new LinkedNodeClass< T >(NULL, valToInsert, NULL);
    head = newNode;
    tail = newNode;
  }
  else
  {
    //this traverses the nonempty list to find insertion point
    while (temp != NULL 
        && valToInsert >= temp->getValue())
    {
      temp = temp->getNext();
    }
    //insert at beginning
    if (temp == head)
    {
      newNode = new LinkedNodeClass< T >(NULL, valToInsert, head);
      newNode->setBeforeAndAfterPointers();
      head = newNode;
    }
    //insert at end
    else if (temp == NULL)
    {
      newNode = new LinkedNodeClass< T >(tail, valToInsert, NULL);
      newNode->setBeforeAndAfterPointers();
      tail = newNode;
    }
    //insert in the middle
    else
    {
      newNode = new LinkedNodeClass< T >(temp->getPrev(), valToInsert, temp);
      newNode->setBeforeAndAfterPointers();
    }
  }
}

//Prints the contents of this list from head to tail.
template < class T >
void SortedListClass< T >::printForward() const
{
  //temp is a pointer for traversing the list
  LinkedNodeClass< T >* temp = head;
  cout << "Forward List Contents Follow:" << endl;
  //traverse, and do nothing if it's an empty list
  while (temp != NULL)
  {
    cout << "  " << temp->getValue() << endl;
    temp = temp->getNext();
  }
  cout << "End Of List Contents" << endl;
}

//Prints the contents of this list from tail to head.
template < class T >
void SortedListClass< T >::printBackward() const
{
  //temp is a pointer for traversing the list
  LinkedNodeClass< T >* temp = tail;
  cout << "Backward List Contents Follow:" << endl;
  //traverse, and do nothing if it's an empty list
  while (temp != NULL)
  {
    cout << "  " << temp->getValue() << endl;
    temp = temp->getPrev();
  }
  cout << "End Of List Contents" << endl;
}


//Removes the front item in the list and returns its value to theVal.
//returns true or false corresponding to success or failure of removal
template < class T >
bool SortedListClass< T >::removeFront(
  T &theVal
  )
{
  //do nothing if this is an empty list
  if (head == NULL)
  {
    return false;
  }

  else
  {
    LinkedNodeClass< T >* deletedNode = head;
    theVal = deletedNode->getValue();
    head = deletedNode->getNext();
    //if the list has just one element, it becomes empty
    if (head == NULL)
    {
      tail = NULL;
    }
    //if the list has more than one element
    else
    {
      head->setPreviousPointerToNull();
    }
    delete deletedNode;
    return true;
  }
}
//Removes the last item in the list and returns its value to theVal
//returns true or false corresponding to success or failure of removal
template < class T >
bool SortedListClass< T >::removeLast(
  T &theVal
  )
{
  //do nothing if this is an empty list
  if (tail == NULL)
  {
    return false;
  }

  else
  {
    LinkedNodeClass< T >* deletedNode = tail;
    theVal = deletedNode->getValue();
    tail = deletedNode->getPrev();
    //if the list has just one element, it becomes empty
    if (tail == NULL)
    {
      head = NULL;
    }
    //if the list has more than one element
    else
    {
      tail->setNextPointerToNull();
    }
    delete deletedNode;
    return true;
  }
}

//returns the number of elements in the list.
template < class T >
int SortedListClass< T >::getNumElems() const
{
  int numElems = 0;
  //temp traverses the list
  LinkedNodeClass< T >* temp = head;
  while (temp != NULL)
  {
    temp = temp->getNext();
    numElems += 1;
  }
  return numElems;
}

//returns the value at index to outVal, returns true if successful,
//but if index is out of range, returns false and outVal is unchanged.
template < class T >
bool SortedListClass< T >::getElemAtIndex(
  const int index,
  T &outVal
  ) const
{
  int tempIndex = 0;
  //temp traverses the list at index tempIndex
  LinkedNodeClass< T >* temp = head;
  //empty list has no elements
  if (head == NULL)
  {
    return false;
  }
  while (temp != NULL)
  {
    if (tempIndex == index)
    {
      outVal = temp->getValue();
      return true;
    }
    temp = temp->getNext();
    tempIndex += 1;
  }
  //traversed whole list, never reached index
  return false;
}

#endif