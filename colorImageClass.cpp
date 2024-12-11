#include "colorImageClass.h"
#include "rowColumnClass.h"
#include "constants.h"
#include "checkOutOfBoundry.h"
#include <iostream>
#include <sstream>


using namespace std;

// Author: Hao-Chun, Shih
// Date: 10/23/2024
// Purpose: Implement the member functions of the ColorImageClass, 
//          allowing image manipulation, drawing shapes, applying
//          patterns, inserting images, and reading/writing files.


ColorImageClass::ColorImageClass()
{
  imageArray = NULL;
}

void ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &inColor)
{
  int row = inRowCol.getRow();
  int col = inRowCol.getCol();
  imageArray[row][col].setTo(inColor);
}

void ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol,
                                         ColorClass &outColor)
{
  int row = inRowCol.getRow();
  int col = inRowCol.getCol();
  outColor.setTo(imageArray[row][col]);
}

bool ColorImageClass::readPPM(const string fileName)
{  
  // Read File:
  ifstream inFile;
  inFile.open(fileName.c_str());

  // Check the validation of opening file
  if(inFile.fail())
  {
    cout << "ERROR: Unable to read PPM file: " << fileName << endl;
    inFile.clear();
    inFile.ignore(IGNORE_LENGTH, NEW_LINE);
    inFile.close();
    return FAIL_INPUT_BOOLEAN;
  }
  
  // Magic Number:
  string magicNumberOfPPM;
  inFile >> magicNumberOfPPM;
 
  // Check the validation of magic number of PPM file
  if(magicNumberOfPPM != MAGIC_NUMBER)
  {
    cout << "ERROR: Invalid magic number of PPM file." << endl;
    inFile.clear();
    inFile.ignore(IGNORE_LENGTH, NEW_LINE);
    inFile.close();
    return FAIL_INPUT_BOOLEAN;
  }
  
  // Number of column, row, and maxColorValue :
  string colStr;
  string rowStr;
  string maxColorValueStr;
  string tempString;
  istringstream iss;
  
  // The reason why here using istringstram is that, I want to make sure
  // information of columns, rows are integer 
  inFile >> colStr >> rowStr >> maxColorValueStr;
  tempString = colStr + " " + rowStr + " " + maxColorValueStr;
  iss.str(tempString);
  iss >> numCol >> numRow >> maxColorValue;

  // Check validation of column, row number, and maxColorValue
  if (iss.fail() || !iss.eof())
  {
    cout << "ERROR: Non-numerical values in PPM header info" << endl;
    return FAIL_INPUT_BOOLEAN;
  }
  // Check columns, rows are positive
  if(numCol <= ROW_COL_MINIMUM || numRow <= ROW_COL_MINIMUM)
  {
    cout << "ERROR: Number of columns and rows should be Positive" << endl;
    return FAIL_INPUT_BOOLEAN;
  }
  // Check maxColorValue = 255, which align to project3 spec
  if(maxColorValue != MAX_COLOR)
  {
    cout << "ERROR: Max amount of color should be " << MAX_COLOR << endl;
    return FAIL_INPUT_BOOLEAN;
  }

  // After checking all potential error, we can dynamic allocate 2D-array
  imageArray = new ColorClass*[numRow];
  for(int i = 0; i < numRow; i++)
  {
    imageArray[i] = new ColorClass[numCol];
  }

  // Store value into declared 2D array
  for(int rowIdx = 0; rowIdx < numRow; rowIdx++)
  {
    for(int colIdx=0; colIdx < numCol; colIdx++)
    {
      // Create a RowColumnClass object for potential error message
      // with the use of RowColumnClass member function printRowCol()
      RowColumnClass Loc(rowIdx, colIdx);

      // Check if the color value is valid in getColorFromFile, 
      // if it is out of range, getColorFromFile() will return false, 
      // then print out location, and return false(end of reading PPM file).
      // Otherwise, it will set the color to specified location
      ColorClass tempColor;
      bool isValidColor = tempColor.getColorFromFile(inFile);

      if(!isValidColor)
      {
        cout << "Invalid color value at location: ";
        Loc.printRowCol();
        cout << endl;
        return FAIL_INPUT_BOOLEAN;
      }
      else
      {
        setColorAtLocation(Loc, tempColor);
      }
    }
  }

  string dataLeft;
  inFile >> dataLeft;
  if(!inFile.eof())
  {
    cout << "ERROR: There are extra content in .ppm file" << endl;
    return FAIL_INPUT_BOOLEAN;
  }

  return true;
}

