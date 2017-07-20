/*              Prog6.cpp

  Three ways to fill character arrays or strings from keyboard.
--------------------------------------------------------------------*/
#include <iostream>
using namespace std;

void main()
{
  const int Size = 50;
  char S1[Size], S2[Size], S3[Size];

  cout << "Enter first sentence ==> ";
  cin >> S1;
  cout << "First sentence = " << "\"" << S1 << "\"" << endl;

/*-------------------- First Output ------------------------------------
Enter first sentence ==> This is Fun!
First sentence = "This"

NOTE* Using "cin >>" to read in strings will skip leading white spaces
      and stops reading when comes to a white space, a NULL terminator is
      put at the end of string and REST OF CHARACTERS LEFT IN BUFFER,
      use a cin.ignore() to empty input buffer.
------------------------------------------------------------------------*/

  cin.ignore(100,'\n');      // empties input buffer

  cout << "\nEnter second sentence ==> ";
  cin.get(S2, Size);
  cout << "Second sentence = " << "\"" << S2 << "\"" << endl;

/*------------------------ Second Output --------------------------------
Enter second sentence ==> This is Bad!
Second sentence = "This is Bad!"

NOTE* Using "cin.get(ArrayName, ArraySize)" to read strings will continue
      to read in characters and store in array until the newline is encountered
     or until ArraySize is reached. Null terminator is put at end of string
    and NEWLINE CHARACTER IS LEFT IN BUFFER, use a cin.ignore() to eat newline
--------------------------------------------------------------------------*/

  cin.ignore(100, '\n');         //empties input buffer

  cout << "\nEnter third sentence ==> ";
  cin.getline(S3, Size);
  cout << "Third sentence = " << "\"" << S3 << "\"" << endl;
}

/*----------------------  Third Output  ------------------------------------
Enter third sentence ==> This is Cool!
Third sentence = "This is Cool!"

NOTE* Using "cin.getline(ArrayName, ArraySize)" to read char arrays will
      continue to read until newline is found or until ArraySize is reached.
      Newline is removed from string and from the BUFFER and is replaced with
      NULL character.  If ArraySize is reached last character must be NULL.
--------------------------------------------------------------------------*/