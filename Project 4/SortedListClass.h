#ifndef _SORTEDLISTCLASS_H
#define _SORTEDLISTCLASS_H

/*
Andrew Jones
November 13th, 2024
This class encompasses a sorted doubly linked list of LinkedNodeClass objects.
*/

#include <iostream>
#include "LinkedNodeClass.h"
using namespace std;
//A SortedListClass object is a doubly linked list of LinkedNodeClass objects
//where any integer can be inserted and will be sorted. The head points to the
//first node in the list, and the tail to the last node in the list.
class SortedListClass
{
  private:
    //head points to the first node in the list, or NULL if the list is empty
    LinkedNodeClass *head;
    //tail points to the last node in the list, or NULL if the list is empty
    LinkedNodeClass *tail;

  public:
    //default constructor initializes an empty list
    SortedListClass(
      );

    //Copy constructor which makes a deep copy of the list
    SortedListClass(
      const SortedListClass &rhs
      );

    //Destructor clears all of the nodes within the list in 
    //addition to this list
    ~SortedListClass(
      );

    //Assignment operator 
    SortedListClass& operator=(
      const SortedListClass &rhs
      );

    //clears the nodes within the list, deletes the head and tail
    //and deletes this list
    void clear(
      );
    

    //this inserts valToInsert into this list at its proper, sorted location.
    //If there are other nodes in the list with the same value as valToInsert,
    //it will put valToInsert last among them.
    void insertValue(
      const int &valToInsert
      );

    //Prints the contents of this list from head to tail.
    void printForward(
      ) const;

    //Prints the contents of this list from tail to head.
    void printBackward(
      ) const;

    //Removes the front item from the list and returns its value to theVal.
    //If the list is empty, returns false, and otherwise returns true.
    bool removeFront(
      int &theVal
      );

    //Removes the last item in the list and returns its value to theVal.
    //if the list is empty, returns false, otherwise returns true.
    bool removeLast(
      int &theVal
      );

    //returns the number of nodes in this list
    int getNumElems(
      ) const;

    //Provides the value stored in the node at index to outVal,
    //returns true if succcessful, and returns false if index out of range
    bool getElemAtIndex(
      const int index,
      int &outVal
      ) const;
};

#endif