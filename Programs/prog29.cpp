/*              Prog29.cpp

  This program uses a function that will make an exact copy of an
  existing linked list, which was already entered in by the user.
  The function will return the node pointer address of the copied list.
  Then a function is called that will use a slow bubble sort to sort the
  copied list.
--------------------------------------------------------------------------*/
#include <iostream>
#include <stdlib.h>
#include <new>
using namespace std;

struct Node
{
   char Ch;
   Node *Link;
};

typedef Node* NodePtr;

void BuildList(NodePtr L);
NodePtr CopyList(NodePtr L);
void DisplayList(NodePtr L);
void SortList(NodePtr L);


int main()
{
  NodePtr List = NULL;         //List is the origanl linked list
  NodePtr CopiedList = NULL;   //CopiedList will be the copied linked list

  List = new(nothrow) Node;    //create first node for dummy head node
  if (List == NULL)
  {
    cerr << "Memory allocation error";
    return 1;
  }

  List->Ch =char(1);           //first node is dummy head node
  List->Link = NULL;

  BuildList(List);

  CopiedList = CopyList(List);

  cout << "\nOriginal entered list is: \n";
  DisplayList(List);

  cout << "\n\nThe coped list is: \n";
  DisplayList(CopiedList);

  SortList(CopiedList);

  cout << "\n\nThe coped list sorted is: \n";
  DisplayList(CopiedList);

  return 0;
}
/************************  BuildList  ********************************
Action:  Builds a single linked list from user input, list stops when
         newline encounterd.  List will end in NULL.
Parameter
   IN:   L, a node pointer, this is the input parameter, it holds address of
         linked list, where all the data is found to be copied
Returns : Nothing
Precondition : List has a dummy head node, List ends in NULL
--------------------------------------------------------------------*/
void BuildList(NodePtr L)
{
  char Ch;
  NodePtr Last = L;          // not really needed because pass in by value

  cout << "Enter list --> ";     //enter list from user
  cin.get(Ch);                   //and get first character
  while (Ch != '\n')
    {
      Last->Link = new(nothrow) Node;  //create next node
      if (Last->Link == NULL)          //and check if enough memory
      {
        cerr << "Memory allocation error";
        exit(1);
      }

      Last = Last->Link;           //move Last to point and just created node
      Last->Ch = Ch;               //insert data into char member
      Last->Link = NULL;           //initialize last pointer to null
      cin.get(Ch);                 //get the next character from input
    }
}
/****************************  DisplayList  *****************************
Action :  Function displays all elements of any linked list ending in NULL
-----------------------------------------------------------------------*/
void DisplayList(NodePtr L)
{
  L = L->Link;
  while (L != NULL)
  {
    cout << L->Ch;
    L = L->Link;
  }
}

/***************************  CopyList  **********************************
Action : This function will create a dummy head node linked list and
         fill it up with the data from the linked list passed into it
Parameters
  L    : a node pointer, this is the input parameter, it holds address of
         linked list, where all the data is found to be copied
Returns : A NodePtr, which holds the address of copied list
Precondition: Inputed list is dummy head node list ending in NULL
-----------------------------------------------------------------------*/
NodePtr CopyList(NodePtr L)
{
  NodePtr Copy = NULL, Temp;   //Copy will point to the copied linked list

  Copy = new(nothrow) Node;    //created first node as dummy head node
  if (Copy == NULL)
  {
    cerr << "Memory allocation error";
    return Copy;
  }
  Copy->Ch = char(1);          //fill in dummy head node value
  Copy->Link = NULL;
  Temp = Copy;                 //use Temp node to build on to Copy list

  while (L->Link != NULL)
    {
      L = L->Link;
      Temp->Link = new(nothrow) Node;   //create next node to copy
      if (Temp->Link == NULL)           //and check for error
      {
        cerr << "Memory allocation error";
        Copy = NULL;                //if error then let Copy list be NULL
        return Copy;                //and return a NULL list
       }
      Temp = Temp->Link;        //point temp at that node
      Temp->Ch = L->Ch;         //copy data from L list member to Temp node
      Temp->Link = NULL;
    }
  return Copy;
}

/***************************  SortList  ******************************
Action  :  Will use a slow bubble sort algorithm and sort a single
           linked list into ascending order.
Parameters
   IN:   L, nodeptr, holds address of inputed list to sort
Returns :  Nothing
Precondition : List is a dummy head node list ending in NULL
-------------------------------------------------------------------*/
void SortList(NodePtr L)
{
  NodePtr Current, Next;
  int NotSorted = 1, SwappedChar;

  if (L->Link == NULL || L->Link->Link == NULL)
    return;

  while (NotSorted)
   {
    SwappedChar = 0;               //nothing swapped
    Current = Next = L->Link;      //point pointers at first node in list
    while (Next->Link != NULL)
     {
      Next = Next->Link;           //advance Next pointer to next node
      if (Current->Ch > Next->Ch)  // compare two adjacent nodes
      {
        char Temp = Current->Ch;   //swap two adjacent nodes
        Current->Ch = Next->Ch;
        Next->Ch = Temp;
        SwappedChar = 1;           // yes there is a switch of data
      }
      Current = Current->Link;     // advance Current pointer
    }
   NotSorted = SwappedChar ? 1 : 0;
  }
}