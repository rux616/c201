/*************************************************************************

	AUTHOR		:	Dan Cassidy and John Russo and some by Matt Holloway

	SOURCE		:	Homework 09.cpp
					with the help from shell program a9shell.cpp

	DATE		:	2014-04-09

	COMPILER	:	Microsoft Visual Studio 2013

	ACTION		:	The program tests routines designed to perform various
					operations on singly linked lists. The lists have a
					dummy head node that holds the  character. The tail of
					the lists points to NULL.
					
					This is an extended program of homework #8
					The menu choices also all reading in a list from an
					external file and sorting a list.

*************************************************************************/
#ifndef SHELL
#define SHELL
#include "a9shell.cpp"
#endif

#include "Homework 08.cpp"
using namespace std;

/****************************   ReadList    *****************************

  DESCRIPTION   Builds a singly linked list with a dummy head node. The
                characters in the list are read in from an external file
                in the same order in which they are found in file.

                Input to list terminates when the End of File is encountered

  PARAMETERS

    IN, List    A pointer to a singly linked list with a dummy head node.
                It is imperative that List be initialized before calling
                this routine.

    IN, FileName  A pointer to a string that has the name of the file to
                  open, if error in opening then return a 1;

  RETURNS      1 if file opening error, 0 if read from file successful

  NOTE          Before building the new list, ZapList is called. This
                ensures that a memory leak does not develop.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int ReadList(NodePtr List, char FileName[])
{
	//Deletes current list to ensure memory leaks do not occur
	ZapList(List);

	ifstream fin;
	char Ch = 0;

	fin.open(FileName);

	if (fin.fail())
		//Opening of FileName was NOT successful
		return 1;

	fin.get(Ch);

	//Loop through FileName, reading sequential characters and adding them to the linked list
	while (!fin.eof())
	{
		//Declare new Node and attempt to allocate memory for it
		NodePtr NewNode = new(nothrow)Node;

		//Check if memory allocation was successful
		if (NewNode == NULL)
		{
			//Memory allocation error; close file then abort program
			fin.close();
			AbortProgram();
		}

		//Memory was allocated successfully; fill in the data for the new Node, making Link
		//NULL to guard against null pointers
		NewNode->Ch = Ch;
		NewNode->Link = NULL;

		//Add the new Node to the end of the linked list and then move List on to the new
		//final Node
		List->Link = NewNode;
		List = List->Link;

		fin.get(Ch);
	}

	fin.close();

	return 0;
}

/**************************  SortList ************************************

Description  Arranges the singly linked list pointed to by List in
             natural order.  It is assumed that the list has a dummy
             head node.

             The algorithm used is a linked variation of the selection
             sort and works like this:
             Start with EndSorted aimed at first node of list

             repeat
               Find smallest char between EndSorted and end of list
               Swap smallest element with char in EndSorted
               Change EndSorted to next node
             until we get to end of list

             None of the pointers in linked list are changed

Parameters
  IN, List  A pointer to a singly linked list with a dummy head node
-----------------------------------------------------------------------*/
void SortList(NodePtr List)
{
	if (List->Link == NULL)
		//Empty list
		return;

	NodePtr EndSorted = List->Link;

	//Iterates through the list, sorting as it goes
	while (EndSorted->Link != NULL)
	{
		NodePtr SearchNode = EndSorted->Link;
		NodePtr SmallNode = EndSorted;
		unsigned char TempCh = 0;

		//SearchNode iterates from the EndSorted+1 Node to end of list, finding the smallest
		//Node along the way and storing its address in SmallNode
		while (SearchNode != NULL)
		{
			if (SearchNode->Ch < SmallNode->Ch)
				SmallNode = SearchNode;
			SearchNode = SearchNode->Link;
		}

		//If SmallNode->Ch is different than EndSorted->Ch then it must be smaller; swap the
		//values utilizing a temporary storage variable
		if (SmallNode->Ch != EndSorted->Ch)
		{
			TempCh = EndSorted->Ch;
			EndSorted->Ch = SmallNode->Ch;
			SmallNode->Ch = TempCh;
		}

		//Iterate to the next link in the list
		EndSorted = EndSorted->Link;
	}
}

/*
PROGRAM OUTPUT

*** READLIST TESTS ***
NOTE: For tests 2 through 4, there is an extra line between lines that is put there by the
	  ShowList function and not by my ReadList function.

Test Case 1: Specific (Command: ReadList, Data: words.1)
	Tests that ReadList reads the file "words.1" correctly.
		The list created from the file -- words.1 --

		"This is fun!"

Test Case 2: Specific (Command: ReadList, Data: words.2)
	Tests that ReadList reads the file "words.2" correctly.
		The list created from the file -- words.2 --

		"My number is as fol-

		lows, (219) 237 - 4496.

		Two large numbers are

		123456789123456

		10000000000000005"

Test Case 3: Specific (Command: ReadList, Data: words.4)
	Tests that ReadList reads the file "words.4" correctly.
		The list created from the file -- words.4 --

		"hy-

		pen

		!!wishy-washy!!"

Test Case 4: Specific (Command: ReadList, Data: words.5
	Tests that ReadList reads the file "words.5" correctly.
		The list created from the file -- words.5 --

		"Did you ever wonder what happened to Dick, Jane, a
		nd Spot?  As you

		might expect, they lived happily ever after.  Jane
		 is a top account

		executive for a large brokerage firm.  Dick is a s
		enior engineer for

		a major computer vendor.  Spot passed away a few y
		ears ago, but he

		was happy to the end.  All of his success never al
		tered Spot's

		pleasant personality."

Test Case 5: Limit (Command: ReadList, Data: words.3)
	Tests that ReadList handles an empty file correctly.
		The list created from the file -- words.3 --

		""

Test Case 6: Limit (Command: ReadList, Data: non-existant file)
	Tests that ReadList handles a non-existant file correctly.
		Error in opening the file words.0
		Press ENTER KEY



*** SORTLIST TESTS ***

Test Case 7: Limit (Command: SortList, Linked List: Empty)
	Tests that SortList handles an empty list.
		List = ""

Test Case 8: Limit (Command: SortList, Linked List: 1)
	Tests that SortList handles a list with one element.
		List = "1"

Test Case 9: Limit (Command: SortList, Linked List: 21)
	Tests that SortList sorts a list with only two elements.
		List = "12"

Test Case 10: Limit (Command: SortList, Linked List: 11111)
	Tests that SortList handles a list with mutiples of only one value.
		List = "11111"

Test Case 11: Normal (Command: SortList, Linked List: 32221)
	Tests that SortList sorts a list with duplicates.
		List = "12223"

Test Case 12: Normal (Command: SortList, Linked List: 54321)
	Tests that SortList sorts a normal list correctly.
		List = "12345"

Test Case 13: Normal (Command: SortList, Linked List: cBa5!)
	Tests that SortList sorts a normal list correctly.
		List = "!5Bac"
*/