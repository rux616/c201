/*
Name:			Dan Cassidy
Date:			2014-04-26
Homework #:		10
Source File:	MyFloatD.cpp
Class:          C-201 MW 1000
Action:			This file represents the detailed abstraction and implementation of the Abstract Data Type
				"MyFloat", which is a dynamically-precise decimal (up to 65535 places) between 0 and 1.
				
				In this implementation of the class, trailing zeroes are deemed insignificant.  This means
				that when comparing two MyFloats, precision does not matter, e.g. 0.10 is considered equal
				to 0.1000 but 0.10 is still considered smaller than 0.1001.
				
				When adding two MyFloats, any portion of the result that is larger than 1 is automatically
				ignored, e.g. 0.52 + 0.61 = 0.13.

				Class Data Members:
				
					unsigned char *Float
						A char array that represents the main data structure and has its data in subscripts
						0 through a dynamic number.  Digits read in are stored, in order, starting at
						subscript 0.  For example, if the value 0.987 was read in, 9 would be
						stored in subscript 0, 8 would be stored in subscript 1, and 7 would be stored in
						subscript 2.  The rest of the array is zeroed out.

					unsigned short NumDigits
						An unsigned short that represents the current number of significant digits stored
						in Float.  If NumDigits is zero then either the MyFloat object has not been
						initialized yet, an illegally formatted float was encountered while reading, or
						there was an error while allocating dynamic memory for the Float array.

					unsigned short MaxLength
						An unsigned short that represents the maximum possible number of digits that can
						be stored in Float.  If MaxLength is zero then there was an error while attempting
						to dynamically allocate memory for the Float array.
						
				Class Member Functions:

					Digits
						Returns the current number of significant digits in a MyFloat object.

					MaxDigits
						Returns the maximum possible number of digits in a MyFloat object.

				Class Operator Overloads:

					+
						Adds two MyFloat objects together.

					<<
						Writes a leading zero, a decimal point, and then the contents of the MyFloat
						object.

					>>
						Reads standard input and puts a valid float into a MyFloat object.

					>
						Compares two MyFloat objects and determines if the left hand side is greater than
						the right hand side.

					==
						Compares two MyFloat objects and determines if they are equal.

					= (String)
						Converts a string representating a float between 0 and 1 (for example: "0.14159")
						to a MyFloat object.

					= (MyFloat)
						Sets the calling MyFloat object equal to the source MyFloat object.

				Class Destructor:
					~MyFloat
						Frees the dynamically allocated memory once the variable goes out of scope.

				Class Constructors:

					MyFloat (Default)
						Initializes a MyFloat object with a max length of DEFAULT_MAX_LENGTH.

					MyFloat (Short Int)
						Initializes a MyFloat object with a custom length.

					MyFloat (Copy)
						Copies the source MyFloat object to the calling MyFloat object.

				Detailed descriptions of the member functions' actions including input and output
				parameters, return value data types, and preconditions can be found further down in the
				file just ahead of their respective functions.
*/



//MYFLOAT ABSTRACTION

#include <iostream>
#include <cstdlib>
using namespace std;

class MyFloat
{
private:
	enum { DEFAULT_MAX_LENGTH = 10 };

	//Data Members
	unsigned char *Float;
	unsigned short NumDigits;
	unsigned short MaxLength;

public:
	//Member Functions
	unsigned short Digits();
	unsigned short MaxDigits();

	//Operator Overloads
	const MyFloat operator+(const MyFloat &Other) const;

	friend ostream& operator<<(ostream &MFout, const MyFloat &Source);
	friend istream& operator>>(istream &MFin, MyFloat &Target);

	const bool operator>(const MyFloat &Other) const;
	const bool operator==(const MyFloat &Other) const;

	const MyFloat& operator=(const char String[]);
	const MyFloat& operator=(const MyFloat &Source);

	//Destructor
	~MyFloat();

	//Constructors
	MyFloat();
	MyFloat(const unsigned short RequestedMaxLength);
	MyFloat(const MyFloat &Source);
};



//MYFLOAT IMPLEMENTATION

