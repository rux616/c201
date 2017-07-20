/*    		Prog24.cpp

      Program shows small example of use of constructors and how to call
      constructors.
-------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

class Numbers
 {
   private:                  // data only accessible through member functions
    int A;
    int B;

   public:
    void Write();            // will display private data to screen
    void Get_A();            // loads private data A
    void Get_B();            // loads private data B
    Numbers(int X, int Y);   // constructor to initialize both private data
    Numbers(int X);          // constructor to initialize only one private
    Numbers();               // default contructor
 };

//     End of Specification for Numbers Class
//------------------------------------------------------------------------

void main()
{
  Numbers N, R(10,5), X(25);

  cout << "Values for N before assigning values";
  N.Write();

  cout << "\nEnter number --> ";
  N.Get_A();
  cout << "Enter next number --> ";
  N.Get_B();

  cout << "\nValues just entered are";
  N.Write();

  cout << "\nValues for R are";
  R.Write();

  cout << "\nValues for X are";
  X.Write();

}











//**************************************************************************
//      Implementation for numbers class

void Numbers::Write()
{
  cout << "\nA = " << A << "\nB = " << B << endl;
}

void Numbers::Get_A()
{
  cin >> A;
}

void Numbers::Get_B()
{
  cin >> B;
}

Numbers::Numbers(int X, int Y)
{
  A = X;
  B = Y;
}

Numbers::Numbers(int X)
{
  B = X;
}

Numbers::Numbers()
{
  A = 0;
  B = 0;
}

/******************  Program Output  ********************************
Values for N before assigning values
A = 0
B = 0

Enter number --> 6
Enter next number --> 7

Values just entered are
A = 6
B = 7

Values for R are
A = 10
B = 5

Values for X are
A = 1356        // note this is just a garbage value for A
B = 25               */