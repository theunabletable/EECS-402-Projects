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
LIFOStackClass::LIFOStackClass()
{
  head = NULL;
  tail = NULL;
}

//destructor clears out any dynamic memory associated with this stack.
LIFOStackClass::~LIFOStackClass()
{
  clear();
}

//clear() traverses the queue and deletes all nodes in the stack
void LIFOStackClass::clear()
{
  //temp is a pointer that traverses the list
  LinkedNodeClass* temp = head;
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
void LIFOStackClass::push(
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

//pops the next item off the stack's tail, setting outItem to its value.
//returns true if successful, returns false if the stack is empty.
bool LIFOStackClass::pop(
  int &outItem
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
    LinkedNodeClass* temp = tail;
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
void LIFOStackClass::print() const
{
  //temp is a pointer for traversing the list
  LinkedNodeClass* temp = tail;
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
int LIFOStackClass::getNumElems() const
{
  int numElems = 0;

  //temp traverses the stack
  LinkedNodeClass* temp = head;
  while (temp != NULL)
  {
    temp = temp->getNext();
    numElems += 1;
  }

  return numElems;
}