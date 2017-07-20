/*
Name:			Dan Cassidy
Date:			2014-01-28
Homework #:		01
Source File:	Homework 01.cpp
Class:          C-201 MW 1000
Action:			This program is designed to read input via a redirected file from the command prompt, count
				the number of words and each of their lengths, and display the list of word lengths and how
				many there are.

				The specifics of what constitutes a word as well as the caveats are detailed in the
				function comments for WordLength.
*/

#include <iostream>
#include <cctype>
#include <iomanip>

using namespace std;

int WordLength();
void OutputResults(int[]);

const int MAX_WORD_LENGTH = 15;

void main()
{
	int WordLengthList[MAX_WORD_LENGTH + 1] = {0};

	do
	{
		++WordLengthList[WordLength()];
	} while (!WordLengthList[0]);

	OutputResults(WordLengthList);
}

/****************************** WordLength ****************************************************************
Action:			Determines the length of any word inputted through standard input using the following
				rules:
				1. Alphanumeric characters are always counted.
				2. Apostrophies are counted except for multiples and individual apostrophies by themselves.
				3. Underscores are counted except for multiples, individual underscores by themselves, and
				   those that are leading or trailing.
				4. Hyphens are counted except for multiples, individual hyphens by themselves, those that
				   are leading or trailing, and those that are breaking up a word over multiple lines.
				5. Whitespace is used as a delimiter for words.
				6. Other punctuation is always ignored.

Parameters:
IN:				None 
OUT:			None

Returns:		The length of the word that has been parsed.

Precondition:	Due to the way this function works, certain strings containing mixes of apostrophies,
				hyphens, and underscores will be counted as words, e.g. -_' will be counted as a word of
				length two.
**********************************************************************************************************/
int WordLength()
{
	char Ch = 0;
	char ChPrevious = ' ';		// Default value of ' ' so that the function can appropriately discard
	char ChNext = 0;			// leading hyphens and underscores.
	int Count = 0;

	cin.get(Ch);

	while (!cin.eof())
	{
		ChNext = cin.peek();

		if (isalnum(Ch))
		{
			++Count;
		}
		else if (Ch == '\'')
		{
			// Increments Count only if Ch is not multiple and is part of a word
			if (ChPrevious != '\'' && ChNext != '\'' && !(isspace(ChPrevious) && isspace(ChNext)))
				++Count;
		}
		else if (Ch == '_')
		{
			// Increments Count only if Ch is not mutiple, is part of a word, and is not leading/trailing
			if (ChPrevious != '_' && ChNext != '_' && !isspace(ChPrevious) && !isspace(ChNext))
				++Count;
		}
		else if (Ch == '-')
		{
			// Increments Count only if Ch is not multiple, is part of a word, and is not-leading/trailing
			if (ChPrevious != '-' && ChNext != '-' && !isspace(ChPrevious) && !isspace(ChNext))
				++Count;
		}
		else if (isspace(Ch))
		{
			// Breaks out of the while loop if the whitespace encountered is not '\n' with a preceeding '-'
			// and Count is not zero.
			if (Count && !(ChPrevious == '-' && Ch == '\n'))
				break;
		}

		ChPrevious = Ch;
		cin.get(Ch);
	}

	return (Count > MAX_WORD_LENGTH) ? MAX_WORD_LENGTH : Count;
}

