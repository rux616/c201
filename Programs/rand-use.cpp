/*========================================================================

SOURCE FILE:  Rand-Use.cpp

DESCRIPTION:  A simple program that shows one way to setup "includes" to
              use a programmer defined module.

NOTES:        This way of setting up the includes works only if a
              programmer has access to the source code.

              The usual includes, such as "#include <iostream>"
              rely on the fact that standard library files are
              precompiled and automatically linked to main().
------------------------------------------------------------------------*/
#include <iostream>     // Look in "standard" head file location
#include <iomanip>      // for standard library files.

#include "random1.cpp"    // Look in current directory for header file.
using namespace std;

void main()
{
  cout << "Before Randomize() is called:" << endl;
  for ( int N = 1;  N <= 10;  ++N )
    cout << "Random number " << setw(2) << N << " = " << Random() << endl;
  
  cout << endl << endl;
  cout << "After Randomize() is called:" << endl;
  Randomize();
  for ( int N = 1;  N <= 10;  ++N )
    cout << "Random number " << setw(2) << N << " = " << Random() << endl;
}

/*************************** program output  **************************
   RUN #1                                 RUN #2
Before Randomize() is called:   Before Randomize() is called:
Random number  1 = 13849        Random number  1 = 13849
Random number  2 = 48742        Random number  2 = 48742
Random number  3 = 31223        Random number  3 = 31223
Random number  4 = 17180        Random number  4 = 17180
Random number  5 = 13925        Random number  5 = 13925
Random number  6 = 61346        Random number  6 = 61346
Random number  7 = 51939        Random number  7 = 51939
Random number  8 = 31096        Random number  8 = 31096
Random number  9 = 31473        Random number  9 = 31473
Random number 10 = 18974        Random number 10 = 18974


After Randomize() is called:   After Randomize() is called:
Random number  1 = 65028       Random number  1 = 26855
Random number  2 = 5485        Random number  2 = 30924
Random number  3 = 3402        Random number  3 = 27093
Random number  4 = 62379       Random number  4 = 58322
Random number  5 = 37856       Random number  5 = 16083
Random number  6 = 3961        Random number  6 = 55336
Random number  7 = 43846       Random number  7 = 19297
Random number  8 = 57431       Random number  8 = 24398
Random number  9 = 252         Random number  9 = 46847
Random number 10 = 453         Random number 10 = 38596             */