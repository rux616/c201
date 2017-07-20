/*
Name:			Dan Cassidy
Date:			2014-03-02
Homework #:		05
Source File:	MyFloat.cpp
Class:          C-201 MW 1000
Action:			This file represents the detailed abstraction and implementation of the Abstract Data Type
				"MyFloat", which is a highly precise decimal (up to 20 digits) between 0 and 1.
				
				In this implementation of the class, trailing zeroes are deemed significant as they specify
				exactly how precise a given MyFloat should be.  This means that when comparing two
				MyFloats, even if the values evaluate to the same thing when precision is taken out of the
				picture, e.g. 0.10 being compared to 0.1000, if the precision isn't the same, they are
				considered not equal.
				
				When adding two MyFloats, any result larger than 1 is automatically ignored, e.g. 0.52 + 
				0.61 = 0.13.

				Class Members:
				
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

					int Digits()
						Returns the number of digits in a MyFloat.  If it returns 0 then that means there
						has been an illegally formatted float or the MyFloat has not been initialized yet.

					int MaxDigits()
						Returns the maximum number of digits in a MyFloat.

					void Read()
						Reads a MyFloat from standard input.  If an error is detected, NumDigits is set to
						0.  Also puts the last character read from the input buffer back into it, and
						zeroes out the rest of the array.

					void Write()
						Writes a leading zero, a decimal point, and then the contents of the MyFloat.  If
						there has been an error in reading, it will output a question mark instead of the
						contents of the MyFloat after the leading zero and decimal point.

					const MyFloat operator+(const MyFloat &Other) const
						Operator overload for + for MyFloat.  Adds two MyFloats together.  If either
						MyFloat object is in an error state, this operation will return an uninitialized
						MyFloat object.

					const bool operator==(const MyFloat &Other) const
						Operator overload for == for MyFloat.  Compares two MyFloats and determines if they
						are equal.  Will compare MyFloats that are in an error status or are uninitialized
						as well.Note that trailing zeroes are deemed significant, therefore 0.1 is NOT
						equal to 0.10.

					MyFloat()
						Default constructor which initializes the contents of Float to 0 and sets NumDigits
						to 0 as well.

				Detailed descriptions of the member functions can be found further down in the file.
*/



//MYFLOAT ABSTRACTION
class MyFloat
{
	private:
	enum { MAX_PRECISION = 20 };
	unsigned char Float[MAX_PRECISION];
	unsigned char NumDigits;

	public:
	//Member Functions
	int Digits();
	int MaxDigits();
	void Read();
	void Write();

	//Operator Overloads
	const MyFloat operator+(const MyFloat &Other) const;
	const bool operator==(const MyFloat &Other) const;

	//Constructor
	MyFloat();

	friend void AssignValue(MyFloat& X);
};



//MYFLOAT IMPLEMENTATION
#include <iostream>
using namespace std;

/****************************** Digits ********************************************************************
Action:			Returns the number of digits in a MyFloat.  If 0 is returned, then an illegally formatted
				float has been detected or the MyFloat has not been initialized yet.

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
Action:			Returns the maximum number of possible digits in a MyFloat.

Parameters:
IN:				None
OUT:			None

Returns:		int representing the maximum number of possible digits in a MyFloat.

Precondition:	None
**********************************************************************************************************/
int MyFloat::MaxDigits()
{
	return int(MAX_PRECISION);
}

/****************************** Read **********************************************************************
Action:			Reads a MyFloat from standard input.  If an error is detected, NumDigits is set to 0.  Also
				puts the last character read from the input buffer back into it, and zeroes out the rest of
				the array.

Parameters:
IN:				None
OUT:			None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
void MyFloat::Read()
{
	char Ch = 0, ChPrevious = 0;
	bool Error = false, Finished = false;
	int i = 0;

	//Do the initial read of the data and discard any leading spaces and zeroes, and the decimal point.
	cin >> Ch;
	while (!Error && !Finished)
	{
		if (Ch == '0')
		{
			ChPrevious = Ch;
			Ch = cin.get();
		}
		else if (Ch == '.' && ChPrevious == '0')
			Finished = true;
		else
			Error = true;
	}

	//Reset the Finished flag for the next loop.
	Finished = false;

	//Read the digits after the decimal.
	for (i = 0; i < MAX_PRECISION && !Error && !Finished; ++i)
	{
		Ch = cin.get();
		if (isdigit(Ch))
			Float[i] = Ch - '0';
		else if (!i)
			Error = true;
		else
			Finished = true;
	}

	//Put back the last character extracted from the input buffer because the TestMyFl program expects at
	//least one character in the input buffer.
	cin.putback(Ch);

	//Determine what NumDigits gets set to.
	//	0 if there was an error
	//	(i - 1) if the previous loop encountered a non-numeric and finished because of that
	//	i if the previous loop retrieved MAX_PRECISION number of digits
	if (Error)
		NumDigits = 0;
	else if (Finished)
		NumDigits = i - 1;
	else
		NumDigits = i;

	//Zero out the remainder of the array.
	for (i = NumDigits; i < MAX_PRECISION; ++i)
		Float[i] = 0;
}

/****************************** Write *********************************************************************
Action:			Writes a leading zero, a decimal point, and then the contents of the MyFloat.  If there has
				been an error in reading, it will output a question mark instead of the contents of the
				MyFloat after the leading zero and decimal point.

Parameters:
IN:				None
OUT:			None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
void MyFloat::Write()
{
	cout << "0.";

	if (!NumDigits)
	{
		cout << "?";
	}
	else
	{
		for (int i = 0; i < NumDigits; ++i)
			cout << (int)Float[i];
	}
}

/****************************** operator+ *****************************************************************
Action:			Operator overload for + for MyFloat.  Adds two MyFloats together.  If either MyFloat object
				is in an error state or is uninitialized, this operation will return an uninitialized
				MyFloat object.

Parameters:
IN:				MyFloat &Other, holds the reference to the MyFloat that will be added to the calling
				MyFloat object.
OUT:			None

Returns:		const MyFloat representing the sum of the two MyFloats, or an uninitialized MyFloat if one
				or both of the MyFloats were in an error state or uninitialized themselves.

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

/****************************** operator== ****************************************************************
Action:			Operator overload for == for MyFloat.  Compares two MyFloats and determines if they are
				equal.  Will compare MyFloats that are in an error status or are uninitialized as well.
				Note that trailing zeroes are deemed significant, so 0.1 is NOT equal to 0.10.

Parameters:
IN:				MyFloat &Other, holds the reference to the MyFloat that is going to be compared against.
OUT:			None

Returns:		bool representing whether the two MyFloats are equal or not.

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
