/*   Source file  Date2.cpp

     Program overloads the assignment operator and uses the "this" pointer
-------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

class Date
{
  private:
    int Month, Day, Year;

  public:
    Date(int = 7, int = 4, int = 96);     // constructor
    Date& operator=(const Date&);        // define assignment of a date
    void Showdate(void);                // member function to display a date
};

Date::Date(int mm, int dd, int yy)
{
  Month = mm;
  Day = dd;
  Year = yy;
}

Date& Date::operator=(const Date& Newdate)
{
  Day = Newdate.Day;       // assign the day
  Month = Newdate.Month;   // assign the month
  Year = Newdate.Year;     // assign the year

  return *this;
}

void Date::Showdate(void)
{
  cout << Month << '/' << Day << '/' << Year << endl;
}

//*****************************  Main  ********************************
void main()
{
  Date a(4,1,97), b(12,18,98), c(1,1,99); // declare three objects

  cout << "Before assignment a's date value is ";
  a.Showdate();
  cout << "Before assignment b's date value is ";
  b.Showdate();
  cout << "Before assignment c's date value is ";
  c.Showdate();

  a = b = c;     // multiple assignment

  cout << "\nAfter assignment a's date value is ";
  a.Showdate();
  cout << "After assignment b's date value is ";
  b.Showdate();
  cout << "After assignment c's date value is ";
  c.Showdate();
}
/**********************  Program Output ****************************
Before assignment a's date value is 4/1/97
Before assignment b's date value is 12/18/98
Before assignment c's date value is 1/1/99

After assignment a's date value is 1/1/99
After assignment b's date value is 1/1/99
After assignment c's date value is 1/1/99  */