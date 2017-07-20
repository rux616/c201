/*************************************************************************

   AUTHOR  : <your name here>  and John Russo and some by Matt Holloway

   SOURCE  :
              with the help from shell program a9shell.cpp

   DATE    :

   COMPILER: Microsoft Visual C++ .NET

   ACTION  : The program tests routines designed to perform various
             operations on singly linked lists. The lists have a
             dummy head node that holds the  character. The tail of
             the lists points to NULL.

             This is an extended program of homework #8
             The menu choices also all reading in a list from an
             external file and sorting a list.

*************************************************************************/

#include <ctype.h>
#include <iostream>
#include <process.h>        //  Needed for call to exit
#include <fstream>
#include <new>
using namespace std;

struct Node
  {
  enum  { DUMMY_VALUE = 1 };  //  Value () stored in dummy head node.
  char  Ch;                   //  Holds the char data.
  Node *Link;                 //  Points to another struct of type Node.
  };

typedef Node* NodePtr;

void AbortProgram (void);

void AddNode (char NewChar,  NodePtr List);

void BuildList (NodePtr List);

void ZapList (NodePtr P);

void DeleteNode (char CharToDelete,  NodePtr List,  int &CharFound);

void StartList (NodePtr &List);

void ShowList (NodePtr List);

void DisplayMenuAndGetMenuChoice (char &MenuChoice);

void TestAddNode (NodePtr List);

void TestBuildList (NodePtr List);

void TestDeleteNode (NodePtr List);

void TestZapList (NodePtr List);

void TestReadList (NodePtr List);

int ReadList (NodePtr List, char FileName[]);

void TestSortList (NodePtr List);

void SortList (NodePtr List);


/*****************************  main   ********************************/

int main(void)
{
  NodePtr List = NULL;

  char MenuChoice;

  system("cls");
  cout << "This program allows you to test the routines needed \n"
          "for homework #9. \n\n";

  StartList(List);
  if (List == NULL)                        //  Unexpected error.
    AbortProgram ();

  do
    {
    DisplayMenuAndGetMenuChoice(MenuChoice);

    switch( MenuChoice )
      {
      case 'Q':  break;                // Exit program

      case 'B':  TestBuildList(List);
                 break;

      case 'A':  TestAddNode(List);
                 break;

      case 'D':  TestDeleteNode(List);
                 break;

      case 'Z':  TestZapList(List);
                 break;

      case 'R':  TestReadList(List);
                 break;

      case 'S':  TestSortList(List);
                 break;

      default :  cout << "\nError: '" << MenuChoice
                      << "' is not an option \n\n";
      }
     }
  while ( MenuChoice != 'Q' );

  return 0;
}

