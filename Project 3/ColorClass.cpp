#include <iostream>
#include <string>
#include <fstream>
#include "ColorClass.h"
#include "constants.h"
#include "getValidInput.h"

/*
Andrew Jones
November 3rd, 2024
This class encompasses a digital colored "pixel", with a red, green, and
blue value.
*/

//Default constructor sets to white (all values
// are set to MAX_INTENSITY), using the below setTo function.
ColorClass::ColorClass()
{
  setTo(MAX_INTENSITY, MAX_INTENSITY, MAX_INTENSITY);
}


//This constructor uses the below setTo function to set the initial
//values of this object, with clipping to ensure none of the values
//are below MIN_INTENSITY or above MAX_INTENSITY, and sets them respectively
//if the input values are.
ColorClass::ColorClass(
  int inRed,
  int inGreen,
  int inBlue
  )
{
  setTo(inRed, inGreen, inBlue);
}


//setTo sets the given object to user input specific color values, and 
//if any of them are less than MIN_INTENSITY or greater than MAX_INTENSITY,
//it "clips" them to MIN_INTENSITY or MAX_INTENSITY respectively.
//It outputs true if any clipping occurred, and false otherwise.
bool ColorClass::setTo(
  int inRed,
  int inGreen,
  int inBlue
  )
{
  //clipRequired is defaulted to false and eventually returned.
  //It's set to true if at any point clipping was required.
  bool clipRequired = false;

  //set red possibly with clipping
  if (inRed < MIN_INTENSITY)
  {
    red = MIN_INTENSITY;
    clipRequired = true;
  }
  else if (inRed > MAX_INTENSITY)
  {
    red = MAX_INTENSITY;
    clipRequired = true;
  }
  else
  {
    red = inRed;
  }

  //set green possibly with clipping
  if (inGreen < MIN_INTENSITY)
  {
    green = MIN_INTENSITY;
    clipRequired = true;
  }
  else if (inGreen > MAX_INTENSITY)
  {
    green = MAX_INTENSITY;
    clipRequired = true;
  }
  else
  {
    green = inGreen;
  }

  //set blue possibly with clipping
  if (inBlue < MIN_INTENSITY)
  {
    blue = MIN_INTENSITY;
    clipRequired = true;
  }
  else if (inBlue > MAX_INTENSITY)
  {
    blue = MAX_INTENSITY;
    clipRequired = true;
  }
  else
  {
    blue = inBlue;
  }
  return clipRequired;
}


//Sets the given ColorClass object to the colors of another ColorClass
//object, inColor. It outputs true if any clipping was required, and false 
//otherwise, but will always return false, because inColor already has
//valid colors.
bool ColorClass::setTo(
  ColorClass &inColor
  )
{
  return setTo(inColor.red, inColor.green, inColor.blue);
}


//These setter functions set the given ColorClass object to preset colors
//using the general setTo function.
void ColorClass::setToBlack()
{
  setTo(MIN_INTENSITY, MIN_INTENSITY, MIN_INTENSITY);
}
void ColorClass::setToRed()
{
  setTo(MAX_INTENSITY, 0, 0);
}
void ColorClass::setToGreen()
{
  setTo(0, MAX_INTENSITY, 0);
}
void ColorClass::setToBlue()
{
  setTo(0, 0, MAX_INTENSITY);
}
void ColorClass::setToWhite()
{
  setTo(MAX_INTENSITY, MAX_INTENSITY, MAX_INTENSITY);
}


//Adds the color values from rhs to this object's color values, subject to
//clipping that ensures color values remain valid. It outputs true if
//any clipping was required, and false otherwise.
bool ColorClass::addColor(
  ColorClass &rhs
  )
{
  return setTo(red + rhs.red, green + rhs.green, blue + rhs.blue);
}


//Subtracts the color values of rhs from the given ColorClass object,
//performing any required clipping. It outputs true if any clipping was
//required, and false otherwise.
bool ColorClass::subtractColor(
  ColorClass &rhs
  )
{
  return setTo(red - rhs.red, green - rhs.green, blue - rhs.blue);
}


//Multiplies the values of each color value by adjFactor, the result rounded
//down, and subject to clipping.
bool ColorClass::adjustBrightness(
  double adjFactor
  )
{ 
  int newRed = int(adjFactor * red);
  int newGreen = int(adjFactor * green);
  int newBlue = int(adjFactor * blue);
  return setTo(newRed, newGreen, newBlue);
}

//returns true if inColor and this color have the same values.
bool ColorClass::sameColor(
  ColorClass &inColor
  )
{
  if (red == inColor.red &&
      green == inColor.green &&
      blue == inColor.blue)
  {
    return true;
  }
  return false;
}

//reads a triplet of integers from a file stream to this pixel.
//returns false if the input is formatted incorrectly, or
//out of range.
bool ColorClass::readPixel(
  ifstream &inFile
  )
{
  int inRed;
  int inGreen;
  int inBlue;

  inFile >> inRed >> inGreen >> inBlue;

  if (inFile.fail())
  {
    return false;
  }

  if (inRed < MIN_INTENSITY || inRed > MAX_INTENSITY 
   || inGreen < MIN_INTENSITY || inGreen > MAX_INTENSITY
   ||  inBlue < MIN_INTENSITY || inBlue > MAX_INTENSITY)
  {
    return false;
  }
  
  setTo(inRed, inGreen, inBlue);
  return true;
  
  
}



//Outputs color values to a given filestream object.
void ColorClass::writeValues(
  ofstream &outFile
  )
{
  outFile << red << " " << green << " "  << blue << " ";
}

//Prompts a user to select a color from five choices for a given purpose.
void ColorClass::chooseColor(
  string purpose)
{
  int userChoice = 0;
  bool isValidInt = false;
  while (!isValidInt)
  {
    int minVal = 1;
    int maxVal = 5;
    cout << "1. Red" << endl;
    cout << "2. Green" << endl;
    cout << "3. Blue" << endl;
    cout << "4. Black" << endl;
    cout << "5. White" << endl;
    cout << purpose;
  
    isValidInt = getValidInput(userChoice, minVal, maxVal);
    if (!isValidInt)
    {
      cout << "Invalid input, enter an integer between 1 and 5." << endl;
    }
  }
  if (userChoice == RED)
  {
    setToRed();
  }
  else if (userChoice == GREEN)
  {
    setToGreen();
  }
  else if (userChoice == BLUE)
  {
    setToBlue();
  }
  else if (userChoice == BLACK)
  {
    setToBlack();
  }
  else if (userChoice == WHITE)
  {
    setToWhite();
  }
}
