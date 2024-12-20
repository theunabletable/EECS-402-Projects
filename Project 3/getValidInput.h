#ifndef _GETVALIDINPUT_H
#define _GETVALIDINPUT_H
/*
Andrew Jones
November 3rd, 2024
This function takes a variable and prompts the user to put in a value
outputting true or false, depending on whether the value is valid.
*/
#include <iostream>
#include <string>
using namespace std;

//This assigns userVal to the value the user puts in, and outputs true if
//it is an integer between minVal and maxVal.
bool getValidInput(
  int &userVal,
  int minVal,
  int maxVal);

//This assigns by user input to userVal and checks if it is an integer. 
//Outputs false if not.
bool getValidInput(
  int &userVal);

//This assigns by user input to userVal a string.
bool getValidInput(
  string &userVal);


#endif