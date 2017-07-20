/*        Frac2.cpp

  A fraction class similar to the one in the file, Frac1.cpp, but with a
  number of new member functions added, including a default constructor
  and functions to support

  +  :  Overloaded + to support addition of fractions

  *  :  Overloaded * to support Fractions * int

  *  :  Overloaded * to support int * Fractions

  << :  Overloaded "<<", that replaces Write()

  The specification (header) file and implementation file have been
  combined below.

------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

class Fraction    // Improved Fraction class
{
 private:

  long Numer;     // Holds numerator of the fraction
  long Denom;     // Holds denominator

public:

Fraction (long Numerator,       // Constructor that does initialization
          long Denominator );

Fraction ()                     // Default constructor, defined inline
{
  Numer = 0;
  Denom = 1;
}

float Float() const;            // Converts Fraction to float

void  Simplify();               // Reduces fraction to simplest form

Fraction operator* (Fraction F2) const;

Fraction operator+ (Fraction F2) const;

Fraction operator* (long N) const;

friend Fraction operator* (long N, Fraction F2);

friend ostream& operator<< (ostream & cout, Fraction F);

int operator== (Fraction F2) const;     // Supports use of "=="

};  // End of specification file.



/***************************  operator*   ********************************

  Supports multiplication of a Fraction and an int. A typical call would
  be
        F * N,  where F is a Fraction and N is an int type.

  Returns the product, reduced to lowest terms.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
Fraction Fraction::operator* (long N) const
{
  long Numerator = Numer * N;             //  a/b * c = (a*c)/b

  Fraction Product(Numerator, Denom);     //  Create fraction with product

  Product.Simplify();

  return Product;

}
/***************************  operator*   ********************************

  Supports multiplication of an int and a Fraction. A typical call is

     N * F2,  where F2 is a Fraction and N is an int type.

  Returns the product, reduced to lowest terms.

  IMPORTANT COMMENT
  ~~~~~~~~~~~~~~~~~
  One of the requirements of C++ is that an operator that  belongs to a
  class must be associated with the class member to the left of the
  operator.

  This means that there is an important difference between a function
  that supports products of the form "F1 * N" and a function that supports
  products of the form "N * F2".

  In the case of the latter, N is not a Fraction, so the "*" operator
  cannot be associated with it. To get around this problem, C++ allows
  the declaration of "friend" functions. Friend functions can access
  private data just like member functions. Note that friend functions,
  including the one below have all parameters explicitly declared. Note
  also that the word "friend" appears only in the prototype above and not
  in the actual definition of the function below.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
Fraction operator* (long N, Fraction F2)
{
  long Numerator = N * F2.Numer;            // c * a/b = (c*a)/b

  Fraction Product(Numerator, F2.Denom);    // Create fraction with product

  Product.Simplify();

  return Product;
}

/***********************  Fraction (constructor) *************************

   A constructor that allows the declaration of fractions with a specified
   numerator and denominator.  For example, the declaration

     Fraction F(1, 3);

   declares F to be a fraction with numerator == 1 and denominator == 3.

   PARAMETERS
   ~~~~~~~~~~
     Numerator   The numerator to be used

     Denominator The denominator to be used
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
Fraction::Fraction (long Numerator, long Denominator )
{
  Numer = Numerator;
  Denom = Denominator;
}

/***************************    Float   **********************************

   Returns the float equivalent of this fraction. For example if F = 1/4
   then this function returns a 0.25
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
float Fraction::Float() const
{
  return Numer/float(Denom);  // "float" forces floating point division
}

/**********************    operator*  ************************************

   Computes the product of two fractions, using the familiar rule:

     a     c    a*c
    --- * --- = ---
     b     d    b*d

   Returns the product of the two functions, reduced to lowest terms.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
Fraction Fraction::operator* (Fraction F2 ) const
{
  long ProductNumer = Numer * F2.Numer;
  long ProductDenom = Denom * F2.Denom;

  Fraction ProductFrac(ProductNumer, ProductDenom);

  ProductFrac.Simplify();

  return ProductFrac;
}

/*************************** operator <<    *****************************

   Writes a Fraction to standard output. If Numer = 1 and Denom = 4, the
   output is "1/4" (written with no padding blanks.)

   This function overloads the << operator to give us output of objects
   in the Fraction class. Overloading of this insertion or put to operator
   requires that one understand how expressions of the form

   a)  cout << "F = " << F or the equivalent b) (cout << "F = ") << F

   are evaluated. First, cout is an object in the class ostream that
   is associated with standard output. As is the case with most C++
   operators, an expression such as cout << "F = " has both a value
   and a side effect. The side effect of the operation is, of course,
   to send the Fraction "F = " to the standard output stream. A careful
   inspection of the parenthesized expression b) above makes it clear that
   the value of the expression   cout << "F = "  must be an object that
   belongs to ostream. This explains the return type of the overloaded
   operator<< as defined below.

   Recall that one of the requirements of C++ is that an operator that
   belongs to a class must be associated with the class member to the left
   of the operator. In the case of the overloaded "<<" operator, the
   object to the left of "<<" is not a Fraction member. This means that
   as in the case of the function "Fraction operator* (int N, Fraction F2)"
   above, we must declare operator<< to be a "friend" of the class.

   This is an important example, since the code below can be used as an
   pattern to write code that supports output of any class.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
ostream& operator<< (ostream & Sout, Fraction F)
{
  Sout << F.Numer << '/' << F.Denom;

  return Sout;
}
/**********************   operator+   ************************************

   Computes the sum of two fractions, using the familiar rule:

     a     c    a*d + b*c
    --- + --- = ---------
     b     d       b*d

   Returns the sum of the two functions, reduced to lowest terms.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
Fraction Fraction::operator+ (Fraction F2 ) const
{
  long SumNumer = Numer * F2.Denom + Denom*F2.Numer;
  long SumDenom = Denom * F2.Denom;

  Fraction SumFrac(SumNumer, SumDenom);

  SumFrac.Simplify();

  return SumFrac;
}

/**********************  operator==  *************************************

   Returns a 1 if "this" fraction, is equal to F2, and a 0 otherwise.
   Uses the familiar rule

     a     c
    --- = ---  iff a*d = b*c
     b     d
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int Fraction::operator== ( Fraction F2 ) const
{
  return (Numer*F2.Denom == Denom*F2.Numer);
}

/*********************  GreatestCommonDivisor   **************************

  DESCRIPTION    Finds the greatest common divisor of First and Second.
                 The GCD is computed by using the Euclidean algorithm.

  PARAMETERS

      First     The first long int passed
      Second    The second long int passed

  RETURNS       The largest long int that divides both First and Second
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
long GreatestCommonDivisor (long First,
                           long Second)
{
  if ( First < 0 )        // Want numbers to be positive
    First = -First;

  if ( Second < 0 )
    Second = -Second;
  else if ( Second == 0 ) //  GCD(First,0) == 0
    return First;

  long Remainder = First % Second;

  while (Remainder > 0)
    {
    First     = Second;
    Second    = Remainder;
    Remainder = First % Second;
    }

  return Second;    //  Return first divisor that gives 0 remainder
}

/**********************    Simplify   ************************************

  Reduces Fraction to lowest terms, i.e. no long int greater than 1 evenly
  divides both Numer and Denom.

  NOTE: Calls a function GreatestCommonDivisor, that computes the greatest
	common divisor of two long int.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void Fraction::Simplify()
{
  long Gcd = GreatestCommonDivisor(Numer, Denom);

  if ( Gcd > 1 )
    {
    Numer /= Gcd;   // Eliminate common factors
    Denom /= Gcd;
    }
}