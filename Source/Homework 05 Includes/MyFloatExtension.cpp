/*
Name:			Dan Cassidy
Date:			2014-03-02
Homework #:		05
Source File:	MyFloat.cpp
Class:          C-201 MW 1000
Action:			This file has the raw data for a couple operator overloads of the MyFloat class.
						
				Class Member Functions:

					MyFloat operator+=(const MyFloat &Other) const
						Operator overload for += for MyFloat.  Adds a MyFloat to the calling MyFloat
						object.

					const bool operator!=(const MyFloat &Other) const
						Operator overload for != for MyFloat.  Simply returns the ! value of the ==
						operator.

				Detailed descriptions of the member functions can be found further down in the file.
*/

//MYFLOATEXTENSION ABSTRACTION
class MyFloat
{
	public:
	//Additional Operator Overloads
	MyFloat operator+=(const MyFloat &Other);
	const bool operator!=(const MyFloat &Other) const;
};

//MYFLOATEXTENSION IMPLEMENTATION
#include <iostream>
using namespace std;

/****************************** operator+= ****************************************************************
Action:			Operator overload for += for MyFloat.  Adds a MyFloat to the calling MyFloat object.

Parameters:
IN:				MyFloat &Other, holds the reference to the MyFloat that will be added to the calling
				MyFloat object.
OUT:			None

Returns:		the calling MyFloat object

Precondition:	None
**********************************************************************************************************/
MyFloat MyFloat::operator+=(const MyFloat &Other)
{
	*this = (*this + Other);
	return *this;
}

/****************************** operator!= ****************************************************************
Action:			Operator overload for != for MyFloat.  Returns the opposite value of the == operator.
				Compares two MyFloats and determines if they are equal.  Note that trailing zeroes are
				deemed significant, so 0.1 is NOT equal to 0.10.

Parameters:
IN:				MyFloat &Other, holds the reference to the MyFloat that is going to be compared against.
OUT:			None

Returns:		bool representing whether the two MyFloats are equal or not.

Precondition:	None
**********************************************************************************************************/
const bool MyFloat::operator!=(const MyFloat &Other) const
{
	return !(*this == Other);
}
