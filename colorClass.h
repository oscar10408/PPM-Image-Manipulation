#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Programmer: Hao-Chun, Shih
// Date: 10/23/2024
// Purpose: Define ColorClass for working with RGB colors, color manipulation

class ColorClass
{
  private:
    int redAmt;
    int greenAmt;
    int blueAmt;

  public:
    // Default constructor
    ColorClass();
    // Constructor with input color value
    ColorClass(int inRed, int inGreen, int inBlue);
    
    // Setting color to Black
    void setToBlack();
    // Setting color to Red
    void setToRed();
    // Setting color to Green
    void setToGreen();
    // Setting color to Blue
    void setToBlue();
    // Setting color to White
    void setToWhite();
    // Overload setTo function. For dealing with individual color value
    // instead of using ColorClass object
    bool setTo(int inRed, int inGreen, int inBlue);
    // Overload setTo function. For dealing with ColorClass object
    // instead of using individual color value
    bool setTo(ColorClass &inColor);
    // Check if the color value valid
    bool checkColorValidation();
    // Check if two ColorClass objects are same for transparency use
    bool isEqualColor(const ColorClass &rhs);
    // Save color to outFile
    bool saveColorToFile(ofstream &outFile);
    // Get color value from inFile
    bool getColorFromFile(ifstream &inFile);
};

#endif // _COLORCLASS_H_ 
