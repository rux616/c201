/*************************************************************************
Name:  Brian Kolaczyk
Date:  January 31, 2014
Homework:  #1
Source File:
Action:  This program is designed to identify words in a text file and
tabulate word lengths in the file.
*************************************************************************/
int WordLength();

#include <iomanip>
#include <ctype.h>
#include <iostream>
using namespace std;

void main()
{
	int WordSize[16] = {0};
	float NumberOfWords = 0.0, TotalLength = 0.0;
	float AverageLength = 0.0;
	int LengthOfWord = 0;

	cout << "Please enter a sentence: ";

	LengthOfWord = WordLength();

	while (LengthOfWord)
	{
		if (LengthOfWord >= 15)
			WordSize[15] ++;
		else WordSize[LengthOfWord] ++;
		LengthOfWord = WordLength();
	}

	cout << "Word Length" << "          " << "Frequency" << endl;
	cout << "-----------" << "          " << "---------" << endl;
	for (int i = 1; i <= 15; ++i)
	{
		cout << setw(7) << i << setw(20) << WordSize[i] << endl;
		NumberOfWords = NumberOfWords + WordSize[i];
		TotalLength = TotalLength + (i * WordSize[i]);
	}
	AverageLength = TotalLength / NumberOfWords;
	if (NumberOfWords == 0)
		AverageLength = 0;

	cout << endl << "Average word length : " << AverageLength;
	cin.get();
}

/******************************************************************************
Action:  This function counts the number of letters in a given word
Parameters:
IN:  none
OUT: RVDT
Returns:  Integer value of letter count of a word
Precondition:
********************************************************************************/
int WordLength()
{
	char Ch;
	int EndOfWord = 0, Length = 0;
	cin >> Ch;
	while (!cin.eof() && !EndOfWord)
	{
		if (isalnum(Ch))
			++Length;
		Ch = cin.get();
		if (isspace(Ch) || ispunct(Ch) || cin.eof())
		{
			if (Ch == 39)
				++Length;
			else if (Ch == '-')
			{
				Ch = cin.get();
				if (Ch == '\n')
					Ch = cin.get();
				if (isalnum(Ch))
				{
					++Length;
					Ch = cin.get();
				}
				else ++EndOfWord;
			}
			else ++EndOfWord;
		}
	}
	return Length;
}