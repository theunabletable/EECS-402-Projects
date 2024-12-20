using namespace std;

/*
Andrew Jones
November 3, 2024
This class encompasses a rectangular "Pattern" of 0s and 1s, which can
be read in from a text file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "constants.h"
#include "PatternClass.h"

PatternClass::PatternClass()
{
  patternWidth = 0;
  patternHeight = 0;
  patternGrid = NULL;
}

int PatternClass::getWidth()
{
  return patternWidth;
}

int PatternClass::getHeight()
{
  return patternHeight;
}

void PatternClass::setWidth(
  int inWidth)
{
  patternWidth = inWidth;
}

void PatternClass::setHeight(
  int inHeight)
{
  patternHeight = inHeight;
}




bool PatternClass::readPattern(
  string fName)
{
  ifstream inFile(fName.c_str());
  if (inFile.fail())
  {
    cout << "Unable to open file" << endl;
    return false;
  }

  inFile >> patternWidth;
  inFile >> patternHeight;
  //Make sure that the dimensions exist and are integers.
  if (inFile.fail())
  {
    cout << "Invalid pattern dimensions in file" << endl;
    inFile.close();
    return false;
  }

  if (patternWidth <= 0 ||
      patternHeight <= 0)
  {
    cout << "Dimensions of pattern must be positive." << endl;
    inFile.close();
    return false;
  }
  //allocate the memory for array.
  patternGrid = new int[patternWidth * patternHeight];

  //Read the pattern into a matrix
  for (int row = 0; row < patternHeight; ++row)
  {
    for (int col = 0; col < patternWidth; ++col)
    {
      inFile >> patternGrid[row * patternWidth + col];
      if (inFile.fail() ||
          (patternGrid[row * patternWidth + col] != 0 &&
           patternGrid[row * patternWidth + col] != 1)
      )
      {
        cout << "Invalid pattern data at entry "
             << row << " " << col << endl;
        delete[] patternGrid;
        patternGrid = NULL;
        inFile.close();
        return false;
      }
    }
  }
  //Check if the pattern has extra values it shouldn't
  string extraValue;
  inFile >> extraValue;
  if (!inFile.fail())
  {
    cout << "File has too many values." << endl;
    clearPattern();
    inFile.close();
    return false;
  }
  inFile.close();
  return true;
  //!!!What if the pattern has extra values but they are type other than int?
}


//clearPattern clears and unassigns the matrix pointer to prevent memory leaks
void PatternClass::clearPattern(
  )
{
  delete[] patternGrid;
  patternGrid = NULL;
}

//isPixel returns true if the given location is a 1, and false otherwise.
bool PatternClass::isPixel(
  int inRow,
  int inCol)
{
  return patternGrid[inRow * patternWidth + inCol] == 1;
}


