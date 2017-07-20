/*			Prog7.cpp
   Program uses character pointers and shows that it is not possible
   to display contents of a char pointer if it points to char array.
   That is cannot display the address stored in this pointer variable
-------------------------------------------------------------------*/
#include <iostream>
using namespace std;
void main()
{
   char A[20] = "Hello there";
   char *P = A;
   char **M = &P;       // error with char **M = P;
                        // way written says M holds address of P
   
   cout << "A =     " << A << endl;
   cout << "P =     " << P << endl;
   cout << "*P =    " << *P << endl;
   cout << "*A =    " << *A << endl;
   cout << "A[0] =  " << A[0] << endl;
   cout << "P[0] =  " << P[0] << endl;
   cout << "&A[0] = " << &A[0] << endl;
   cout << "&P[0] = " << &P[0] << endl;
   cout << "&A =    " << &A << endl;
   cout << "&P =    " << &P << endl;
   cout << "&*A =   " << &*A << endl;
   cout << "&*P =   " << &*P << endl;

   cout << "M =     " << M << endl;    //displays contents of M which is
                                       // address of P
   cout << "*M =    " << *M << endl;
   cout << "**M =   " << **M << endl;
   cout << "*M[0] = " << *M[0] << endl;
   cout << "M[0] =  " << M[0] << endl;
   cout << "&M[0] = " << &M[0] << endl;
   cout << "&*M =   " << &*M << endl;

   cout << "int(*M) " << hex << long(*M);
}
/**********************  Program Output  *****************************
A =     Hello there
P =     Hello there
*P =    H
*A =    H
A[0] =  H
P[0] =  H
&A[0] = Hello there
&P[0] = Hello there
&A =    0x16f4ffe0
&P =    0x16f4fff4
&*A =   Hello there
&*P =   Hello there
M =     0x16f4fff4
*M =    Hello there
**M =   H
*M[0] = H
M[0] =  Hello there
&M[0] = 0x16f4fff4
&*M =   0x16f4fff4
int(*M) 16f4ffe0      */