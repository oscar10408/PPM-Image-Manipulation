#include <iostream>
#include <string>
#include "mainMenu.h"
#include "constants.h"

using namespace std;

//Programmer: Hao-Chun(Oscar) Shih
//Date: 2024/10/23
//Purpose: Display the main menu and decide what action to do

char mainMenu()
{
  bool validInput = false;
  int option;

  while(!validInput)
  {
    cout << RECTANGLE_OPTION << ". Annotate image with rectangle" << endl;
    cout << PATERN_OPTION << ". Annotate image with pattern from file" << endl;
    cout << IMAGE_OPTION << ". Insert another image" << endl;
    cout << SAVE_OPTION << ". Write out current image" << endl;
    cout << EXIT_OPTION << ". Exit the program" << endl;
    cout << "Enter int for main menu choice: ";

    cin >> option;

    if(cin.fail() || option > MAX_MENU_INDEX || option < MIN_MENU_INDEX)
    {
      cin.clear();
      cin.ignore(IGNORE_LENGTH, NEW_LINE);
      cout << "Invalid input. Please enter number from " 
           << RECTANGLE_OPTION << "-" << EXIT_OPTION << endl;
    }
    else
    {
      validInput = true;
    }
  }
  return option;
}
