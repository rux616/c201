#include <iostream>
#include <cctype>
#include <conio.h>

using namespace std;

/****************************** ShowMenu ******************************************************************
Action:			Displays a menu then gets the choice and sends it back to the calling function.

Parameters:
IN:				char *MenuItems[], holds the different menu item texts
IN:				char MenuChoices[], holds the different menu choices
IN:				int NumItems, holds the number of menu items
IN:				bool CaseSensitive = false, determines whether the validation is case-sensitive or not
OUT:			None

Returns:		char Choice, holds the valid choice of the user.

Precondition:	NumItems should be kept under 21 to make sure the user doesn't have to scroll.
				MenuItems should each be less than 73 characters long, and must be a null-terminating character array.
**********************************************************************************************************/
char ShowMenu(char *MenuItems[], char MenuChoices[], int NumItems, bool CaseSensitive = false)
{
	char Choice = 0;
	bool IsValidChoice = false;

	cout << "Please choose from the following menu:\n\n";

	for (int i = 0; i < NumItems; ++i)
		cout << "  " << MenuChoices[i] << ")  " << MenuItems[i] << "\n";

	do
	{
		Choice = _getch();
		for (int i = 0; i < NumItems && !IsValidChoice; ++i)
			if (CaseSensitive)
			{
				if (Choice == MenuChoices[i])
					IsValidChoice = true;
			}
			else
			{
				if (tolower(Choice) == tolower(MenuChoices[i]))
					IsValidChoice = true;
			}
	} while (!IsValidChoice);

	return Choice;
}
