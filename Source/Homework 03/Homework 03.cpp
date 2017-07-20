/*
Name:			Dan Cassidy
Date:			2014-02-11
Homework #:		03
Source File:	Homework 03.cpp
Class:          C-201 MW 1000
Action:			
*/

#include <iostream>
#include <ctime>
#include <cctype>
#include <conio.h>
#include <algorithm>			//Included to enable the sort() function.
#include <iomanip>
using namespace std;

char ShowMenu();
void ExplainBirthdayParadox();
void VerifyBirthdayParadox();
void GenerateSortedBirthdaySet(int []);
void DisplayBirthdaySet();
void ConvertDayOfYear(int, int &, int &);
int DaysInMonth(int);

const int SAMPLE_SIZE = 23;
const int NUMBER_OF_SETS = 1000;

void main()
{
	char MenuChoice = 0;

	srand(time(NULL));

	do
	{
		MenuChoice = ShowMenu();

		cout << "----------------------------------------------------------------------------\n";

		switch (MenuChoice)
		{
			case '1':
				ExplainBirthdayParadox();
				cout << "----------------------------------------------------------------------------\n\n";
				break;

			case '2':
				VerifyBirthdayParadox();
				cout << "----------------------------------------------------------------------------\n\n";
				break;

			case '3':
				DisplayBirthdaySet();
				cout << "----------------------------------------------------------------------------\n\n";
				break;
		}
	} while (toupper(MenuChoice) != 'E');

}

/****************************** ShowMenu ******************************************************************
Action:			Shows the user a menu, gets their choice, validates their choice, and returns their choice
				to the calling function.

Parameters:
IN:				None
OUT:			None

Returns:		char holding the validated value of which menu choice the user picked

Precondition:	None
**********************************************************************************************************/
char ShowMenu()
{
	char Choice = 0;
	bool IsValidChoice = false;

	cout << "Please choose from the following menu:\n\n";
	cout << "  1)  Explain birthday paradox\n";
	cout << "  2)  Check birthday paradox by generating " << NUMBER_OF_SETS << " sets of birthdays\n";
	cout << "  3)  Display one set of " << SAMPLE_SIZE << " birthdays\n";
	cout << "  E)  Exit\n\n";
	cout << "Choice: ";

	do
	{
		Choice = toupper(_getch());
		switch (Choice)
		{
			case '1':
			case '2':
			case '3':
			case 'E':
				cout << Choice << "\n\n";
				IsValidChoice = true;
		}
	} while (!IsValidChoice);

	return Choice;
}

/****************************** ExplainBirthdayParadox ****************************************************
Action:			Displays the explanation of the birthday paradox.

Parameters:
IN:				None
OUT:			None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
void ExplainBirthdayParadox()
{
	cout << "If 23 persons are chosen at random, then the chances are more than 50% that\n"
		<< "at least two will have the same birthday!\n";
}

/****************************** VerifyBirthdayParadox *****************************************************
Action:			Verifies the birthday paradox by generating NUMBER_OF_SETS sets of SAMPLE_SIZE birthdays
				and then checking to see if any birthdays match in each of those sets.  When complete, it
				then displays the results.

Parameters:
IN:				None
OUT:			None

Returns:		Nothing

Precondition:	Nothing
**********************************************************************************************************/
void VerifyBirthdayParadox()
{
	int BirthdaySet[SAMPLE_SIZE] = { 0 };
	int NumberOfMatches = 0;
	bool IsMatch = false;

	cout << "Generating " << NUMBER_OF_SETS << " sets of " << SAMPLE_SIZE << " birthdays and checking "
		<< "for matches...\n\n";

	for (int i = 1; i <= NUMBER_OF_SETS; ++i)
	{
		GenerateSortedBirthdaySet(BirthdaySet);
		IsMatch = false;
		for (int j = 0; j < SAMPLE_SIZE - 1 && !IsMatch; ++j)
			if (BirthdaySet[j] == BirthdaySet[j + 1])
			{
				++NumberOfMatches;
				IsMatch = true;
			}
	}

	cout << setprecision(1) << setiosflags(ios::fixed);
	cout << "Results: " << NumberOfMatches << " out of " << NUMBER_OF_SETS << " (" <<
		(float)NumberOfMatches / NUMBER_OF_SETS * 100 << "%) of the sets contained matching birthdays\n";
}

/****************************** GenerateSortedBirthdaySet *************************************************
Action:			Generates an array of random numbers between 1 and 365 that is sorted from smallest to
				largest.

Parameters:
IN:				int BirthdaySet[], holds the pointer to the array that shall be filled and sorted
OUT:			int BirthdaySet[], holds the pointer to the array that contains sorted random numbers
				between 1 and 365

Returns:		Nothing

Precondition:	BirthdaySet[] must be an array of at least size SAMPLE_SIZE.
**********************************************************************************************************/
void GenerateSortedBirthdaySet(int BirthdaySet[])
{
	for (int i = 0; i < SAMPLE_SIZE; ++i)
		BirthdaySet[i] = rand() % 365 + 1;

	sort(BirthdaySet, BirthdaySet + SAMPLE_SIZE);	//Built-in sort function from <algorithm> header
}

