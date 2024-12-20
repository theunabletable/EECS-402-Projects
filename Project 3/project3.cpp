#include <iostream>
#include <string>
#include <fstream>
/*
Andrew Jones
November 3, 2024
This program can read and write PPM Image files, as well as edit them,  
using user input in a menu. The image is read into an ImageColorClass object, 
which is a matrix of pixels of type ColorClass. There are various
ImageColorClass methods used to annotate a rectangle, or a pattern file,
or another PPM file.*/
#include "ColorClass.h"
#include "constants.h"
#include "ImageColorClass.h"
#include "PatternClass.h"
#include "RectangleClass.h"
#include "getValidInput.h"

using namespace std;

int main()
{
  string fileName;
  ImageColorClass image;
  cout << "Enter string for PPM image file name to load: ";
  cin >> fileName;

  bool successfulRead;
  successfulRead = image.readPPMFile(fileName);
  if (!successfulRead)
  {
    cout << "File not read" << endl;
    return 1;
  }

  bool programContinues = true;
  int menuChoice;
  //main menu loop
  while (programContinues)
  { 
    //minVal, maxVal, and isValidInt used to track validity of user input
    int minVal = 1;
    int maxVal = 5;
    bool isValidInt = false;
    
    
    while (!isValidInt)
    {
      cout << "1. Annotate image with rectangle" << endl;
      cout << "2. Annotate image with pattern from file" << endl;
      cout << "3. Insert another image" << endl;
      cout << "4. Write out current image" << endl;
      cout << "5. Exit the program "<< endl;
      cout << "Enter int for main menu choice: ";
      //isValidInt outputs true if the user's choice is valid and false 
      //otherwise
      isValidInt = getValidInput(menuChoice, minVal, maxVal);
      if (!isValidInt)
      {
        cout << "Invalid input, enter an integer between 1 and 5." << endl;
      }
    }


    //annotate with rectangle
    if (menuChoice == ANNOTATE_WITH_RECT)
    {  
      int minVal = 1;
      int maxVal = 3;
      isValidInt = false;
      while(!isValidInt)
      { 
        cout << "1. Specify upper left and lower right corners ";
        cout << "of rectangle" << endl;
        cout << "2. Specify upper left corner and dimensions of ";
        cout << "rectangle" << endl;
        cout << "3. Specify extent from center of rectangle" << endl;
        cout << "Enter int for rectangle specification method: ";
        //isValidInt outputs true if the user's choice is valid and false 
        //otherwise
        isValidInt = getValidInput(menuChoice, minVal, maxVal);
        if (!isValidInt)
        {
          cout << "Invalid input, enter an integer between 1 and 3." << endl;
        }
      }
      
      //use corners
      if (menuChoice == CORNERS)
      {
        //these determine the location of the upper left/lower right corners
        int upperLeftRow;
        int upperLeftCol;
        int lowerRightRow;
        int lowerRightCol;

        //this determines and whether the rectangle is filled
        bool rectFill;

        bool firstInputIsValid = false;
        bool secondInputIsValid = false;
        //these loops take two inputs, and finishes only when both inputs
        //are valid, to decide location of rectangle.
        while (!(firstInputIsValid && secondInputIsValid))
        {
          cout << "Enter upper left corner row and column: ";
          firstInputIsValid = getValidInput(upperLeftRow);
          secondInputIsValid = getValidInput(upperLeftCol);
          if((!firstInputIsValid) || !(secondInputIsValid))
          {
            cout << "Invalid. Inputs must be integers." << endl;
          }
          
        }
        firstInputIsValid = false;
        secondInputIsValid = false;
        while (!(firstInputIsValid && secondInputIsValid))
        {
          cout << "Enter lower right corner row and column: ";
          firstInputIsValid = getValidInput(lowerRightRow);
          secondInputIsValid = getValidInput(lowerRightCol);
          if ((!firstInputIsValid) || !(secondInputIsValid))
          {
            cout << "Invalid. Inputs must be integers." << endl;
          }
          if (lowerRightRow <= upperLeftRow)
          {
            cout << "Invalid. Lower right corner row must be larger than ";
            cout << "upper left corner row " << upperLeftRow << endl;
            firstInputIsValid = false;
          }
          if (lowerRightCol <= upperLeftCol)
          {
            cout << "Invalid. Lower right corner column must be larger than ";
            cout << "upper left corner column " << upperLeftCol << endl;
            secondInputIsValid = false;
          }
          
        }

        //User picks rectangle color.
        string purpose = "Enter int for rectangle color: ";
        ColorClass rectColor = ColorClass();
        rectColor.chooseColor(purpose);

        //User picks whether rectangle is filled or not
        isValidInt = false;
        while (!isValidInt)
        {
          minVal = 1;
          maxVal = 2;
          cout << "1. No" << endl;
          cout << "2. Yes" << endl;
          cout << "Enter int for rectangle fill option: ";

          isValidInt = getValidInput(menuChoice);
          if (!isValidInt)
          {
            cout << "Invalid input, enter the integer 1 or 2." << endl;
          }
        }
        if (menuChoice == minVal)
        {
          rectFill = false;
        }
        else if (menuChoice == maxVal)
        {
          rectFill = true;
        }

        //create a RectangleClass object with the inputs specified by user
        RectangleClass userRect = RectangleClass();
        userRect.setWithCorners(
          upperLeftCol, 
          upperLeftRow,
          lowerRightCol, 
          lowerRightRow);
        userRect.setColor(rectColor);
        image.annotateRectangle(
          userRect,
          rectFill);
      }


      //use upper left corner and dimensions
      else if (menuChoice == CORNER_AND_DIMENSIONS)
      {
        //these determine the location of the upper left corner and dimensions
        int upperLeftRow;
        int upperLeftCol;
        int numRows;
        int numCols;

        //this determines whether the rectangle is filled
        bool rectFill;

        bool firstInputIsValid = false;
        bool secondInputIsValid = false;
        //this loop takes two inputs, and finishes only when both inputs
        //are valid, to decide location of rectangle.
        while (!(firstInputIsValid && secondInputIsValid))
        {
          cout << "Enter upper left corner row and column: ";
          firstInputIsValid = getValidInput(upperLeftRow);
          secondInputIsValid = getValidInput(upperLeftCol);
          if((!firstInputIsValid) || !(secondInputIsValid))
          {
            cout << "Invalid. Inputs must be integers." << endl;
          }
          
        }
        
        //number of rows and columns must be a positive integer.
        isValidInt = false;
        while (!isValidInt)
        {
          cout << "Enter int for number of rows: ";
          isValidInt = getValidInput(numRows);
          if (!isValidInt)
          {
            cout << "Invalid. Input must be an integer." << endl;
          }
          if (numRows <= 0)
          {
            cout << "Invalid. Number of rows must be positive." << endl;
            isValidInt = false;
          }
        }

        isValidInt = false;
        while (!isValidInt)
        {
          cout << "Enter int for number of columns: ";
          isValidInt = getValidInput(numCols);
          if (!isValidInt)
          {
            cout << "Invalid. Input must be an integer." << endl;
          }
          if (numCols <= 0)
          {
            cout << "Invalid. Number of columns must be positive." << endl;
            isValidInt = false;
          }
        }
        //User picks rectangle color.
        string purpose = "Enter int for rectangle color: ";
        ColorClass rectColor = ColorClass();
        rectColor.chooseColor(purpose);
      
        //user decides if rectangle is filled
        isValidInt = false;
        while (!isValidInt)
        {
          minVal = 1;
          maxVal = 2;
          cout << "1. No" << endl;
          cout << "2. Yes" << endl;
          cout << "Enter int for rectangle fill option: ";

          isValidInt = getValidInput(menuChoice);
          if (!isValidInt)
          {
            cout << "Invalid input, enter the integer 1 or 2." << endl;
          }
        }
        if (menuChoice == minVal)
        {
          rectFill = false;
        }
        else if (menuChoice == maxVal)
        {
          rectFill = true;
        }

        //create a RectangleClass object with the inputs specified by user
        RectangleClass userRect = RectangleClass();
        userRect.setWithCornerAndDimensions(
          upperLeftCol,
          upperLeftRow,
          numCols,
          numRows);
        userRect.setColor(rectColor);
        image.annotateRectangle(
          userRect,
          rectFill);
      }
      //use center and extent from center
      else if (menuChoice == CENTER_AND_EXTENT)
      {
        //these determine the location of the center and the width and height
        int centerRow;
        int centerCol;
        int halfRows;
        int halfCols;

        //this determines whether it's filled
        bool rectFill;

        bool firstInputIsValid = false;
        bool secondInputIsValid = false;
        //these loops take two inputs, and finishes only when both inputs
        //are valid, to decide location of rectangle.
        while (!(firstInputIsValid && secondInputIsValid))
        {
          cout << "Enter center row and column: ";
          firstInputIsValid = getValidInput(centerRow);
          secondInputIsValid = getValidInput(centerCol);
          if ((!firstInputIsValid) || !(secondInputIsValid))
          {
            cout << "Invalid. Inputs must be integers." << endl;
          }
          
        }

        isValidInt = false;
        while (!isValidInt)
        {
          cout << "Enter int for half number of rows: ";
          isValidInt = getValidInput(halfRows);
          if (!isValidInt)
          {
            cout << "Invalid. Inputs must be integers." << endl;
          }
          if (halfRows <= 0)
          {
            cout << "Invalid. Half number of rows must be positive." << endl;
            isValidInt = false;
          }
        }

        isValidInt = false;
        while (!isValidInt)
        {
          cout << "Enter int for half number of columns: ";
          isValidInt = getValidInput(halfCols);
          if (!isValidInt)
          {
            cout << "Invalid. Inputs must be integers." << endl;
          }
          if (halfCols <= 0)
          {
            cout << "Invalid. Half number of columns must be positive" << endl;
            isValidInt = false;
          }
        }


        //User picks rectangle color.
        string purpose = "Enter int for rectangle color: ";
        ColorClass rectColor = ColorClass();
        rectColor.chooseColor(purpose);
        
        //user decides if rectangle is filled
        isValidInt = false;
        while (!isValidInt)
        {
          minVal = 1;
          maxVal = 2;
          cout << "1. No" << endl;
          cout << "2. Yes" << endl;
          cout << "Enter int for rectangle fill option: ";

          isValidInt = getValidInput(menuChoice);
          if (!isValidInt)
          {
            cout << "Invalid input, enter the integer 1 or 2." << endl;
          }
        }
        if (menuChoice == minVal)
        {
          rectFill = false;
        }
        else if (menuChoice == maxVal)
        {
          rectFill = true;
        }
        
        //Create RectangleClass object with the inputs specified
        RectangleClass userRect = RectangleClass();
        userRect.setWithCenterAndExtent(
          centerCol,
          centerRow,
          halfCols,
          halfRows);
        userRect.setColor(rectColor);
        image.annotateRectangle(
          userRect,
          rectFill);
      }
    }
    
    //annotate with pattern file
    else if (menuChoice == ANNOTATE_WITH_PATTERN)
    {  
      //upperLeftRow and upperLeftCol determine the location of the corner
      int upperLeftRow;
      int upperLeftCol;
      PatternClass userPattern = PatternClass();

      successfulRead = false;
      while (!successfulRead)
      {
        cout << "Enter string for file name containing pattern: ";
        cin >> fileName;
        successfulRead = userPattern.readPattern(fileName);
        if (!successfulRead)
        {
          cout << "Pattern file not read." << endl;
        }
      }
      

      //User picks pattern location.
      isValidInt = false;
      bool firstInputIsValid = false;
      bool secondInputIsValid = false;
      //this loop takes two inputs, and finishes only when both inputs
      //are valid, to decide location of pattern.
      while (!(firstInputIsValid && secondInputIsValid))
      {
        cout << "Enter upper left corner of pattern row and column: ";
        firstInputIsValid = getValidInput(upperLeftRow);
        secondInputIsValid = getValidInput(upperLeftCol);
        if ((!firstInputIsValid) || !(secondInputIsValid))
        {
          cout << "Invalid. Inputs must be integers." << endl;
        }
      }

      //user picks pattern color
      string purpose = "Enter int for pattern color: ";
      ColorClass patternColor = ColorClass();
      patternColor.chooseColor(purpose);

      image.annotatePattern(
        userPattern,
        upperLeftRow,
        upperLeftCol,
        patternColor);
    }
    
    //insert image, and the user can choose which color in the inserted image
    //is treated as "transparent"
    else if (menuChoice == INSERT_IMAGE)
    {
      int upperLeftRow;
      int upperLeftCol;
      ImageColorClass newImage = ImageColorClass();

      //We read in the image of choice to newImage
      successfulRead = false;
      while (!successfulRead)
      {
        cout << "Enter string for file name of PPM image to insert: ";
        cin >> fileName;
        successfulRead = newImage.readPPMFile(fileName);
        if (!successfulRead)
        {
          cout << "PPM file not read." << endl;
        }
      }
      
      //User picks image location
      isValidInt = false;
      bool firstInputIsValid = false;
      bool secondInputIsValid = false;
      while (!(firstInputIsValid && secondInputIsValid))
      {
        cout << "Enter upper left corner to insert image row and column: ";
        firstInputIsValid = getValidInput(upperLeftRow);
        secondInputIsValid = getValidInput(upperLeftCol);
        if ((!firstInputIsValid) || !(secondInputIsValid))
        {
          cout << "Invalid. Inputs must be integers." << endl;
        }
      }

      //user picks transparency color
      string purpose = "Enter int for transparency color: ";
      ColorClass transparencyColor = ColorClass();
      transparencyColor.chooseColor(purpose);
      image.annotateWithImage(
        newImage,
        upperLeftRow,
        upperLeftCol,
        transparencyColor);
      newImage.clearImage();
    }
    
    //write out current image
    else if (menuChoice == WRITE_IMAGE)
    {
      string outFileName;
      bool successfulWrite = false;
      while (!successfulWrite)
      {
        cout << "Enter string for PPM file name to output: ";
        cin >> outFileName;
	      successfulWrite = image.writePPMFile(outFileName);
        if (!successfulWrite)
        {
          cout << "PPM file not written." << endl;
        }
      }      
    }
    
    //exit program
    else if (menuChoice == EXIT)
    {
      cout << "Thank you for using this program" << endl;
      programContinues = false;
      image.clearImage();
    }
  }
}
