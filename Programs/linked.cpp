#include <iostream>
#include <new>
using namespace std;

int main(void)
{
  struct Node
  {
    char Ch;
    Node *Link;
  };

  Node *List = NULL,   //List is pointer to first node in the list
       *Last;          //Last points to last node of list

  char Ch;

  cout << "This program will build a linked list of characters.\n"
	  "Type as many characters as you wish -- then a return.\n\n==>";

  cin.get(Ch);
  if (Ch == '\n')           //User wishes to exit immediately
    return 0;

  List = new(nothrow) Node; //Build first node as special case
  if (List == NULL)         //Unlikely, but possible memory error
    return 1;

  List->Ch = Ch;           //Store first character in node.
  List->Link = NULL;       //Make sure tail pointer is initialized
  Last = List;             //Last always points to end of list

  cin.get(Ch);
  while (Ch != '\n')
  {
    Last->Link = new(nothrow) Node;  //Create new node at tail
	
	if (Last->Link == NULL)          //error trying to allocate memory
	  return 1;
	else
	{
	  Last = Last->Link;             //Keep Last aimed at the last node             
      Last->Ch = Ch;                 //Store Char just read in linked list
	  Last->Link = NULL;             //Don't leave unitialized pointers
	}
	cin.get(Ch);                     //Get the next char, exit if newline
  }

  cout << "\nHere is the list: \"";

  while (List != NULL)
  {
    cout << List->Ch;        //Display data
    List = List->Link;       //Point at next node
  }

  cout << "\"\n";
  return 0;
}