/****************************** DisplayBirthdaySet ********************************************************
Action:			Generates and displays a human-readable table of birthdays, noting where there are
				multiples on one date.

Parameters:
IN:				None
OUT:			None

Returns:		Nothing

Precondition:	None
**********************************************************************************************************/
void DisplayBirthdaySet()
{
	const int COLUMNS = 4;

	char *MonthName[13] = { "ERROR", "January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December" };

	int BirthdaySet[SAMPLE_SIZE + 1] = { 0 };
	int SameCount = 1, DisplayCount = 0;
	int MonthNumber = 0, DayNumber = 0;

	GenerateSortedBirthdaySet(BirthdaySet);

	cout << "Here are the results of generating a set of " << SAMPLE_SIZE << " birthdays:\n\n";

	for (int i = 0; i < SAMPLE_SIZE; ++i)
		if (BirthdaySet[i] == BirthdaySet[i + 1])
			++SameCount;
		else
		{
			//All the cout statements in this code block may seem extraneous, but I found it to be the
			//most effective way to control the formatting of the table.
			
			++DisplayCount;				//Variable used to track how many columns have actually displayed
										//so that a \n can be used at the appropriate time.
			ConvertDayOfYear(BirthdaySet[i], MonthNumber, DayNumber);

			if (SameCount > 9)
				cout << "(" << SameCount << ") ";
			else if (SameCount > 1)
				cout << " (" << SameCount << ") ";
			else
				cout << "     ";

			cout << setiosflags(ios::left) << setw(9) << MonthName[MonthNumber];

			cout << " ";
			
			cout << resetiosflags(ios::left) << setw(2) << DayNumber;
			
			if (!(DisplayCount % COLUMNS) || i == SAMPLE_SIZE - 1)
				cout << "\n";
			else
				cout << "  ";
			
			SameCount = 1;				//Reset SameCount for the next iteration of the for loop
		}
	//cout << "\n";
}

/****************************** ConvertDayOfYear **********************************************************
Action:			Converts the raw day of the year, 1-365, into a month number and a day (of the month)
				number.

Parameters:
IN:				int DayOfYear, holds the raw day of the year
OUT:			int MonthNumber, holds the month number that the day of the year falls in
OUT:			int DayNumber, holds the day number that the day of the year converts to

Returns:		Nothing

Precondition:	DayOfYear should be greater than of equal to 1 and less than or equal to 365.
**********************************************************************************************************/
void ConvertDayOfYear(int DayOfYear, int &MonthNumber, int &DayNumber)
{
	MonthNumber = 1;

	while (DayOfYear > DaysInMonth(MonthNumber))
	{
		DayOfYear -= DaysInMonth(MonthNumber);
		++MonthNumber;
	}

	DayNumber = DayOfYear;
}

/****************************** DaysInMonth ***************************************************************
Action:			Finds the number of days in a given month, provided by MonthNumber.

Parameters:
IN:				int MonthNumber, holds the month number of which to find the days
OUT:			None

Returns:		int that holds the number of days in the given month

Precondition:	MonthNumber should be greather than or equal to 1 and less than or equal to 12.
**********************************************************************************************************/
int DaysInMonth(int MonthNumber)
{
	switch (MonthNumber)
	{
		case 2:
			return 28;

		case 4:
		case 6:
		case 9:
		case 11:
			return 30;

		default:
			return 31;
	}
}

