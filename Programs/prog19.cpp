/*              Prog19.cpp

   This program uses structs to read in a string and then reverse the string.
   Functions are used to do this, one with a struct as a reference parameter
   the other function returns a struct. Function comments purposely left out.
----------------------------------------------------------------------------*/
#include <iostream>
#include <string>
using namespace std;

struct String
  {
    enum {MAX_LENGTH = 50};        //constant tucked inside struct
    char Ch[MAX_LENGTH];           //char array
    int Length;                    //length needed because no null terminator
  };

void ReadString(String &);            //struct as reference parameter
String ReverseString(const String);   //function returns a struct

void main()
{
  String S, Reverse;

  ReadString(S);
  Reverse = ReverseString(S);

  cout << "\nReversed string is  ==> ";
  for (int i = 0; i < Reverse.Length; i++)
    cout << Reverse.Ch[i];
}

void ReadString(String &Str)
{
  char Ch;
  int k = 0;

  cout << "Please enter string ==> ";
  cin.get(Ch);
  while ((Ch != '\n') && (k < Str.MAX_LENGTH))
    {
      Str.Ch[k++] = Ch;
      cin.get(Ch);
    }
  Str.Length = k;
}

String ReverseString(const String Str)
{
  String Rev = Str;      //copys the length to Rev

  for (int k = Str.Length-1, i = 0; k >= 0; --k, ++i)
     Rev.Ch[i] = Str.Ch[k];
  return Rev;
}
/*------------------  Program Output  -------------------------------
Please enter string ==> Hello
Reversed string is  ==> olleH
*/