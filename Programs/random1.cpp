/***************************  random1.cpp  *******************************

   An implementation file for a module that provide a random number
   generating function. See random1.h for overview of module.
-------------------------------------------------------------------------*/
#include "random1.h"

#include <time.h>      //  Needed for Randomize function.
#include <stddef.h>

static unsigned Seed = DEFAULT_SEED; // DEFAULT_SEED defined in random1.h

/***********************    Random    ***********************************

  DESCRIPTION  Generates a random unsigned ints between 0 and MODULUS
               using the linear congruential method.

  RETURNS      A random number R such that  0 <= R <= 65535

  NOTE         This function references an external static variable, Seed.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
unsigned Random(void)
{
  const unsigned long MULTIPLIER = 25173,  // Carefully chosen constants
                      INCREMENT  = 13849,
                      MODULUS    = 65536;

  Seed = unsigned ( (MULTIPLIER*Seed + INCREMENT) % MODULUS );

  return Seed;
}

/***********************  SeedGenerator  *********************************

DESCRIPTION  "Seeds" the random number generator function Random, i.e.
             provides an initial value for the variable Seed used to
             calculate a random number.

PARAMETERS   NewSeed, an unsigned int containing the new value to be
             assigned to the external variable, Seed.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void SeedGenerator (unsigned NewSeed)
{
  Seed = NewSeed;
}

/***************************  Randomize  *********************************

DESCRIPTION  Provides a randomly chosed new seed for the random number
             generating function, Randomize.

CALLS        time, a function prototyped in time.h. The time function
             returns the number of seconds that have elapsed since
             January 1, 1970 (if called with a NULL parameter).
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void Randomize (void)
{
  SeedGenerator(time(NULL));
}