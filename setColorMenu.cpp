#include "colorClass.h"
#include "setColorMenu.h"
#include "constants.h"

using namespace std;

//Programmer: Hao-Chun(Oscar) Shih
//Date: 2024/10/23
//Purpose: Display the color setting menu and decide which color to use


void setColorMenu(const int choice, ColorClass &color)
{
  if(choice == RED_OPTION)
  {
    color.setToRed();
  }
  else if(choice == GREEN_OPTION)
  {
    color.setToGreen();
  }
  else if(choice == BLUE_OPTION)
  {
    color.setToBlue();
  }
  else if(choice == BLACK_OPTION)
  {
    color.setToBlack();
  }
  else if(choice == WHITE_OPTION)
  {
    color.setToWhite();
  }
}
