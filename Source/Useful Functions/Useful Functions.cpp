#include <iostream>
#include <iomanip>
using namespace std;

/****************************** GCD ***********************************************************************
Action:			Uses Euclid's algorithm to return the greatest common divisor of two numbers

Paremeters:		
	IN:			int Num1, integer that holds the first number to analyze
	IN:			int Num2, integer that holds the second number to analyze
	OUT:		None

Returns:		Integer that holds the greatest common divisor of int Num1 and int Num2

Precondition:	None
**********************************************************************************************************/
int GCD(int Num1, int Num2)
{
	int Temp;

	while (Num2 != 0)
	{
		Temp = Num2;
		Num2 = Num1 % Num2;
		Num1 = Temp;
	}

	return Num1;
}

/****************************** NumLength *****************************************************************
Action:			Determines the number of digits in a number

Paremeters:		
	IN:			int Num, holds the number whose length is to be determined
	OUT:		None

Returns:		The number of digits of int Num

Precondition:	None
**********************************************************************************************************/
unsigned NumLength(int Num)
{
	int Count = 1;
	if (Num < 0)
	{
		++Count;
		Num = -Num;
	}
	
	while (Num >= 10)
	{
		++Count;
		Num /= 10;
	}

	return Count;
}

/****************************** DisplayCentered ***********************************************************
Action:			Displays a number that is centered in a field of Width number of characters

Paremeters:		
	IN:			int Num, holds the number which will be centered
	IN:			unsigned Width, holds the width of the output
	IN:			char Padding, optional, is the character that will be the padding for the output, default
				is a space
	IN:			bool Left, determines whether to show int Num with left hand centering or right hand
				centering; e.g. " 1  " or "  1 "
	OUT:		None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
void DisplayCentered(int Num, unsigned Width, char Padding=' ', bool Left=true)
{
	unsigned NumLen = NumLength(Num);

	if (NumLen > Width)
		Width = NumLen;

	if (Width == NumLen)
		cout << Num;
	else
	{
		cout << setfill(Padding);

		cout << setw(int((Width + NumLen) / 2.0 + (Left ? 0 : 0.5))) << Num;

		if (int((Width - NumLen) / 2.0 + (Left ? 0.5 : 0)) != 0)
			cout << setw(int((Width - NumLen) / 2.0 + (Left ? 0.5 : 0))) << Padding;
	}
}

