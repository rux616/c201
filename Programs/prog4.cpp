/*              Prog4.cpp

   Program will read in grades then compute and display the average,
   cin is used and will continue until the end of file is returned by cin.
   End of File is typed in by ctrl - Z, (^Z)
---------------------------------------------------------------------*/
#include <iostream>
#include <iomanip>
using namespace std;

void main()
{
  int Grade, Total = 0, NumberOfGrades = 0;
  float Average;

  cout << "\nEnter grade (enter end-of-file to quit) --> ";
  while (cin >> Grade)
   {
     Total += Grade;
     ++NumberOfGrades;
     cout << "Enter grade (enter end-of-file to quit) --> ";
   }

  Average = float(Total)/NumberOfGrades;

  cout << setiosflags(ios::showpoint) << setprecision(2);
  cout << "\nAverage is " << Average << endl;
  
}

/*********************  Program output  *************************

Enter grade (enter end-of-file to quit) --> 78
Enter grade (enter end-of-file to quit) --> 88
Enter grade (enter end-of-file to quit) --> 94
Enter grade (enter end-of-file to quit) --> 58
Enter grade (enter end-of-file to quit) --> 69
Enter grade (enter end-of-file to quit) --> 83
Enter grade (enter end-of-file to quit) --> 80
Enter grade (enter end-of-file to quit) --> ^Z

Average is 78.57
*/

