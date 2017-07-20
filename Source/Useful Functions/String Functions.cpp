#include <iostream>
#include <cctype>
using namespace std;

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

	for (int i = 0; StringCensored[i] != '\0'; ++i)
	{
		Ch = StringCensored[i];

		if (IsMatch(&StringCensored[i], StringBad))
			if (!isalnum(ChPrevious) && !isalnum(StringCensored[i + StringLength(StringBad)]))
			{
				ReplaceString(&StringCensored[i], StringLength(StringBad), StringGood);
				i += StringLength(StringGood - 1);					//If part of the string is censored,
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
bool IsMatch(char StringToCheck[], char StringToFind[], bool CaseSensitive = false)
{
	bool Matches = true;

	for (int i = 0; StringToFind[i] != '\0' && Matches; ++i)
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

	for (int i = 0; String[i] != '\0'; ++i)
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
void ReplaceString(char String[], int NumCharToReplace, char ReplacementString[], int ReplacementCase = 0)
{
	int IsUpper = false;

	ResizeString(String, NumCharToReplace - 1, StringLength(ReplacementString) - NumCharToReplace);

	for (int i = 0; ReplacementString[i] != '\0'; ++i)
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
void ResizeString(char String[], int ResizeAnchor, int ResizeLength, char Filler = ' ')
{
	if (ResizeLength < 0)
	{
		//Shrink
		for (int i = ResizeAnchor + 1; String[i - 1] != '\0'; ++i)
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
