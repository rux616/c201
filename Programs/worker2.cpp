/*
        Source file Worker2.cpp

        Uses member function SamePay as opposed to a friend function
        The default copy contructor is automatically called
        and overloads the assignment operator, =, in a simple fashion
*/
#include <iostream>
using namespace std;

class Worker
{
  private:
    int Id;
    int Pay;

  public:
    void ShowIdPay()
     {
       cout << "Id Number is " << Id << " Pay is " << Pay << endl;
     }

    Worker()                    //default constructor
     {
       Id = 0;
       Pay = 0;
     }

    Worker(int X, int Y)       // Contructor
     {
       Id = X;
       Pay = Y;
     }


  int SamePay(Worker B)                 // member function to determine
    {                                   // if pay is same or not
      return (Pay == B.Pay);
    }

  void GetIdPay()               // member function to get new Id and Pay
   {
     cin >> Id >> Pay;
   }

  void operator=(Worker B)      // overloads the assignment operator
   {                            // poor overload does not return anything
     Id = B.Id;                 // or allow cascading i.e. A = B = C;
     Pay = B.Pay;
   }                            // could also have used operator=(Worker &B)

};







void main()
{
  Worker A;             // calls default contructor
  Worker B(10,150);     // calls constructor
  Worker C = B;         // calls default copy constructor


  A.ShowIdPay();
  B.ShowIdPay();
  C.ShowIdPay();

  if (C.SamePay(B))           // calls the member function SamePay
    cout << "\nSame Pay\n";
  else
    cout << "\nDifferent Pay\n";

  cout << "\nenter Id number and Pay --> ";
  A.GetIdPay();
  cout << "\nA has ";
  A.ShowIdPay();

  B = A;                    // uses the overloaded assignment operator
  cout << "\nB has ";
  B.ShowIdPay();

}

/*************************  Program Output  ******************************
Id Number is 0 Pay is 0
Id Number is 10 Pay is 150
Id Number is 10 Pay is 150

Same Pay

enter Id number and Pay --> 23  145

A has Id Number is 23 Pay is 145

B has Id Number is 23 Pay is 145

*/