/*              Prog18.cpp

     This is a variation of prog17 that demonstrates some struct
     pointer syntax.
----------------------------------------------------------------------*/
#include <iostream>
#include <string>
using namespace std;

void main (void)
{
   struct StudentRecord
      {
      char     Name[32];
      long     IDnumber;
      int      NumberOfExams;
      int      ExamScore[5];
      };

   StudentRecord  Student;

   StudentRecord *Ptr;        //  A pointer to a StudentRecord struct

   strcpy (Student.Name, "John Smith");
   Student.IDnumber  = 1234321;
   Student.NumberOfExams = 0;

   cout << "Student.Name          = " << Student.Name << endl;
   cout << "Student.IDnumber      = " << Student.IDnumber << endl;
   cout << "Student.NumberOfExams = " << Student.NumberOfExams << "\n\n";

   Ptr = &Student;

   cout << "(*Ptr).IDnumber = " << (*Ptr).IDnumber << endl;
   cout << "  Ptr->IDnumber = " <<  Ptr->IDnumber << endl;
}
/*--------------------  Program Output  ------------------------------

   Student.Name          = John Smith
   Student.IDnumber      = 1234321
   Student.NumberOfExams = 0

   (*Ptr).IDnumber = 1234321
     Ptr->IDnumber = 1234321

=====================   Program Comments   ===========================

1)  The assignment statement "Ptr = &Student;"  assigns the address of
    the variable Student to the pointer variable Ptr, i.e. "points" Ptr
    at Student.

2)  Since Ptr holds the address of Student, *Ptr is an alias (another
    name) for Student.  To reference the fields of Student in this way,
    parentheses are needed around "*Ptr" since the "." operator has very
    high precedence.  This means that the rather awkward reference
    "(*Ptr).IDnumber)" must be made to access the field IDnumber.
    Fortunately, C provides another notation that can be used with
    pointers to record structures. In the example above, "Ptr->IDnumber"
    is used.                                                          */