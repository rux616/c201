/*              Prog9.cpp
  Introduces C++ two-dimensional arrays. The program first stores
  some information in the two-dimensional array, then displays the
  contents of the array.
---------------------------------------------------------------------------*/
#include <iostream>
#include <iomanip>
using namespace std;

const int COLUMNS = 10; //Note external constant here, often need with arrays

void Display (int Table[][COLUMNS], // Constant required in second position
              int Rows);

/*************************   main     **************************************/
void main (void)
{
  const int ROWS =  8;            // Number of rows required.

  int Table[ROWS][COLUMNS];       // 2-dimensional array
  int Row, Column;

  for ( Row = 0; Row < ROWS; ++Row )               //  Fill up table
    for ( Column = 0; Column < COLUMNS; ++Column )
      Table[Row][Column] = 10 * Column + Row + 1;

  Display (Table, ROWS);
}
//************************   Display   *************************************

void Display (int Table[][COLUMNS], int NumberOfRows)
{
  const int FIELD_WIDTH =   7;      // Field Width for table entries

  for ( int Row = 0; Row < NumberOfRows; ++Row )          //  Display table
    {
    for ( int Column = 0; Column < COLUMNS; ++Column )
      cout << setw(FIELD_WIDTH) << Table[Row][Column];
    cout << endl;
    }
}
/*-------------------------  Program Output -------------------------------
      1     11     21     31     41     51     61     71     81     91
      2     12     22     32     42     52     62     72     82     92
      3     13     23     33     43     53     63     73     83     93
      4     14     24     34     44     54     64     74     84     94
      5     15     25     35     45     55     65     75     85     95
      6     16     26     36     46     56     66     76     86     96
      7     17     27     37     47     57     67     77     87     97
      8     18     28     38     48     58     68     78     88     98

/***********************  Program Comments  ********************************
1)  2-dimensional arrays are often a good choice for storing information
    of a "table" nature.

2)  If needed, arrays of higher dimension can also be declared. For
    example,    int A[12][10][3];

3)  Pay close attention to the required syntax for protyping functions that
    have two-dimensional arrays as parameters, must have constant or number
    in second parameter.  First parameter may be left blank.  */