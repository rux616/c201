/*********  SAMPLE PROGRAM FOR STYLE AND FORMAT  ************************
Name  :  
Date  :            
Homework # : 
Sorce file : Homework.cpp
Action   :  Will ask user to input test scores until negative one is
            entered.  Program will then display number of inputed
            scores and the average of them.
Note  :  Will use a maximum number of test scores of no more than 50.
-----------------------------------------------------------------------*/
#include <iostream>
using namespace std;

float AverageOfNumbers(float X[], int Size);       // function prototype

void main()
{
  const int MAX_SIZE = 50;
  int i = 0;
  float Scores[MAX_SIZE];     // Array holding the inputed scores

  cout << "Enter test score, negative to quit --> ";
  cin >> Scores[i];
  while (Scores[i] >= 0 && i <= (MAX_SIZE-1))
    {
      i++;
      cout << "Enter next test score --> ";
      cin >> Scores[i];
    }

  cout << "You entered " << i << " test scores, with an average of ";
  cout << AverageOfNumbers(Scores, i) << endl;

  cout << "Press ENTER key to continue";
  cin.ignore(2);
}

/***************************  AverageOfNumbers  ***************************
Action : Calculates the average of the numbers in an array.
Parameters
  IN   :  X, which points to array that holds numbers to find average of and
          Size, which is the number of elements in array to use.

  OUT  : None

Returns  : The average of numbers in array
Precondition :  X points to an int or float array, and Size is positive and
                within boundary of array
-----------------------------------------------------------------------*/
float AverageOfNumbers(float X[], int Size)
{
    float Sum = 0;

    for (int i = 0; i < Size; i++)      // calculates sum of numbers in array
      Sum += X[i];

    return Sum/i;                      // return average of numbers
}