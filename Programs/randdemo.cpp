/*	randdemo.cpp

This program shows the use of rand() and srand(), which are generic C++ functions that 
deal with creating random numbers.  These functions are available in stdlib.h and 
are in all versions of C++ including C.
------------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>		//needed for call to rand() and srand()
#include <time.h>		//needed for call to time() function 
using namespace std;

void main()
{
  const LARGEST_RAND_GENERATED = 100;	//this is the largest random number
  const HOW_MANY = 15;                  // display 15 random numbers

  cout << "\nBefore calling srand(), rand() generates: \n\n";
  
  for (int N = 1; N <= HOW_MANY; ++N)
    cout << setw(4) << rand()%LARGEST_RAND_GENERATED;

  cout << "\n-------------------------------------------------------------\n";

  srand(time(NULL));        //seed random number generator

  cout << "\n\nAfter calling srand(), rand() generates: \n\n";

  for (N = 1; N <= HOW_MANY; ++N)
    cout << setw(4) << rand()%LARGEST_RAND_GENERATED;

  cout << "\n=============================================================\n";
}

/*********************  Output from 2 separate runs  ******************************

Before calling srand(), rand() generates:

  41  67  34   0  69  24  78  58  62  64   5  45  81  27  61
-------------------------------------------------------------


After calling srand(), rand() generates:

   4  52  71  42  52  15   9  56  40  74  75  56  47  74  19
=============================================================




Before calling srand(), rand() generates:

  41  67  34   0  69  24  78  58  62  64   5  45  81  27  61
-------------------------------------------------------------


After calling srand(), rand() generates:

  96  16  81  53  88  16  36  87  84  86  48  55  20  68  36
=============================================================             */