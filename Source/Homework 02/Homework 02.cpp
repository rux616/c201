/*
Name:			Dan Cassidy
Date:			2014-02-03
Homework #:		02
Source File:	Homework 02.cpp
Class:          C-201 MW 1000
Action:			This program asks the user to input a sentence, then replaces any instance of the word
				"hell" with the word "heck", matching case and ignoring matches inside words.  It can also
				be modified easily to specify the words to be checked and replaced.
*/

#include <iostream>
#include <cctype>
using namespace std;

void GetSentence(char []);
void CopyString(char [], char []);
void ShowSentences(char [], char []);
void Censor(char [], char [], char []);
bool IsMatch(char [], char [], bool = false);
int StringLength(char []);
void ReplaceString(char [], int, char [], int = 0);
void ResizeString(char [], int, int, char = ' ');

const int MAX_SENTENCE_LENGTH = 300;

void main()
{
	
	char Sentence[MAX_SENTENCE_LENGTH] = "";
	char CensoredSentence[MAX_SENTENCE_LENGTH] = "";

	char StringBad[] = "hell";						//This block can be swapped out with the commented
	char StringGood[] = "heck";						//block below to enter your own good and bad words.
	//char StringBad[20] = "";
	//char StringGood[20] = "";
	//
	//cout << "Enter the bad word: ";
	//cin.getline(StringBad, 20);
	//cout << "Enter the good word: ";
	//cin.getline(StringGood, 20);

	GetSentence(Sentence);

	while (Sentence[0])
	{
		CopyString(Sentence, CensoredSentence);
		Censor(CensoredSentence, StringBad, StringGood);
		ShowSentences(Sentence, CensoredSentence);
		GetSentence(Sentence);
	}

	cout << "Goodbye!\n";
}

/****************************** GetSentence ***************************************************************
Action:			Asks for and reads a full sentence of user input.

Parameters:
IN:				None
OUT:			char Sentence[], holds the sentence of user input

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
void GetSentence(char Sentence[])
{
	cout << "Enter a sentence: ";
	cin.getline(Sentence, MAX_SENTENCE_LENGTH);
}

/****************************** CopyString ****************************************************************
Action:			Copies the contents of OriginalString[] to CopiedString[] until it reaches a null character
				in OriginalString[].

Parameters:
IN:				char OriginalString[], holds the string to be copied
OUT:			char CopiedString[], holds the copied string from OriginalString[]

Returns:		Nothing

Precondition:	OriginalString[] must be a null-terminated character array.
**********************************************************************************************************/
void CopyString(char OriginalString[], char CopiedString[])
{
	CopiedString[0] = OriginalString[0];

	for (int i = 1; OriginalString[i - 1]; ++i)
		CopiedString[i] = OriginalString[i];
}

/****************************** ShowSentences *************************************************************
Action:			Displays Sentence[] and CensoredSentence[] inside quotes and labels each.

Parameters:
IN:				char Sentence[], 
IN:				char CensoredSentence[], 
OUT:			None

Returns:		Nothing

Precondition:	Sentence[] and CensoredSentence[] must be null-terminating character arrays.
**********************************************************************************************************/
void ShowSentences(char Sentence[], char CensoredSentence[])
{
	cout << "\nOriginal: \"" << Sentence << "\"\n";
	cout << "Censored: \"" << CensoredSentence << "\"\n\n";
	cout << "--------------------------------------------------------------------\n\n";
}

/****************************** Censor ********************************************************************
Action:			Searches StringCensored[] for the string contained in StringBad[] and replaces it with the
				string in StringGood[].

Parameters:
IN:				char StringCensored[], holds the string that is going to be searched for words to censor
IN:				char StringBad[], holds the bad word that will be censored
IN:				char StringGood[], holds the good word that the bad word will be changed to
OUT:			char StringCensored[], holds the string that has been censored

Returns:		Nothing

Precondition:	-StringCensored[], StringBad[], and StringGood[] must all be null-terminating character
				arrays.
				-StringBad[] must not be an empty string.
**********************************************************************************************************/
void Censor(char StringCensored[], char StringBad[], char StringGood[])
{
	char ChPrevious = '\0';
	char Ch = '\0';

	for (int i = 0; StringCensored[i]; ++i)
	{
		Ch = StringCensored[i];

		if (IsMatch(&StringCensored[i], StringBad))
			if (!isalnum(ChPrevious) && !isalnum(StringCensored[i + StringLength(StringBad)]))
			{
				ReplaceString(&StringCensored[i], StringLength(StringBad), StringGood);
				i += StringLength(StringGood) - 1;					//If part of the string is censored,
				Ch = StringCensored[StringLength(StringGood) - 1];	//jump the counter to the end of that
			}														//replaced portion to prevent possible
																	//infinite loops and help speed the
		ChPrevious = Ch;											//function up
	}
}

