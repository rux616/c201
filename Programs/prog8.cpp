/*             Prog8.cpp

    Program uses array of pointers

  This program uses an array of pointers to hold the days of the week in it.
  A random number between 1 and 7 is chosen and then used as the subscript in
  the array of pointers, tomorrow is also found
---------------------------------------------------------------------------*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void main()
{
  char *WeekDay[8] = {"ERROR","Sunday", "Monday", "Tuesday", "Wednesday",
                      "Thursday", "Friday", "Saturday"};

  int DayNumber;

  srand(time(NULL));
  DayNumber = rand()%7 + 1;

  cout << "Today is " << WeekDay[DayNumber] << " and tomorrow is ";

  if (DayNumber == 7)
    DayNumber = 1;
  else
    DayNumber++;

  cout << WeekDay[DayNumber] << endl;

  cin.ignore(2);
}

/*------------------------  Program Output  ----------------------------

Today is Monday and tomorrow is Tuesday

*/
