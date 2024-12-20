#ifndef _IMAGECOLORCLASS_H
#define _IMAGECOLORCLASS_H

/*
Andrew Jones
November 3rd, 2024
This class encapsulates an image full of pixels of type ColorClass.
Data is stored in a matrix, which is read in from a PPM file type.
It supports the annotation of rectangles, patterns from a file, 
and of another image onto this image.
*/

using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include "ColorClass.h"
#include "RectangleClass.h"
#include "constants.h"
#include "PatternClass.h"

class ImageColorClass
{
  private:
    //colorGrid is the matrix which stores our pixels
    ColorClass* colorGrid;
    int width;
    int height;

  public:
    ImageColorClass(
      );

    //reads a PPM file of name fName, and stores the data in colorGrid, width
    //and height. The PPM file must be formatted correctly, beginning with
    //the magic number "P3", the width, the height, and then a sequence of
    //width*height triplets of integers between 0 and 255. Outputs true
    //if it reads the file without issue, outputs false if the file is
    //formatted incorrectly or can't be read.
    bool readPPMFile(
      string fName
      );
    
    //writes the data of colorGrid to a text file named outFileName.
    //outputs false if it fails to write, and true if it writes successfully.
    bool writePPMFile(
      string outFileName
      );
    
    //annotates a rectangle object onto the image, which is either filled in
    //or just a border, depending on rectFill.
    void annotateRectangle(
      RectangleClass &inRect,
      bool rectFill
      );

    //annotates a pattern object onto the image. Pattern objects have "pixels"
    //which overwrite the image at that location with patternColor, but
    //portions of the pattern object which are not pixels remain transparent.
    void annotatePattern(
      PatternClass &pattern,
      int upperLeftRow,
      int upperLeftCol,
      ColorClass &patternColor
      );

    //annotates another image object onto this image. Pixels in inImage of the
    //transparencyColor will not overwrite this image.
    void annotateWithImage(
      ImageColorClass &inImage,
      int upperLeftRow,
      int upperLeftCol,
      ColorClass &transparencyColor
      );

    int getWidth();
    int getHeight();

    //This clears out the image's colorgrid from memory, and unassigns
    //its pointer.
    void clearImage();
};

#endif
