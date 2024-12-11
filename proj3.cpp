#include <iostream>
#include <string>
#include "constants.h"
#include "rowColumnClass.h"
#include "colorClass.h"
#include "colorImageClass.h"
#include "mainMenu.h"
#include "setColorMenu.h"

using namespace std;

//Programmer: Hao-Chun(Oscar) Shih
//Date: 2024/10/23
//Purpose: Implement manipulation on PPM image files,
//         including adding rectangles, patterns, and inserting images


int main()
{
  // Dealing with base image, if readPPM fails, shut down the program
  string inputFile;

  cout << "Enter string for PPM image file name to load: ";
  cin >> inputFile;

  // Create a boolean isValidPPM to determine shutting down or not 
  bool isValidPPM;
  ColorImageClass image;
  isValidPPM = image.readPPM(inputFile);

  if(!isValidPPM)
  {
    cin.clear();
    cin.ignore(IGNORE_LENGTH, NEW_LINE);
    return FAIL_INPUT_BOOLEAN;
  }
  // If successfully read base image, show user mainMenu options
  else
  {
    // Create boolean continueProgram for exit menu option 
    bool continueProgram = true;
    while(continueProgram)
    {
      int option;
      option = mainMenu();
      
      // Inseting Rectangle Menu
      if(option == RECTANGLE_OPTION)
      {
        // Declare integer for user input
        int rectangleMethod;
        int upperLeftRow;
        int upperLeftCol;
        int lowerRightRow;
        int lowerRightCol;
        int colorChoice;
        int fillChoice;

        // To avoid using continue, I declare a boolean to immediate back to 
        // mainMenu when invalid input occurs
        bool isValidInput = true;
        
        // If rectangleMethod is valid, go to next step
        // setting up 2 corner of rectangle. Otherwise, back to mainMenu
        while(isValidInput)
        {  
          cout << RECTANGLE_TWO_CORNER << 
          ". Specify upper left and lower right corners of rectangle" << endl;
          cout << RECTANGLE_UL_EDGE << 
          ". Specify upper left corner and dimensions of rectangle" << endl;
          cout << RECTANGLE_CENTER <<
          ". Specify extent from center of rectangle" << endl;
          cout << "Enter int for rectangle specification method: ";
          cin >> rectangleMethod;
          
          // If invalid input for rectangleMethod, clear cin buffer and 
          // print out error message
          if(cin.fail() ||
             rectangleMethod > RECTANGLE_CENTER ||
             rectangleMethod < RECTANGLE_TWO_CORNER)
          {
            cin.clear();
            cin.ignore(IGNORE_LENGTH, NEW_LINE);
            cout << "ERROR: Input number should between " << 
            RECTANGLE_TWO_CORNER << "-" << RECTANGLE_CENTER << endl;
            isValidInput = false;
          }
  
          if(rectangleMethod == RECTANGLE_TWO_CORNER)
          {
            cout << "Enter upper left corner row and column: ";
            cin >> upperLeftRow >> upperLeftCol;
            cout << "Enter lower right corner row and column: ";
            cin >> lowerRightRow >> lowerRightCol;
          }
          else if(rectangleMethod == RECTANGLE_UL_EDGE)
          {
            int numRows;
            int numCols;
            cout << "Enter upper left corner row and column: ";
            cin >> upperLeftRow >> upperLeftCol;
            cout << "Enter int for number of rows: ";
            cin >> numRows;
            cout << "Enter int for number of columns: ";
            cin >> numCols;
            
            // Derive lowerRight corner by given information  
            lowerRightRow = upperLeftRow + numRows - 1;
            lowerRightCol = upperLeftCol + numCols - 1;
          }
          else if(rectangleMethod == RECTANGLE_CENTER)
          {
            int centerRow, centerCol, halfRows, halfCols;
            cout << "Enter rectangle center row and column: ";
            cin >> centerRow >> centerCol;
            cout << "Enter int for half number of rows: ";
            cin >> halfRows;
            cout << "Enter int for half number of columns: ";
            cin >> halfCols;
            
            // Derive lowerRight corner by given information  
            upperLeftRow = centerRow - halfRows;
            upperLeftCol = centerCol - halfCols;
            lowerRightRow = centerRow + halfRows;
            lowerRightCol = centerCol + halfCols;
          }
          
          // If Color Choice is valid, go to next step, determining fill or not
          // Otherwise, back to mainMenu
          while(isValidInput)
          {
            cout << RED_OPTION << ". Red" << endl;
            cout << GREEN_OPTION << ". Green" << endl;
            cout << BLUE_OPTION << ". Blue" << endl;
            cout << BLACK_OPTION << ". Black" << endl;
            cout << WHITE_OPTION << ". White" << endl;
            cout << "Enter int for rectangle color: ";
            cin >> colorChoice;
  
            if(cin.fail() || 
               colorChoice < RED_OPTION ||
               colorChoice > WHITE_OPTION)
            {
              cin.clear();
              cin.ignore(IGNORE_LENGTH, NEW_LINE);
              cout << "ERROR: Invalid input for choosing color" << endl;
              isValidInput = false;
            }

            // If filling option is valid, go to next step:
            // Inserting rectangle on base image. Otherwise, back to mainMenu
            while(isValidInput)
            {
              bool fillOrNot;
        
              cout << NOT_FILL_OPTION << ". No" << endl;
              cout << FILL_OPTION << ". Yes" << endl;
              cout << "Enter int for rectangle fill option: ";
              cin >> fillChoice;
        
              if(cin.fail() || 
                 fillChoice < NOT_FILL_OPTION ||
                 fillChoice > FILL_OPTION)
              {
                cin.clear();
                cin.ignore(IGNORE_LENGTH, NEW_LINE);
                cout << "ERROR: Invalid input for choosing fill or not" << endl;
                isValidInput = false;
              }
            
              if(fillChoice == NOT_FILL_OPTION)
              {
                fillOrNot= false;
              }
              else if(fillChoice == FILL_OPTION)
              {
                fillOrNot = true;
              }
              
              // Create a ColorClass object for member function
              ColorClass color;
              // setColorMenu() will turn color into specified color
              // based on user choice
              setColorMenu(colorChoice, color);
              
              // I unify insertRectangle function to based soley on UL, LR
              // Even user choose different method, it'll yield same result
              RowColumnClass upperLeft(upperLeftRow, upperLeftCol);
              RowColumnClass lowerRight(lowerRightRow, lowerRightCol);
              image.insertRectangle(upperLeft, lowerRight, fillOrNot, color);
              // To end the while loop, setting isValidInput to false
              isValidInput = END_OF_WHILE_BOOL;
            }
          }
        }
      }
      
      else if(option == PATERN_OPTION)
      {
        string patternFileName;
        int startRow;
        int startCol;
        int colorChoice;
        
        cout << "Enter string for file name containing pattern: ";
        cin >> patternFileName;
        cout << "Enter upper left corner of pattern row and column: ";
        cin >> startRow >> startCol;
      
        if(cin.fail())
        {
          cin.clear();
          cin.ignore(IGNORE_LENGTH, NEW_LINE);
          cout << "ERROR: Invalid input for infomation of pattern" << endl;
        }
  
        RowColumnClass loc(startRow, startCol);

        // To avoid using continue, I declare a boolean to immediate back to 
        // mainMenu when invalid input occurs
        bool isValidInput = true;
        while(isValidInput)
        {          
          cout << RED_OPTION << ". Red\n" <<
                  GREEN_OPTION << ". Green\n" <<
                  BLUE_OPTION << ". Blue\n" <<
                  BLACK_OPTION << ". Black\n" <<
                  WHITE_OPTION << ". White" << endl;
          cout << "Enter int for pattern color: ";
          cin >> colorChoice;
          
          if(cin.fail()|| 
             colorChoice < RED_OPTION ||
             colorChoice > WHITE_OPTION)
          {
            cin.clear();
            cin.ignore(IGNORE_LENGTH, NEW_LINE);
            cout << "ERROR: Invalid input for pattern color" << endl;
            isValidInput = false;
          }

          // If pattern color option is valid, go to next step:
          // Inserting pattern on base image. Otherwise, back to mainMenu
          if(isValidInput)
          {
            ColorClass color;
            setColorMenu(colorChoice, color);
            image.insertPattern(loc, color, patternFileName);
            // To end the while loop, setting isValidInput to false
            isValidInput = END_OF_WHILE_BOOL;
          }
        }
      }
  
      else if(option == IMAGE_OPTION)
      {
        string insertFileName;
        int startRow;
        int startCol;
        int colorChoice;
  
        cout << "Enter string for file name of PPM image to insert: ";
        cin >> insertFileName;
  
        cout << "Enter upper left corner to insert image row and column: ";
        cin >> startRow >> startCol;
  
        RowColumnClass loc(startRow, startCol);

        // To avoid using continue, I declare a boolean to immediate back to 
        // mainMenu when invalid input occurs
        bool isValidInput = true;
        while(isValidInput)
        {
          cout << RED_OPTION << ". Red\n" <<
                  GREEN_OPTION << ". Green\n" <<
                  BLUE_OPTION << ". Blue\n" <<
                  BLACK_OPTION << ". Black\n" <<
                  WHITE_OPTION << ". White" << endl;
          cout << "Enter int for transparency color: ";
          cin >> colorChoice;

          if(cin.fail()|| 
             colorChoice < RED_OPTION ||
             colorChoice > WHITE_OPTION)
          {
            cin.clear();
            cin.ignore(IGNORE_LENGTH, NEW_LINE);
            cout << "ERROR: Invalid input for transparency color" << endl;
            isValidInput = false;
          }

          // If pattern color option is valid, go to next step:
          // Inserting image on base image. Otherwise, back to mainMenu
          if(isValidInput)
          {
            ColorClass color;
            setColorMenu(colorChoice, color);
      
            ColorImageClass *insertedImage = new ColorImageClass();
            insertedImage->readPPM(insertFileName);
            image.insertImage(loc, *insertedImage, color);
            delete insertedImage;
            // To end the while loop, setting isValidInput to false
            isValidInput = END_OF_WHILE_BOOL;
          }
        }
      }
  
      else if(option == SAVE_OPTION)
      {
        string outFile;
        bool fileOpensuccess = false;
        
        while(!fileOpensuccess)
        {
          cout << "Enter string for PPM file name to output: ";
          cin.ignore(IGNORE_LENGTH, NEW_LINE);
          cin >> outFile;
  
          if(cin.fail())
          {
            cin.clear();
            cin.ignore(IGNORE_LENGTH, NEW_LINE);
            cout << "ERROR: Not a valid input for outFile name: "
                 << outFile << endl;
          }
          
          // If successfully save PPM, then update fileOpensuccess to true
          fileOpensuccess = image.savePPMFile(outFile);
        }
      }
  
      else if(option == EXIT_OPTION)
      {
        cout << "Thank you for using this program" << endl;
        return false;
      }
  
      else
      {
        cin.ignore(IGNORE_LENGTH, NEW_LINE);
        cout << "ERROR: Invlaid choice input" << endl;
        cout << "Please select choice again" << endl;
      }
    }
  }
}
