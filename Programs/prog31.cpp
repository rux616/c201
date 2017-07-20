/*              Prog31.cpp

  This program uses function templates
-------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

template<class DataType>
DataType Maximum(DataType A,      //NOTE, Prototypes for Function
                 DataType B);     //templates MUST have a variable name
                                  //given with parameter list, eles error.

void main()
{
   int I = 56, J = 2;
   float X = 56.78, Y = 345.67;
   char C = 'B', H = 'D';

   cout << "\nThe maximum of " << I << " and " << J << " = " << Maximum(I,J);
   cout << "\nThe maximum of " << X << " and " << Y << " = " << Maximum(X,Y);
   cout << "\nThe maximum of " << C << " and " << H << " = " << Maximum(C,H);

}
/*******************************  Maximum  *******************************
Action :  Function will return the maximum of two inputed data types
          Uses a template so function will work on any data type
-------------------------------------------------------------------------*/
template<class DataType>
DataType Maximum(DataType A, DataType B)
{
  if (A > B)
    return A;
  else
    return B;
}


/**************************  Program Output  *****************************

The maximum of 56 and 2 = 56
The maximum of 56.78 and 345.67 = 345.67
The maximum of B and D = D


---------------------------  Program Comments  ---------------------------

1)  When prototyping a function that is also a template the formal parameter
    list MUST have variable names given that match the variable names given
    where the function template is defined.  If not an error will occur.
    Note this is different from prototypes of regular functions, where no
    variable name need be given, just the data type.   */