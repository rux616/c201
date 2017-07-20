/*        Prog11.cpp

Action  : Reads characters from standard input and then displays
          a table showing the number of times each character appears
          in the input stream.  input ends with EOF.
*********************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

void main()
{
  const char FIRST_CHAR = ' ';     // first and last printable characters
  const char LAST_CHAR = '~';
  const int MAX_ROW_SIZE = 4;      // Max number of items in table row

  int ChCount[LAST_CHAR + 1] = {0}; // use characters as array subscipts
  char Ch;
  int RowSize = 0;

  cin.get(Ch);
  while (!cin.eof())     // read chars until end of file
   {
     ++ChCount[Ch];      // increment count in position of Ch of array
     cin.get(Ch);
   }

  for ( Ch = FIRST_CHAR; Ch <= LAST_CHAR; ++Ch)
    {
      cout << Ch << setw(5) << ChCount[Ch] << "           ";
      ++RowSize;
      if (RowSize % MAX_ROW_SIZE == 0)
         cout << endl;
    }
}
/*********  Program output with WORDS.4 file ************************
    63           !    0           "    0           #    0
$    0           %    0           &    0           '    1
(    0           )    0           *    0           +    0           
,    4           -    0           .    5           /    0
0    0           1    0           2    0           3    0           
4    0           5    0           6    0           7    0
8    0           9    0           :    0           ;    0           
<    0           =    0           >    0           ?    1           
@    0           A    2           B    0           C    0           
D    3           E    0           F    0           G    0           
H    0           I    0           J    2           K    0           
L    0           M    0           N    0           O    0           
P    0           Q    0           R    0           S    3           
T    0           U    0           V    0           W    0           
X    0           Y    0           Z    0           [    0           
\    0           ]    0           ^    0           _    0           
`    0           a   27           b    2           c    9           
d    9           e   39           f    6           g    5           
h    9           i   14           j    1           k    3           
l    8           m    4           n   14           o   20           
p   15           q    0           r   19           s   15
t   19           u    7           v    6           w    5
x    2           y    8           z    0           {    0
|    0           }    0           ~    0
*/