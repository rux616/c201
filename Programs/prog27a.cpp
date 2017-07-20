/*              Prog27a.cpp   -- using typedef

    This program redoes prog27.cpp but uses type definitions to make program
    easier to read
--------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

typedef int* IntPtr;         // IntPtr is now like new data type

void Change(IntPtr &, IntPtr);       //note easier to read

void main()
{
  int N = 5, M = 10;
  IntPtr P;              //pointer to an int

  P = &N;           //P has address of N or points to N

  cout << " P = " << P << endl;    //P, which has address of N, is displayed
  cout << "*P = " << *P << endl;   //what P points to is displayed, value of N
  cout << "&M = " << &M << endl;   //displays address of M

  Change(P, &M);          //pass down pointer P and address of M

  cout << "\nAfter function call\n";
  cout << " P = " << P << endl;
  cout << "*P = " << *P << endl;
}

/****************************  Change  *********************************
  This function will change what the pointer T is pointing to, to that
  of the address inside X.  T corresponds to the pointer P in main, and
  X corresponds to the address of int M in main.
-------------------------------------------------------------------------*/
void Change(IntPtr &T, IntPtr X)
{
  T = X;
}

/****************************  Program Output  ****************************
 P = 0012FED4
*P = 5
&M = 0012FEC8

After function call
 P = 0012FEC8
*P = 10

===========================  Program Comments  ============================

1)  By using "typedef", programmer is able to redefine any data type name to
    whatever you want.

     ex:   typedef int integer;
           typedef double  VeryBig;

2)  "typedef" is mainly used with pointer notation though                */