/*----------------------------------------------------------------------

   SOURCE:     TestFr2.CPP

   ACTION:     Provides a partial test of the new member functions in the
               enhanced Fraction class (defined in Frac2.cpp).

-------------------------------------------------------------------------*/
#include <iostream>
#include "Frac2.cpp"
using namespace std;

void main()
{
  cout << "Declaring 'Fraction F1(1, 6);' and 'Fraction F2(1, 3);' \n\n";

  Fraction F1(1, 6);
  Fraction F2(1, 3);

  cout << "F1 = " << F1 << ", F2 = " << F2 << "\n\n";

  cout << F1 << " + " << F2 << " = " << F1 + F2 << "\n\n";

  cout << F1 << " * 10 = " << F1 * 10 << "\n\n";

  cout << "10 * " << F1 << " = " << 10 * F1 << "\n\n";

}

/*------------------  program output  -------------------------------

Declaring 'Fraction F1(1, 6);' and 'Fraction F2(1, 3);'

F1 = 1/6, F2 = 1/3

1/6 + 1/3 = 1/2

1/6 * 10 = 5/3

10 * 1/6 = 5/3                                                         */