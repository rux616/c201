/*              Prog2.cpp
  Program has user enter test scores, then uses functions to find average.
----------------------------------------------------------------------------*/
#include <iostream>
#include <iomanip>
using namespace std;

const int SIZE = 5;                 //Global constant used for functions
void ReadScores(float S[]);         //prototypes
float TotalScores(const float S[]);

void main()
{
  float Scores[SIZE] = {0};    // initializes all elements in array to zero
  float Average;

  ReadScores(Scores);

  cout << "\nEntered scores are as follows\n";
  cout << setprecision(2);
  for(int i = 0; i < SIZE; i++)
     cout << Scores[i] << "  ";                 //displays all test scores

  Average = TotalScores(Scores)/SIZE;

  cout << "\n\nThe average of the " << SIZE << " test scores is "
       << Average << endl;
}
/****************************  ReadScores  *******************************
Action  : Function ask user to enter test scores to store in an array.
Parameters
  OUT :  The parameter S, which is an array is used as output parameter
Returns   :  Nothing

Note      :  When using arrays as output parameters you do not need to
             include the ampersand sign, "&". With arrays we are just passing
             the address of the starting element from the corresponding
             actual parameter.
---------------------------------------------------------------------------*/
void ReadScores(float S[])
{
  for(int i = 0; i < SIZE; i++)
    {
      cout << "Please enter test score --> ";
      cin >> S[i];                       //input test scores
    }
}
/****************************  TotalScores  *******************************
Action  : Function will find the total of all elements in the array
Parameters
  IN    : The array to find total of elements, made a constant as well
Returns : The total of all elements from inputed array
-------------------------------------------------------------------------*/
float TotalScores(const float S[])
{ float Total = 0;
  for(int i = 0; i < SIZE; i++)
     Total += S[i];                //Totals up all test scores
  return Total;
}