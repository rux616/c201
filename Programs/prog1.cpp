//			Prog1.cpp
//
//  Program uses function "LeftMostDigit" to find the left most digit of int

#include <iostream>
using namespace std;

int LeftMostDigit (int N);  //function prototype, required by C and C++

void main()
{
  int Number;

  cout << "This program test the function LeftMostDigit\n";
  cout << "To end program, enter 0.\n\n";
  cout << "Enter integer ==> ";
  cin >> Number;

  while (Number != 0)
    {
     cout << "The leftmost digit of " << Number << " is "
          << LeftMostDigit(Number) << endl;
     cout << "\nEnter next integer ==> ";
     cin >> Number;
    }
  cin.ignore(2);
}

/*************************** LeftMostDigit ******************************
Description : Computes and returns the leftmost digit of an int

Parameters  :
   N        : IN parameter, holds the integer whose leftmost digit
              will be returned.

Returns     : The leftmost digit of int N

Precondition: N must be non-negative
--------------------------------------------------------------------------*/
int LeftMostDigit (int N)
{
  while (N >= 10)
    N /= 10;

  return N;
}
/************************ Program Comments ******************************
1) The "prototype" of the function LeftMostDigit must come before main and
   is required in C++.  Similiar to Pascal "forward", gives compiler info
   when compiling the main function, function can now be declared after main.
   If don't use function prototype then whole function declaration must
   come before main. Standard to use prototypes in programming.

2) The actual parameter Number is passed by value to formal parameter N.  Only
   a copy is passed into function.  Destroying N does not affect Number.  */