//Class Member Functions
/****************************** Digits ********************************************************************
Action:			Returns the current number of significant digits in a MyFloat.  If 0 is returned, then an
				illegally formatted float has been detected or the MyFloat has not been initialized yet.

Parameters:
IN:				None
OUT:			None

Returns:		unsigned short representing the number of digits in a MyFloat.

Precondition:	None
**********************************************************************************************************/
unsigned short MyFloat::Digits()
{
	return NumDigits;
}

/****************************** MaxDigits *****************************************************************
Action:			Returns the maximum possible number of digits in a MyFloat.

Parameters:
IN:				None
OUT:			None

Returns:		unsigned short representing the maximum possible number of digits in a MyFloat.

Precondition:	None
**********************************************************************************************************/
unsigned short MyFloat::MaxDigits()
{
	return MaxLength;
}



//Class Operator Overloads
/****************************** operator+ *****************************************************************
Action:			Operator overload for + for the MyFloat class.  Adds two MyFloat objects together.  If
				either MyFloat object is in an error state or is uninitialized, this operation will return
				an uninitialized MyFloat object.

Parameters:
IN:				const MyFloat &Other, holds the reference to the MyFloat object that will be added to the
				calling MyFloat object.
OUT:			None

Returns:		const MyFloat containing either the sum of the two MyFloats, or an uninitialized MyFloat if
				one or both of the MyFloats were in an error state or uninitialized themselves.

Precondition:	None
**********************************************************************************************************/
const MyFloat MyFloat::operator+(const MyFloat &Other) const
{
	MyFloat Result;
	unsigned char CarryBit = 0;

	//Verify that both operands are initialized MyFloats.  If not, skip the addition and return the still-
	//uninitialized MyFloat object Result.
	if (NumDigits && Other.NumDigits)
	{
		//Set Result.NumDigits to whichever NumDigits is greater.  This ensures that no precision is lost.
		Result.NumDigits = (NumDigits >= Other.NumDigits ? NumDigits : Other.NumDigits);

		//Check to make sure the Result MyFloat object is large enough to receive the data from the
		//addition operation and if it is not, deallocate the current memory and allocate more.
		if (Result.MaxLength < Result.NumDigits)
		{
			delete[] Result.Float; Result.Float = nullptr;

			Result.Float = new (nothrow) unsigned char[Result.NumDigits];
			if (Float == nullptr)
			{
				Result.NumDigits = 0;
				Result.MaxLength = 0;
				return Result;
			}
			Result.MaxLength = Result.NumDigits;
		}

		for (long i = Result.NumDigits - 1; i >= 0; --i)
		{
			unsigned char Sum = (NumDigits < i + 1 ? 0 : Float[i])
				+ (Other.NumDigits < i + 1 ? 0 : Other.Float[i]) + CarryBit;

			CarryBit = Sum / 10;
			Sum -= CarryBit * 10;

			Result.Float[i] = Sum;
		}
	}

	return Result;
}

/****************************** operator<< ****************************************************************
Action:			Writes a leading zero, a decimal point, and then the contents of the calling MyFloat
				object.  If there has been an error in reading, or if the MyFloat object has not been
				initialized yet, it will output a question mark instead of the contents of the MyFloat
				object after the leading zero and decimal point.

Parameters:
IN:				ostream &MFout, holds the reference to the ostream object that will be used to output the
				MyFloat object referenced by &Source.
IN:				const MyFloat &Source, holds the reference to the MyFloat object that will be output.
OUT:			None

Returns:		ostream& referencing &MFout in order to facilitate ostream cascading.

Precondition:	None
**********************************************************************************************************/
ostream& operator<<(ostream &MFout, const MyFloat &Source)
{
	MFout << "0.";

	if (Source.NumDigits)
		for (unsigned short i = 0; i < Source.NumDigits; ++i)
			MFout << int(Source.Float[i]);
	else
		MFout << "?";

	return MFout;
}

