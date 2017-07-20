/*********************   STRING1.CPP  *************************************

   A C++ class definition that shows the language's ability to implement an 
   abstract data type.  The definition below does a partial implementation of 
   the type String, a type designed to hold strings of length up to 255.

   Before trying to read the code below, it is recommended that you study
   the handout "Abstract Data Types".

   Recall that an abstract data type is a set of data objects, together 
   with a collection of operations on those objects.  The operations are 
   defined without reference to the way the objects are represented in 
   memory.  

   In the case of the abstract data type string, the objects are the strings 
   themselves.  There are a number of "standard" string operations that one 
   would like to include, but in this program we'll only implement a few.  
   This implementation will view a string as a record (struct) with two 
   fields. The first field is a character array, Chr, of length MAX_LENGTH, 
   while the second field, Len, will hold the length of the string.

   The following string operations are implemented below:

   Assignment  :  Assigning a value to a string variable.
   Length      :  Finding the number of characters in a string.
   Max Length  :  Finding the maximum possible length of a string.
   Output      :  Writing a string to stdout.

   This file contains both the specification file and the
   implementation file. The commenting style assumes the reader is not
   very familiar with classes.
= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = */
#include <iostream>
using namespace std;
class String
{
//------------------------  private --------------------------------------

private:  //  Class  members following this keyword can only be
	  //    accessed by member functions declared below.

  enum { MAX_LENGTH = 255 };  // Max value of unsigned char

  char Chr[MAX_LENGTH];       // Array to hold the characters in string

  unsigned char Len;          // Number of characters in string. A NULL
			      //   terminator is NOT used.

//-------------------------  public  -------------------------------------

public:   //  Members following this keyword can can be accessed
	  //  anywhere within the scope of the class definition.

void Assign (const char C_Str[]);       //  See implementation file for
int  Length();                          //    descriptions
int  MaxLength();
void Write();
};    // Semicolon is required!
// ============  End of specification file  ==============================
/*================ Implementation file for String class  =================

    The implementation file contains the actual definitions of the
    functions prototyped in the specification file. Note that

    1)  The scope resolution operator, "::", must be used as a prefix to
	the function name. This allows different classes to have member
	functions with the same name.

    2)  Note that the private data fields are referenced in the code below.

/***************************  Length   ***********************************
  Returns the length of a String, i.e. the number of chars in the string.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int  String::Length()  // "::" is the scope resolution operator.  Tells
		       //    compiler we're defining a String function.
{
  return Len;          // Member functions can reference private fields
}

/************************   MaxLength   **********************************
   Returns the maximum possible length of an instance of class String.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int String::MaxLength()
{
  return MAX_LENGTH;
}

/***************************   Write *************************************
  Writes the characters of a String to standard output (cursor remains on
  the same line.)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void String::Write()
{
  cout.write(Chr, Len);   // Send Len chars to std output.
}

/************************  Assign  ***************************************
   This function gives us the ability to convert an ordinary null
   terminated C string to a member of the String class.

   If S has been declared to be in our string class, this routine will
   permit such things as

   S.Assign ("Hello!");
   S.Assign (A);         // Where declaration of A is "char A[] = "
   S.Assign (P);         // Where declaration of P is "char* P"
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void String::Assign (const char C_Str[])
{
   int k = 0;

   while ( k < MAX_LENGTH && C_Str[k] != 0 )
     {
     Chr[k] = C_Str[k];                  // Copy chars from C string
     k++;
     }

   Len = k;                              // No null terminator
}