/*
Name:			Dan Cassidy
Date:			2014-03-13
Homework #:		06
Source File:	MyFloat2.cpp
Class:          C-201 MW 1000
Action:			This file represents the detailed abstraction and implementation of the Abstract Data Type
				"MyFloat", which is a highly precise decimal (up to 20 digits) between 0 and 1.
				
				In this implementation of the class, trailing zeroes are deemed significant as they specify
				exactly how precise a given MyFloat should be.  This means that when comparing two
				MyFloats, even if the values evaluate to the same thing when precision is taken out of the
				picture, e.g. 0.10 being compared to 0.1000, if the precision isn't the same, they are
				considered not equal.
				
				When adding two MyFloats, any portion of the result that is larger than 1 is automatically
				ignored, e.g. 0.52 + 0.61 = 0.13.

				Class Data Members:
				
					unsigned char Float[MAX_PRECISION]
						A char array that represents the main data structure and has its data in subscripts
						0 through 19.  Digits read in through the Read() function are stored in order
						starting at subscript 0.  For example, if the value 0.987 was read in, 9 would be
						stored in subscript 0, 8 would be stored in subscript 1, and 7 would be stored in
						subscript 2.  The rest of the array is zeroed out.

					unsigned char NumDigits
						An unsigned char that represents the current number of significant digits stored in
						Float.  If NumDigits is zero then either MyFloat has not been initialized yet, or
						there was an error and an illegal float was encountered while reading.
						
				Class Member Functions:

					Digits
						Returns the current number of significant digits in a MyFloat.

					MaxDigits
						Returns the maximum possible number of digits in a MyFloat.

				Class Operator Overloads:

					+
						Adds two MyFloats together.

					<<
						Writes a leading zero, a decimal point, and then the contents of the MyFloat.

					>>
						Reads a MyFloat from standard input.

					>
						Compares two MyFloats and determines if the left hand side is greater than the
						right hand side.

					==
						Compares two MyFloats and determines if they are equal.

					=
						Converts a string representating a float between 0 and 1 (for example: "0.14159")
						to a MyFloat.

				Class Constructors:

					MyFloat()
						Default constructor which initializes the contents of Float to 0 and sets NumDigits
						to 0.

				Detailed descriptions of the member function's actions including input and output
				parameters, return value data types, and preconditions can be found further down in the
				file just ahead of their respective functions.
*/


//MYFLOAT ABSTRACTION

#include <iostream>
using namespace std;

class MyFloat
{
private:
	enum { MAX_PRECISION = 20 };

	//Data Members
	unsigned char Float[MAX_PRECISION];
	unsigned char NumDigits;

public:
	//Member Functions
	int Digits();
	int MaxDigits();

	//Operator Overloads
	const MyFloat operator+(const MyFloat &Other) const;
	friend ostream& operator<<(ostream &MFout, const MyFloat &Source);
	friend istream& operator>>(istream &MFin, MyFloat &Target);
	const bool operator>(const MyFloat &Other) const;
	const bool operator==(const MyFloat &Other) const;
	const MyFloat& operator=(const char String[]);

	//Constructors
	MyFloat();
};



//MYFLOAT IMPLEMENTATION

//Class Member Functions
/****************************** Digits ********************************************************************
Action:			Returns the current number of significant digits in a MyFloat.  If 0 is returned, then an
				illegally formatted float has been detected or the MyFloat has not been initialized yet.

Parameters:
IN:				None
OUT:			None

Returns:		int representing the number of digits in a MyFloat.

Precondition:	None
**********************************************************************************************************/
int MyFloat::Digits()
{
	return int(NumDigits);
}

/****************************** MaxDigits *****************************************************************
Action:			Returns the maximum possible number of digits in a MyFloat.

Parameters:
IN:				None
OUT:			None

Returns:		int representing the maximum possible number of digits in a MyFloat.

Precondition:	None
**********************************************************************************************************/
int MyFloat::MaxDigits()
{
	return int(MAX_PRECISION);
}



