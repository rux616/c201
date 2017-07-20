/*	     Prog22.cpp

  A program that shows how to prototype a function to which one can pass
  either cin or an instance of ifstream.  This allows the same routine to
  handle either file input or standard keyboard input.
--------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
using namespace std;

void ReadAndDisplay(istream& F);

int main ()
{
  char Filename[30];

  cout << "Enter the name of a file or just press Enter key to "
          "read from keyboard input\n";
  cout << "==> ";

  cin.getline(Filename, sizeof Filename);

  if ( Filename[0] == '\0' )    // Filename == ""
    {
      cout << "Press Enter key and then Ctrl-Z and Enter key to end input\n";
      ReadAndDisplay(cin);
    }
  else
    {
      ifstream FileIn(Filename);   // Open file named Filename for input

      if ( !FileIn.good() )        // Error opening file
        {
          cerr << "Error trying to open \"" << Filename << "\": exiting..\n";
          return 1;
        }

      ReadAndDisplay(FileIn);
      FileIn.close();
      }

  return 0;
}
/*****************************  ReadAndDisplay  ************************
Action  : Reads and displays input taken from file stream, which can
          either be keyboard input or a file stream associated with ifstream.

Parameters:
  File   A reference to istream.  The actual parameter can be either cin
         or a member of ifstream that has been opened.

Calls    get and good, both member functions of the istream class.

NOTE     Buffered input is used when reading from keyboard input, so output
         will be displayed a line at a time, immediately after the
         File.get has echoed the line read.
--------------------------------------------------------------------------*/
void ReadAndDisplay(istream& File)
{
  char Ch;

  File.get(Ch);         // At least one char must be read to set EOF
  while ( File.good() )
    {
      cout << Ch;
      File.get(Ch);
    }
}