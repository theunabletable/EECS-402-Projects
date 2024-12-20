#include <iostream>
using namespace std;

/* 
  Program of Image Classes
  EECS402 Fall 2024 Project 2
 
  Name: Andrew Jones
  Uniqname: drej
  Email: drej@umich.edu
  Student ID 8324 8056
  Date: October 7, 2024

  This program sets up the classes to describe an image. The data is kept
  in a matrix inside of ColorImageClass. The elements, or pixels of this 
  matrix are of type ColorClass, which have RGB values between 0 and 1000.
  The locations of these pixels are described with RowColumnClass objects.
*/


//These are the number of rows and columns that our ColorImageClass can have.
const int NUM_ROWS = 10;
const int NUM_COLS = 18;

//These are the minimum and maximum values for colors in ColorClass.
const int MIN_INTENSITY = 0;
const int MAX_INTENSITY = 1000;

//This is the default value for the number of rows and columns for an object of ColorImageClass 
const int DEFAULT_COORDINATE = -99999;

//This function checks if a given RowColumnClass object provides a location
//which fits inside our ColorImageClass
bool isValidLocation(
  int row,
  int col
  );



//        !!Class Declarations!!



//RowColumnClass objects are used to represent the location of a pixel
//by its row and column.
class RowColumnClass 
{
  private:
    int col;
    int row;


  public:
    //Default constructor, both values set to invalid -99999
    RowColumnClass(
      );
    //Parameterized constructor
    RowColumnClass(
      int inRow,
      int inCol
      );

    //Setters
    void setRowCol(
      int inRow,
      int inCol
      );
    void setRow(
      int inRow
      );
    
    void setCol(
      int inCol
      );


    //Getters
    int getRow(
      );
    int getCol(
      );


    //adds the row and column values of a RowColumnClass object to the row and 
    //column values of this instance of RowColumnClass
    void addRowColTo(
      RowColumnClass &inRowCol
      );

    //prints the dimensions of this RowColumnClass object
    void printRowCol(
      );
      

};


//An object of ColorClass represents a pixel of color, with an integer red,
//green, and blue value. Each value can be no smaller than MIN_INTENSITY
//and no larger than MAX_INTENSITY. If a value is too small or too large,
//it is "clipped" to MIN_INTENSITY or MAX_INTENSITY respectively.
class ColorClass
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
};


//ColorImageClass is a matrix of dimension NUM_ROWS by NUM_COLS which represents
//an image. Each cell of this matrix is occupied by a ColorClass object,
//and the locations of these cells are kept by RowColumnClass objects.
class ColorImageClass
{
  private:
    //colorGrid is the matrix which stores our pixels.
    ColorClass colorGrid[NUM_ROWS][NUM_COLS];
 
  
  public:
    //This constructor uses the below initializeTo function to set every pixel
    //to black.
    ColorImageClass(
      );
    
    //This sets the entire colorGrid to the inputted inColor.
    void initializeTo(
      ColorClass &inColor
      );

   
    //Adds each pixel from rhsImg to be added to this image in the corresponding
    //location. This function returns true if any of the additions required
    //color value clipping, otherwise it returns false.
    bool addImageTo(
      ColorImageClass &rhsImg
      );

    //This function adds the images in imagesToAdd together, and replaces
    //the pixels of this image with the sum acquired. It outputs true
    //if any clipping was required for that sum, and false otherwise.
    bool addImages(
      int numImgsToAdd,
      ColorImageClass imagesToAdd []
      );

    //This function sets the pixel at the location given by inRowCol to the 
    //color given by inColor as long as the location is valid and returns true
    //if so, but if the location is invalid, it will return false and do nothing
    //to this object.
    bool setColorAtLocation(
      RowColumnClass &inRowCol,
      ColorClass &inColor
      );
    

    //Overwrites the color value of outColor to the value contained in the pixel
    //given by inRowCol. If the location given is invalid, the function
    //returns false immediately and changes nothing. It returns true otherwise.
    bool getColorAtLocation(
      RowColumnClass &inRowCol,
      ColorClass &outColor
      );

    //Prints the color values of each pixel in the image from top left to
    //bottom right.
    void printImage();
};
//        !END OF CLASS PROTOTYPES!

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 
int main()
{
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;

  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  testImage.addImages(3, testImages);
  
  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2)
  {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  for (int rowInd = 0; rowInd < 8; rowInd += 2)
  {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  cout << "Printing entire test image:" << endl;
  testImage.printImage();

  return 0;
}
#endif 



//        !!Global function definitions!!

//This function checks if a given row and column provides a location which
//fits inside our bounds. Outputs true if so, and false otherwise.
bool isValidLocation(
  int row,
  int col
  )
{
  if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS)
  {
    return false;
  }
  else
  {
    return true;
  }
}


//        !!Class method definitions!!



//        !Definitions of RowColumnClass methods!

//default constructor which sets our row and column to DEFAULT_COORDINATE
RowColumnClass::RowColumnClass(
    )
{
  col = DEFAULT_COORDINATE;
  row = DEFAULT_COORDINATE;
}
//constructor which allows the user to initialize values
RowColumnClass::RowColumnClass(
  int inRow,
  int inCol
  )
{
  col = inCol;
  row = inRow;
}

