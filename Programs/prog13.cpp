/*              Prog13.cpp

  Small program showing how to use command line arguments.
  Program will display numbers 1 to 25 in columns, the number of
  columns will be the second argument and the field width will be
  the third argument.
--------------------------------------------------------------------*/
#include <iostream>
#include <iomanip>
using namespace std;

void main (int argc, char* argv[])		//  Allows command line args
{
  int Columns, FW;   // FW is the fieldwidth for display

  if ( argc == 3 )						// if two command line arguments
    {
     Columns = int(argv[1][0]) - '0';   //extract char and convert to int
     FW = int(argv[2][0]) - '0';

     for (int i = 1; i <= 25; i++)
       {
	 cout << setiosflags(ios::right) << setw(FW) << i;

	 if (i % Columns == 0)
	   cout << endl;
       }
    }
}

/***********************  Program Output  *******************************

C:\>prog13 5 8
       1       2       3       4       5
       6       7       8       9      10
      11      12      13      14      15
      16      17      18      19      20
      21      22      23      24      25

*************************  Program Comments  ******************************

1)  The first command line argument is always the program name, here it is
    prog13.

2)  The second command line argument, even though typed in as a number six,
    is actually stored in an pointer to char, hence it is a string.  In order
    to actually use the number six, have to convert from char to int, which
    is why '0' is subtracted, which is ASCII 48.

3)  Also use setiosflags(ios::right) to make the output appear in the right
    side of the columns.  */
