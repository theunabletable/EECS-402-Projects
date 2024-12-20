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

class LinkedNodeClass
{
  private:
    LinkedNodeClass *prevNode;

    int nodeVal;
    LinkedNodeClass *nextNode;



  public:
    LinkedNodeClass(
      LinkedNodeClass *inPrev,
      const int &inVal,
      LinkedNodeClass *inNext
      );

    int getValue(
      ) const;

    LinkedNodeClass* getNext(
      ) const;

    LinkedNodeClass* getPrev(
      ) const;


    void setNextPointerToNull(
      );

    void setPreviousPointerToNull(
      );

    void setBeforeAndAfterPointers(
      );

};

#endif