/****************************** OutputResults *************************************************************
Action:			Displays a list of the word lengths and how many words of specified lengths.  Also
				calculates and displays the average word length to the nearest tenth.

Parameters:
IN:				int WordLengthList[], holds the list of how many words are what length.
OUT:			None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
void OutputResults(int WordLengthList[])
{
	const int PRECISION = 7;
	const int WIDTH = 2;

	int TotalWordLength = 0;
	int NumberOfWords = 0;

	cout << "Word Length         Frequency\n";
	cout << "-----------         ---------\n";

	for (int i = 1; i <= MAX_WORD_LENGTH; ++i)
	{
		TotalWordLength += WordLengthList[i] * i;
		NumberOfWords += WordLengthList[i];
		cout << "     " << setw(WIDTH) << i << "                 " << setw(WIDTH) << WordLengthList[i]
			 << "\n";
	}

	cout << setprecision(PRECISION);
	cout << "\nAverage word length: " << (NumberOfWords ? (float)TotalWordLength / NumberOfWords : 0);
}

/*
PROGRAM OUTPUT

Test Case 1: Specific (Redirected input file: words.1)
	Tests that the program handles normal input, including punctuation.
		Word Length         Frequency
		-----------         ---------
			  1                  0
			  2                  1
			  3                  1
			  4                  1
			  5                  0
			  6                  0
			  7                  0
			  8                  0
			  9                  0
			 10                  0
			 11                  0
			 12                  0
			 13                  0
			 14                  0
			 15                  0

		Average word length: 3

Test Case 2: Specific (Redirected input file: words.2)
	Tests that the program handles hyphens breaking up words across lines correctly, as well as handling
	words that are larger than the MAX_WORD_LENGTH.
		Word Length         Frequency
		-----------         ---------
			  1                  0
			  2                  3
			  3                  4
			  4                  1
			  5                  1
			  6                  1
			  7                  2
			  8                  0
			  9                  0
			 10                  0
			 11                  0
			 12                  0
			 13                  0
			 14                  0
			 15                  2

		Average word length: 5.5

Test Case 3: Specific (Redirected input file: words.3)
	Tests that the program handles empty input appropriately.
		Word Length         Frequency
		-----------         ---------
			  1                  0
			  2                  0
			  3                  0
			  4                  0
			  5                  0
			  6                  0
			  7                  0
			  8                  0
			  9                  0
			 10                  0
			 11                  0
			 12                  0
			 13                  0
			 14                  0
			 15                  0

		Average word length: 0

Test Case 4: Specific (Redirected input file: words.4)
	Tests that the program doesn't count, but handles hyphens breaking up words over two lines and also
	counts hyphens that are in the middle of a word.
		Word Length         Frequency
		-----------         ---------
			  1                  0
			  2                  0
			  3                  0
			  4                  0
			  5                  1
			  6                  0
			  7                  0
			  8                  0
			  9                  0
			 10                  0
			 11                  1
			 12                  0
			 13                  0
			 14                  0
			 15                  0

		Average word length: 8

Test Case 5: Specific (Redirected input file: words.5)
	Tests a larger input of "normal" text and apostrophies.
		Word Length         Frequency
		-----------         ---------
			  1                  5
			  2                  7
			  3                 15
			  4                 12
			  5                  8
			  6                  6
			  7                  4
			  8                  4
			  9                  2
			 10                  0
			 11                  1
			 12                  0
			 13                  0
			 14                  0
			 15                  0

		Average word length: 4.328125

Test Case 6: Custom
	Input data:
		'a ab' _abc abcd_ -abcde abcdef-
		abc''defg abc--defgh ab___cdefghi
	Tests the ability of the program to ignore leading and trailing hyphens and underscores, and to ignore
	multiples.
		Word Length         Frequency
		-----------         ---------
			  1                  0
			  2                  1
			  3                  2
			  4                  1
			  5                  1
			  6                  0
			  7                  0
			  8                  1
			  9                  1
			 10                  0
			 11                  0
			 12                  0
			 13                  1
			 14                  0
			 15                  0

		Average word length: 5.875

Test Case 7: Custom
	Input data:
		' '' '''
		- -- ---
		_ __ ___
	Tests how the program handles single and multiple isolated groupings.
		Word Length         Frequency
		-----------         ---------
			  1                  0
			  2                  0
			  3                  0
			  4                  0
			  5                  0
			  6                  0
			  7                  0
			  8                  0
			  9                  0
			 10                  0
			 11                  0
			 12                  0
			 13                  0
			 14                  0
			 15                  0

		Average word length: 0

Test Case 8: Custom
	Input data:
		-_- _-_ -_' '-'
	Demonstrates some of the limitations of the program when different special punctuation marks are mixed.
		Word Length         Frequency
		-----------         ---------
			  1                  2
			  2                  1
			  3                  1
			  4                  0
			  5                  0
			  6                  0
			  7                  0
			  8                  0
			  9                  0
			 10                  0
			 11                  0
			 12                  0
			 13                  0
			 14                  0
			 15                  0

		Average word length: 1.75

Test Case 9: Custom
	Input data:
		Uses the output data from words.5
	Tests the program's ability to handle differing amounts of whitespace.
		Word Length         Frequency
		-----------         ---------
			  1                 22
			  2                  8
			  3                  0
			  4                  2
			  5                  0
			  6                  2
			  7                  2
			  8                  0
			  9                  1
			 10                  0
			 11                  0
			 12                  0
			 13                  0
			 14                  0
			 15                  0

		Average word length: 2.189189
*/