/*
PROGRAM OUTPUT

Test Case 1: Specific (Menu)
	Tests to make sure the menu displays properly.
		Please choose from the following menu:

		  1)  Explain birthday paradox
		  2)  Check birthday paradox by generating 1000 sets of birthdays
		  3)  Display one set of 23 birthdays
		  E)  Exit

		Choice:

Test Case 2: Specific (Option 1: Explain)
	Tests to make sure that the explanation displays properly.
		----------------------------------------------------------------------------
		If 23 persons are chosen at random, then the chances are more than 50% that
		at least two will have the same birthday!
		----------------------------------------------------------------------------

Test Case 3: Specific (Option 2: Verify, 5 run-throughs)
	Tests to make sure that the verification works properly.
		Run 1
		----------------------------------------------------------------------------
		Generating 1000 sets of 23 birthdays and checking for matches...

		Results: 494 out of 1000 (49.4%) of the sets contained matching birthdays
		----------------------------------------------------------------------------

		Run 2
		----------------------------------------------------------------------------
		Generating 1000 sets of 23 birthdays and checking for matches...

		Results: 520 out of 1000 (52.0%) of the sets contained matching birthdays
		----------------------------------------------------------------------------

		Run 3
		----------------------------------------------------------------------------
		Generating 1000 sets of 23 birthdays and checking for matches...

		Results: 523 out of 1000 (52.3%) of the sets contained matching birthdays
		----------------------------------------------------------------------------

		Run 4
		----------------------------------------------------------------------------
		Generating 1000 sets of 23 birthdays and checking for matches...

		Results: 520 out of 1000 (52.0%) of the sets contained matching birthdays
		----------------------------------------------------------------------------

		Run 5
		----------------------------------------------------------------------------
		Generating 1000 sets of 23 birthdays and checking for matches...

		Results: 497 out of 1000 (49.7%) of the sets contained matching birthdays
		----------------------------------------------------------------------------

Test Case 4: Specific (Option 3: Display Set, No Duplicates)
	Tests to make sure that the program displays a basic no-duplicate set properly.
		----------------------------------------------------------------------------
		Here are the results of generating a set of 23 birthdays:

			 January   17       January   19       January   20       January   25
			 February   7       February   9       February  22       March     10
			 April     16       April     24       April     26       May        3
			 May       23       May       26       June      16       June      18
			 August    11       September 18       October    2       November   6
			 November  14       December  27       December  28
		----------------------------------------------------------------------------

Test Case 5: Specific (Option 3: Display Set, 1 Duplicate)
	Tests to make sure that the program displays the sample birthday set appropriately when it has
	a duplicate in it.
		----------------------------------------------------------------------------
		Here are the results of generating a set of 23 birthdays:

			 February  10       March      2       March      7       April     18
			 April     19       April     30       May        8       May       11
			 June      14       June      16       July      10       July      23
			 August     3       August    28       September  6       September 13
			 September 25   (2) October    4       October   28       October   29
			 November   7       November  29
		----------------------------------------------------------------------------

Test Case 6: Specific (Option 3: Display Set, Multiple Duplicates)
	Tests to make sure that the program displays the sample birthday set appropriately when there are
	multiple duplicates.
		----------------------------------------------------------------------------
		Here are the results of generating a set of 23 birthdays:

			 January    7       January   29       February  18       March     16
			 March     22       March     29       April      9       April     11
			 April     29       May       26       June       4       July      16
			 August    18   (2) September  1       September  9   (2) October    4
			 October   15       December   3       December  22       December  25
			 December  29
		----------------------------------------------------------------------------

Test Case 7: Specific (Option 3: Display Set, Matches at Beginning and End of Set)
	Tests to make sure the program can handle having matches at the beginning and end of the set and
	doesn't exceed the bounds of the array.
		----------------------------------------------------------------------------
		Here are the results of generating a set of 23 birthdays:

		 (2) January    4       February   3       April      3       April     12
			 May       11       May       14       May       15       May       18
			 May       21       May       25       July      10       July      15
			 August    29       October    1       October    5       October   11
			 October   20       October   24       November  29       December   6
		 (2) December  23
		----------------------------------------------------------------------------

Test Case 8: Specific (Option 3: Display Set, Extreme Match)
	Tests to make sure that in the exceptionally unlikely event that all the numbers were to match, the
	program could display the output appropriately.
		----------------------------------------------------------------------------
		Here are the results of generating a set of 23 birthdays:

		(23) February   1
		----------------------------------------------------------------------------

Test Case 9: Specific (Option E, Exit)
	Tests to make sure that the program exits after 'E' is pressed.
		Please choose from the following menu:

		  1)  Explain birthday paradox
		  2)  Check birthday paradox by generating 1000 sets of birthdays
		  3)  Display one set of 24 birthdays
		  E)  Exit

		Choice: E

		----------------------------------------------------------------------------
		Press any key to continue . . .
Test Case 10: Limit (Option 3: Display Set, Month Breakpoints)
	Test Data:
		BirthdaySet[0] = 1; BirthdaySet[1] = 31; BirthdaySet[2] = 32; BirthdaySet[3] = 59;
		BirthdaySet[4] = 60; BirthdaySet[5] = 90; BirthdaySet[6] = 91; BirthdaySet[7] = 120;
		BirthdaySet[8] = 121; BirthdaySet[9] = 151; BirthdaySet[10] = 152; BirthdaySet[11] = 181;
		BirthdaySet[12] = 182; BirthdaySet[13] = 212; BirthdaySet[14] = 213; BirthdaySet[15] = 243;
		BirthdaySet[16] = 244; BirthdaySet[17] = 273; BirthdaySet[18] = 274; BirthdaySet[19] = 304;
		BirthdaySet[20] = 305; BirthdaySet[21] = 334; BirthdaySet[22] = 335; BirthdaySet[23] = 365;
	Uses a SAMPLE_SIZE of 24 to make sure that the ConvertDayOfYear and DaysInMonth functions are working 
	for all the transition periods of the months (beginnings and ends.)
		----------------------------------------------------------------------------
		Here are the results of generating a set of 24 birthdays:

			 January    1       January   31       February   1       February  28
			 March      1       March     31       April      1       April     30
			 May        1       May       31       June       1       June      30
			 July       1       July      31       August     1       August    31
			 September  1       September 30       October    1       October   31
			 November   1       November  30       December   1       December  31
		----------------------------------------------------------------------------
*/