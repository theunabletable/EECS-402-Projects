using namespace std;

/*
Andrew Jones
November 3, 2024
an object of rectangle class represents a 2D rectangle with dimensions
and a color. The dimensions are determined by the x and y coordinates of
the upper-left corner, and lower-right corner
*/

#include "RectangleClass.h"
#include <iostream>
#include <fstream>
#include "ColorClass.h"
#include "constants.h"
#include "RectangleClass.h"

//the default constructor gives a degenerate rectangle that takes up no space.
RectangleClass::RectangleClass(
  )
{
  upperLeftX = 0;
  upperLeftY = 0;
  lowerRightX = 0;
  lowerRightY = 0;

  color = ColorClass();
}

//sets the upper left corner
void RectangleClass::setUpperLeft(
  int inX,
  int inY
  )
{
  upperLeftX = inX;
  upperLeftY = inY;
}
//sets the lower right corner
void RectangleClass::setLowerRight(
  int inX,
  int inY
  )
{
  lowerRightX = inX;
  lowerRightY = inY;
}

//sets the rectangle up with given corner coordinates
void RectangleClass::setWithCorners(
  int inUpperLeftX,
  int inUpperLeftY,
  int inLowerRightX,
  int inLowerRightY
  )
{
  setUpperLeft(
    inUpperLeftX,
    inUpperLeftY
    );
  setLowerRight(
    inLowerRightX,
    inLowerRightY
    );
}

//Given the corners and width and height of the rectangle, sets the rectangle
//with the proper corners.
void RectangleClass::setWithCornerAndDimensions(
  int inUpperLeftX,
  int inUpperLeftY,
  int width,
  int height
  )
{
  setWithCorners(
    inUpperLeftX, 
    inUpperLeftY, 
    inUpperLeftX + width - 1,
    inUpperLeftY + height - 1
    );
}

//Given the center and half width and half height of the rectangle, sets
//the corners properly.
void RectangleClass::setWithCenterAndExtent(
  int inCenterX,
  int inCenterY,
  int halfWidth,
  int halfHeight
  )
{
  setWithCorners(
    inCenterX - halfWidth,
    inCenterY - halfHeight,
    inCenterX + halfWidth,
    inCenterY + halfHeight
    );
}


void RectangleClass::setColor(
  ColorClass inColor
  )
{
  color = inColor;
}

int RectangleClass::getUpperLeftX()
{
  return upperLeftX;
}

int RectangleClass::getUpperLeftY()
{
  return upperLeftY;
}

int RectangleClass::getLowerRightX()
{
  return lowerRightX;
}

int RectangleClass::getLowerRightY()
{
  return lowerRightY;
}

ColorClass RectangleClass::getColor()
{
  return color;
}













