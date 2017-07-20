/*        Prog33.cpp

  A programmer sometimes feels the following tension when designing a
  function:

    A)  Functions can be made more powerful by adding parameters.

    B)  On the other hand, functions are easier to use if they have as
        few parameters as possible.

  In practice, one usually favors B), as it tends to encourage logically
  coherent functions that are resuable. However, C++ has a feature that
  may allow the best of both worlds:  default parameters (arguments).

  Example:  A function that reads a string.  By default, the function
            reads at most 80 chars, but can read more if an optional
            second parameter is supplied.  Screen echo is provided by
            default, but by passing an optional third parameter, echo
            can be turned off.

            Note that if only one parameter is omitted, it is assumed
            to be the last.

= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
#include <iostream>
#include <conio.h>       // needed for nonbuffered input
using namespace std;


int GetString(char Line[],
              int  MaxChars = 80,   //  80  is the default parameter
              int  Echo     = 1);   //   1  is the default parameter

/*****************************  main  ***********************************/

int main()
{
  int LineLength;
  char Line[80];

  cout << "\nEnter string --> ";
  LineLength = GetString(Line);     // Default of MaxChars = 80 and Echo = 1

  cout << "Line = '" << Line << "'\n"
       << "Length(Line) = "  << LineLength << "\n";

  cout << "Enter string at most 10 chars long --> ";
  LineLength = GetString(Line, 10);               // MaxChars = 10, Echo = 1

  cout << "\nLine = '" << Line << "'\n"
       << "Length(Line) = "  << LineLength << "\n";

  cout << "Enter password --> ";
  LineLength = GetString(Line, 20, 0);            // MaxChars = 20, Echo = 0

  cout << "\nLine = '" << Line << "'\n"
       << "Length(Line) = "  << LineLength << "\n";
  return 0;
}
/***************************  GetString  ********************************

DESCRIPTION  Reads a string up to MaxChars characters long. The read can
             be done either with or without echo. Extra characters are
             discarded. The function will not return to the caller until
             the enter key is pressed.
PARAMETERS
  Line       The address of the array in which to store the characters.

  MaxChars   IN parameter with default value 80. No more that MaxChars
             characters will be stored in Line.

  Echo       IN parameter with a default value of 1. If non-zero, the
             characters are echoed to the screen as they are typed.
             If 0, no echo is provided.

RETURNS      The number of characters stored in Line

CALLS        _getch() in conio; does unbuffered, unechoed char input

NOTE         The prototype for this function is

             int GetString(char Line[],
                            int  MaxChars = 80,
                            int  Echo     = 1);

             C++ does not allow the default parameters to be repeated
             in the actual function definition below.

             This function can be called with the 3rd parameter omitted
             or with the 2nd and 3rd parameter omitted. It CANNOT be
             called with just the 2nd parameter omitted.
-------------------------------------------------------------------------*/
int GetString(char Line[],
              int  MaxChars,  // Note default values occur ONLY
              int  Echo)      //   in the function prototype.
{
  char Ch;
  int  L = 0;

  Ch = _getch();                        //  Read char with no echo
  while ( Ch != '\r' && L < MaxChars )  // '\r' is carriage return
    {
    if ( Echo )                         //  Provide optional echo
      cout << Ch;

    Line[L++] = Ch;                     //  Note post increment
    Ch = _getch();                      //  Read char with no echo
    }

  Line[L] = 0;                          //  Overwrite return char with nul

  while ( Ch != '\r' )                  //  User must press return key
    Ch = _getch();                      //  Don't echo discarded chars.

  if ( Echo )                           //  Echo return char as newline
    cout << '\n';

  return L;                             //  Length of string read
}