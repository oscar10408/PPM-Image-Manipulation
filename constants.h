#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <string>

using namespace std;

// Programmer: Hao-Chun, Shih
// Date: 10/23/2024
// Purpose: Define all constatns for various files

// MainMenu constant:
// Minimum menu index
const int MIN_MENU_INDEX = 1;
// Maximum menu index
const int MAX_MENU_INDEX = 5;
// MainMenu options constant
const int RECTANGLE_OPTION = 1;
const int PATERN_OPTION = 2;
const int IMAGE_OPTION = 3;
const int SAVE_OPTION = 4;
const int EXIT_OPTION = 5;

// cin clear constant:
// new line constant
const char NEW_LINE = '\n';
// Ignore length
const int IGNORE_LENGTH = 200;
// Boolean for invalid input
const bool FAIL_INPUT_BOOLEAN = false;

// ColorClass constant:
// Max color value is set to 255
const int MAX_COLOR = 255;
// Min color value is set to 0
const int MIN_COLOR = 0;

// ColorImageClass constant:
// Magic number for PPM file
const string MAGIC_NUMBER = "P3";
// Determine change pattern or not 
const int DO_PATTERN = 1;
// Determine fill triangle or not
const int NOT_FILL_OPTION = 1;
const int FILL_OPTION = 2;
// Determine the method to declare rectangle
const int RECTANGLE_TWO_CORNER = 1;
const int RECTANGLE_UL_EDGE = 2;
const int RECTANGLE_CENTER = 3;

// RowColumnClass constant:
// Initial value for rows, columns
const int ROW_COL_DEFAULT_VALUE = -99999;
// Min value of rows, columns
const int ROW_COL_MINIMUM = 0;

// SetColorMenu constant:
// ColorMenu options constant
const int RED_OPTION = 1;
const int GREEN_OPTION = 2;
const int BLUE_OPTION = 3;
const int BLACK_OPTION = 4;
const int WHITE_OPTION = 5;

// project3 constant
// constant in order to end the loop
const bool END_OF_WHILE_BOOL = false;

#endif // _CONSTANTS_H_
