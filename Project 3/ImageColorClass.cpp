using namespace std;

/*
Andrew Jones
November 3rd, 2024
This class encapsulates an image full of pixels of type ColorClass.
Data is stored in a matrix, which is read in from a PPM file type.
It supports the annotation of rectangles, patterns from a file, 
and of another image onto this image.
*/

#include <iostream>
#include <string>
#include <fstream>
#include "ColorClass.h"
#include "constants.h"
#include "RectangleClass.h"
#include "ImageColorClass.h"

ImageColorClass::ImageColorClass()
{
  width = 0;
  height = 0;
  colorGrid = NULL;
}

int ImageColorClass::getWidth()
{
  return width;
}

int ImageColorClass::getHeight()
{
  return height;
}

bool ImageColorClass::readPPMFile(
  string fName
  )
{
  ifstream inFile;
  inFile.open(fName.c_str());
  //error message if the file doesn't open.
  if (inFile.fail())
  {
    cout << "Unable to open file" << endl;
    return false;
  }
      
  //Read in the magic number and ensure that it is "P3"
  string magicNumber;
  inFile >> magicNumber;
  if (inFile.fail() || (magicNumber != MAGIC_NUMBER))
  {
    cout << "File does not start with the magic number P3" << endl;
    inFile.close();
    return false;
  }


  inFile >> width;
  inFile >> height;

  if (inFile.fail() || width <= 0 || height <= 0)
  {
    cout << "Invalid image dimensions" << endl;
    inFile.close();
    return false;
  }
 
  int maxColorValue;
  inFile >> maxColorValue;
  if (maxColorValue != MAX_INTENSITY)
  {
    cout << "Max color value is not 255" << endl;
    inFile.close();
    return false;
  }
      
  colorGrid = new ColorClass[width * height];

  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      bool checkSuccess;
      //reads a set of data in from the file and creates a pixel.
      //checkSuccess determines if the data is formatted correctly.
      checkSuccess = colorGrid[row * width + col].readPixel(inFile);
      if (!checkSuccess)
      {
        cout << "Unexpected problem in file at entry "
             << row << " " << col << endl;
        clearImage();
        inFile.close();
        return false;
      }
    }
  }
  
  //Check if the image has the right amount of values
  string extraValue;
  inFile >> extraValue;
  if (!inFile.fail())
  {
    cout << "File has too many values." << endl;
    clearImage();
    inFile.close();
    return false;
  }
  
  inFile.close();
  return true;
}



bool ImageColorClass::writePPMFile(
  string outFileName
  )
{
  ofstream outFile;
  outFile.open(outFileName.c_str());

  //ensure we're allowed to write where we want to
  if (outFile.fail())
  {
    cout << "Unable to open file" << endl;
    return false;
  }
      
  //write the PPM header
  outFile << MAGIC_NUMBER << endl;
  outFile << width << " " << height << endl;
  outFile << MAX_INTENSITY << endl;
  if (outFile.fail())
  {
    cout << "Unable to write to file." << endl;
  }

  //Write the pixels
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      colorGrid[row * width + col].writeValues(outFile);          
    }
    outFile << endl;
  }
      
  return true;
}

void ImageColorClass::annotateRectangle(
  RectangleClass &inRect,
  bool rectFill
  )
//This method "annotates" the image with a given rectangle, by coloring
//every pixel on the image the color of the rectangle. If rectFill is
//true, only the rectangle will be colored. If rectFill is false,
//then everything within the rectangle is colored as well.
{
  ColorClass rectColor = inRect.getColor();
  //The start and end rows and columns are subject to a type of "clipping"
  //where if the rectangle has vertices that lie outside the image,
  //only the section of the image which contains part of the rectangle
  //will be affected. 
  int startRow = inRect.getUpperLeftY();
  if (startRow < 0)
  {
    startRow = 0;
  }
  int startCol = inRect.getUpperLeftX();
  if (startCol < 0)
  {
    startCol = 0;
  }

  //if the endCol or endRow exceed the right or lower edges of our
  //image, we adjust the bounds.
  int endRow = inRect.getLowerRightY();
  if (endRow > height - 1)
  {
    endRow = height - 1;
  }
  int endCol = inRect.getLowerRightX();
  if (endCol > width - 1)
  {
    endCol = width - 1;
  }

  //if the given rectangle lies totally outside the image, we want to
  //do nothing.
  if (startRow > endRow
   || startCol > endCol)
  {
    return;
  }
    
  //Annotate the image
  for (int row = startRow; row <= endRow; ++row)
  {
    for (int col = startCol; col <= endCol; ++col)
    {
      if (!rectFill)
      //we only color the border
      {
        if (row == startRow
         || row == endRow
         || col == startCol
         || col == endCol)
        {
          colorGrid[row * width + col].setTo(rectColor);
        }
      }
      else
      //we fill up the entire rectangle
      {
        colorGrid[row * width + col].setTo(rectColor);
      }
    }
  }
  
}


