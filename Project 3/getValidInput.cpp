#include <iostream>
#include "getValidInput.h"

/*
Andrew Jones
November 3rd, 2024
This function takes a variable and prompts the user to put in a value
outputting true or false, depending on whether the value is valid.
*/ 
using namespace std;

bool getValidInput(
  int &userInput, 
  int minVal, 
  int maxVal)
{
  cin >> userInput;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(200, '\n');
    return false;
  }
  if (userInput < minVal
   || userInput > maxVal)
  {
    return false;
  }
  return true;
}

bool getValidInput(
  int &userInput)
{
  cin >> userInput;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(200, '\n');
    return false;
  }
  return true;
}

bool getValidInput(
  string &userInput)
{
  cin >> userInput;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(200, '\n');
    return false;
  }
  return true;
}
