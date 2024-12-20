#include <iostream>
#include "LinkedNodeClass.h"

/*
Andrew Jones
November 13th, 2024
This class encompasses a single node in a doubly linked-list data structure.
Nodes have a value inVal, and pointers to the previous
and next nodes, inPrev and inNext.
*/

//This constructor creates a node with specified attributes.
LinkedNodeClass::LinkedNodeClass(
  LinkedNodeClass *inPrev,
  const int &inVal,
  LinkedNodeClass *inNext
  )
{
  nodeVal = inVal;
  prevNode = inPrev;
  nextNode = inNext;
}

int LinkedNodeClass::getValue() const
{
  return nodeVal;
}

LinkedNodeClass* LinkedNodeClass::getNext() const
{
  return nextNode;
}

LinkedNodeClass* LinkedNodeClass::getPrev() const
{
  return prevNode;
}

void LinkedNodeClass::setNextPointerToNull()
{
  nextNode = NULL;
}

void LinkedNodeClass::setPreviousPointerToNull()
{
  prevNode = NULL;
}

//Sets the node prevNode points to to point to this node,
//and likewise for the node nextNode points to
void LinkedNodeClass::setBeforeAndAfterPointers()
{
  if (prevNode != NULL)
  {
    prevNode->nextNode = this;
  }
  if (nextNode != NULL)
  {
    nextNode->prevNode = this;
  }
}
