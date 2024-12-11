#include "colorClass.h"
#include "constants.h"
#include <iostream>
#include <sstream>


using namespace std;

// Author: Hao-Chun, Shih
// Date: 10/23/2024
// Purpose: Define ColorClass for working with RGB colors, color manipulation


ColorClass::ColorClass()
{
  redAmt = MAX_COLOR;
  greenAmt = MAX_COLOR;
  blueAmt = MAX_COLOR;
}

ColorClass::ColorClass(int inRed, int inGreen, int inBlue)
{
  redAmt = inRed;
  greenAmt = inGreen;
  blueAmt = inBlue;
}

void ColorClass::setToBlack()
{
  redAmt = MIN_COLOR;
  greenAmt = MIN_COLOR;
  blueAmt = MIN_COLOR;
}

void ColorClass::setToRed()
{
  redAmt = MAX_COLOR;
  greenAmt = MIN_COLOR;
  blueAmt = MIN_COLOR;
}

void ColorClass::setToGreen()
{
  redAmt = MIN_COLOR;
  greenAmt = MAX_COLOR;
  blueAmt = MIN_COLOR;
}

void ColorClass::setToBlue()
{
  redAmt = MIN_COLOR;
  greenAmt = MIN_COLOR;
  blueAmt = MAX_COLOR;
}

void ColorClass::setToWhite()
{
  redAmt = MAX_COLOR;
  greenAmt = MAX_COLOR;
  blueAmt = MAX_COLOR;
}

bool ColorClass::setTo(int inRed, int inGreen, int inBlue)
{
    bool isValid;

    redAmt = inRed;
    greenAmt = inGreen;
    blueAmt = inBlue;
    isValid = checkColorValidation();
    
    return isValid;
}

bool ColorClass::setTo(ColorClass &inColor)
{
  bool isValid;

  redAmt = inColor.redAmt;
  greenAmt = inColor.greenAmt;
  blueAmt = inColor.blueAmt;
  isValid = checkColorValidation();
  
  return isValid;
}

bool ColorClass::checkColorValidation()
{
  bool isValid = true;

  if(redAmt > MAX_COLOR || redAmt < MIN_COLOR)
  {
    isValid = false;
    cout << "ERROR: Invalid value for the red color" << endl;
    return isValid;
  }
  else if(greenAmt > MAX_COLOR || greenAmt < MIN_COLOR)
  {
    isValid = false;
    cout << "ERROR: Invalid value for the green color" << endl;
    return isValid;
  }
  else if(blueAmt > MAX_COLOR || blueAmt < MIN_COLOR)
  {
    isValid = false;
    cout << "ERROR: Invalid value for the blue color" << endl;
    return isValid;
  }

  return isValid;
}

bool ColorClass::isEqualColor(const ColorClass &rhs)
{
  if(redAmt == rhs.redAmt && 
     greenAmt == rhs.greenAmt && 
     blueAmt == rhs.blueAmt)
  {
    return true;
  }

  return false;
}

bool ColorClass::saveColorToFile(ofstream &outFile) 
{
  if(outFile << redAmt << " " << greenAmt << " " << blueAmt << " ") 
  {
    return true;
  }
  else 
  {
    return FAIL_INPUT_BOOLEAN;
  }
}

bool ColorClass::getColorFromFile(ifstream &inFile)
{
  // Check if RGB value is valid 
  string redStr;
  string greenStr;
  string blueStr;
  int intRed;
  int intGreen;
  int intBlue;
  
  string tempString;
  istringstream iss;
   
  // If inFile cannot successfully parsing in 3 RGB value, meaning that
  // it reaches the end of file before required amount of data
  if(!(inFile >> redStr >> greenStr >> blueStr))
  {
    cout << "ERROR: End of file before reading all pixels" << endl;
    return FAIL_INPUT_BOOLEAN;
  }

  // Similarly, try to make sure PPM content is integer
  tempString = redStr + " " + greenStr + " " + blueStr;
  iss.str(tempString);
  iss >> intRed >> intGreen >> intBlue;  
   
  if(iss.fail() || !iss.eof())
  {
    cout << "ERROR: Non-numerical values in PPM pizel value" << endl;
    return FAIL_INPUT_BOOLEAN;
  }
  
  // Create a ColorClass object to check color value valid or not
  ColorClass tempColor(intRed,intGreen, intBlue);

  if(!tempColor.checkColorValidation())
  {
    return FAIL_INPUT_BOOLEAN;
  }

  this->setTo(intRed, intGreen, intBlue);

  return true;
}

