#include "rowColumnClass.h"
#include "constants.h"
#include <iostream>

using namespace std;

// Author: Hao-Chun, Shih
// Date: 10/23/2024
// Purpose: Define the RowColumnClass, representing a pixel at a 
//          specific matrix position.


RowColumnClass::RowColumnClass()
{
  rowIndex = ROW_COL_DEFAULT_VALUE;
  colIndex = ROW_COL_DEFAULT_VALUE;
};

RowColumnClass::RowColumnClass(int inRow, int inCol)
{
  rowIndex = inRow;
  colIndex = inCol;
};

void RowColumnClass::setRowCol(int inRow, int inCol)
{
  rowIndex = inRow;
  colIndex = inCol;
};

void RowColumnClass::setRow(int inRow)
{
  rowIndex = inRow;
};

void RowColumnClass::setCol(int inCol)
{
  colIndex = inCol;
};

int RowColumnClass::getRow()
{
  return rowIndex;
};

int RowColumnClass::getCol()
{
  return colIndex;
};

void RowColumnClass::printRowCol()
{
  cout << "[" << rowIndex << "," << colIndex << "]";
};

