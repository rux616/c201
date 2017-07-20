/****************************  random1.h  *****************************

  A specification file for a module that provides a random number
  generating function.  Introduces the preprocessor directives,
  "ifndef" and "define", used to guard against illegal multiple
  declarations of a constant.

  The random numbers are generated by the "linear congruential method",
  which uses the "magic formula"

        Seed = (25173 * Seed + 13849) % 65536;

  to generate a random unsigned int, which then becomes the next value
  of Seed.

  At present the module contains the following functions:

  unsigned Random(void)
     Generates a random unsigned int between 0 and MODULUS ( 65536)

  void SeedGenerator(unsigned NewSeed)
     "Seeds" the random number generator, i.e. determines the initial
     value of the static variable Seed.

  void Randomize(void)
     Calls SeedGenerator with a clock reading (itself random) so that
     when Random() is called, the random numbers will not be
     predictable in advance.

  The "#ifndef" ( if not defined ) compiler preprocessor directive below is
  used to prevent problems that would occur if this header file is
  included twice.

-----------------------------------------------------------------------*/

#ifndef RANDOM1_H      // if this file has not been previously processed
                       // then execute all statements up to "#endif".
  #define  RANDOM1_H   //Put RANDOM1_H in a "defined" state.

  const unsigned DEFAULT_SEED = 0;  // value used to seed generator

#endif

unsigned Random(void);

void SeedGenerator(unsigned NewSeed);

void Randomize(void);