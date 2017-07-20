/*		Prog3.cpp

Action : Program has user enter a sentence terminated by a newline.
	 Program then uses a function to keep track of number of
	 punctuations, whitespaces, numbers and uppercase letters.
	 Results are then displayed on screen.

	 Int Array is used to keep track of values with the 0 subscript
	 corresponding to punctuations, 1 subscript for whitespaces,
	 2 subscript for numbers and 3 subscript for uppercase letters.
-------------------------------------------------------------------------*/
#include <iostream>
#include <ctype.h>
using namespace std;

void CheckChar(char Ch, int T[]);

void main()
{
  char Ch;
  int Total[4] = {0};   // initialize all elements to zero

  cout << "Please enter a sentence\n";
  Ch = cin.get();
  while (Ch != '\n')
   {
     CheckChar(Ch, Total);
     Ch = cin.get();
   }

  cout << "\nPunctuations = " << Total[0];
  cout << "\nWhitespaces = " << Total[1];
  cout << "\nNumbers     = " << Total[2];
  cout << "\nUppercase   = " << Total[3];

  cout << "\nPress ENTER to continue";
  cin.ignore();
}
/*************************  CheckChar  *******************************
Action : Determines if character is one looking for.
Parameters:
  In   : Ch, a character to see if one looking for
  Out  : T, an int array, each location is used as a separate counter,
	 0 subscript for punctuation, 1 for whitespace and so on.
Returns : Nothing
---------------------------------------------------------------------*/
void CheckChar(char Ch, int T[])
{
  if (ispunct(Ch))
     ++T[0];
  else if (isspace(Ch))
     ++T[1];
  else if (isdigit(Ch))
     ++T[2];
  else if (isupper(Ch))
     ++T[3];
}
/**********************  Program Output  *****************************
Please enter a sentence
This Is 345!! , and NOT?

Punctuations = 4
Whitespaces = 5
Numbers     = 3
Uppercase   = 5       */
