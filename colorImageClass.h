#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

#include <iostream>
#include <string>
#include <fstream>
#include "colorClass.h"
#include "rowColumnClass.h"

using namespace std;

// Programmer: Hao-Chun, Shih
// Date: 10/23/2024
// Purpose: Define ColorImageClass for dynamic allocate 2D array and perform 
//          some insertion on base image, such as inserting rectangle, 
//          pattern, and other images.

class ColorImageClass
{
  private:
    ColorClass **imageArray;
    int numCol;
    int numRow;
    int maxColorValue;

  public:
    // Default Constructor setting all pixel to black
    ColorImageClass();

    // Setting color of inColor to the location inRowCol
    void setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);
    // Changing Outcolor's color value at location inRowCol respectingly to
    // the object who call this function (if location is valid)
    void getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);
    // Read PPM file and store it into ColorImageClass
    bool readPPM(const string fileName);
    // Insert Rectangle into base image
    void insertRectangle(RowColumnClass upperLeft, RowColumnClass lowerRight,
                         bool FilledOrNot, ColorClass inColor);
    // Insert Pattern into base image
    bool insertPattern(RowColumnClass upperLeft,
                       ColorClass inColor,
                       const string &fileName);
    // Insert Image into base image
    bool insertImage(RowColumnClass upperLeft,
                     ColorImageClass inImage,
                     ColorClass inTransparency);
    // Save current image to PPM file
    bool savePPMFile(const string &fileName);

};

#endif // _COLORIMAGECLASS_H_
