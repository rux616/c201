/*      Source Date3.cpp

        Program shows how to overload the insertion, <<, and
        extraction, >>, operators, using the class Date.
-------------------------------------------------------------------------*/
#include <iostream>
using namespace std;
class Date
{
        // overload insertion operator
  friend ostream& operator<<(ostream& Out , const Date& X);

         // overload extraction operator
  friend istream& operator>>(istream& In, Date& Y);

  private:
     int Month;
     int Day;
     int Year;
   public:
     Date(int = 7, int = 4, int = 96);     // constructor
};

// overloaded insertion operator function
ostream& operator<<(ostream& Out, const Date& X)
{
  Out << X.Month << '/' << X.Day << '/' << X.Year;

  return Out;
}

// overloaded extraction operator function
istream& operator>>(istream& In, Date& Y)
{
  In >> Y.Month;          // accept the month part
  In.ignore(1);           // ignore 1 character, the '/' character
  In >> Y.Day;            // get the day part
  In.ignore(1);           // ignore 1 character, the '/' character
  In >> Y.Year;           // get the year part

  return In;
}

Date::Date(int mm, int dd, int yy)   // constructor
{
  Month = mm;     Day = dd;     Year = yy;
}

void main()
{
  Date A;      

  cout << "Enter a date: ";
  cin  >> A;                                 // accept the date using cin
  cout << "The date just entered is " << A;  // display date using cout
}
/************************   Program output  *****************************
Enter a date: 7/13/99
The date just entered is 7/13/99                       */