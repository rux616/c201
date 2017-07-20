/*               Prog16.cpp

    A C++ program that shows C++ handling of enumerated types
    and its type checking.
-----------------------------------------------------------------------*/

#include <iostream>
using namespace std;

void main(void)
{
  enum DayOfWeek {SUN = 1, MON, TUE, WED, THU, FRI, SAT};

  DayOfWeek  Day;
  int        N;

  cout << "Enter a number between 1 and 7 (inclusive) --> ";
  cin >> N;

  Day = DayOfWeek(N);              // Convert N to type DayOfWeek

  cout << endl << "Day #" << N << " = ";

  switch (Day)
    {
    case SUN:  cout << "Sunday";
               break;
    case MON:  cout << "Monday";
               break;
    case TUE:  cout << "Tuesday";
               break;
    case WED:  cout << "Wednesday";
               break;
    case THU:  cout << "Thursday";
	       break;
    case FRI:  cout << "Friday";
	       break;
    case SAT:  cout << "Saturday";
	       break;
    default:   cout << "User input error";
    }
  cout << endl;
}
/*********************  program notes  ***********************************

1)  In C++, the tagname for an enum type becomes a type name.  In ANSI C,
    the declaration "DayOfWeek  Day;" would have to be written as "enum DayOfWeek  Day;"

2)  The line

     Day = DayOfWeek(N);

    converts N to type DayOfWeek.  The assignment

      Day = N

    generates a warning in C++, but not in ANSI C.                     */