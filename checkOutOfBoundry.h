#ifndef _CHECKOUTOFBOUNDRY_H_
#define _CHECKOUTOFBOUNDRY_H_
#include "rowColumnClass.h"

//Programmer: Hao-Chun(Oscar) Shih
//Date: 2024/10/23
//Purpose: Check if the given corner out of the base image's boundry
//         if it is out of boundry, then return true.

bool checkOutOfBoundry(RowColumnClass upperLeft, RowColumnClass lowerRight,
                       int numRow, int numCol);

#endif //_CHECKOUTOFBOUNDRY_H_
