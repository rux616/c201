/*
	     Prog10.cpp

Action : Reads words from stdin and displays them in four columns
Note   : Program does not handle correctly words longer than
         MAX_WORD_LENGTH. Only up to MAX_WORD_COUNT words may be
         stored in the array holding the words.
         Input terminates with End of File.
------------------------------------------------------------------------*/

#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

const MAX_WORD_LENGTH = 15;
const MAX_WORD_COUNT = 130;

// The type definition below permits easier prototyping of
// functions that pass arrays of strings.

typedef char WordStr[MAX_WORD_LENGTH + 1];    // +1 for null terminator

void ReadWord(WordStr NewWord);
void WriteWords(const WordStr Word[], int WordCount);
void StoreWord(WordStr NewWord, WordStr Word[], int &WordCount);

void main()
{
  WordStr NewWord,
          Word[MAX_WORD_COUNT + 1];

  int WordCount = 0;

  ReadWord(NewWord);                        // get first word
  while( NewWord[0] != 0)                   // while NewWord is not null
    {
      StoreWord(NewWord, Word, WordCount);  // save NewWord in array
      ReadWord(NewWord);                    // get next word
    }

  WriteWords(Word, WordCount);
}


/****************************  ReadWord  *****************************
Action : Reads a word from standard input and stores in the array Word.
Parameters
  OUT  : Word, an array of char.
Note  : A "word" is any contiguous sequence of non-blank characters.
        And if MAX_WORD_LENGTH is violated, memory errors may occur
Precondition: Word cannot have more chars then MAX_WORD_LENGTH
----------------------------------------------------------------------*/
void ReadWord(WordStr NewWord)
{
  cin >> NewWord;       // skips blanks, reads until white space
}









/**************************  StoreWord  ******************************
Action : Adds a string NewWord to the end of array Word
Parameters
  IN:  NewWord, the string or array of char. to be added
  OUT: Word, an array of WordStr, ie 2-Dimensional char array
  OUT: WordCount, the number of words in the array
----------------------------------------------------------------------*/
void StoreWord(WordStr NewWord, WordStr Word[], int &WordCount)
{
  if (WordCount == MAX_WORD_COUNT)    // no more room in array
    return;

  strcpy(Word[WordCount], NewWord);   // can't use '=' on strings

  ++WordCount;
}

/*************************  WriteWords  ****************************
Action : Writes the strings in the array Word to standard output.
         The words are left justified and padded with blanks.  Only
         WORDS_PER_ROW are displayed per line.
Parameters
   IN : Word, An array of WordStr (char[MAX_WORD_LENGTH])
   IN : WordCount, Number of words in array
----------------------------------------------------------------------*/
void WriteWords(const WordStr Word[], int WordCount)
{
  const int WORDS_PER_ROW = 4;

  cout.setf(ios::left);                  // left justify the output

  for (int Row = 0; Row < WordCount; ++Row)
    {
      if (Row % WORDS_PER_ROW == 0)
         cout << endl;                   // start a new row

      cout << setw(MAX_WORD_LENGTH + 1) << Word[Row];
    }
}

/*********************  Program Output ******************************

Today is not Friday the 13th.  But tomorrow could be if today
is Thursday the 12th.  Remember that Christmas always falls on
December the 25th and not December the 26th.

Today           is              not             Friday
the             13th.           But             tomorrow        
could           be              if              today           
is              Thursday        the             12th.           
Remember        that            Christmas       always          
falls           on              December        the             
25th            and             not             December
the             26th.
*/
