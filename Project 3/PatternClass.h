#ifndef _PATTERNCLASS_H
#define _PATTERNCLASS_H

/*
Andrew Jones
November 3, 2024
This class encompasses a rectangular "Pattern" of 0s and 1s, which can
be read in from a text file.
*/
#include <fstream>
#include <string>
#include "constants.h"
#include <iostream>
class PatternClass
{
  private:
    int patternWidth;
    int patternHeight;
    int* patternGrid;

  public:
    PatternClass();
 
    //readPattern takes in a string and reads the Pattern file with that name,
    //and assigns to patternGrid the data from that pattern file. Outputs true
    //if it reads without issue. Outputs false if it fails to read.
    //Proper pattern files begin with an integer for the number of columns
    //and an integer for the number of rows. Then a rectangular pattern of
    //0s and 1s.
    bool readPattern(string fName);

    int getWidth();
    int getHeight();

    void setWidth(
      int inWidth);
    void setHeight(
      int inHeight);
    //Checks if a given cell is a "1"
    bool isPixel(
      int inRow,
      int inCol);
    
    //deletes patternGrid's data to avoid memory leaks.
    void clearPattern(
      );
};


#endif