void ColorImageClass::insertRectangle(RowColumnClass upperLeft, 
                                      RowColumnClass lowerRight,
                                      bool filledOrNot,
                                      ColorClass inColor)
{ 
  // If upperLeft corner(UL) of inserted rectangle is negative indexing:
  // turn it into 0
  // If lowerRight corner(LR) of inserted rectangle is out of image:
  // turn it into LR of base image
  int startRow = max(0, upperLeft.getRow());
  int startCol = max(0, upperLeft.getCol());
  int endRow = min(numRow - 1, lowerRight.getRow());
  int endCol = min(numCol - 1, lowerRight.getCol());

  // Determine whether to draw edge of rectangle or not
  bool drawTop = upperLeft.getRow() >= 0 && upperLeft.getRow() < numRow;
  bool drawBottom = lowerRight.getRow() >= 0 && lowerRight.getRow() < numRow;
  bool drawLeft = upperLeft.getCol() >= 0 && upperLeft.getCol() < numCol;
  bool drawRight = lowerRight.getCol() >= 0 && lowerRight.getCol() < numCol;
  
  // Equivalent to (drawTop && drawBottom && drawLeft && drawRight)
  bool isOutOfBound = checkOutOfBoundry(upperLeft, lowerRight, numRow, numCol);

  if(isOutOfBound)
  {
    cout << "WARNING: Inserted rectangle out of bound" << endl;
  }
  
  if(startRow >= endRow || startCol >= endCol)
  {
    cout << "WARNING: lowerRight and upperLeft corner are opposite" << endl;
    cout << "WARNING: There will have no rectangle be inserted" << endl;
  }

  if(filledOrNot)
  {
    for(int rowIdx = startRow; rowIdx <= endRow; rowIdx++)
    {
      for(int colIdx = startCol; colIdx <= endCol; colIdx++)
      {
        RowColumnClass loc(rowIdx, colIdx);
        setColorAtLocation(loc, inColor);
      }
    }
  }

  else
  {
    if(drawLeft)
    {
      for(int rowIdx = startRow; rowIdx <= endRow; rowIdx++)
      {
        RowColumnClass leftEdge(rowIdx, startCol);
        setColorAtLocation(leftEdge, inColor);
      }
    }
    if(drawRight)
    {
      for(int rowIdx = startRow; rowIdx <= endRow; rowIdx++)
      {
        RowColumnClass rightEdge(rowIdx, endCol);
        setColorAtLocation(rightEdge, inColor);
      }
    }
    if(drawTop)
    {
      for(int colIdx = startCol; colIdx <= endCol; colIdx++)
      {
          RowColumnClass upperEdge(startRow, colIdx);
          setColorAtLocation(upperEdge, inColor);
      }
    }
    if(drawBottom)
    {
      for(int colIdx = startCol; colIdx <= endCol; colIdx++)
        {
          RowColumnClass lowerEdge(endRow, colIdx);
          setColorAtLocation(lowerEdge, inColor);
        }
    }
  }
}

