/*              Prog32.cpp

  Program deals with a class template which allows the user
  to dynamically create classes with arrays of any data type and size

  Also uses the destructor for the class.
  NOTE: Purposely did not check for enough memory after "new" operator
-----------------------------------------------------------------------*/
#include <iostream>
#include <new>
using namespace std;

template<class Type>
class Num
{
  private:
    Type *N;               // N points to array of given data type
    int Size;              // Size holds the number of elements in array

  public:
    Num(int X = 0)              // inline constructor with default argument
    {
      N = new(nothrow) Type[X]; // create array of given type and size
      Size = X;
    }

    Num(const Num &Y)        // inline copy constructor
    {
      N = new(nothrow) Type[Y.Size];  // create array of given type and size
      Size = Y.Size;
      for (int i = 0; i < Size; i++)
        N[i] = Y.N[i];                // copy elements to new array
    }

    ~Num()                    // inline Destructor
    {
      delete N;
    }

    void Load();           // Fills array up with user input
    void Display();        // Displays array on standard output
    Type Largest();        // Function finds and returns largest element
};
//-------------------------------  Implementation  ------------------------
template<class Type>
void Num<Type>::Load()
{
  for (int i = 0; i < Size; i++)
    cin >> N[i];
}

template<class Type>
void Num<Type>::Display()
{
  cout << endl;
  for (int i = 0; i < Size; i++)
    cout << N[i] << " ";
  cout << endl;
}

template<class Type>
Type Num<Type>::Largest()
{
  Type Max = N[0];
  for (int i = 0; i < Size; i++)
    if (N[i] > Max)
      Max = N[i];

  return Max;
}

/************************* Main *******************************************/
void main()
{
  int X;

  cout << "Enter size of arrays to deal with --> ";
  cin >> X;

  Num<int> R(X);        // integer class
  Num<char> C(X);       // character class
  Num<float> F(X);      // float class

  cout << "\nFill up int array \n";
  R.Load();
  R.Display();
  cout << "Largest element is " << R.Largest();

  cout << "\n\nFill up char array \n";
  C.Load();
  C.Display();
  cout << "Largest element is " << C.Largest();

  cout << "\n\nFill up float array \n";
  F.Load();
  F.Display();
  cout << "Largest element is " << F.Largest();
}

/******************************  Program Output  **************************
Enter size of arrays to deal with --> 3

Fill up int array
4 7 1

4 7 1
Largest element is 7

Fill up char array
f b w

f b w
Largest element is w

Fill up float array
3.5 7.6 2.4

3.5 7.6 2.4
Largest element is 7.6                  */