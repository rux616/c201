/*			Prog21.cpp
Action  :  Program will make a copy of one file and store it in
           another.  User types in both file names from keyboard.
------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ifstream Old;
  ofstream New;
  char OldName[20];
  char NewName[20];
  char Error[] = "*** Error in opening file *** ";
  char Ch;

  cout << "Enter Old file name --> ";
  cin >> OldName;

  Old.open(OldName);      // try to open Old input file
  if (Old.fail())
    {
      cerr << Error << OldName;
      return 0;
    }

  cout << "\nEnter New file name --> ";
  cin >> NewName;
  cin.ignore(100,'\n');    //eats newline left over from cin

  New.open(NewName);      // try to open New output file
  if (New.fail())
    {
      cerr << Error << NewName;
      return 0;
    }

  Old.get(Ch);           // priming read, get first character
  while (!Old.eof())
    {
      New << Ch;        // or use New.put(Ch);  both write char to new file
      Old.get(Ch);      // get next char from input file
    }

  New.close();          // close both files
  Old.close();

  cout << "\nFile copying complete\n\n";
  return 1;
}

/*******************  program output **********************************
Enter Old file name --> input.dat

Enter New file name --> data.dat

File copying complete                                               */