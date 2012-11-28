
#include <iostream>
#include <iomanip>
#include <ios>
#include <vector>
#include <algorithm>
#include <ostream>


// if you are using Eclipse, there is a known bug
// that causes ctrl+d not to send an EOF signal to the program
// (from the Console view). There is a workaround, though.
// edit "Run configurations..." and uncheck the option
// "Connect process input & output to a terminal"
// More info: http://www.eclipse.org/forums/index.php/t/173494/

int main() {

	using namespace std;

	int x;

	vector<int> data;

	// read
	while (cin >> x){
		data.push_back(x);
	}

	// sort
	sort(data.begin(), data.end());

	for (vector<int>::iterator i(data.begin()); i != data.end(); i++ ){
		cout << *i << " ";
	}

}
