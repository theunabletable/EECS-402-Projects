#ifndef _LIFOSTACKCLASS_H
#define _LIFOSTACKCLASS_H


/*
Andrew Jones
November 16th, 2024
This class encompasses a last-in-first-out Stack structure of LinkedNodeClass
objects.
*/
#include <iostream>
#include "LinkedNodeClass.h"
//A LIFOStackClass object contains a doubly-linked list, where items can only
//be accessed in a last-in-first-out manner. Assignment or copying this object
//creates a shallow copy -- does not copy the data within the stack.
template < class T >
class LIFOStackClass
{
  private:
    //head points to the first node in the stack or NULL if the stack is empty
    LinkedNodeClass< T > *head;
    //tail points to the last node in the stack or NULL if the stack is empty
    LinkedNodeClass< T > *tail;


  public:
  //Default constructor initializes an empty stack.
  LIFOStackClass(
    );

  //destructor deletes all the data inside the stack
  ~LIFOStackClass(
    );

  //Inserts the value newItem into the stack
  void push(
  const T &newItem
  );

  //attempts to take the next item off the stack. If the stack is empty,
  //the function returns false and outItem is unchanged. If the stack is
  //nonempty, returns true and the value of the item taken off the stack
  //is copied to outItem.
  bool pop(
    T &outItem
    );

  //Prints the contents of the stack from the top to bottom.
  void print(
    ) const;

  //returns the number of elements in the stack
  int getNumElems(
    ) const;

  //Clears the stack to an empty state, deleting dynamically allocated memory.
  void clear(
    );
};

#include "LIFOStackClass.inl"
#endif
