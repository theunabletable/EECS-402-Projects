#ifndef _FIFOQUEUECLASS_H
#define _FIFOQUEUECLASS_H
#include "LinkedNodeClass.h"
/*
Andrew Jones
November 13th, 2024
This class encompasses a first-in-first-out Queue structure of LinkedNodeClass
objects. 
*/
#include <iostream>
//A FIFOQueueClass object contains a doubly-linked list, where items can be
//accessed only in a first-in-first-out manner. Data inside of the queue 
//cannot be copied using assignment, and has no copy constructor.

template < class T >
class FIFOQueueClass
{
  private:
    //head points to the first node in the list, or NULL if the list is empty
    LinkedNodeClass< T > *head;
    //tail points to the last node in the list, or NULL if the list is empty
    LinkedNodeClass< T > *tail;

  public:
    //default constructor initiliazes an empty queue. There is no
    //copy constructor or assignment overload, so do not attempt
    //attempt 
    FIFOQueueClass(
      );

    //destructor clears out any dynamic memory associated with this queue
    ~FIFOQueueClass(
      );

    //inserts newItem into the queue
    void enqueue(
      const T &newItem
      );

    //Takes next item out of queue and assigns it to outItem.
    //returns true if successful, returns false if the queue is empty 
    bool dequeue(
      T &outItem
      );

    //prints out the contents of the queue from first to last
    void print(
      ) const;

    //returns the number of elements in the queue.
    int getNumElems(
      ) const;

    //clears the queue to an empty state, freeing any memory
    //dynamically allocated.
    void clear(
      );


};

#include "FIFOQueueClass.inl"
#endif