/****************************** operator>> ****************************************************************
Action:			Reads a MyFloat from standard input.  If an error is detected, NumDigits is set to 0.  Also
				puts the last character read from the input buffer back into it, and zeroes out the rest of
				the array.

Parameters:
IN:				istream &MFin, holds the reference to the istream object that will be used to input the
				MyFloat referenced by &Target.
OUT:			MyFloat &Target, holds the reference to the target MyFloat which will receive the input.

Returns:		istream& referencing &MFin in order to facilitate istream cascading.

Precondition:	None
**********************************************************************************************************/
istream& operator>>(istream &MFin, MyFloat &Target)
{
	//Clears anything and everything remaining in the input buffer and then triggers the now empty input
	//buffer to ask for input.
	cin.ignore(MFin.rdbuf()->in_avail());
	MFin.peek();

	//Get length of input buffer
	unsigned short Length = MFin.rdbuf()->in_avail();

	//Dynamically create a char array to hold the user input and if it is created successfully, read in a
	//line of user input as a string, and then set Target equal to that utilizing the overloaded =
	//operator.
	char *Buffer = new (nothrow) char[Length];
	if (Buffer != nullptr)
	{
		MFin.getline(Buffer, Length);

		//Put back the last character read from the input buffer because the test program expects at least
		//one character in the input buffer.
		MFin.unget();

		Target = Buffer;

		delete[] Buffer; Buffer = nullptr;
	}

	return MFin;
}

/****************************** operator> *****************************************************************
Action:			Operator overload for > for the MyFloat class.  Compares two MyFloat objects and determines
				if the left hand side is greater than the right hand side.  Will compare MyFloat objects
				that are in an error status or are uninitalized as well (these are both considered to be
				the smallest possible value for a MyFloat object.)

Parameters:
IN:				const MyFloat &Other, holds the reference to the MyFloat object that will be compared to
				the calling MyFloat object.
OUT:			None

Returns:		const bool representing whether the left hand side MyFloat object is greater than the right
				hand side MyFloat object or not.

Precondition:	None
**********************************************************************************************************/
const bool MyFloat::operator>(const MyFloat &Other) const
{
	bool IsLessThan = false, IsGreaterThan = false;

	//Uninitialized MyFloats are considered to be the smallest possible value, so if the calling MyFloat is
	//uninitialized, it is automatically either less than or equal to Other.  Conversely, if *this is
	//initialized and Other is not, *this is automatically greater than Other.
	if (!NumDigits)
		IsGreaterThan = false;
	else if (!Other.NumDigits)
		IsGreaterThan = true;
	else
	{
		//Compare up to the lesser length of the two MyFloat objects.
		unsigned short LesserDigits = (NumDigits < Other.NumDigits ? NumDigits : Other.NumDigits);
		for (unsigned short i = 0; i < LesserDigits && !IsLessThan && !IsGreaterThan; ++i)
			if (Float[i] < Other.Float[i])
				IsLessThan = true;
			else if (Float[i] > Other.Float[i])
				IsGreaterThan = true;

		//If the two MyFloat objects are still equal after comparing the smallest number of digits, check
		//to make sure they are not equal in length, then test the longer MyFloat object to see if any of
		//the remaining digits are not zero.  If they are, the longer MyFloat object is automatically
		//larger.
		if (!IsLessThan && !IsGreaterThan && NumDigits != Other.NumDigits)
		{
			if (NumDigits < Other.NumDigits)
			{
				for (unsigned short i = LesserDigits; i < Other.NumDigits && !IsLessThan; ++i)
					if (Other.Float[i])
						IsLessThan = true;
			}
			else
				for (unsigned short i = LesserDigits; i < NumDigits && !IsGreaterThan; ++i)
					if (Float[i])
						IsGreaterThan = true;
		}
	}

	return IsGreaterThan;
}

/****************************** operator== ****************************************************************
Action:			Operator overload for == for the MyFloat class.  Compares two MyFloat objects and
				determines if they are equal.  Will compare MyFloat objects that are in an error status or
				are uninitialized as well. Note that trailing zeroes are deemed insignificant, so 0.1 is
				equal to 0.10.

Parameters:
IN:				const MyFloat &Other, holds the reference to the MyFloat object that will be compared to
				the calling MyFloat object.
OUT:			None

Returns:		const bool representing whether the two MyFloat objects are equal.

Precondition:	None
**********************************************************************************************************/
const bool MyFloat::operator==(const MyFloat &Other) const
{
	bool IsEqual = true;
	
	//Compare up to the lesser length of the two MyFloat objects.
	unsigned short LesserDigits = (NumDigits < Other.NumDigits ? NumDigits : Other.NumDigits);
	for (unsigned short i = 0; i < LesserDigits && IsEqual; ++i)
		if (Float[i] != Other.Float[i])
			IsEqual = false;

	//If the two MyFloat objects are still equal after comparing the smallest number of digits, check to
	//make sure they are not equal in length, then test the longer MyFloat object to see if any of the
	//remaining digits are not zero.  If they are, the longer MyFloat object is automatically larger and
	//therefore not equal to the other MyFloat object.
	if (IsEqual && NumDigits != Other.NumDigits)
	{
		if (NumDigits < Other.NumDigits)
		{
			for (unsigned short i = LesserDigits; i < Other.NumDigits && IsEqual; ++i)
				if (Other.Float[i])
					IsEqual = false;
		}
		else
			for (unsigned short i = LesserDigits; i < NumDigits && IsEqual; ++i)
				if (Float[i])
					IsEqual = false;
	}

	return IsEqual;
}

