/*      Source file Worker5.cpp

        Shows how having a pointer as a private data member will affect
        the way the copy constructor and over loaded assignment operator
        will behave as opposed to the default ones.

        This file deals with what is called a deep copy of the members,
        where contents of what pointer is pointing to will change and
        not to where the pointer points.
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

    Worker(const Worker & W)   // Copy Constructor
     {                         // this will do a deep copy of elements
       Id = W.Id;
       Pay = new int;
       *Pay = *(W.Pay);
     }

  void GetIdPay()               // member function to get new Id and Pay
   {
     cin >> Id >> *Pay;
   }

  void ShowPay()
   {
     cout << "Pay address = " << Pay << "   Pay contents = " << *Pay << endl;
   }

  void operator=(const Worker &B)
   {
     Id = B.Id;
     *Pay = *(B.Pay);
   }  };


void main()
{
  Worker A;             // calls default contructor
  Worker B(10,150);     // calls constructor
  Worker C = B;         // calls copy constructor, could also use Worker C(B);


  cout << "A :  ";
  A.ShowPay();
  cout << "\nB :  ";
  B.ShowPay();
  cout << "\nC :  ";
  C.ShowPay();

  A = B;                  // uses the overloaded assignment operator
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

C :  Pay address = 00320FD0   Pay contents = 150

After "A = B"
A :  Pay address = 00322FA8   Pay contents = 150

enter new Id and Pay for B --> 45 250

A :  Pay address = 00322FA8   Pay contents = 150

*/