/****************************** IsMatch *******************************************************************
Action:			Checks the string StringToCheck[] for a match to StringToFind[], starting at subscript 0
				and going until a null is encountered in StringToFind[].  Matching is case sensitive if
				CaseSensitive is true.

Parameters:
IN:				char StringToCheck[], holds the string that will be checked to see whether it contains the
				string held by StringToFind[]
IN:				char StringToFind[], holds the string that will be searched for inside StringToCheck[]
IN:				bool CaseSensitive = true, tells the function whether the matching will be case sensitive
				or not
OUT:			None

Returns:		Bool that holds the result of whether StringToFind[] was found in StringToCheck[].

Precondition:	StringToCheck[] and StringToFind[] must be null-terminating character arrays.
**********************************************************************************************************/
bool IsMatch(char StringToCheck[], char StringToFind[], bool CaseSensitive)
{
	bool Matches = true;

	for (int i = 0; StringToFind[i] && Matches; ++i)
	{
		if (CaseSensitive)
		{
			if (StringToFind[i] != StringToCheck[i])
				Matches = false;
		}
		else
		{
			if (tolower(StringToFind[i]) != tolower(StringToCheck[i]))
				Matches = false;
		}
	}

	return Matches;
}

/****************************** StringLength **************************************************************
Action:			Measures the length of String[] until the first null is encountered.

Parameters:
IN:				char String[], holds the string that will be measured
OUT:			None

Returns:		Integer that holds the length of the string.

Precondition:	String[] must be a null-terminating character array.
**********************************************************************************************************/
int StringLength(char String[])
{
	int Length = 0;

	for (int i = 0; String[i]; ++i)
		++Length;

	return Length;
}

/****************************** ReplaceString *************************************************************
Action:			Replaces the first some number of characters (determined by NumCharToReplace) in String[]
				with ReplacementString[].

Parameters:
IN:				char String[], holds the string that have part of itself replaced by ReplacementString[]
IN:				int NumCharToReplace, holds the number of characters that are going to be replaced
IN:				char ReplacementString[], holds the string that will replace the number of characters
				specified by NumCharToReplace in String[]
IN:				int ReplacementCase = 0, tells the function what case to use when replacing the string: 0
				makes it match the case in String and if the character being replaced isn't a letter, it
				will use whatever the last case encountered was; 1 makes it lower case; 2 makes it upper
				case; 3 makes it whatever case the character in ReplacementString[] is
OUT:			char String[], holds the string that has had some of its characters replaced

Returns:		Nothing

Precondition:	-String[] and ReplacementString[] must be null-terminating character arrays.
				-NumCharToReplace must be positive.
**********************************************************************************************************/
void ReplaceString(char String[], int NumCharToReplace, char ReplacementString[], int ReplacementCase)
{
	int IsUpper = false;

	ResizeString(String, NumCharToReplace - 1, StringLength(ReplacementString) - NumCharToReplace);

	for (int i = 0; ReplacementString[i]; ++i)
	{
		switch (ReplacementCase)
		{
			case 0:
				//Smart Case Matching
				if (isalnum(String[i]))				//If the character to be replaced is alphanumeric,
					IsUpper = isupper(String[i]);	//place the case state of that char into IsUpper,
													//so that if the char is not alphanumeric, the
				if (IsUpper)						//replacement case will just carry over from the last.
					String[i] = toupper(ReplacementString[i]);
				else
					String[i] = tolower(ReplacementString[i]);
				break;

			case 1:
				//Lower Case
				String[i] = tolower(ReplacementString[i]);
				break;

			case 2:
				//Upper Case
				String[i] = toupper(ReplacementString[i]);
				break;

			case 3:
				//Ignore Case, use ReplacementString as is
				String[i] = ReplacementString[i];
				break;
		}
	}
}

