/*              Prog27.cpp

    Program shows the messy syntax for functions using
    reference parameters with pointers
------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

void Change(int* &, int*);       //note the messy syntax

void main()
{
  int N = 5, M = 10;
  int *P;              //pointer to an int

  P = &N;           //P has address of N or points to N

  cout << " P = " << P << endl;    //P, which has address of N, is displayed
  cout << "*P = " << *P << endl;   //what P points to is displayed, value of N
  cout << "&M = " << &M << endl;   //displays address of M

  Change(P, &M);          //pass down pointer P and address of M

  cout << "\nAfter function call\n";
  cout << " P = " << P << endl;
  cout << "*P = " << *P << endl;

}

/************************* Change ***************************************
  This function will change what the pointer T is pointing to, to that
  of the address inside X.  T corresponds to the pointer P in main, and
  X corresponds to the address of int M in main.
-------------------------------------------------------------------------*/
void Change(int* &T, int *X)
{
  T = X;
}

/***************************  Program Output  ****************************
 P = 0012FED4
*P = 5
&M = 0012FEC8

After function call
 P = 0012FEC8
*P = 10
                                                     */
