/**********************************************************************
SOURCE FILE:  TestStDy.cpp
COMPILER   :  Visual C++ .NET

DESCRIPTION:  A simple program to partially test some of the member
              functions of the class, String, a dynamically allocated
              string class. Refer to the file, stringdy.cpp for further
              details.

***********************************************************************/
#include "stringdy.cpp"

String Doubled (String S);

int main()
{
  cout << "---------  Testing member functions of class String--------\n\n";

  String S1("abc");                          // Call constructor that
  String S2 = "DEF";                         //   initializes.

  cout << "S1 = '" << S1 << "'\n"    // Test above initialization and
       << "S2 = '" << S2 << "'\n";   //   overloaded <<

  cout << "S1 + S2 = '" << (S1 + S2) << "'\n\n";    // Check + operator

  String S3, S4;                      // Should be initialized to null string.

  S4 = S3 = "g";                      // Call overloaded "=" operator.

  cout << "S3 = '" << S3 << "'\n";    // Did assignment operator work?
  cout << "S4 = '" << S4 << "'\n\n";

  String S[4]; //declare array of strings
  
  S[0] = "a";
  S[1] = "ab";
  S[2] = "abc";
  S[3] = "abcd";    

  for ( int N = 0;  N <= 3;  ++N )
    cout << "S[" << N << "] = '" << S[N] << "'\n\n";

  cout << "Length(S[1]) = " << S[1].Length() << "\n\n";

  cout << "Enter two words, both less then or equal to 3 characters => ";

  cin >> S1 >> S2;

  cout << "\n S1 = '" << S1 << "', S2 = '" << S2 << "'\n\n";

  String Str = S[3];

  cout << "Str = '" << Str << "'\n\n";

  cout << "Doubled(Str) = '" << Doubled(Str) << "'\n";

  return 0;
}

/***************************  Doubled ************************************

  A string that returns the "doubled" version of the string S. The real
  purpose, however, is to illustrate the automatic calling of class
  constructors and destructors.                                          */

String Doubled (String S)     // Copy constructor called to make copy of S
{
  String S1 = S;              // Copy constructor called to make copy of S1

  S1 = S1 + S1;               // Overloaded assigment operator called

  return S1;                  // Copy constructor called to make copy of S1

}                             // Destructor called to deallocate storage
                              //   created by copy constructor.


/***********************   program output  ****************************
---------  Testing member functions of class String--------

S1 = 'abc'
S2 = 'DEF'
S1 + S2 = 'abcDEF'

S3 = 'g'
S4 = 'g'

S[0] = 'a'

S[1] = 'ab'

S[2] = 'abc'

S[3] = 'abcd'

Length(S[1]) = 2

Enter two words, both less then or equal to 3 characters => the cat

 S1 = 'the', S2 = 'cat'

Str = 'abcd'

Doubled(Str) = 'abcdabcd'                      */