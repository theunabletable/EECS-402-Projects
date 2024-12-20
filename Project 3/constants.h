#ifndef _CONSTANTS_H
#define _CONSTANTS_H
/*
Andrew Jones
November 3rd, 2024
This encapsulates the necessary constants for Project 3 of EECS 402.*/
#include <string>

//these define the minimum and maximum intensity of a color value
const int MAX_INTENSITY = 255;
const int MIN_INTENSITY = 0;


//these are used in ColorClass for the chooseColor method
const int RED = 1;
const int GREEN = 2;
const int BLUE = 3;
const int BLACK = 4;
const int WHITE = 5;

//constants used for selecting options in the main menu
const int ANNOTATE_WITH_RECT = 1;
const int ANNOTATE_WITH_PATTERN = 2;
const int INSERT_IMAGE = 3;
const int WRITE_IMAGE = 4;
const int EXIT = 5;

const int CORNERS = 1;
const int CORNER_AND_DIMENSIONS = 2;
const int CENTER_AND_EXTENT = 3;

//this is used for reading a PPM file
const string MAGIC_NUMBER = "P3";

#endif