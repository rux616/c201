/*******************************************************************
Author  :  < your name here >  and Matt Holloway
Date    :
Homework:
Compiler:  (Place Complire used here)
Source  :
Action  :  Program will read in text and keeps track of the number of
           characters, words and lines from an external file. File name
           is the second argument in command line.  Main program also
           gives the user the ability to use command line input to program.
           This will tell program what to display, i.e. display the
           number of words only, or lines or all of them.
           example at command line if this file is called "hw4.cpp":

                  hw4  filename  /options

           possible options are
                    l  : liness
                    w  : words
                    c  :characters

   NOTE : This program will only run with command line input from external
          file given on the command line.  Cannot use keyboard input with
          this program.
*********************************************************************/
#include <iostream>
#include <ctype.h>
#include <string>
#include <fstream>
using namespace std;

struct CmdLineRecord
{
   enum { MAX_NAME_LENGTH = 32 };    // Max allowable filename chars
   int SyntaxError;                  // True if user syntax is incorrect
   int WantsLineCount;               // set to true if user wants line count
   int WantsWordCount;               // set to true if user wants word count
   int WantsCharCount;               // set to true if user wants char count
};

struct CountsRecord
{
   unsigned LineCount;          // number of lines
   unsigned WordCount;          // number of words
   unsigned CharCount;          // number of characters
};

void DetermineWhatUserWants(CmdLineRecord & User, int arg, char * arv[]);
int CountLineWordChar(CountsRecord & Data, char File[]);
void ReportResults(CmdLineRecord User, const CountsRecord & Data);


int main(int argc, char * argv[])
{
   CmdLineRecord User;
   CountsRecord Data;
   int FileOpened = 1;

   DetermineWhatUserWants(User, argc, argv);
   if (!User.SyntaxError)
      FileOpened = CountLineWordChar(Data, argv[1]);

   if (FileOpened)
      ReportResults(User, Data);
   else
     cerr << "Cannot open file " << argv[1];

   return 0;
}

/**************  DetermineWhatUserWants  ****************************
Action  :  Function will determine what the user wants to have displayed
           for the count, based on command line input, i.e. does user
           want to display how many lines or words or characters or
           combination of them, or if an input error occurred. Second
           argument in command line must be the file name the third argument
           is the option of display.

           Command line options are inputed after the "/" char and are:
                c : character count
                w : word count
                l : line count

           If no options are inputed then the default of display all count
           totals is done, otherwise the option is done.  One option or two
           is permitted after the "/", illegal character option will result
           in a syntax error.

Parameters:
  Reference  :
    U        : User variable of struct type given above
  Value
    arg      : number of command line arguments
    *arv[]   : array of pointers each pointing to different argument
Returns    : nothing
Preconditions : None
=======================================================================*/
void DetermineWhatUserWants(CmdLineRecord & U, int arg, char * arv[])
{

  U.SyntaxError = 0;
  U.WantsLineCount = 0;    //initialize all wants to zero to start
  U.WantsCharCount = 0;
  U.WantsWordCount = 0;
}

/*********************  CountLineWordChar  *****************************
Action  :  Function will count the number of characters, words and lines
           in given input stream of text ended by control Z, ^Z, EOF

Parameters:
  Reference :
    Data    : variable of type struct given above
  Value
    File[]  : second command line argument that has the file to read from

Returns   : 1 if file opened, 0 if can not open file or not found

NOTE   :  Characters are everything, including newline and form feed.
          Words are delimited by whitespace characters and EOF.
          Does not take into consideration hypentation, words are composed
          numbers and letters, punctuation also included in words.

Precondition : none
=======================================================================*/
int CountLineWordChar(CountsRecord & Data, char File[])
{
   char ch;                  // current character in stream
   char NextCh;              // Next character in stream
   ifstream FileIn;          // declare FileIn to be input file

   Data.CharCount = 0;
   Data.WordCount = 0;
   Data.LineCount = 0;

   return 1;
}

/**********************  ReportResults  ********************************
Action  :  Function will display the number of words, lines or characters
           or all of them depending on what the user entered on the command
           line input.
Parameters :
  Value    : 2 value parameters, User - what to display
                                 Data - holds the number to display
Returns    : nothing
======================================================================*/
void ReportResults(CmdLineRecord User, const CountsRecord & Data)
{
  cout << "Not written yet";
}