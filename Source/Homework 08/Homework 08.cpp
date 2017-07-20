/*************************************************************************

   AUTHOR   :  Dan Cassidy      (with John Russo and modified some
                                     by Matt Holloway)

   SOURCE   :  Homework 08.cpp
               with the help from shell program a8shell.cpp

   DATE     :  2014-04-05

   COMPILER :  Visual Studio 2013

   ACTION   :  The program tests routines designed to perform various
               operations on singly linked lists. The lists have a
               dummy head node that holds the "Happy Face" character. 
               The tail of the lists points to NULL.

*************************************************************************/
#ifndef SHELL
#define SHELL
#include "a8shell.cpp"
#endif

using namespace std;

/*****************************   ZapList  ********************************
  DESCRIPTION  Frees all the storage space currently occupied by the
               linked list pointed to by List. Does NOT delete the delete
               the dummy head node.

  PARAMETER

    OUT, List  A pointer to a singly linked list with a dummy head node.
               After this call, List will contain only the dummy head node.

  PRECONDITION List must point to a linked list that has a dummy head node
               and a tail node that points at NULL.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void ZapList(NodePtr List)
{
	NodePtr Temp;

	//Preserve the Dummy Head Node, but change its Link to point to NULL
	Temp = List;
	List = List->Link;
	Temp->Link = NULL;

	//Run through the rest of the linked list and delete the other Nodes
	while (List != NULL)
	{
		Temp = List;
		List = List->Link;
		delete Temp;
	}
}

/****************************   AddNode  *********************************
  DESCRIPTION  Adds a node containing NewChar to the end of List.

  PARAMETERS

    IN, NewChar The character to be added to the end of the list.

    IN, List    A pointer to a singly linked list with a dummy head node.
                The value of List (address of dummy head node) is not
                changed by this routine, so List is passed by value.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void AddNode(char NewChar, NodePtr List)
{
	//Create new Node and fill with data - Doing this first prevents
	//unnecessarily running through the rest of the function if memory
	//allocation fails
	NodePtr NewNode = new(nothrow)Node;
	if (NewNode == NULL)
		//Memory allocation failed
		AbortProgram();

	//Fill in the new Node's data
	NewNode->Ch = NewChar;
	NewNode->Link = NULL;

	//Iterate through linked list to final Node
	while (List->Link != NULL)
		List = List->Link;

	//Change final Node's Link to the new Node
	List->Link = NewNode;
}

/****************************    DeleteNode   ****************************
  DESCRIPTION  Deletes the first node of List that contains the char
               CharToDelete. The storage occupied by the deleted
               node is returned to the heap.

  PARAMETERS

    IN, CharToDelete  The character to be deleted.

    IN, List    A pointer to a singly linked list with a dummy head node.
                The value of List is not changed by this routine but the
                linked list itself is changed.

    OUT, CharFound Set to 1 if the CharToDelete is found and deleted and
         0 otherwise.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DeleteNode(char CharToDelete, NodePtr List, int &CharFound)
{
	NodePtr NodeToBeDeleted = NULL;

	//Make sure that the list has data in it before continuing
	if (List->Link == NULL)
	{
		//No data after head node
		CharFound = 0;
		return;
	}
	else
		//Data after head node, so set NodeToBeDeleted to the first node.
		NodeToBeDeleted = List->Link;

	//Iterate through linked list until CharToBeDeleted is found or Link is NULL
	while (NodeToBeDeleted->Ch != CharToDelete && NodeToBeDeleted->Link != NULL)
	{
		//List is one link behind NodeToBeDeleted
		List = List->Link;
		NodeToBeDeleted = NodeToBeDeleted->Link;
	}

	//Determine whether Link was NULL or CharToDelete was found
	if (NodeToBeDeleted->Ch != CharToDelete)
		//Link was NULL
		CharFound = 0;
	else
	{
		//CharToDelete was found
		List->Link = NodeToBeDeleted->Link;			//Remove NodeToBeDeleted from linked list
		delete NodeToBeDeleted;						//Deallocate memory occupied by NodeToBeDeleted
		CharFound = 1;
	}
}

/****************************   BuildList    *****************************
  DESCRIPTION   Builds a singly linked list with a dummy head node. The
                characters in the list are in the same order in which the
                user enters them, i.e. new characters are added to the tail
                end of the list.

                Input terminates when the enter key is pressed.

  PARAMETERS

    IN, List    A pointer to a singly linked list with a dummy head node.
                It is imperative that List be initialized before calling
                this routine.

  NOTE          Before building the new list, ZapList is called. This
                ensures that a memory leak does not develop.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void BuildList(NodePtr List)
{
	//Clear the list first to ensure that memory leaks do not develop
	ZapList(List);

	char NewChar = 0;
	
	//Work through the input buffer until a new line is encountered
	cin.get(NewChar);
	while (NewChar != '\n')
	{
		NodePtr NewNode = NULL;

		NewNode = new(nothrow)Node;
		if (NewNode == NULL)
			//Memory allocation failed
			AbortProgram();

		//Fill in the new Node's data
		NewNode->Ch = NewChar;
		NewNode->Link = NULL;

		//Add the new Node to the end of the linked list
		List->Link = NewNode;
		
		//Move List along to the new last node
		List = List->Link;

		cin.get(NewChar);				
	}
}

/*
PROGRAM OUTPUT

Test Case 1: Limit (Command: BuildList, Data: \n)
	Tests that BuildList gracefully exits when the user enters nothing.
		After BuildList, List = ""

Test Case 2: Limit (Command: BuildList, Data: a\n)
	Tests that BuildList works properly when only one character is entered.
		After BuildList, List = "a"

Test Case 3: Normal (Command: BuildList, Data: abc\n)
	Tests that BuildList works properly for multiple characters.
		After BuildList, List = "abc"

Test Case 4: Limit (Command: AddNode, Existing Linked List: Empty, Data: a)
	Tests that AddNode properly adds a node when the linked list contains only the dummy head node.
		The new list: "a"

Test Case 5: Limit (Command: AddNode, Existing Linked List: a, Data: b)
	Tests that AddNode properly adds a node when only one data link exists in the list.
		The new list: "ab"

Test Case 6: Normal (Command: AddNode, Existing Linked List: ab, Data: c)
	Tests that AddNode properly adds a node to the list.
		The new list: "abc"

Test Case 7: Limit (Command: DeleteNode, Existing Linked List: Empty, Data: a)
	Tests that DeleteNode properly functions when there is an empty linked list.
		'a' was not in the list,

		List = ""

Test Case 8: Limit (Command: DeleteNode, Existing Linked List: a, Data: a)
	Tests that DeleteNode properly functions when there is only one element in the linked list.
		'a' has been deleted,

		List = ""

Test Case 9: Normal (Command: DeleteNode, Existing Linked List: abc, Data: d)
	Tests that DeleteNode properly responds in a normal situation of not finding a character in a linked
	list with data in it.
		'd' was not in the list,

		List = "abc"

Test Case 10: Limit (Command: DeleteNode, Existing Linked List: abc, Data: a)
	Tests that DeleteNode properly removes the first node of an existing linked list.
		'a' has been deleted,

		List = "bc"

Test Case 11: Normal (Command: DeleteNode, Existing Linked List: abc, Data: b)
	Tests that DeleteNode properly removes a middle node in a linked list.
		'b' has been deleted,

		List = "ac"

Test Case 12: Limit (Command: DeleteNode, Existing Linked List: abc, Data: c)
	Tests that DeleteNode properly removes the last node of an existing linked list.
		'c' has been deleted,

		List = "ab"

Test Case 13: Limit (Command: ZapList, Existing Linked List: Empty)
	Tests to verify that ZapList works properly on an empty linked list.
		List = ""

Test Case 14: Limit (Command: ZapList, Existing Linked List: a)
	Tests to veify that ZapList works properly for a linked list with only one element.
		List = ""

Test Case 15: Normal (Command: ZapList, Existing Linked List: abc)
	Tests to verify that ZapList works properly for a normal linked list with multiple elements.
		List = ""
*/