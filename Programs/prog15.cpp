/*              Prog15.cpp

  Program that shows how enumerated data types work
---------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

void main()
{
  enum Material { Straw = 1, Wood = 2, Brick = 3 };
       //data type of Material, with constants or values of Straw, Wood, Brick

  enum { MAX = 5 };   //No data type given, but yet constant is MAX value of 5

  int C[MAX] = {1,2,3,4,5};

  Material House;      // variable House of type Material
  int Answer;

  cout << "Enter number type of material ==> ";
  cin >> Answer;

  House = Material(Answer);    // convert int to type Material

  if (House == Straw)
     cout << "The Wolf Huffed and Puffed and blew the house down!";
  else if (House == Wood)
     cout << "The Wolf Huffed and Puffed and blew the house down!";
  else if (House == Brick)
     cout << "The Wolf couldn't blow the house down!";

  cout << "\nArray C is \n";
  for (int i = 0; i < MAX; i++)
    cout << C[i] << " ";

  cout << "\nHouse = " << int(House);

}
/*------------------------  Program Output  ---------------------------
Enter number type of material ==> 3
The Wolf couldn't blow the house down!
Array C is
1 2 3 4 5
House = 3

*************************  Program Comments  ***************************
1)  "enum" stands for enumerate, and is used for user created data types.
    An enumeration type is a type whose values are defined by a list of
    constants of type int.  An enumeration type is very much like a list
    of declared constants.

2)  If no numeric values assigned, the identifiers in enumeration type list
    are assigned consecutive values beginning with 0.

2)  "Material" is a new user created data type and has values or names of
    new types or identifiers of Straw, Wood, and Brick.  Just like "int"
    is a data type with values or identifiers of: 0, 1, 2, ... 32,767.  */