//Class Operator Overloads
/****************************** operator+ *****************************************************************
Action:			Operator overload for + for MyFloat.  Adds two MyFloats together.  If either MyFloat object
				is in an error state or is uninitialized, this operation will return an uninitialized
				MyFloat object.

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
	short int CarryBit = 0;

	//Verify that both operands are initialized MyFloats.  If not, skip the addition and return the still-
	//uninitialized MyFloat object Result.
	if (NumDigits && Other.NumDigits)
	{
		//Set Result.NumDigits to whichever NumDigits is greater.  This ensures that no precision is lost.
		Result.NumDigits = (NumDigits >= Other.NumDigits ? NumDigits : Other.NumDigits);

		for (int i = Result.NumDigits - 1; i >= 0; --i)
		{
			char Sum = Float[i] + Other.Float[i] + CarryBit;

			CarryBit = Sum / 10;
			Sum -= CarryBit * 10;

			Result.Float[i] = Sum;
		}
	}

	return Result;
}

/****************************** operator<< ****************************************************************
Action:			Writes a leading zero, a decimal point, and then the contents of the MyFloat.  If there has
				been an error in reading, or if the MyFloat has not been initialized yet, it will output a
				question mark instead of the contents of the MyFloat after the leading zero and decimal
				point.

Parameters:
IN:				ostream &MFout, holds the reference to the ostream object that will be used to output the
				MyFloat referenced by &Source.
IN:				const MyFloat &Source, holds the reference to the MyFloat that will be outputted.
OUT:			None

Returns:		ostream& referencing &MFout in order to facilitate ostream cascading.

Precondition:	None
**********************************************************************************************************/
ostream& operator<<(ostream &MFout, const MyFloat &Source)
{
	MFout << "0.";

	if (!Source.NumDigits)
	{
		MFout << "?";
	}
	else
	{
		for (unsigned char i = 0; i < Source.NumDigits; ++i)
			MFout << (int)Source.Float[i];
	}

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
	unsigned char Ch = 0, ChPrevious = 0;
	bool Error = false, Finished = false;
	unsigned char i = 0;

	//Do the initial read of the data and discard any leading spaces and zeroes, and the decimal point.
	MFin >> Ch;
	while (!Error && !Finished)
	{
		if (Ch == '0')
		{
			ChPrevious = Ch;
			Ch = MFin.get();
		}
		else if (Ch == '.' && ChPrevious == '0')
			Finished = true;
		else
			Error = true;
	}

	//Reset the Finished flag for the next loop.
	Finished = false;

	//Read the digits after the decimal.
	for (i = 0; i < Target.MAX_PRECISION && !Error && !Finished; ++i)
	{
		Ch = MFin.get();
		if (isdigit(Ch))
			Target.Float[i] = Ch - '0';
		else if (!i)
			Error = true;
		else
			Finished = true;
	}

	//Put back the last character extracted from the input buffer because the TestMyFl program expects at
	//least one character in the input buffer.
	MFin.putback(Ch);

	//Determine what NumDigits gets set to.
	//	0 if there was an error
	//	(i - 1) if the previous loop encountered a non-numeric and finished because of that
	//	i if the previous loop retrieved MAX_PRECISION number of digits
	if (Error)
		Target.NumDigits = 0;
	else if (Finished)
		Target.NumDigits = i - 1;
	else
		Target.NumDigits = i;

	//Zero out the remainder of the array.
	for (i = Target.NumDigits; i < Target.MAX_PRECISION; ++i)
		Target.Float[i] = 0;

	return MFin;
}