//These functions let you set and acquire values of the matrix.
void RowColumnClass::setRowCol(
  int inRow,
  int inCol
  )
{
  col = inCol;
  row = inRow;
}

void RowColumnClass::setRow(
  int inRow
  )
{
  row = inRow;
}
    
void RowColumnClass::setCol(
  int inCol
  )
{
  col = inCol;
}

int RowColumnClass::getRow()
{
  return row;
}

int RowColumnClass::getCol()
{
  return col;
}


//adds the row and column values of a RowColumnClass object to the row and 
//column values of this instance of RowColumnClass
void RowColumnClass::addRowColTo(
  RowColumnClass &inRowCol
  )
{
  row += inRowCol.getRow();
  col += inRowCol.getCol();
}

//prints the dimensions of this RowColumnClass object
void RowColumnClass::printRowCol(
  )
{
  cout << "[" << row << "," << col << "]";
}
      

//        !Definitions of ColorClass methods!

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


//Prints the color values of this ColorClass object.
void ColorClass::printComponentValues()
{
  cout << "R: " << red << " G: " << green << " B: " << blue;
}


//        !Definitions of ColorImageClass methods!
 
//This constructor uses the below initializeTo function to set every pixel
//to black.
ColorImageClass::ColorImageClass(
     )
{
  //Dummy pixel used for our various methods
  ColorClass currentPixel;
  currentPixel.setToBlack();
  initializeTo(currentPixel);
}
    
//This sets the entire colorGrid to the inputted inColor.
void ColorImageClass::initializeTo(
  ColorClass &inColor
  )
{
  for (int i = 0; i < NUM_ROWS; i++)
  {
    for (int j = 0; j < NUM_COLS; j++)
    {
      colorGrid[i][j].setTo(inColor);
    }
  }
}


//Adds each pixel from rhsImg to be added to this image in the corresponding
//location. This function returns true if any of the additions required
//color value clipping, otherwise it returns false.
bool ColorImageClass::addImageTo(
  ColorImageClass &rhsImg
  )
{
  bool clipRequired = false;
  for (int i = 0; i < NUM_ROWS; i++)
  {
    for (int j = 0; j < NUM_COLS; j++)
    {
      if (colorGrid[i][j].addColor(rhsImg.colorGrid[i][j]))
      {
        clipRequired = true;
      }
    }
  }
  return clipRequired;
}


//This function adds the images in imagesToAdd together, and replaces
//the pixels of this image with the sum acquired. It outputs true
//if any clipping was required for that sum, and false otherwise.
bool ColorImageClass::addImages(
  int numImgsToAdd,
  ColorImageClass imagesToAdd []
  )
{
  //clipRequired is the return of the function and defaults to false, but if
  // clipping ever occurs, it is set to true
  bool clipRequired = false;
  //Dummy pixel used for our various methods
  ColorClass currentPixel;

  //We set our dummy pixel to black and us it to set our entire grid to 
  //black so that its elements can be easily replaced.
  currentPixel.setToBlack();
  initializeTo(currentPixel);

  //This loop adds the images together and stores their values in our now
  //"empty" grid, and if any clipping occurred, it sets clipRequired to true
  for (int i = 0; i < numImgsToAdd; i++)
  {
    if (addImageTo(imagesToAdd[i]))
    {
      clipRequired = true;
    }
  }
  return clipRequired;
}


//This function sets the pixel at the location given by inRowCol to the 
//color given by inColor as long as the location is valid and returns true
//if so, but if the location is invalid, it will return false and do nothing
//to this object.
bool ColorImageClass::setColorAtLocation(
  RowColumnClass &inRowCol,
  ColorClass &inColor
  )
{
  //Check if the location given by inRowCol is valid, that is, if the values
  //are non-negative, and not larger than our bounds. If not, return false
  //immediately. Otherwise, the function will later return true.
  if (!isValidLocation(inRowCol.getRow(), inRowCol.getCol()))
  {
    return false;
  }

  //row and col are the row and column coordinates specified by inRowCol.
  int row = inRowCol.getRow();
  int col = inRowCol.getCol();
  colorGrid[row][col].setTo(inColor);
  return true;
}
    

//Overwrites the color value of outColor to the value contained in the pixel
//given by inRowCol. If the location given is invalid, the function
//returns false immediately and changes nothing. It returns true otherwise.
bool ColorImageClass::getColorAtLocation(
  RowColumnClass &inRowCol,
  ColorClass &outColor
  )
{
  //Check if the location given by inRowCol is valid, that is, if the values
  //are non-negative, and not larger than our bounds. If not, return false
  //immediately. Otherwise, the function will later return true.
  if (!isValidLocation(inRowCol.getRow(), inRowCol.getCol()))
  {
    return false;
  }

  int row = inRowCol.getRow();
  int col = inRowCol.getCol();
  ColorClass inColor = colorGrid[row][col];
  outColor.setTo(inColor);

  return true;
}


//Prints the color values of each pixel in the image from top left to bottom
//right.
void ColorImageClass::printImage()
{
  for (int i = 0; i < NUM_ROWS; i++)
  {
    for (int j = 0; j < NUM_COLS; j++)
    {
      colorGrid[i][j].printComponentValues();
      if (j < NUM_COLS - 1)
      {
        cout << "--";
      }
      else
      {
        cout << endl;
      }
    }
  }
}