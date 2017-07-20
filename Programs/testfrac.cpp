/*       testfrac.cpp

  Program test the class Fraction that is found in file Frac1.cpp

*/
#include <iostream>
#include "Frac1.cpp"
using namespace std;

void main()
{
  Fraction F(1,2), F1(1,2), F2(2,1);

  cout << "Fraction F = ";
  F.Write();


  cout << "\nDecimal value of fraction F = " << F.Float() << endl;

  cout << "\nFraction F1 = ";
  F1.Write();

  cout << "\nFraction F2 = ";
  F2.Write();

  F = F1 * F2;

  cout << "\nafter multiply two fractions F1 and F2 = ";
  F.Write();

  cout << "\n\nComparing Fractions F1 and F2";
  if (F1 == F2)
    cout << "\nFractions are the same";
  else
    cout << "\nFractions are different";
}


/*********************  Program Output  *********************************

Fraction F = 1/2
Decimal value of fraction F = 0.5

Fraction F1 = 1/2
Fraction F2 = 2/1
after multiply two fractions F1 and F2 = 1/1

Comparing Fractions F1 and F2
Fractions are different

*/