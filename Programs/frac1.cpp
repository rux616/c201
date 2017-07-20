/**********************   Frac1.cpp   ************************************

  An implementation file for a simple fraction class. The implementation
  is an enhanced version the one presented that we have used 
  in class.

  The motivation for writing the class is that programs usually handle
  fractions in an inexact way -- they are stored as floats. This leads to
  roundoff errors. 

  This file provides only a partial implementation of a fraction class,
  providing some output support, conversion to float and two operators,
  * and ==.

  For the reader's convenience, the header file and implementation
  file are combined below.

------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

class Fraction
{

 private:

  long Numer;     // Holds numerator of the fraction
  long Denom;     // Holds denominator

 public:

  Fraction (long Numerator,       // Constructor that does initialization
            long Denominator);

  void  Write() const;            // Provides simple output

  float Float() const;            // Converts Fraction to float

  void  Simplify();               // Reduces fraction to simplest form


  Fraction operator* (Fraction Frac2) const; // Supports use of "*" when
                                             //   multiplying fractions.
  int operator== (Fraction Frac2) const;     // Supports use of "=="

};  // End of specification file.


// const used above is a way to safeguard and make certain that no data
// in the class will be changed, either public or private.
// This way all the data is read only.







/***********************  Fraction (constructor) *************************

   A constructor that allows the declaration of fractions with a specified
   numerator and denominator.  For example, the declaration

     Fraction F(1, 3);

   declares F to be a fraction with numerator == 1 and denominator == 3.

   Params
   ~~~~~~  Numerator   The numerator to be used

           Denominator The denominator to be used
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
Fraction::Fraction (long Numerator, long Denominator )
{
  Numer = Numerator;
  Denom = Denominator;
}



/***************************    Float   **********************************

   Returns the float equivalent of this fraction. For example if F = 1/4
   then a call, F.Float(), to this function returns a 0.25
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
float Fraction::Float() const
{
  return Numer/float(Denom);  // "float" forces floating point division
}


/**********************   operator*  *************************************

   Computes the product of two fractions, using the familiar rule:

     a     c    a*c
    --- * --- = ---
     b     d    b*d

   Returns the product of the two functions, reduced to lowest terms.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
Fraction Fraction::operator* (Fraction Frac2 ) const
{
  long ProductNumer = Numer * Frac2.Numer;
  long ProductDenom = Denom * Frac2.Denom;

  Fraction ProductFrac(ProductNumer, ProductDenom);

  ProductFrac.Simplify();

  return ProductFrac;
}






/**********************   operator==  ************************************

   Returns a 1 if "this" fraction, is equal to Frac2, and a 0 otherwise.
   Uses the familiar rule

     a     c
    --- = ---  iff a*d = b*c
     b     d
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int Fraction::operator== ( Fraction Frac2 ) const
{
  return (Numer*Frac2.Denom == Denom*Frac2.Numer);
}


/**********************    Write   ***************************************

  Writes a Fraction to standard output. If Numer = 1 and Denom = 4, the
  output is "1/4" (written with no padding blanks.)
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void Fraction::Write() const
{
  cout << Numer << '/' << Denom;
}

/*********************  GreatestCommonDivisor   **************************

  DESCRIPTION    Finds the greatest common divisor of First and Second.
                 The GCD is computed by using the Euclidean algorithm.

  PARAMETERS

      First     The first long int passed
      Second    The second long int passed

  RETURNS       The largest long int that divides both First and Second
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
long GreatestCommonDivisor (long First, long Second)
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