/*                      stringdy.cpp

  This class definition adds a number of enhancements to the String2
  class defined earlier. Recall that the strings of that class had a
  maximum length of 255, since the data fields holding the string were
  defined as follows:

  enum { MAX_LENGTH = 255 };  // Max value of unsigned char.

  char Chr[MAX_LENGTH];       // The actual characters in string.

  unsigned char Len;          // Number of characters in string.

  Suppose we want to allow the possibility of longer strings. One approach
  would be to change the Len type to unsigned and the up the value of
  MAX_LENGTH. This approach would allow larger strings, but would be
  wasteful in situations where we need a mixture of short and long
  strings. A more satisfactory solution is via dynamically allocated
  strings, i.e. strings whose storage is allocated a run-time.

  This approach requires considerable skill on the part of the programmer
  implementing the class. For example, assuming that the name of our
  dynamically implemented class is "String":

  1)  The default constructor supplied automatically by the compiler will
      not work properly. A programmer can declare variables of type String,
      but they won't behave as expected.

      * The programmer must write constructor(s) to support the class.

  2)  The memory for local variables of type String is not automatically
      deallocated when a function is exited. Similarly, the copies of
      String parameters that are passed by value are not automatically
      deallocated when a function is exited.

      * The programmer must write a destructor function to handle this.

  3)  The automatic support for passing Strings by value and returning a
      String as a function value is removed. Also the ability to declare
      an intialize simultaneously does not function as expected.

      The programmer must write a copy constructor to support these
      operations.

  Below is a partial implementation of a dynamic string class. The
  following string operations are implemented now: (refer to the
  header comments preceding these functions for more information).

  =           :  Assigning a value to a string variable.
  <<          :  Printing a string to stdout.
  >>          :  Reading a string from stdin.
  +           :  Concatenation of two strings
  Length      :  Finding the number of characters in a string.
  Max Length  :  Finding the maximum possible length of a string.

  NOTE: To get a really useful implementation, many additional member functions
  ~~~~  would need to be written, including, the operators !=, ==, >, <, <=, >=,
        +=, pattern matching, and substrings, to name a few.
----------------------------------------------------------------------- */
#include <iostream>
#include <new>
using namespace std;

class String                    // Dynamically allocated string class
{
  enum { DEFAULT_LENGTH = 80 }; // Default string length

  char*    Chr;                 // Pointer to create dynamic char

  unsigned Len;                 // Number of valid chars in Chr array
  unsigned MaxLen;              // Max possible length of the string
                                // Set to 0 if memory allocation error
public:

unsigned Length() const      // inline that provides access to length
{
  return Len;
}

unsigned MaxLength() const   // inline that provides access to MaxLen
{
  return MaxLen;
}

~String();                   // Class destructor: see comments below.



String (const String &S);    // The class copy constructor

String();                    // Constructor creates string with default length

String (unsigned Length);    // Constructor permitting any size string

String (const char* S);      // Constructor allowing 'String("Hello")'


String& operator= (const char* Rhs);    // Overloaded assignment
                                              //  operators.
String& operator= (const String& Rhs);


String operator+ (const String& Rhs);       //  Concatenation.

friend ostream& operator<< (ostream& Cout,       // String output
                            const    String& S);

friend istream& operator>> (istream& Cin,        // String input
                            String&  S);
};









