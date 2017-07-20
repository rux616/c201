/*              Prog25.cpp

  A short program that demonstrates C++ support for dynamic arrays
  i.e., arrays whose size is determined at run-time.
-----------------------------------------------------------------------*/
#include <iostream>
#include <new>			//needed for the "nothrow" exception below
using namespace std;

int main()
{
  unsigned ArraySize;

  cout << "How big an array would you like? ";
  cin >> ArraySize;

  int *A;             //declare a pointer to int

  A = new(nothrow) int[ArraySize];    //create new array of integers
                                      //nothrow causes no exceptions to occur
                                      //if not enough memory, and then 
                                      //assigns NULL to the pointer

  if ( A != NULL )
     cout << "The array has been created.\n";
  else
    {
      cerr << "ERROR trying to allocate memory for array of length "
	   << ArraySize << "\n now exiting .. \n";
      return 1;
    }

  //The program could now use and fill up the array and do something
  //interesting with it.  When array is no longer needed, the next line
  //would be used to deallocate the storage.

  delete[] A;  //return storage when no longer needed.  The brackets
	      //are not required for arrays of built-in type, but
	      //are nonetheless suggested in the Turbo manual.

  return 0;
}
/**************************  Program Comments  **************************
1) Dynamic arrays are useful in situations where the programmer cannot
   predict in advance how large an array might be needed.  As an example,
   consider a function that needs to declare an array as a local variable.
   One way to handle this situation is to declare the array as follows:
   "char A[ARRAY_SIZE];", where ARRAY_SIZE is an external constant.  However,
   with this approach, the function is no longer self-contained, and worse, it
   only works for one particular size array.  A better solution would be to
   compute the length of the needed array and then make an appropriate call
   to new.

2) In the case of the simple demo program above, the call to delete is not
   needed, since storage is deallocated automatically when main terminates

   However, in general, it is VERY important to remember to use delete to
   return unneeded storage to the heap.  If storage is not deallocated, the
   resulting "memory leak" may eventually cause the program to fail.  */