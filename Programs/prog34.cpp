/*              Prog34.cpp

    Deals with a base class and a derived class, both found in
    file bclass.cpp
------------------------------------------------------------------------*/
#include <iostream>
#include "bclass.cpp"
using namespace std;

void main()
{
  Person X;
  WorkPerson Y;      // WorkPerson is derived class of Person

  X.GetInfo();
  X.ShowPerson();

  Y.GetInfo();
  Y.ShowPerson();
  Y.GetWageHour();

  cout << endl;
  Y.Who();
  cout << " Gross Pay is " << Y.GrossPay() << endl;
  Y.Who();
  cout << " Net Pay is  " << Y.NetPay() << endl;
}


/*******************************  Program Output  ************************

Enter name --> Matt Holloway
Enter age --> 25
Enter Sex --> m
Enter Code Number --> 1234

Matt Holloway  25  m  1234

Enter name --> Becky
Enter age --> 24
Enter Sex --> f
Enter Code Number --> 555

Becky  24  f  555

Enter Wage --> 8
Enter Hours --> 4

Becky Gross Pay is 32
Becky Net Pay is  22.4

*/