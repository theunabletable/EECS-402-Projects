#ifndef _COLORCLASS_H
#define _COLORCLASS_H

/*
Andrew Jones
November 3rd, 2024
This class encompasses a digital colored "pixel", with a red, green, and
blue value.
*/
#include <iostream>
using namespace std;

class ColorClass
//An object of ColorClass represents a pixel of color, with an integer red,
//green, and blue value. Each value can be no smaller than MIN_INTENSITY
//and no larger than MAX_INTENSITY. If a value is too small or too large,
//it is "clipped" to MIN_INTENSITY or MAX_INTENSITY respectively.
{
  private:
    int red;
    int green;
    int blue; 


  public:
    //Default constructor
    ColorClass(
      );


    //Parameterized constructor, which uses clipping to ensure none of the
    //color values are below MIN_INTENSITY or above MAX_INTENSITY, and sets
    //them respectively if they are out of range
    ColorClass(
      int inRed,
      int inGreen,
      int inBlue
      );


    //setTo sets the given object to user input specific color values, and 
    //if any of them are less than MIN_INTENSITY or greater than MAX_INTENSITY,
    //it "clips" them to MIN_INTENSITY or MAX_INTENSITY respectively.
    //It outputs true if any clipping occurred, and false otherwise.
    bool setTo(
      int inRed,
      int inGreen,
      int inBlue
      );

    //Sets the given ColorClass object to the colors of another ColorClass
    //object, inColor. It outputs true if any clipping was required, and false 
    //otherwise, but will always return false, because inColor already has
    //valid colors.
    bool setTo(
      ColorClass &inColor
      );

    //These setter functions set the given ColorClass object to preset colors
    //using the general setTo function.
    void setToBlack(
      );
    void setToRed(
      );
    void setToGreen(
      );
    void setToBlue(
      );
    void setToWhite(
      );


    //Adds the color values from rhs to this object's color values, subject to
    //clipping that ensures color values remain valid. It outputs true if
    //any clipping was required, and false otherwise.
    bool addColor(
      ColorClass &rhs
      );


    //Subtracts the color values of rhs from the given ColorClass object,
    //performing any required clipping. It outputs true if any clipping was
    //required, and false otherwise.
    bool subtractColor(
      ColorClass &rhs
      );


    //Multiplies the values of each color value by adjFactor, the result rounded
    //down, and subject to clipping.
    bool adjustBrightness(
      double adjFactor
      );
    //Prints the color values of this ColorClass object.
    void printComponentValues(
      );

    //returns true if this color has the same values as inColor
    bool sameColor(
      ColorClass &inColor
      );

    
    //reads three consecutive values from a filestream and assigns
    //them to red, green, and blue. The values must be integers
    //between MIN_INTENSITY and MAX_INTENSITY. Returns true if the pixel is
    //formatted correctly, and false otherwise.
    bool readPixel(
      ifstream &inFile
      );

    //writes this object's red, green, and blue values to the given
    //output stream.
    void writeValues(
      ofstream &outFile
      );
    //Prompts a user to choose from five colors, and sets this object
    //to that color.
    void chooseColor(
      string purpose
      );
};

#endif