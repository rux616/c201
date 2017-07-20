/*          Prog26.cpp

Description :  A program that shows how different C++ is from pascal and
               most other procedural languages.  Depending on the compiler
               warnings may or may not be generated. Also shows some strange things!
***********************************************************************************/
#include <iostream>
using namespace std;

void SayHello(void)         //The two "voids" have different meanings:
{                           //  First void means non-value returning function
  cout << "\nHello! \n";    //  Second void means no parameters in list
}
                            // Function prototype of function that is never
g();                        // defined elsewhere, g returns an int by default.
                            // Empty parantheses mean different things
                            // in C and C++.  C++ means same as "void".
void main()
{
  const PI = 3.14159;       // PI is converted to 3, should use const float PI

  int i = 3, j = 7;

  int *p, q;                // Only p is a pointer to an int, q is not.

                            // Note difference in meaning of *ptr:
  int *ptr = &i;            //   This one declares ptr to be pointer to int
      *ptr = i;             //   This one says what ptr points to change to i

  cout << ptr;              // Output "0012FEC8", actual address of ptr.

  if ( 4 > i > 2 )          //Legal, but evaluates to false, ">" left to right
     cout << "4 > i > 2 ";

  char* Ptr = "Hello";      //location of * not critical in pointer declaration

  if ( Ptr == "Hello" )     // We're comparing pointers here, so there may or may
    cout << "Yes";          // not be output, this just compares memory addresses.

  SayHello;                 // Nothing happens, need "SayHello();", to work
  cout << SayHello;         // Displays address of function "SayHello"  "00419DED"

  i == 0;                   // Legal, but does nothing, value of 0.

  cout << cout << " Hi \n ";  //Output "0045768C Hi"

  cout << 'ab';               //Output " 24930"

  i = 2; j = 3;

  if ( i = 1 & j != 2 )     // Output "Yes", Bitwise comparison with "&".
     cout << "\nYes \n";

  i = j = 0;                // Works as expected, i and j set to 0.

  if ( i == j == 1 )            // Legal, but does not work as expected
    cout <<  "i == j == 1 \n";  // and outputs " i == j == 1"
                                // "==" evaluates left to right.
}