/****************************** operator> *****************************************************************
Action:			Operator overload for > for MyFloat.  Compares two MyFloats and determines if the left hand
				side is greater than the right hand side.  Will compare MyFloats that are in an error
				status or are uninitalized (these are both considered to be the smallest possible value for
				a MyFloat) as well.  Note that trailing zeroes are deemed significant, so 0.123000 IS
				greater than 0.123.

Parameters:
IN:				const MyFloat &Other, holds the reference to the MyFloat object that will be compared to
				the calling MyFloat object.
OUT:			None

Returns:		const bool representing whether the left hand side MyFloat is greater than the right hand
				side MyFloat or not.

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
		//Only need to check the number of place up to the smaller of the two NumDigits.  This is because
		//anything beyond that does not matter for the purposes of this operator.
		unsigned char CheckedPrecision = (NumDigits < Other.NumDigits ? NumDigits : Other.NumDigits);

		for (unsigned char i = 0; i < CheckedPrecision && !IsLessThan && !IsGreaterThan; ++i)
			if (Float[i] < Other.Float[i])
				IsLessThan = true;
			else if (Float[i] > Other.Float[i])
				IsGreaterThan = true;

		//If both MyFloats are equal up to this point, check the number of digits.  If *this has more
		//significant digits than Other, it is greater than Other by virtue of being able to be greater
		//than (it doesn't matter whether the extra numbers are zeroes or not and the flag is changed to
		//indicate this.
		if (!IsLessThan && !IsGreaterThan)
			if (NumDigits > Other.NumDigits)
				IsGreaterThan = true;
	}

	return IsGreaterThan;
}

/****************************** operator== ****************************************************************
Action:			Operator overload for == for MyFloat.  Compares two MyFloats and determines if they are
				equal.  Will compare MyFloats that are in an error status or are uninitialized as well.
				Note that trailing zeroes are deemed significant, so 0.1 is NOT equal to 0.10.

Parameters:
IN:				const MyFloat &Other, holds the reference to the MyFloat object that will be compared to
				the calling MyFloat object.
OUT:			None

Returns:		const bool representing whether the two MyFloats are equal or not.

Precondition:	None
**********************************************************************************************************/
const bool MyFloat::operator==(const MyFloat &Other) const
{
	bool IsEqual = true;
	
	//Check to see if the number of digits are equal.  If not, no need to test every digit.
	//This assumes that the zeroes are significant even if entered after the last non-zero digit, e.g.
	//0.1000.  Therefore 0.1000 would not be equal to 0.10.
	if (NumDigits != Other.NumDigits)
		IsEqual = false;
	else
	{
		for (int i = 0; i < NumDigits && IsEqual; ++i)
			if (Float[i] != Other.Float[i])
				IsEqual = false;
	}

	return IsEqual;
}

/****************************** operator= *****************************************************************
Action:			Operator overload for = for MyFloat.  Converts a string representating a float between 0
				and 1 (for example: "0.14159") to a MyFloat.  Also zeroes out the unused portion of the
				MyFloat.

Parameters:
IN:				const char String[], holds the pointer to the null-terminating character array that will be
				read in as a MyFloat.
OUT:			None

Returns:		const MyFloat& referencing the calling MyFloat object now holding the contents of String[].

Precondition:	String must be a null-terminating character array the form "0.xyz", where xyz is a quantity
				(from 1 to MAX_PRECISION) of digits.
**********************************************************************************************************/
const MyFloat& MyFloat::operator=(const char String[])
{
	for (NumDigits = 0; String[NumDigits + 2]; ++NumDigits)
		Float[NumDigits] = String[NumDigits + 2] - '0';

	for (unsigned char i = NumDigits; i < MAX_PRECISION; ++i)
		Float[i] = 0;

	return *this;
}



//Class Constructors
/****************************** MyFloat *******************************************************************
Action:			Default constructor for the MyFloat class.  Sets NumDigits to 0 and also zeroes out the
				array Float.

Parameters:
IN:				None
OUT:			None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
MyFloat::MyFloat()
{
	NumDigits = 0;

	for (int i = 0; i < MAX_PRECISION; ++i)
		Float[i] = 0;
}
