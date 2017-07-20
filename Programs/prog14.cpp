/*              Prog14.cpp

   Shows how to pass command line arguments to a function and how to
   reference individual characters of command line arguments.
------------------------------------------------------------------------*/
#include <iostream>
#include <string>
using namespace std;

void ShowCommandLineArgs (int ArgCount, char* Argument[]);

//**************************  main   *************************************

void main (int argc, char* argv[])     //  Allow command line args
{
  ShowCommandLineArgs (argc, argv);

}

/**********************  ShowCommandLineArgs *****************************

  Reveals some information about command line arguments that have been
  passed to main().

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void ShowCommandLineArgs (int ArgCount, char* Argument[])
{
  cout << "\nNumber of command line args: " << ArgCount
       << "\n\nHere's what you entered on the command line: \n\n";

  for ( int N = 0; N < ArgCount ; ++N )
    cout << Argument[N] << "  ";

  cout << "\n\nThe first character of argv[1] is '" << Argument[1][0] << "'"
       << "\nThe third character of argv[1] is '" << Argument[1][2]   << "'"

       << "\n\nThe length of the second argument is " << strlen(Argument[1]);
}

/*********************   program notes    *****************************
1)  Refer to prog12.cpp for introductory comments on command line args.

2)  If the user ran this program via the command, "prog14 /abc def"
    the program would output:

    Number of command line args: 3

    Here's what you entered on the command line:

    PROG14.EXE  /abd  def

    The first character of argv[1] is '/'
    The third character of argv[1] is 'b'

    The length of the second argument is 4

3)  A careful reading of the function ShowCommandLineArgs will yield
    insights into how to send command line info to a function and how
    to process command line info.   */