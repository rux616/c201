/*		   Prog30.cpp
    Deals with dynamically created memory for a class
--------------------------------------------------------------------------*/
#include <iostream>
#include <new>
using namespace std;

class Num
{
  protected:
    int *N;	           // points to an int, holds address of integer
    int Size;

  public:
    Num(int X = 5)	   // constructor , also acts as default constructor
     {
       N = new(nothrow) int[X];
       Size = X;
     }

    Num(const Num &Y)  // copy constructor,  does a deep copy
     {
       N = new(nothrow) int[Y.Size];
       Size = Y.Size;
       for (int i = 0; i < Size; i++)
	      N[i] = Y.N[i];
     }

    void Load()
     {  
       for (int i = 0; i < Size; i++)
         cin >> N[i];
     }

    void Display()
     { 
       cout << endl;
       for (int i = 0; i < Size; i++)
         cout << N[i];
       cout << endl;
     }
};

void main()
{
  Num R;	    // calls constructor, with default value
  Num S(3);	    // calls standard constructor, size of integer array is 3

  S.Load();	    // enter 2, 4, 6
  S.Display();  // contents of S.N[] displayed, 246

  Num T(S);	    // copy constructor called, does deep copy of T

  T.Display();  // contents of T.N[] displayed, 246
  S.Load();	    // enter 1, 3, 7
  T.Display();  // contents of T.N[] displayed, 246, verified deep copy

  {
    Num S(5);	   // standard constructor, size of array is 5
    S.Load();	   // enter 1,2,3,4,5 to fill up array
    int X = 3;
    cout << endl << X << endl;
    S.Display();   // contents of S.N[] displayed, 12345
  }
     // leave block automatic variables deallocated back to memory,
     // but not memory created dynamically for class, memory leak

  S.Display();    // contents of S.N[] displayed, 137
}