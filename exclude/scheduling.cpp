
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <iterator>

using namespace std;

struct proc {

	int weight;
	int length;

	proc()
	{
		proc(0,0);
	}
	proc(int w, int l): weight(w), length(l)
	{
		/* empty */
	}
};

struct comp {

	bool operator()(const proc& a, const proc& b) const{
		int pri1 = a.weight - a.length;
		int pri2 = b.weight - b.length;

		if (pri1==pri2){
			return a.length > b.length;
		}else{
			return pri1>pri2;
		}

	}


};

struct comp2 {

	bool operator()(const proc& a, const proc& b) const{
		float pri1 = (float)a.weight/a.length;
		float pri2 = (float)b.weight/b.length;

			return pri1>pri2;

	}


};



void readFile(std::string const& name, int& numProcs, vector<proc>& procesos){

	int weight, length;
	std::ifstream in(name.c_str());

	if (not in)
		perror(name.c_str());
	else {
		in >> numProcs;
		cout << numProcs << endl;
	}

	// read file
	while (in >> weight >> length) {
		proc proceso;
		proceso.weight = weight;
		proceso.length = length;

		procesos.push_back(proceso);
	}

}

int main(int argc, char **argv) {

	int numProcs;
	vector<proc> procesos;

	string file("/home/juanan/Dropbox/Public/datastructures2/jobs.txt");
	readFile(file, numProcs, procesos);

	sort(procesos.begin(), procesos.end(), comp());

	long long int sum = 0;
	int time = 0;

	for (vector<proc>::iterator it(procesos.begin()); it != procesos.end(); ++it)
	{
		time += it->length;
		sum += it->weight*time;

	}

	cout << sum ;

return 0;
}
