/*             Prog5.cpp

   Reads characters from the keyboard, then echoes these to the console.
   This short program seems useless at first, (but see comments below).
-----------------------------------------------------------------------*/

#include <iostream>
using namespace std;

void main (void)
{
  char Ch;

  cin.get(Ch);           // Read first char from input stream
  while ( !cin.eof() )   // Stop when EOF or error occurs
  {
    cout << Ch;          // Display the last character read
    cin.get(Ch);         // Read next char from input stream
  }
}

/***********************  program notes **********************************

1)  This program is actually quite powerful, and can be used to view files
    or copy files. To view a file, one would redirection. For example, to
    view a file named "MyFile.Txt", one would redirect input from the
    keyboard to a file. For example at the operating system prompt one
    could enter

      prog5 < MyFile.Txt

    This assumes that this file has been compiled to create a file named
    "prog5.exe" in MS-DOS (or "prog5" in a UNIX environment). To copy
    a file named "File1.cpp" to a file "File2.cpp", one would use the
    command

      prog5 < File1.txt > File2.txt

2)  Output from most programs can also be redirected. For example, to
    create a file that contains a list of all files in the current
    working directory, one could use "DIR > MyFiles.Lst". This does a
    directory listing, but sends output to the file named "MyFiles.Lst".
    This overwrites any previous file with the same name.

    To append instead of overwrite, use the ">>" redirection symbol..

3)  If redirected input is not used, to end the program the user must
    enter the end of file character. In MS-DOS, this is ^Z (Ctrl-Z). On
    UNIX systems, the EOF character is user selectable, but is often ^D.
    Because input is often buffered, the user may also have to press the
    enter key after entering the EOF character.

4)  The cin.fail() function can also be used to detect end of file, and also
    cin.good(), which is a bit safer, then either fail() or eof().

5)  Recall that input and output from conio routines cannot be redirected!
    This is why getche() echos to the console, but not to the printer when
    ^PrintScreen is used to redirect output to the printer.

6)  The initial read before the while loop is needed because in C++, the
    end of file is not detected until at least one char is read.         */