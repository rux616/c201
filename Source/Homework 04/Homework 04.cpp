/*******************************************************************
Author  :  Dan Cassidy and Matt Holloway
Date    :  2014-02-17
Homework:  04
Compiler:  Microsoft Visual Studio 2013.1
Source  :  Homework 04.cpp
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
	int WantsCharCount;               // set to true if user wants char count
	int WantsLineCount;               // set to true if user wants line count
	int WantsWordCount;               // set to true if user wants word count
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

const int ERR_MISSING_FILE_NAME = 1;
const int ERR_TOO_MANY_ARGUMENTS = 2;
const int ERR_INVALID_OPTION = 3;
const int ERR_FILENAME_TOO_LONG = 4;

int main(int argc, char * argv[])
{
	CmdLineRecord User;
	CountsRecord Data;
	int FileOpened = 0;

	DetermineWhatUserWants(User, argc, argv);
	if (!User.SyntaxError)
	{
		FileOpened = CountLineWordChar(Data, argv[1]);
		if (FileOpened)
			ReportResults(User, Data);
		else
			cerr << "Cannot open file " << argv[1];
	}
	else
	{
		if (User.SyntaxError == ERR_FILENAME_TOO_LONG)
			cerr << "Filename is too long";
		else if (User.SyntaxError == ERR_INVALID_OPTION)
			cerr << "Invalid option specified";
		else if (User.SyntaxError == ERR_MISSING_FILE_NAME)
			cerr << "Missing filename";
		else if (User.SyntaxError == ERR_TOO_MANY_ARGUMENTS)
			cerr << "Too many arguments";
	}

	return User.SyntaxError;
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
	U.WantsCharCount = 0;
	U.WantsLineCount = 0;    //initialize all wants to zero to start
	U.WantsWordCount = 0;

	//check syntax of command line
	if (arg == 1)
		U.SyntaxError = ERR_MISSING_FILE_NAME;
	else if (arg == 2)
	{
		int FileNameLength = 0;
		while (arv[1][++FileNameLength]);

		if (FileNameLength > U.MAX_NAME_LENGTH)
			U.SyntaxError = ERR_FILENAME_TOO_LONG;
		else
		{
			U.WantsCharCount = 1;
			U.WantsLineCount = 1;
			U.WantsWordCount = 1;
		}
	}
	else if (arg == 3)
	{
		//parse options
		//'w', 'c', and 'l' are the only allowed characters, duplicates are ignored
		//all others throw a syntax error
		if (arv[2][0] != '/' || !arv[2][1])			//check to make sure that the / exists and is not
			U.SyntaxError = ERR_INVALID_OPTION;		//immediately followed by a null character
		else
		{
			int ErrorEncountered = 0;
			for (int i = 1; arv[2][i] && !ErrorEncountered; ++i)
			{
				if (arv[2][i] == 'c')
					U.WantsCharCount = 1;
				else if (arv[2][i] == 'l')
					U.WantsLineCount = 1;
				else if (arv[2][i] == 'w')
					U.WantsWordCount = 1;
				else
					U.SyntaxError = ERR_INVALID_OPTION;
			}
		}
	}
	else if (arg > 3)
		U.SyntaxError = ERR_TOO_MANY_ARGUMENTS;
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
	ifstream FileIn;          // declare FileIn to be input file

	int CharInLine = 0;			// used to keep track of whether the current line has characters
	int InWord = 0;				// used to keep track of whether the current ch is part of a word

	Data.CharCount = 0;
	Data.WordCount = 0;
	Data.LineCount = 0;

	FileIn.open(File);

	if (FileIn.fail())
		return 0;

	FileIn.get(ch);

	while (!FileIn.eof())
	{
		CharInLine = 1;				//Flag the current line as having characters

		if (isspace(ch))
		{
			if (InWord)
			{
				++Data.WordCount;	//When whitespace is encountered, if currently in a word,
				InWord = 0;			//increment Data.WordCount and reset the InWord flag
			}

			if (ch == '\n')
			{
				++Data.LineCount;	//When \n is encountered, increment Data.LineCount and
				CharInLine = 0;		//reset the CharInLine flag
			}
				
		}
		else if (!isspace(ch))
			InWord = 1;				//Flag that tells the loop that it is currently in a word

		++Data.CharCount;

		FileIn.get(ch);
	}

	//Increment the word count if EOF was encountered while inside a word
	if (InWord)
		++Data.WordCount;

	//Guards against some edge cases with an empty line
	if (CharInLine)
		++Data.LineCount;

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
	if (User.WantsCharCount)
		cout << "Chars = " << Data.CharCount << "\n";
	if (User.WantsLineCount)
		cout << "Lines = " << Data.LineCount << "\n";
	if (User.WantsWordCount)
		cout << "Words = " << Data.WordCount << "\n";
}

/*
PROGRAM OUTPUT

Test Case 1: Specific (Command: hw4.exe)
	Tests that the program checks syntax correctly and exits when there are insufficient arguments.
		Missing filename

Test Case 2: Specific (Command: hw4.exe supermegaholycrapohmygodwhenwillitendlongfilename)
	Tests that the program rejects overly long filenames.
		Filename is too long

Test Case 3: Specific (Command: hw4.exe words.6)
	Tests that the program exits after encountering a bad filename.
		Cannot open file words.6

Test Case 4: Specific (Command: hw4.exe words.1 /c extraneousargument)
	Tests that the program rejects extra arguments.
		Too many arguments

Test Case 5: Specific (Command: hw4.exe words.1 /)
	Tests that the program detects bad options.
		Invalid option specified

Test Case 6: Specific (Command: hw4.exe words.1 /cx)
	Tests that the program detects bad options mixed with good options.
		Invalid option specified

Test Case 7: Specific (Command: hw4.exe words.1)
	Tests that the program is counting properly using words.1.
		Chars = 12
		Lines = 1
		Words = 3

Test Case 8: Specific (Command: hw4.exe words.2)
	Tests that the program is counting properly using words.2.
		Chars = 100
		Lines = 5
		Words = 16

Test Case 9: Specific (Command: hw4.exe words.3)
	Tests that the program is counting properly using words.3.
		Chars = 0
		Lines = 0
		Words = 0

Test Case 10: Specific (Command: hw4.exe words.4)
	Tests that the program is counting properly using words.4.
		Chars = 23
		Lines = 3
		Words = 3

Test Case 11: Specific (Command: hw4.exe words.4)
	Tests that the program is counting properly using words.4.
		Chars = 355
		Lines = 6
		Words = 64

Test Case 12: Specific (Command: hw4.exe words.1 /c)
	Tests that program only displays according to the options given.
		Chars = 12

Test Case 11: Specific (Command: hw4.exe words.1 /l)
	Tests that program only displays according to the options given.
		Lines = 1

Test Case 12: Specific (Command: hw4.exe words.1 /w)
	Tests that program only displays according to the options given.
		Words = 3

Test Case 13: Specific (Command: hw4.exe words.1 /cl)
	Tests that program only displays according to the options given.
		Chars = 12
		Lines = 1

Test Case 14: Specific (Command: hw4.exe words.1 /cw)
	Tests that program only displays according to the options given.
		Chars = 12
		Words = 3

Test Case 15: Specific (Command: hw4.exe words.1 /lw)
	Tests that program only displays according to the options given.
		Lines = 1
		Words = 3

Test Case 16: Specific (Command: hw4.exe words.1 /clw)
	Tests that program only displays according to the options given.
		Chars = 12
		Lines = 1
		Words = 3

Test Case 17: Specific (Command: hw4.exe words.1 /cccc)
	Tests that the program ignores repeated option switches.
		Chars = 12

Test Case 18: Limit (Command: hw4.exe mywords.2)
	Contents of mywords.2:
		  asd  
		  

	Tests an edge case of having a blank line as the end of the file.
		Chars = 11
		Lines = 2
		Words = 1
*/