/************************  ~String  *************************************

   The class destructor. This function is called automatically
   when an instance of the String class goes out of scope. In particular,
   the destructor is called to return dynamically allocated storage when
   a function is exited. Storage for the following will be deallocated.

     1)  local variables
     2)  parameters passed by value

   Dealloacating dynamic memory crucial or memory leaks will eventually
   cause problems.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String::~String()
{
  delete Chr; // Return dynamic storage associated with Chr. The compiler
}             //   automatically generates code to deallocate static vars.


/******************  String (copy constructor)    ***********************

  IMPORTANT   Because this constructor has a single String reference
  NOTE        parameter, the compiler automatically makes it the copy
              constructor for the String class.

  The copy constructor is called under the following circumstances.

  1)  When an instance of the String class is passed by value to a
      function, the copy constructor makes a copy of the class instance.

  2)  When a String is initialized in a declaration, as in
      "String S1 = S2;", the copy constructor is called to make a copy
      of S2.

  3)  When an instance of the String class is returned as a function
      value or from a String operater, the copy constructor makes a
      copy of the return value.

  When working with classes with dynamically created fields, it is vital
  that the programmer define their own "deep copy" constructor. If not
  the compiler merely makes a (shallow) copy of the class instance.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String::String (const String &S)
{
  MaxLen = S.MaxLen;                     //  Make length fields the same
  Len    = S.Len;

  Chr = new(nothrow) char[MaxLen];                //  Create storage for deep copy

  if ( Chr != NULL )                              //  Memory allocation succeeded
    for ( unsigned int k = 0;  k < Len;  ++k )    //  Copy data in dynamic storage
      Chr[k] = S.Chr[k];
  else
    MaxLen = 0;

}


/*********************   String (default constructor)  *******************

   A constructor that supports declarations of the form "String S;",
   which creates a null string having DEFAULT_LENGTH length.

   IMPORTANT Since this constructor has no parameters, it is the default
   NOTE      constructor for the class, one which will be called
             automatically if an array of String is declared such as in
             the declaration "String S[10];"

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String::String()
{
  Len    = 0;
  MaxLen = DEFAULT_LENGTH;
  Chr    = new(nothrow) char[DEFAULT_LENGTH];
  if ( Chr == NULL )                    // Memory allocation error
    MaxLen = 0;                         // No memory available
}

/*********************   String (constructor)  ***************************

   A constructor that allows declarations of the form "String S(100);",
   which creates a string having a maximum length of 100, and which is
   initialized to "".

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String::String(unsigned Length)
{
  Chr    = new(nothrow) char[Length];
  Len    = 0;
  if ( Chr == NULL )                    // Memory allocation error
    MaxLen = 0;                         // No memory available
  else
    MaxLen = Length;
}


/*********************   String (constructor)  ***************************

   A constructor that allows declarations of the form 'String S("abc");'
   or the equivalent 'String S = "abc";'
   A design question here is how large to make the string to be created.
   Do we make it just large enough to hold the string constant or do we
   allow room for some extra chars to be added later. Currently, the newly
   created array is just large enough to hold the string constant.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String::String (const char* S)
{
  unsigned int k = 0;

  while (S[k] != 0)                  // Find length of S
    k++;

  Len    = k;
  MaxLen = k;

  Chr = new(nothrow) char [MaxLen];  //  Create array large enough to hold S


  if ( Chr == NULL )                 //  Memory allocation failure
    {
    MaxLen = 0;                      //  Set error flag
    }
  else
    for ( k = 0;  k < Len;  ++k )
      (Chr[k] = S[k]);               // Copy characters from S.
}


/*************************** operator=     ******************************
   This function gives us the ability to assign an "ordinary C string"
   to one of the strings in the String class. These C strings are of 3
   varieties:

     1) string constants, i.e. pointers to an array of char stored
        in a program's static memory space
     2) Arrays of char, i.e. constant pointers
     3) char *  pointer variables

   If S has been declared to be in our string class, this routine
   permits such things as

   S = "Hello!";
   S = A;         //  where, char A[8];
   S = P;         //  where, char* P;

   The characters of the ordinary null terminated C string Rhs are
   copied to the instance of String on the left hand side of "=".  If the
   string pointed at by Rhs is too large to fit in *this, then
   additional memory is allocated.

   *this is returned in order to permit the cascading of the overloaded
   assignment operator, i.e. to permit lines of the form S1 = S2 = "Hi!";
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String& String::operator= (const char* Rhs)
{
  unsigned int k, LengthRhs = 0;

  while ( Rhs[LengthRhs] )          // Find length of null terminated string
    ++LengthRhs;

  if ( LengthRhs > MaxLen )         // Not enough room in left hand side!
    {
    delete[] Chr;                        // Deallocate old storage
    Chr = new(nothrow) char[LengthRhs];  // Create large enough array
    if ( Chr == NULL )              // Memory allocation error.
      {
      MaxLen = 0;                   // No room for any chars
      return *this;                 // Return reference to Lhs
      }                             // Exit
    MaxLen = LengthRhs;             // String now has longer max length
    }
  for ( k = 0; k < LengthRhs; ++k )
    Chr[k] = Rhs[k];                // Copy char from Rhs to Lhs.

  Len = LengthRhs;
  return *this;   //  "this" is a pointer to object implicitly passed
}
/*************************** operator=     ******************************

  Called when an assignment of the form S1 = S2, where S1 and S2 are
  both instances of the String class. If this routine were not written,
  the system would supply a "standard" assignment operator, which would
  not work properly. It would copy only the address stored in S2.Chr, and
  not the data pointed to by S2.Chr. This copying of a pointer only is
  usually called a "shallow copy".
  The function below makes what is called a "deep copy", i.e. it copies
  all of the fields of S2 as well as the data pointed to by S2.Chr.

  If the receiving string is too small additional memory is allocated.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String& String::operator= (const String &Rhs)
{
  unsigned int k = 0;

  if ( this == &Rhs )             // Don't copy string to itself
    return *this;

  if ( MaxLen < Rhs.Len )         // Not enought room in *this
    {
    delete[] Chr;                 // Deallocate storage

    Chr = new(nothrow) char[Rhs.Len]; // Allocate enough space
    if ( Chr == NULL )                // Not enough free memory
      {
      MaxLen = 0;                 // No room for any chars
      return *this;               // Return reference to Lhs
      }                           // Exit
    MaxLen = Rhs.Len;             // String now has longer max length
    }
  Len = Rhs.Len;                  // New string has length of Rhs

  for ( k = 0; k < Rhs.Len; ++k )
    Chr[k] = Rhs.Chr[k];          // Copy char from Rhs to Lhs.

  return *this;   //  Allow cascading of operator, i.e. allow statements
}                 //    of the form "S1 = S2 = S3;"

/************************  operator +    ********************************

   Returns the concatenation of Strings A and B.

   A and B are passed by reference to avoid the expense of having the
   copy constructor called to make copies of value parameters.
   The caller should take care not to store the concatenation in a
   string whose length is less than the combined length of A and B.
   Exercise:  Eliminate this precondition.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String String::operator+ (const String& B)
{
  String Temp (Len + B.Len);   // Temp big enough to hold both

  unsigned int n, k;

  Temp.Len = Len + B.Len;


  for ( n = 0;  n < Len;  ++n )
    Temp.Chr[n] = Chr[n];                   // Copy chars from A

  for ( k = 0;  k < B.Len;  ++k, ++n )
    Temp.Chr[n] = B.Chr[k];                 // Copy char from second string

  return Temp;                  // Copy constructor makes copy of Temp,
}                               //   then class destructor is called.

/************************   operator <<  *********************************

   A friend function that outputs an instance of the class String.

   The function merely calls a member of the ostream class to write
   the characters in S to the output stream, then returns the state
   of the output stream, so that the overloaded operator can be
   cascaded and permit statements of the form

   cout << S1 << S2;

   This operator  must be written as friend functions, since a non-string
   will appear on the left side of the "<<" operator.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
ostream& operator<< (ostream& Cout,
                     const    String& S)
{
  Cout.write (S.Chr, S.Len);   //  Write S.Len chars to stdout
  return Cout;
}

/************************   operator >>  *********************************

   A friend function that reads an instance of the class String.

   In order to maintain the input conventions of ">>" this routine first
   skips whitespaces, then reads non-whitespace characters, stopping at
   the first whitespace characters.   Thus, if the user entered

     "  The quick brown dog\n"

   the return value of S would be "The".
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
istream& operator>> (istream& In, String&  S)
{
  char Ch;
  In >> Ch;                        // Skip white space and punctuation

  unsigned int  k = 0;
  while ( !isspace(Ch) && k < S.MaxLen && In.good())  // Read blank delimited "word"
  {
    S.Chr[k++] = Ch;                  //  Store non-blank
    In.get(Ch);                       //  Read next char
  }

  S.Len = k;

  return In;   //  Permits cascading of operator
}