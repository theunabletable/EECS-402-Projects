#ifndef _RECTANGLECLASS_H
#define _RECTANGLECLASS_H

/*
Andrew Jones
November 3, 2024
an object of rectangle class represents a 2D rectangle with dimensions
and a color. The dimensions are determined by the x and y coordinates of
the upper-left corner, and lower-right corner
*/


#include <iostream>
#include "ColorClass.h"
#include "constants.h"
using namespace std;

class RectangleClass

{
  private:
    //these are x and y coordinates respectively of the upper left corner
    int upperLeftX;
    int upperLeftY;
    //x and y coordinates respectively of lower right corner
    int lowerRightX;
    int lowerRightY;

    //this is the color of the entire rectangle
    ColorClass color;

  public:
    //Default constructor
    RectangleClass();


    void setUpperLeft(
      int inX,
      int inY
      );
    void setLowerRight(
      int inX, 
      int inY
      );
    void setColor(
      ColorClass inColor
      );

    //sets the coordinates of this rectangle given the corners.
    void setWithCorners(
      int inUpperLeftX,
      int inUpperLeftY,
      int inLowerRightX,
      int inLowerRightY
      );
    //sets the coordinates of this rectangle given a corner and dimensions
    void setWithCornerAndDimensions(
      int inUpperLeftX,
      int inUpperLeftY,
      int width,
      int height
      );
    //sets the coordinates of this rectangle given center and how far
    //the sides of the rectangle extend from the center
    void setWithCenterAndExtent(
      int inCenterX,
      int inCenterY,
      int halfWidth,
      int halfHeight
      );


    int getUpperLeftX();
    int getUpperLeftY();
    int getLowerRightX();
    int getLowerRightY();
    ColorClass getColor();

};



#endif