/*      Source  TestStr.cpp

        Program will test member functions in string2.cpp
        which is enhanced version of the String class
--------------------------------------------------------------------*/
#include "string2.cpp"

void main()
{
  String S1, S2;    //calls default constructor, both initialized to null

  String S3 = "ABC";        // calls contructor, declare and initialize
  String S4("123");


  S1 = S2 = "Hello";      // test assignment operator

  cout << "S1 = " << S1 << endl;       // test insertion operator
  cout << "S2 = " << S2 << endl;
  cout << "S3 = " << S3 << endl;
  cout << "S4 = " << S4 << endl;

  cout << "\nPlease enter a word --> ";
  cin >> S1;                              // test extraction operator

  cout << "\nYou entered \"" << S1 << "\"" << " for S1\n";

  if (S1 == S2)
    cout << "\nS1 and S2 are the same\n";
  else
    cout << "\nS1 and S2 are different\n";

  S1 = S1 + "there";
  cout << "S1 = " << S1 << endl;

  if (S1 < S2)
    cout << "S1 is less then S2\n";
  else
    cout << "S2 is less than S1\n";

}

/************************  Program  output  *************************
S1 = Hello
S2 = Hello
S3 = ABC
S4 = 123

Please enter a word --> good
You entered "good" for S1

S1 and S2 are different
S1 = goodthere
S2 is less than S1

*/