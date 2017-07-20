#include <iostream>
#include "MyFloat.cpp"
using namespace std;

void AssignValue(MyFloat& X)
{
	//X.Float[0] = 0;
	X.Float[1] = 1;
	X.Float[2] = 2;
	X.Float[3] = 3;				// run program first this way with
	X.NumDigits = 0;			// these numbers then change
}								// X.NumberofDigits = 0, to test
								// "0.?", which stands for an error

void main()
{
	MyFloat X, Y, Z;

	//AssignValue(X);

	cout << "X = ";
	X.Read();

	cout << "X = ";
	X.Write();

	//cout << endl << "Y = ";
	//cin.ignore(100, '\n');
	//Y.Read();
	//cout << "Y = ";
	//Y.Write();
	//Z = X + Y;
	//cout << endl << "Z = ";
	//Z.Write();

	cout << endl << "X.Digits() = " << X.Digits();
	cout << endl << "X.MaxDigits() = " << X.MaxDigits();

	//cout << endl << "X == Y: " << (X == Y);
	//cout << endl << "X != Y: " << (X != Y);

	cout << endl << "Press Enter key to continue" << endl;
	cin.ignore();
}
