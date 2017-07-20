/*     Source : BCLASS.CPP
    Program Base Class
------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

class Person
{
  private:          // only base class has direct access to private data
   int CodeNumber;  // through member functions or friend functions

  protected:         // either base class or derived classes have direct
   char Name[30];    // access to protected data by member or friend functions
   int Age;
   char Sex;

  public:              // any one has access to public data
   void GetInfo(void);
   void ShowPerson(void);
};


void Person::GetInfo(void)
{
  cout << "\nEnter name --> ";
  cin.getline(Name,30);
  cout << "Enter age --> ";
  cin >> Age;
  cout << "Enter Sex --> ";
  cin >> Sex;
  cout << "Enter Code Number --> ";
  cin >> CodeNumber;
  cin.ignore(100, '\n');
}


void Person::ShowPerson(void)
{
  cout << endl << Name << "  " << Age << "  "
       << Sex << "  " << CodeNumber << endl;
}



// Derived class from base class of Person

class WorkPerson : public Person
{
  private:
   float Wage, Hours;

  public:
   float GrossPay(void);
   float NetPay(void);
   void Who(void);
   void GetWageHour(void);
};


void WorkPerson::GetWageHour(void)
{
  cout << "\nEnter Wage --> ";
  cin >> Wage;
  cout << "Enter Hours --> ";
  cin >> Hours;
}


float WorkPerson::GrossPay(void)
{
  return Wage * Hours;
}


float WorkPerson::NetPay(void)
{
  return (Wage*Hours) - 0.3*(Wage*Hours);
}


void WorkPerson::Who(void)
{
  cout << Name;

  // cout << CodeNumber;    is illegal because CodeNumber is private member
  //                        in base class, derived class cannot access
  //                        private members directly
}