/*              Prog17.cpp

  C and C++ allow program to group data in two primary ways, using the
  array and the struct(ure).  This program gives a simple example
  of defining and using structs, which are similar to Pascal's records.
-------------------------------------------------------------------------*/
#include <iostream>
#include <string>
using namespace std;

void main (void)
{
  struct StudentRecord
    {
    char  LastName[20],          // Tons of magic numbers!
          FirstName[12];
    long  IDnumber;
    int   NumberOfExams;
    int   ExamScore[3 + 1];
    };                           // Note semicolon after brace
  int K;

  StudentRecord  Student;

  strcpy (Student.LastName, "Smith");
  strcpy (Student.FirstName, "John");
  Student.IDnumber  = 1234321;
  Student.NumberOfExams = 0;
  Student.ExamScore[1] = 90;
  Student.ExamScore[2] = 95;
  Student.ExamScore[3] = 100;

  cout << "\nStudent.LastName      = \"" <<  Student.LastName;
  cout << "\nStudent.FirstName     = \"" <<  Student.FirstName;
  cout << "\nStudent.IDnumber      = \"" <<  Student.IDnumber;
  cout << "\nStudent.NumberOfExams = \"" <<  Student.NumberOfExams;

  for (K= 1; K <= 3; ++K)
    cout << "\nStudent.ExamScore[" << K << "]  = " << Student.ExamScore[K];
}

/*------------------  Program Output  ------------------------------------

Student.LastName      = "Smith"
Student.FirstName     = "John"
Student.IDnumber      = "1234321"
Student.NumberOfExams = "0"
Student.ExamScore[1]  =  90
Student.ExamScore[2]  =  95
Student.ExamScore[3]  = 100

/*=====================   program notes ===================================

1)  A C structure is quite similar to a Pascal record. Accessing fields of
    a C structure can be done in exactly the same way.

2)  C and C++ have different struct declaration rules and syntax is a bit
    different with C.                                                    */