/*********************   DisplayMenuAndGetMenuChoice *********************

   Displays a menu of options and reads the user's choice into the
   parameter MenuChoice. Unbuffered input is used, so the user does
   not have to enter a newline character after typing a menu choice.
   The MenuChoice is upcased.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DisplayMenuAndGetMenuChoice (char &MenuChoice)
{
  char* Option[] = {"B(uildList", "A(ddNode", "D(eleteNode",
                    " Z(apList", "R(eadList", "S(ortList", "Q(uit", "" };

  char DottedLine[] ="\n- - - - - - - - - - - - - - - "
                     "- - - - - - - - - - - - - - - -\n ";
  int K = 0;

  cout << DottedLine;

  while ( Option[K][0] != 0 )  // while we haven't gotten to ""
    {
    cout << Option[K];         // Display menu option
    cout << "  ";              // Add some white space.
    ++K;
    }

  cout << "=> ";
  cin >> MenuChoice;
  MenuChoice = toupper(MenuChoice);
  cin.ignore(10,'\n');

  cout <<  DottedLine;
}

/************************    TestAddNode  ********************************

   Facilitates the testing of the function AddNode, a function which
   adds a node to the tail end of a linked list. If the enter key is
   pressed in response to the prompt, it is assumed that the user
   wants to exit and this function is aborted.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestAddNode (NodePtr List)
{
  char NewChar;

  cout << "\n\n----------------   Testing AddNode   -------------------\n\n";

  cout << "Character to be added? ";
  NewChar = cin.get();
  cin.ignore(10,'\n');

  if (NewChar == '\n')  // User pressed just enter key.
    {
    cout << "Aborting AddNode...";
    return;
    }

  cout << NewChar;
  cout << " --  Adding \'" << NewChar  << "\'";

  AddNode (NewChar, List);

  cout << "\n\nThe new list: ";
  ShowList(List);
}

/*************************    TestBuildList     **************************

   Facilitates the testing of the function BuildList, which is supposed
   to build an ordered linked list of characters.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestBuildList (NodePtr List)
{
  cout << "\n\n=================  Testing BuildList  ===================";
  cout << "\n\nType the characters for the list -  "
           "when finished, press enter key\n\n ->";

  BuildList(List);

  cout << "\n\nAfter BuildList, List = ";
  ShowList(List);
}

/***********************    TestDeleteNode   *****************************

   Facilitates the testing of DeleteNode, a function which is supposed
   to delete characters from a linked list.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestDeleteNode (NodePtr List)

{
  int  CharFound;
  char CharToBeDeleted;


  cout << "\n\n*****************   Testing DeleteNode   *******************";

  cout << "\n\nCharacter to be deleted? ";
  CharToBeDeleted = cin.get();
  cin.ignore(10,'\n');

  DeleteNode (CharToBeDeleted, List, CharFound);

  if ( CharFound )
    cout << "\n\n'" << CharToBeDeleted << "' has been deleted,";
  else
    cout << "\n\n'" << CharToBeDeleted << "' was not in the list,";

  cout << "\n\nList = ";
  ShowList(List);
}

/***********************    TestZapList  *********************************

   Facilitates the testing of ZapList, a function that is supposed to
   return all storage allocated for a linked list to the heap (except the
   storage occupied by the dummy head node.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestZapList (NodePtr List)

{
  cout << "\n\n^^^^^^^^^^^^^^^^^   Calling ZapList  ^^^^^^^^^^^^^^^^^^^^^^^";


  ZapList(List);

  cout << "\n\nList = ";
  ShowList(List);
}

/****************************  AbortProgram   ****************************

   Displays an error message and returns a non-zero error code to
   the operating system.

   Requires exit function prototyped in process.h.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void AbortProgram (void)
{
  cout << "\n\n\a A error has occurred while using the new operator. \n"
          "Returning to the operating system\n";
  cout << "Press ENTER KEY to continue: ";
  cin.get();
  exit(1);
}

/************************    StartList  *********************************

  DESCRIPTION   Creates an empty list, i.e. a singly linked list that
                contains only a dummy head node.

  PARAMETER

    OUT, List   A pointer to the head node of the list. If the
                dynamic memory allocation is unsuccessful, List will
                hold NULL on exit.

  PRECONDITION  List points to NULL. If List points to an actual node,
                calling this routine will create inaccessable memory.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void StartList (NodePtr &List)
{
  List = new(nothrow) Node;
  if (List == NULL)
    return;                        // Memory allocation error.

  List->Ch   = List->DUMMY_VALUE;  // Fill in dummy head node fields
  List->Link = NULL;               // Initialize end of list.
}

/*************************   ShowList  ***********************************

  DESCRIPTION  Displays the character field of all of the nodes in List, a
               singly linked list with a dummy head node. The list is
               enclosed in quotes.

               The constant MAX_CHARS_PER_LINE controls the maximum
               number of characters displayed before a newline char
               is displayed.

  PARAMETER

    IN, List   A pointer to a singly linked list with a dummy head node.

  NOTE         To facilitate debugging this routine displays "NULL"
               if called with List == NULL.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void ShowList (NodePtr List)
{
 const int MAX_CHARS_PER_LINE = 50;

  int CharCount = 0;

  if ( List == NULL )
    {
    cout << " NULL LIST\n\n";
    return;
    }

  cout << "\"";                 //  Display quote for ease of testing.
  while ( List->Link != NULL )
  {
    List = List->Link;
    cout << List->Ch;
    if ( List-> Ch != '\n' )   // Increment CharCount unless newline
      ++CharCount;             //   char is encountered in List
    else
      CharCount = 0;
    if ( CharCount % MAX_CHARS_PER_LINE == 0 )   //this will allow only
      cout << "\n";                              //50 char per line
  }

  cout << "\"\n\n";
}

/************************    TestReadList  ********************************

   Facilitates the testing of the function ReadList, a function which
   reads in a list from an external file.  The file is typed in by the
   user, if file does not exist, then an error will occur.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestReadList (NodePtr List)
{
  char FileName[32];

  cout << "\n\n----------------  Testing ReadList  -------------------\n\n";

  cout << "Please enter the file to read from? ";
  cin >> FileName;
  cin.ignore(10,'\n');

  if (ReadList (List,FileName))
     {
      cerr << "\nError in opening the file " << FileName << endl;
      cerr << "Press ENTER KEY";
	  cin.get();
      return;
     }

  cout << "\n\nThe list created from the file -- " << FileName << " --\n\n";
  ShowList(List);

  cin.ignore(100,'\n');    //discard the enter from reading in filename
}

/***********************    TestSortList  *********************************

   Facilitates the testing of SortList, a function that is supposed to
   return a list that has been sorted, from lowest character value to
   highest.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestSortList (NodePtr List)
{
  cout << "\n\n^^^^^^^^^^^^^^^^   Calling SortList  ^^^^^^^^^^^^^^^^^^^^^^^";

  SortList(List);

  cout << "\n\nList = ";
  ShowList(List);
}
