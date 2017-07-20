/*              Prog23.cpp

   Small program that uses a class definition to show how private and
   public members are used in a program.
-----------------------------------------------------------------------*/
#include <iostream>
using namespace std;

class DayOfYear
{
  public:
    void Input();      //get input from user to fill private data
    void Output();     //display private data to the user

    void Set(int New_Month, int New_Day);
                       // use paramaters to set private data

    int WhatMonth();   //returns corresponding month number from private data
    int WhatDay();     //returns corresponding day number from private data


  private:             //Month and Day are both private members and may be
    int Month;         //accessed or referenced only in or by a member function
    int Day;
};


int main()
{
  DayOfYear Today, Birthday;


  Today.Input();

  cout << "Todays date is ";

  Today.Output();

  Birthday.Set(9, 18);

  cout << "John's Birthday is ";

  Birthday.Output();

  if (Today.WhatMonth() == Birthday.WhatMonth() &&
      Today.WhatDay() == Birthday.WhatDay())

         cout << "Happy Birthday John!\n";

  else
         cout << "Good Day John!\n";

  return 0;
}





/***********************************************************************

Comments have purposely been left out to make program fit onto 
just 2 pages

----------------------------------------------------------------------*/

void DayOfYear::Output()
{
  cout << "month = " << Month << ", day = " << Day << endl;
}

void DayOfYear::Input()
{
  cout << "Enter the month as a number --> ";
  cin >> Month;
  cout << "Enter the day of month --> ";
  cin >> Day;
}

void DayOfYear::Set(int New_Month, int New_Day)
{
  Month = New_Month;
  Day = New_Day;
}

int DayOfYear::WhatMonth()
{
  return Month;
}

int DayOfYear::WhatDay()
{
  return Day;
}



/*****************************  Program Output  ***************************

Enter the month as a number --> 7
Enter the day of month --> 3
Todays date is month = 7, day = 3
John's Birthday is month = 9, day = 18
Good Day John!

-------------  Second run -------------------------------

Enter the month as a number --> 9
Enter the day of month --> 18
Todays date is month = 9, day = 18
John's Birthday is month = 9, day = 18
Happy Birthday John!

*/
