/*              Prog28.cpp

   A program that builds, displays and deletes a circular linked list
   containing characters entered by the user. The list has a dummy
   head node.  Enter "abcd", then displayed in reverse order of "dcba".

---------------------------------------------------------------------------*/
#include <iostream>
#include <new>                // needed for "nothrow" with new operator
using namespace std;

struct Node
{
  enum  { DUMMY_VALUE = 0 };  //  Constant stored in dummy head node.
  char  Ch;                   //  Holds the char data.
  Node *Link;                 //  Points to another struct of type Node.
};

typedef Node* NodePtr;        //  Simplifies declarations.


void GetList (NodePtr &List);       // Creates a circular linked list

void DisplayList (NodePtr List);    // Sends members of list to cout

void DeleteList (NodePtr &P);       // Returns dynamically allocated storage


/************************  main  ****************************************/

int main (void)
{
  NodePtr List;

  cout << "This program will build a linked list of characters.\n"
          "Type as many characters as you wish -- then a return.\n\n"
          "==> ";

  GetList(List);

  if ( List == NULL )
  {
    cerr << "Error trying to allocate memory for linked list.\n\n";
    return 1;
  }

  cout << "\nHere are the characters in reverse order: \"";
  DisplayList (List);
  cout << "\"\n";

  DeleteList (List);  //  Call not really needed since program is ending.

  return 0;
}





/**************************   GetList   **********************************

  DESCRIPTION   Reads characters typed by the user and stores them in a
		a singly linked circular list with a dummy head node.
		Input of characters ends when the user presses the enter
		key, which is removed from the input stream, but not stored
		in the List.
		The last character entered is the first character in the
		list, i.e. if the user enters 'a', 'b' and 'c' the list
		is List -->  c --> b --> a.
  PARAMETER

    OUT, List   A pointer to the head node of the list. If the
		dynamic memory allocation is unsuccessful, List will
		hold NULL on exit.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void GetList (NodePtr &List)
{
  char    Ch;
  NodePtr Front;

  List = NULL;                        //  Start with empty list

  do
  {
    cin.get(Ch);                      //  Get the first character
    Front = new(nothrow) Node;        //  Try to create new node
    if ( Front == NULL )              //  Memory allocation error
    {
      List = NULL;                    //  So caller can detect error
      return;
    }

    if ( Ch != '\n' )                 //  Store ordinary char
      Front->Ch = Ch;
    else                              //  Substitute dummy for newline
      Front->Ch = List->DUMMY_VALUE;

    Front->Link = List;               //  Connect Front to front of List
    List        = Front;              //  Re-aim List to include added node
  }
  while ( Ch != '\n' );

  //  The list is now built, but it is not circular. The code that follows
  //  finds the last node and aims it at the dummy head node.

  NodePtr Searcher = List;

  while ( Searcher->Link != NULL )  // Find the end of the list
    Searcher = Searcher->Link;

  Searcher->Link = List;            // Aim tail node at dummy

}

/************************   DisplayList   ********************************

  DESCRIPTION  Displays the nodes in a singly linked circular list
	       that contains only a dummy head node. Does not display
	       the dummy node.
  PARAMETER

    IN, List   A pointer to the head node of the list. The pointer List is
	       passed by value, and none of the data pointed to is changed,
	       so this function has no side effects.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DisplayList (NodePtr List)
{
  List = List->Link;                         //  Get past the dummy node

  while ( List->Ch != List->DUMMY_VALUE   )
  {
    cout << List->Ch;                       //  Display the character
    List = List->Link;                      //  Point at next node
  }
}

/*************************  DeleteList  **********************************

  DESCRIPTION   Frees the dynamic storage space occupied by the list
		pointed to by P and sets P to NULL.

  PARAMETER

    OUT, List   A pointer to the head node of the list. List will hold
		NULL on exit.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DeleteList (NodePtr &P)
{
  NodePtr Temp;

  P = P->Link;                        //  Skip over dummy head node
  while (P->Ch != P->DUMMY_VALUE)
  {
    Temp = P;
    P = P->Link;                      //  Temp now points to node before P
    delete Temp;                      //  Deallocate memory
  }

  delete P;                           //  Finally get rid of head node

  P = NULL;                           //  Don't leave unitialized pointer
}

/********************  Program Output  ******************************
This program will build a linked list of characters.
Type as many characters as you wish -- then a return.

==> abcdef
Here are the characters in reverse order: "fedcba"              */
