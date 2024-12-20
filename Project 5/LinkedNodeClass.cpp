#ifndef _LINKEDNODECLASS_INL_
#define _LINKEDNODECLASS_INL_

#include "LinkedNodeClass.h"

/*
Andrew Jones
November 13th, 2024
This class encompasses a single node in a doubly linked-list data structure.
Nodes have a value inVal, and pointers to the previous
and next nodes, inPrev and inNext.
*/

//This constructor creates a node with specified attributes.
template < class T >
LinkedNodeClass< T >::LinkedNodeClass(
  LinkedNodeClass< T > *inPrev,
  const T &inVal,
  LinkedNodeClass< T > *inNext
  )
{
  nodeVal = inVal;
  prevNode = inPrev;
  nextNode = inNext;
}

template < class T >
T LinkedNodeClass< T >::getValue() const
{
  return nodeVal;
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getNext() const
{
  return nextNode;
}

template < class T >
LinkedNodeClass< T >* LinkedNodeClass< T >::getPrev() const
{
  return prevNode;
}

template < class T >
void LinkedNodeClass< T >::setNextPointerToNull()
{
  nextNode = NULL;
}

template < class T >
void LinkedNodeClass< T >::setPreviousPointerToNull()
{
  prevNode = NULL;
}

//Sets the node prevNode points to to point to this node,
//and likewise for the node nextNode points to
template < class T >
void LinkedNodeClass< T >::setBeforeAndAfterPointers()
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

#endif