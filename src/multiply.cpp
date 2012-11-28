//============================================================================
// Name        : multiply.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <ios>
#include <ostream>

using namespace std;


int main() {

	cout.setf(ios_base::right);

	cout << setw(4) << "*" << "|" ;
	// header
	for (int i = 1; i <= 10; i++)
		cout << setw(4) << i;

	// first "-" line
	cout << endl;
	cout << setfill ('-') << setw(4) << "-" << "+";
	for (int i = 1; i <= 10; i++)
			cout << setfill ('-') << setw(4) << "-";

	// reset fill char
	cout << setfill(' ');
	cout << endl;

	for (int i = 1; i <= 10; i++) {
		cout <<  setw(4) << i  << "|" ;
		for (int j = 1; j <= 10; j++) {
			cout << setw(4) << i * j ;
		}
		cout << endl;
	}

	return 0;
}