bool ColorImageClass::insertPattern(RowColumnClass upperLeft,
                                    ColorClass inColor,
                                    const string &fileName)
{
  string rowStr;
  string colStr;
  int intRow;
  int intCol;
  ifstream inFile;
  string tempString;
  istringstream iss;

  inFile.open(fileName.c_str());

  if(inFile.fail())
  {
    cout << "ERROR: Unable to open pattern file: " << fileName << endl;
    inFile.clear();
    inFile.ignore(IGNORE_LENGTH, NEW_LINE);
    inFile.close();
    return FAIL_INPUT_BOOLEAN;
  }

  // Similarly check the pattern information is integer or not
  inFile >> colStr >> rowStr;
  tempString = colStr + " " + rowStr;
  iss.str(tempString);
  iss >> intCol >> intRow;

  if (iss.fail() || !iss.eof())
  {
    cout << "ERROR - Non-numerical values in pattern file info" << endl;
    inFile.close();
    inFile.ignore(IGNORE_LENGTH, NEW_LINE);
    inFile.close();
    return FAIL_INPUT_BOOLEAN;
  }

  // Create a lowerRight corner for checking out of boundry or not
  RowColumnClass lowerRight(upperLeft.getRow() + intRow,
                            upperLeft.getCol() + intCol);

  bool isOutOfBound = checkOutOfBoundry(upperLeft, lowerRight, numRow, numCol);

  if(isOutOfBound)
  {
    cout << "WARNING: Inserted pattern out of bound" << endl;
  }

  // Insert pattern into base image
  for(int rowIdx = 0; rowIdx < intRow; rowIdx++)
  {
    for(int colIdx = 0; colIdx < intCol; colIdx++)
    {
      // Parsing 0, 1 into patternValue to determine insert or not 
      int patternValue;
      inFile >> patternValue;
      
      if(inFile.eof())
      {
        cout << "ERROR: End of file before reading all pixels" << endl;
        inFile.close();
        inFile.ignore(IGNORE_LENGTH, NEW_LINE);
        inFile.close();
        return FAIL_INPUT_BOOLEAN;
      }
      
      // Determine out of bound or not (to avoid segmentation fault)
      int patternRow = upperLeft.getRow() + rowIdx;
      int patternCol = upperLeft.getCol() + colIdx;

      // Method 1. We can change following if condition into:
      // RowColumnClass upperLeft(patternRow, patternCol)
      // if(patternValue == DO_PATTERN && 
      //    !chechOutOfBoundry(upperLeft, upperLeft, numRow, numCol))
      // But I think the following notation is clearer

      // Method 2.
      if(patternValue == DO_PATTERN &&
         patternRow >= 0 && patternRow < numRow &&
         patternCol >= 0 && patternCol < numCol)
      {
        RowColumnClass patternLocation(patternRow, patternCol);
        setColorAtLocation(patternLocation, inColor);
      }
    }
  }
  return true;
}

bool ColorImageClass::insertImage(RowColumnClass upperLeft,
                                  ColorImageClass inImage,
                                  ColorClass inTransparency)
{
  // When inserting image, it will call readPPM(), which will do numerous 
  // error checking. Therefore, I skip some error checking here such as
  // checking interger information of inserted image, etc.

  int inImageRow = inImage.numRow;
  int inImageCol = inImage.numCol;
  
  // Create a lowerRight corner for checking out of boundry or not
  RowColumnClass lowerRight(upperLeft.getRow() + inImageRow,
                            upperLeft.getCol() + inImageCol);

  bool isOutOfBound = checkOutOfBoundry(upperLeft, lowerRight, numRow, numCol);

  if(isOutOfBound)
  {
    cout << "WARNING: Inserted image out of bound" << endl;
  }

  for(int rowIdx = 0; rowIdx < inImageRow; rowIdx++)
  {
    for(int colIdx = 0; colIdx < inImageCol; colIdx++)
    {
      int imageRow = upperLeft.getRow() + rowIdx;
      int imageCol = upperLeft.getCol() + colIdx;
      
      // Similarly, we can use other method to implement if condition
      if (imageRow >= 0 && imageRow < numRow &&
          imageCol >= 0 && imageCol < numCol)
      {
        RowColumnClass loc(rowIdx, colIdx);
        ColorClass color;
        // Parsing inImage color into color object
        inImage.getColorAtLocation(loc, color);
        // Checking if inImage color equalt to specified transparent color
        // If not, insert inImage color onto base image
        if(!color.isEqualColor(inTransparency))
        {
          RowColumnClass patternLocation(imageRow, imageCol);
          setColorAtLocation(patternLocation, color);
        }
      }
      
    }
  }
  return true;
}

bool ColorImageClass::savePPMFile(const string &fileName)
{
  ofstream outFile;
  outFile.open(fileName.c_str());

  if(!outFile.is_open())
  {
    cout << "ERROR: Unable to open file: " << fileName << endl;
    return FAIL_INPUT_BOOLEAN;
  }

  // Parsing magicNumber, numCol, numRow, and maxColorValue into outputFile
  outFile << MAGIC_NUMBER << endl;
  outFile << numCol << " " << numRow << endl;
  outFile << maxColorValue << endl;
  
  for(int rowIdx = 0; rowIdx < numRow; rowIdx++)
  {
    for(int colIdx = 0; colIdx < numCol; colIdx++)
    {
      // saveColorToFile will check if successful of saving file
      // If not it will return ERROR message
      if(!imageArray[rowIdx][colIdx].saveColorToFile(outFile))
      {
        outFile.close();
        cout << "ERROR: Failed to write color into PPM file" << endl;
        cout << "At location: [" << rowIdx << ", " << colIdx << "]" << endl;
        return false;
      }
    }
  }
  outFile.close();
  return true;
}