/****************************** operator= *****************************************************************
Action:			Operator overload for = for the MyFloat class.  Converts a string representating a float
				between 0 and 1 (for example: "0.14159") to a MyFloat.  Also zeroes out the unused portion
				of the MyFloat.

Parameters:
IN:				const char String[], holds the pointer to the null-terminating character array that will be
				read in to a MyFloat object.
OUT:			None

Returns:		const MyFloat& referencing the calling MyFloat object now holding the contents of String[].

Precondition:	String must be a null-terminating character array.
**********************************************************************************************************/
const MyFloat& MyFloat::operator=(const char String[])
{
	bool Error = false, Finished = false;
	unsigned short i = 0, Length = 0;

	//Go through the first part of the string until a period is found
	for (bool ZeroEncountered = false; String[i] && !Error && !Finished; ++i)
	{
		if (String[i] == '0')
			ZeroEncountered = true;
		else if (String[i] == '.')
			Finished = true;
		else if (isspace(String[i]) && !ZeroEncountered)
			;//Do nothing, ignore the whitespace
		else
			Error = true;
	}

	if (!Error && !Finished)
		//Null encountered before period found.
		Error = true;

	//Reset the Finished flag for the next loop.
	Finished = false;

	//Run through the rest of String to get the length of the valid data.
	for (unsigned short k = i; String[k] && !Error && !Finished; ++k)
	{
		if (isdigit(String[k]))
			++Length;
		else if (!Length)
			Error = true;
		else
			Finished = true;
	}

	//Check to make sure the calling MyFloat object is large enough to receive the data from String and
	//if it is not, deallocate the current memory and allocate more.
	if (!Error && MaxLength < Length)
	{
		delete[] Float; Float = nullptr;

		Float = new (nothrow) unsigned char[Length];
		if (Float == nullptr)
		{
			NumDigits = 0;
			MaxLength = 0;
			return *this;
		}
		MaxLength = Length;
	}

	//Reset the Finished flag for the next loop.
	Finished = false;

	//Run through the rest of String for real to get the data.
	for (Length = 0; String[i] && !Error && !Finished; ++i)
	{
		if (isdigit(String[i]))
			Float[Length++] = String[i] - '0';
		else
			Finished = true;
	}
		
	//Determine what NumDigits gets set to.
	//	0 if there was an error
	//	Length if the previous loop encountered a non-numeric (null included)
	if (Error)
		NumDigits = 0;
	else
		NumDigits = Length;

	//Zero out the remainder of the array.
	for (i = NumDigits; i < MaxLength; ++i)
		Float[i] = 0;

	return *this;
}

/****************************** operator= *****************************************************************
Action:			Operator overload for = for the MyFloat class.  Performs a deep copy of the source MyFloat
				object into the calling MyFloat object and will expand the calling MyFloat object as
				necessary.  Also zeroes out the unused portion of the Float array in the calling MyFloat
				object.

Parameters:
IN:				const MyFloat &Source, holds the reference to the MyFloat object that will be deep copied
				into the calling MyFloat object.
OUT:			None

Returns:		const MyFloat& referencing the calling MyFloat object now holding the contents of Source.

Precondition:	None
**********************************************************************************************************/
const MyFloat& MyFloat::operator=(const MyFloat &Source)
{
	//Don't copy self
	if (this == &Source)
		return *this;

	//Check if the length of calling MyFloat object is sufficient to handle the incoming data from Source
	//and if not, deallocate the current memory and allocate more.
	if (MaxLength < Source.NumDigits)
	{
		delete[] Float; Float = nullptr;

		Float = new (nothrow) unsigned char[Source.NumDigits];
		if (Float == nullptr)
		{
			NumDigits = 0;
			MaxLength = 0;
			return *this;
		}
		MaxLength = Source.NumDigits;
	}
	NumDigits = Source.NumDigits;

	//Deep copy the contents of Source.Float into the calling object's Float.
	for (unsigned short i = 0; i < NumDigits; ++i)
		Float[i] = Source.Float[i];

	//Zero out the unused portion of the array.
	for (unsigned short i = NumDigits; i < MaxLength; ++i)
		Float[i] = 0;

	return *this;
}



