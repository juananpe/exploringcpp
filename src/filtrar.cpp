//============================================================================
// Name        : filtrar.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : read words from stdin and calculate the frequency of each one

//============================================================================

#include <iostream>
#include <iomanip>
#include <ios>
#include <ostream>
#include <map>

using namespace std;


int main() {

	typedef std::map<string, int> mapa;

	mapa count;

	string word;
	// read from cin
	while (cin >> word){

		string copy;
		for (string::iterator it(word.begin()); it != word.end(); ++it){
			if (isalnum(*it, locale(""))){
				copy.push_back(*it);
			}
		}
		if (copy.size()>0)
			++count[copy];
	}

	for (mapa::iterator it (count.begin()); it!= count.end(); ++it){
		cout << it->first << " aparece " << it->second << " veces \n";
	}
}
