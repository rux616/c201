/*      Source file Worker3.cpp

        Shows how having a pointer as a private data member will affect
        the way the copy constructor and over loaded assignment operator
        will behave as opposed to the default ones.

        This file deals with using the default copy constructor
        and the default for the assignment operator.  Both of theses
        will do what is called a shallow copy of the members,
----------------------------------------------------------------------*/
#include <iostream>
using namespace std;

class Worker
{
  private:
    int Id;
    int *Pay;          // pointer to an int

  public:
    void ShowIdPay()
     {
       cout << "Id Number is " << Id << " Pay is " << *Pay << endl;
     }

    Worker()                    //default constructor
     {
       Id = 0;
       Pay = new int;          // new is used to create storage for an int
       *Pay = 0;
     }

    Worker(int X, int Y)       // Contructor
     {
       Id = X;
       Pay = new int;
       *Pay = Y;
     }

  void GetIdPay()               // member function to get new Id and Pay
   {
     cin >> Id >> *Pay;
   }

  void ShowPay()
   {
     cout << "Pay address = " << Pay << "   Pay contents = " << *Pay << endl;
   }

};









void main()
{
  Worker A;             // calls default contructor
  Worker B(10,150);     // calls constructor
  Worker C = B;         // calls default constructor


  cout << "A :  ";
  A.ShowPay();
  cout << "\nB :  ";
  B.ShowPay();
  cout << "\nC :  ";
  C.ShowPay();

  A = B;                  // uses the default operator
  cout << "\nAfter \"A = B\" ";
  cout << "\nA :  ";
  A.ShowPay();

  cout << "\nenter new Id and Pay for B --> ";
  B.GetIdPay();
  cout << "\nA :  ";
  A.ShowPay();

}

/***********************  Program Output  ******************************

A :  Pay address = 00322FA8   Pay contents = 0

B :  Pay address = 00322FD8   Pay contents = 150

C :  Pay address = 00322FD8   Pay contents = 150

After "A = B"
A :  Pay address = 00322FD8   Pay contents = 150

enter new Id and Pay for B --> 45 250

A :  Pay address = 00322FD8   Pay contents = 250

*/