//Places in this image a PatternClass object of color patternColor
//with its upper left corner placed at upperLeftRow, upperLeftCol.
//the start and end rows are subject to a type of "clipping" where
//if the pattern has vertices lying outside the image, only the
//section of the image which contains part of the pattern will
//be affected. 
void ImageColorClass::annotatePattern(
  PatternClass &pattern,
  int upperLeftRow,
  int upperLeftCol,
  ColorClass &patternColor
  )
{
  int patternWidth = pattern.getWidth();
  int patternHeight = pattern.getHeight();

    

  //If the pattern starts way off the image, it's clipped
  //to the left or top side.
  int startRow = upperLeftRow;
  if (startRow < 0)
  {
    startRow = 0;
  }

  int startCol = upperLeftCol;
  if (startCol < 0)
  {
    startCol = 0;
  }

  //we find the coordinate of the bottom-right corner of the pattern
  //and clip it to the bottom or right side of the image if either
  //is too large.
  int endRow = upperLeftRow + patternHeight - 1;
  if (endRow > height - 1)
  {
    endRow = height - 1;
  }

  int endCol = upperLeftCol + patternWidth - 1;
  if (endCol > width - 1)
  {
    endCol = width - 1;
  }

  //If the pattern lies outside the image, we do nothing
  if (startRow > endRow ||
      startCol > endCol)
  {
    return;
  }
    

  //This loops through colorGrid and reassigns exactly the pixels
  //which correspond to "1"s in the pattern file to patternColor
  for (int row = startRow; row <= endRow; ++row)
  {
    for (int col = startCol; col <= endCol; ++col)
    {
      //the corner of the pattern is (0, 0) from the perspective of the
      //pattern, but is (upperLeftCol, upperLeftRow) in the coordinates
      //of the image, so our inputs into the pattern must be shifted.
      if (pattern.isPixel(
            row - upperLeftRow,
            col - upperLeftCol
            )
         )
      {
        colorGrid[row * width + col].setTo(patternColor);
      }
    }
  }
}

//Places the inImage with its upper left corner at the upperLeftRow
//upperLeftCol of this image. The chosen transparencyColor will not
//overwrite this image, but all other colors will. If the inImage doesn't
//lie totally inside this image, it will only copy the portion of inImage
//which is inside this image.
void ImageColorClass::annotateWithImage(
  ImageColorClass &inImage,
  int upperLeftRow,
  int upperLeftCol,
  ColorClass &transparencyColor
  )
{
  int inHeight = inImage.getHeight();
  int inWidth = inImage.getWidth();

  //If the inImage starts way off this image, it's clipped to the left
  //or top side.
  int startRow = upperLeftRow;
  if (startRow < 0)
  {
    startRow = 0;
  }

  int startCol = upperLeftCol;
  if (startCol < 0)
  {
    startCol = 0;
  }

  //If the inImage bottom or right is way off this image, it's clipped
  //to the bottom or right
  int endRow = upperLeftRow + inHeight - 1;
  if (endRow > height - 1)
  {
    endRow = height - 1;
  }

  int endCol = upperLeftCol + inWidth - 1;
  if (endCol > width - 1)
  {
    endCol = width - 1;
  }

  //If the pattern lies totally outside the image, this copy does nothing.
  if (startRow > endRow ||
      startCol > endCol)
  {
    return;
  }
    
  //This loops through the colorGrid and reassigns every pixel to the
  //corresponding color of inImage, except those which equal
  //transparencyColor. inRow and inCol are the indices corresponding
  //to row and col in inImage's coordinates.
  ColorClass inColor;
  int inRow;
  int inCol;
  for (int row = startRow; row <= endRow; ++row)
  {
    for (int col = startCol; col <= endCol; ++col)
    {
      inRow = row - upperLeftRow;
      inCol = col - upperLeftCol;
      inColor = inImage.colorGrid[inRow*inWidth + inCol];
      if (!inColor.sameColor(transparencyColor))
      {
        colorGrid[row * width + col].setTo(inColor);
      }
    }
  }
}
  
void ImageColorClass::clearImage()
{
  delete[] colorGrid;
  colorGrid = NULL;
}