//Class Destructor
/****************************** ~MyFloat ******************************************************************
Action:			Destructor for the MyFloat class.  Deallocates dynamic memory that was allocated to Float
				and then sets Float to nullptr for safety.

Parameters:
IN:				None
OUT:			None

Returns:		Nothing

Precondition:	Must not be called explicitly.
**********************************************************************************************************/
MyFloat::~MyFloat()
{
	//Only need to free the dynamic memory; compiler handles the statics automagically.
	delete[] Float;

	//Set Float to nullptr just in case someone gets stupid and calls the destructor manually.
	Float = nullptr;
}



//Class Constructors
/****************************** MyFloat (Default Constructor) *********************************************
Action:			Default constructor for the MyFloat class.  Sets NumDigits to 0, MaxLength to
				DEFAULT_MAX_LENGTH, attempts to dynamically allocate enough memory for the Float array,
				then zeroes it out.  If there is an error allocating the required memory to Float,
				MaxLength is set to 0.

Parameters:
IN:				None
OUT:			None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
MyFloat::MyFloat()
{
	NumDigits = 0;
	MaxLength = DEFAULT_MAX_LENGTH;

	//Safe initialization of Float, just in case
	Float = nullptr;

	Float = new (nothrow) unsigned char[MaxLength];

	if (Float != nullptr)
		for (unsigned short i = 0; i < MaxLength; ++i)
			Float[i] = 0;
	else
		MaxLength = 0;
}

/****************************** MyFloat (Constructor) *****************************************************
Action:			Constructor for the MyFloat class.  Sets NumDigits to 0, MaxLength to RequestedMaxLength,
				attempts to dynamically allocate enough memory for the Float array, then zeroes it out.  If
				there is an error allocating the required memory to Float, MaxLength is set to 0.

Parameters:
IN:				const unsigned short RequestedMaxLength, holds the requested number of max digits
OUT:			None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
MyFloat::MyFloat(const unsigned short RequestedMaxLength)
{
	NumDigits = 0;
	MaxLength = RequestedMaxLength;
	
	//Safe initialization of Float, just in case
	Float = nullptr;

	//Added safety measure, just in case 0 gets passed in as the RequestedMaxLength
	if (MaxLength)
		Float = new (nothrow) unsigned char[MaxLength];

	if (Float != nullptr)
		for (unsigned short i = 0; i < MaxLength; ++i)
			Float[i] = 0;
	else
		MaxLength = 0;
}

/****************************** MyFloat (Copy Constructor) ************************************************
Action:			Copy constructor for the MyFloat class.  Sets up a new MyFloat using the MaxLength from
				Source as its own MaxLength, then performs a deep copy of Source to the calling MyFloat
				object.  If there is an error allocating the required memory to Float, NumDigits and
				MaxLength are both set to 0.

Parameters:
IN:				None
OUT:			None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
MyFloat::MyFloat(const MyFloat &Source)
{
	NumDigits = Source.NumDigits;
	MaxLength = Source.MaxLength;

	//Safe initialization of Float, just in case
	Float = nullptr;

	//Added safety measure in case the copy constructor is called to copy a MyFloat object that failed to
	//have dynamic memory allocated to it.
	if (MaxLength)
		Float = new (nothrow) unsigned char[MaxLength];

	if (Float != nullptr)
	{
		for (unsigned short i = 0; i < MaxLength; ++i)
			Float[i] = Source.Float[i];
	}
	else
	{
		NumDigits = 0;
		MaxLength = 0;
	}
}
