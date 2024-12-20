#ifndef _LINKEDNODECLASS_H
#define _LINKEDNODECLASS_H

/*
Andrew Jones
November 13th, 2024
This class encompasses a single node in a doubly linked-list data structure.
Nodes have a value inVal, and pointers to the previous
and next nodes, inPrev and inNext.
*/

#include <iostream>
using namespace std;
template < class T >
class LinkedNodeClass
{
  private:
    LinkedNodeClass< T > *prevNode;
    T nodeVal;
    LinkedNodeClass< T > *nextNode;



  public:
    LinkedNodeClass(
      LinkedNodeClass< T > *inPrev,
      const T &inVal,
      LinkedNodeClass< T > *inNext
      );

    T getValue(
      ) const;

    LinkedNodeClass< T >* getNext(
      ) const;

    LinkedNodeClass< T >* getPrev(
      ) const;


    void setNextPointerToNull(
      );

    void setPreviousPointerToNull(
      );

    void setBeforeAndAfterPointers(
      );

};

#include "LinkedNodeClass.inl"
#endif