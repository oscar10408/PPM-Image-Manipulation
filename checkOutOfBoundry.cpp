#include "rowColumnClass.h"
#include "constants.h"

using namespace std;

//Programmer: Hao-Chun(Oscar) Shih
//Date: 2024/10/23
//Purpose: Check if the given corner out of the base image's boundry
//         if it is out of boundry, then return true.

bool checkOutOfBoundry(RowColumnClass upperLeft, RowColumnClass lowerRight,
                       int numRow, int numCol)
{
  bool isOutOfBound = false;
  
  if(upperLeft.getRow() < 0 || upperLeft.getRow() > numRow - 1 ||
     upperLeft.getCol() < 0 || upperLeft.getCol() > numCol - 1 ||
     lowerRight.getRow() < 0 || lowerRight.getRow() > numRow - 1 ||
     lowerRight.getCol() < 0 || lowerRight.getCol() > numCol - 1)
  {
    isOutOfBound = true;
  }

  return isOutOfBound;
}
