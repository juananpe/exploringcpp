/*
 * Pseudocode
 Prim_Sparse( Vertex s )
 Begin
 // G = (V, E)
 for each v IN V
 dist[v] = infinite
 parent[v] = 0 // treat 0 as a special null vertex
 hPos[v] = 0 // indicates that v NOT IN heap
 h = new Heap // priority queue (heap) initially empty
 h.insert(s) // s will be the root of the MST

 while (not h.isEmpty() ) 	// should repeat |V|-1 times
 v = h.remove()       	// add v to the MST
 dist[v] = -dist[v]   	// marks v as now in the MST
 for each u IN  adj(v)   // examine each neighbour u of v
 if wgt(v, u) < dist[u]
 dist[u] = wgt(v, u)
 parent[u] = v
 if u NOT IN  h
 h.insert( u)
 else
 h.siftUp( hpos[u])
 end if
 end for
 end while

 return parent
 End
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <vector>

using namespace std;

struct arco {
	int index;
	int weight;
};

struct graphNode {
	int index;
	int valor;
	vector<arco> vecinos;
};

void readFile(string name, vector<graphNode>& lista) {

	ifstream in(name.c_str());
	int numVertex, numEdges, src, dst, wgt;

	if (not in)
		perror(name.c_str());
	else {
		in >> numVertex;
		in >> numEdges;

		cout << numVertex << "************" << endl;
		lista.resize(numVertex + 1);

		graphNode dummy;
		dummy.index = 0;
		lista[0] = dummy;

		for (int i = 1; i <= numVertex; i++) {
			graphNode nodo;
			nodo.index = i;
			vector<arco> vecinos;

			nodo.vecinos = vecinos;

			lista.at(i) = nodo;
		}

		while (in >> src >> dst >> wgt) {

			arco edge1;
			arco edge2;

			edge1.index = dst;
			edge1.weight = wgt;
			lista.at(src).vecinos.push_back(edge1);

			edge2.index = src;
			edge2.weight = wgt;
			lista.at(dst).vecinos.push_back(edge2);

			cout << src << " " << dst << " " << wgt << endl;
		}
	}
}

#include <limits>
#include <algorithm>

typedef std::greater<int> less;

bool comp(const graphNode& a, const graphNode& b){

	return a.valor < b.valor;
}


void mst(vector<graphNode> ex, const int numVertex, vector<graphNode> lista)
{
	vector<int> dist(numVertex, numeric_limits<int>::max());
	vector<int> padre(numVertex);

	graphNode pop() {
		pop_heap(ex.begin(), ex.end(), comp);
		return ex.pop_back();
	}

	void push(graphNode v) {
		ex.push_back(v);
		push_heap(ex.begin(), ex.end(), comp);
	}


	ex.push_back(lista.at(1));
	make_heap(ex.begin(), ex.end(), comp);

	while (ex.size() > 0)
	{
		int v = pop();
		dist.at(v) = -dist.at(v);
		vector<arco> vecinos(lista.at(v).vecinos);

		for (vector<arco>::iterator u(vecinos.begin()); u != vecinos.end(); ++u)
		{
			if (u->weight < dist.at(u->index))
			{
				dist.at(u->index) = u->weight;
				padre.at(u->index) = v;
				if (find(ex.begin(), ex.end(), u->index) != ex.end())
					dist.at(u->index) = u->weight;
				else
					push(lista.at(u->index));

			}
		}
	}

}


void main() {
vector<graphNode> lista;

string file("/home/juanan/Dropbox/Public/datastructures2/edgesj.txt");
readFile(file, lista);

//	std::ostream_iterator< int > output( cout, " " );

cout << "------------------------" << endl;

for (vector<graphNode>::iterator it(lista.begin() + 1); it != lista.end();
		++it) {
	cout << it->index << " ";

	vector<arco> vecinos(it->vecinos);
	for (vector<arco>::iterator vec(vecinos.begin()); vec != vecinos.end();
			++vec) {
		cout << vec->index << " ";
	}

	cout << endl;
}

// std::copy( lista.begin(), lista.end(), output );

}

int main2() {
int myints[] = { 10, 20, 30, 5, 15 };
vector<int> v(myints, myints + 5);
std::ostream_iterator<int> output(cout, " ");

make_heap(v.begin(), v.end(), less());
cout << "initial max heap   : " << v.front() << endl;

pop_heap(v.begin(), v.end(), less());
v.pop_back();
cout << "max heap after pop : " << v.front() << endl;

v.push_back(99);
push_heap(v.begin(), v.end(), less());
cout << "max heap after push: " << v.front() << endl;

sort_heap(v.begin(), v.end(), less());

cout << "final sorted range :";
std::copy(v.begin(), v.end(), output);

cout << endl;

return 0;
}

