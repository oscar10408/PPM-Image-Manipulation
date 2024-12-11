#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

using namespace std;

// Programmer: Hao-Chun, Shih
// Date: 10/23/2024
// Purpose: Define the RowColumnClass, representing a pixel at a 
//          specific matrix position.

class RowColumnClass
{
  private:
    int rowIndex;
    int colIndex;

  public: 
    // Default Constructor, setting color to black
    RowColumnClass();
    // Constructor with input row, column value
    RowColumnClass(int inRow, int inCol);
    
    // Setting Row and Column
    void setRowCol(int inRow, int inCol);
    // Setting Row
    void setRow(int inRow);
    // Setting Column
    void setCol(int inCol);
    // Getting Row
    int getRow();
    // Getting Col
    int getCol();
    // Print out the row, and column.
    void printRowCol();
};

#endif // _ROWCOLUMNCLASS_H_ 
