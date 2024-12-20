#include <iostream>
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"

/*
Andrew Jones
November 13th, 2024
This class encompasses a doubly linked queue of LinkedNodeClass objects
*/

using namespace std;

//default constructor sets an empty list
FIFOQueueClass::FIFOQueueClass()
{
  head = NULL;
  tail = NULL;
}

//destructor clears out any dynamic memory associated with this queue
FIFOQueueClass::~FIFOQueueClass()
{
  clear();
}

//clear() traverses the queue and deletes all nodes in the queue
void FIFOQueueClass::clear()
{
  //temp is a pointer that traverses the list
  LinkedNodeClass* temp = head;
  if (temp != NULL)
  {
    //check if we are at the end of a nonempty queue
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

//inserts newItem into the queue at the tail
void FIFOQueueClass::enqueue(
  const int &newItem
  )
{
  //if list is currently empty
  if (head == NULL)
  {
    LinkedNodeClass* newNode = new LinkedNodeClass(NULL, newItem, NULL);
    head = newNode;
    tail = newNode;
  }
  //if the list is nonempty, put new node at tail
  else
  {
    LinkedNodeClass* newNode = new LinkedNodeClass(tail, newItem, NULL);
    newNode->setBeforeAndAfterPointers();
    tail = newNode;
  }
}

//takes out an item from the head of the queue, and outputs value to outItem
//Returns true if successful, returns false if the queue is empty
bool FIFOQueueClass::dequeue(
  int &outItem
  )
{
  //if queue is empty
  if (head == NULL)
  {
    return false;
  }

  //if the queue is nonempty, take node from head
  else
  {
    //temp lags behind head to make sure data is cleared
    LinkedNodeClass* temp = head;
    outItem = head->getValue();
    head = head->getNext();

    //if the queue has only one element
    if (head == NULL)
    {
      tail = NULL;
      delete temp;
      return true;
    }

    //queue has more than one element
    head->setPreviousPointerToNull();
    delete temp;
    return true;
  }
}

//prints out the contents of the queue from first to last
void FIFOQueueClass::print(
  ) const
{
  //temp is a pointer for traversing the list
  LinkedNodeClass* temp = head;
  while (temp != NULL)
  {
    cout << temp->getValue();
    temp = temp->getNext();

    //the last element doesn't have a space after it
    if (temp != NULL)
    {
      cout << " ";
    }
  }
  cout << endl;
}

//returns the number of elements in the queue.
int FIFOQueueClass::getNumElems(
  ) const
{
  int numElems = 0;

  //temp traverses the queue
  LinkedNodeClass* temp = head;
  while (temp != NULL)
  {
    temp = temp->getNext();
    numElems += 1;
  }

  return numElems;
}