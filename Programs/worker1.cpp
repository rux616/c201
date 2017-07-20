/*
        Source file Worker1.cpp

        Shows use of friend function SamePay and  copy constructor.

        Note in copy constructor a reference parameter is used when all
        really needed is a value parameter.  This is to save time if dealing
        with large classes that have a lot of data.  Won't need to make a
        copy of data, just an address is passed as parameter.  Make it a
        constant to insure no data is changed in original.
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

    Worker(const Worker & W)   // Copy Constructor
     {                         // if not given compiler uses default
       Id = W.Id;              // copy constuctor that just copies
       Pay = W.Pay;            // individual members
     }                         //
                               // Also note that would work for
                               // Worker( Worker W )

  friend int SamePay(Worker A, Worker B)   // function is a friend of Worker
    {                                      // has access to private data
      return (A.Pay == B.Pay);             // but IS NOT a member function
    }

  void GetIdPay()               // member function to get new Id and Pay
   {
     cin >> Id >> Pay;
   }
};




void main()
{
  Worker A;             // calls default contructor
  Worker B(10,150);     // calls constructor
  Worker C = B;         // calls copy constructor, could also use Worker C(B);


  A.ShowIdPay();
  B.ShowIdPay();
  C.ShowIdPay();

  if (SamePay(C, B))           // calls and uses the friend function SamePay
    cout << "\nSame Pay\n";           // friend functions sometime easier to use
  else                            // then member functions, see Worker2.cpp
    cout << "\nDifferent Pay\n";

  cout << "\nenter Id number and Pay --> ";
  A.GetIdPay();
  cout << "\nA has ";
  A.ShowIdPay();

  B = A;                    // uses the default assignment operator
  cout << "\nB has ";
  B.ShowIdPay();

}

/***********************  Program Output  ******************************

Id Number is 0 Pay is 0
Id Number is 10 Pay is 150
Id Number is 10 Pay is 150

Same Pay

enter Id number and Pay --> 23  145

A has Id Number is 23 Pay is 145

B has Id Number is 23 Pay is 145

*/
