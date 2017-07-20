/*              Prog20.cpp

  This program uses fstream and deals with reading from a file
  The file just contains ints, which are stored in an int array in main.
-------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main()
{
  ifstream InputFile;               //declare an input file
  char NameOfFile[] = "Input.dat";
  int Number, i = 0, NumberArray[100] = {0};

  InputFile.open(NameOfFile);   //open input file, prepare to read from it

  if ( InputFile.fail())		//make sure can open file to read from
    {
      cerr << "Cannot open file name " << NameOfFile << " enter any key";
      exit(1);            //if error in opening, exit program
    }

  InputFile >> Number;          //do a priming read first, get first number
  while (!InputFile.eof())      //while not EOF
    {
      NumberArray[i] = Number;   //store number in array of ints
      InputFile >> Number;       //get next number
      i++;
    }

  for (int k = 0; k < i; k++)          //display the numbers to screen
    cout << NumberArray[k] << " ";

  InputFile.close();         //closing file

  return 0;
}
/***************** Input.dat ****************************************
   given below is the input file

1 2 3 4 5 6 7 8 9 10

======================  Program Comments  ===========================
Six things to always do when working with files:

1) Include header file <fstream>

2) Declare file variables; type "ifstream" for input, or "ofstream" for output

3) Open the file, to either read from or write to it

4) Check to make sure file was successfully opened

5) Read from or write to file, use the standard operators used with
   cin, >> or .get, and for cout, << or .put

6) Close the file.                          */