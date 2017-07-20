/*              Prog12.cpp

 Shows how C and C++ programs access information supplied by the user
 via command line arguments.  In this case, the user invokes the program
 and supplies additional arguments that are simply echoed to the screen.
 For example,if this program is invoked via

       prog12 first second third

 then the program output would be:

      argv[1] = first
      argv[2] = second
      argv[3] = third

   Note that argv[0] is the command used to run this program, presumably
   "prog12".                                                              */

//**************************  main   *************************************

#include <iostream>
using namespace std;

int main (int argc, char* argv[])     //  Allows command line args
{
  const ERROR = 1;                    //  Used to signal user error.

  if ( argc == 1 )                    //  No command line parameters.
    {
    cout << "No command line args provided for '" << argv[0] << "'";
    return ERROR;
    }
  else
    {
    for (int N = 1; N < argc; N++)
      cout << "\n argv[" << N << "] = '" << argv[N] << "'";

    return !ERROR;
    }
}


/*********************   program notes    *****************************


1)  This program shows how a user can invoke a program and at the same time
    pass information to the program.

2)  The declaration in the header of main "char* argv[]" says that argv is a
    an array of pointers, each of which points at a string.  Thus, argv[0],
    argv[1], .. are  each strings.  Since a string is an array of char,
    argv[K] is, in fact, an address holding the start of the string.

    Note that to reference the first character of argv[1], one would use the
    symbol "argv[1][0]".

3)  argc contains the number of command line arguments.  This is always at
    least 1, since the invoking command, argv[0], is counted as one of the
    command line arguments.                                               */