/****************************** ResizeString **************************************************************
Action:			Resizes String[], starting at subscript ResizeAnchor, and then removes ResizeLength
				characters left (if ResizeLength is negative) or adds characters right (if ResizeLength is
				positive).

Parameters:
IN:				char String[], holds the string to be resized
IN:				int ResizeAnchor, holds the subscript of the character in String[] that will serve as the
				anchor for shrinking or expanding
IN:				int ResizeLength, holds the number of characters to shrink the array by (if negative) or
				expand the array by (if positive)
IN:				char Filler = ' ', holds the character that will be used as a filler when expanding
				String[]
OUT:			char String[], holds the ttring that has been shrunk or expanded (or left alone, if
				ResizeLength == 0

Returns:		Nothing

Precondition:	-String[] must be a null-terminating character array.
				-ResizeAnchor must not be larger than the length of String[] - 1.
				-If ResizeLength is negative (shrink), ResizeAnchor must be non-negative and (ResizeAnchor
				+ ResizeLength) must not be less than -1.
				-If ResizeLength is positive (expand), ResizeAnchor must not be less than -1 and (the
				length of String[] + ResizeLength) must not be greater than the largest subscript of
				String[].
				-Filler must not be a null character.
**********************************************************************************************************/
void ResizeString(char String[], int ResizeAnchor, int ResizeLength, char Filler)
{
	if (ResizeLength < 0)
	{
		//Shrink
		for (int i = ResizeAnchor + 1; String[i - 1]; ++i)
			String[i + ResizeLength] = String[i];
	}
	else if (ResizeLength > 0)
	{
		//If ResizeAnchor + ResizeLength is longer than the length of String[], prefill the space beyond
		//the null terminator of String with the contents of Filler.  This prevents having unknown values
		//in subscripts that aren't explicitly touched by the for loop during expansion.
		if (ResizeAnchor + ResizeLength > StringLength(String))
			for (int i = StringLength(String) + 1; i <= ResizeAnchor + ResizeLength; ++i)
				String[i] = Filler;

		//Expand
		for (int i = StringLength(String); i > ResizeAnchor; --i)
		{
			String[i + ResizeLength] = String[i];
			String[i] = Filler;			//Overwrites the character that was just read from to prevent some
		}								//cases of a null character still being there, such as when the
	}									//ResizeAnchor is 1 less than the length of String and ResizeLength
}										//is 1.

/*
PROGRAM OUTPUT

Test Case 1: Specific (Sentence = Hell, its hot as hell looking for shells in hell!)
	Tests the case sensitivity of the replacing functions, as well as the ability to ignore punctuation and
	determine if the word is alone (and should be replaced.)  This output will be extended, further output
	will be only the sentence portion in the interest of saving space.
		Enter a sentence: Hell, its hot as hell looking for shells in hell!

		Original: "Hell, its hot as hell looking for shells in hell!"
		Censored: "Heck, its hot as heck looking for shells in heck!"

		--------------------------------------------------------------------

		Enter a sentence:
		Goodbye!

Test Case 2: Specific (Sentence = Hello Hell!)
	Tests to make sure the program ignores the bad word embedded in other words, but still replaces it in a
	case-sensitive manner.
		Original: "Hello Hell."
		Censored: "Hello Heck."

Test Case 3: Normal (Sentence 1 = Debugging can be hell! ; Sentence 2 = Aw, hell.)
	Tests to make sure that the program can handle a second sentence that is shorter than the first.
		Enter a sentence: Debugging can be hell!

		Original: "Debugging can be hell!"
		Censored: "Debugging can be heck!"

		--------------------------------------------------------------------

		Enter a sentence: Aw, hell.

		Original: "Aw, hell."
		Censored: "Aw, heck."

Test Case 4: Normal (Sentence = .HeLl. HELL !helL* hEll's sHELL)
	Tests a variety of cases and punctuation around the words, as well as a word that contains the word be
	censored.
		Original: ".HeLl. HELL !helL* hEll's sHELL"
		Censored: ".HeCk. HECK !hecK* hEck's sHELL"

Test Case 5: Normal (Sentence: What in the world is going on?)
	Tests a normal sentence that has no need of replacing anything.
		Original: "What in the world is going on?"
		Censored: "What in the world is going on?"

Test Case 6: Limit (Sentence = He)
	Tests a short sentence to make sure the program doesn't try to match to match beyond the bounds and
	crash.
		Original: "He"
		Censored: "He"

Test Case 7: Limit (Sentence = Debugging can be hell)
	Tests a how the program handles a word to be replaced at the very end of a sentence.
		Original: "Debugging can be hell"
		Censored: "Debugging can be heck"
*/