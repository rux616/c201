/*      Source file Date1.cpp

	Shows how the special pointer variable "this" is used
	and is implicity already passed into functions.

	Each object or instance of a class has a pointer to themselves
	called "this"
----------------------------------------------------------------------*/
#include <iostream>
using namespace std;

class Date
{
  private:
     int Month;
     int Day;
     int Year;

   public:
     Date(int = 7, int = 4, int = 96);   // default constructor
     void Showdate(void);                // member function to display a Date
};

// implementation section

Date::Date(int mm, int dd, int yy)       // constructor
{                                        // Same as following
  (*this).Month = mm;                    // Month = mm;
  (*this).Day = dd;                      // Day = dd;
  (*this).Year = yy;                     // Year = yy;
}

void Date::Showdate(void)
{
  cout << (*this).Month << '/' << (*this).Day << '/' << (*this).Year << endl;
}

void main()
{
  Date A(4,1,97), B(12,18,98);     // declare two objects

  cout << "The date stored in A is originally ";
  A.Showdate();               // display the original date
  A = B;                      // assign B's value to A, default assignment op.

  cout << "After assignment the date stored in A is ";
  A.Showdate();               // display A's values

}

/****************************  Program Output  ***************************

The date stored in A is originally 4/1/97
After assignment the date stored in A is 12/18/98

*/