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
#include <limits>
#include <vector>

using namespace std;

struct arco {
	int index;
	int weight;
};

std::ostream& operator<<(std::ostream &strm, const arco &a) {
  return strm << "arco(" << a.index << " " <<  a.weight << ")\n";
}

struct graphNode {
	int index;
	int valor;
	vector<arco> vecinos;
};

std::ostream& operator<<(std::ostream &strm, const graphNode &a) {
  return strm << "node(" << a.index << " " <<  a.valor << ") \n";
}


struct predicate
{
    predicate( int uCode ) : indice(uCode) {}

    bool operator() (graphNode u)
    {
        return u.index == indice;
    }
private:
    int indice;
};

void readFile(string name, vector<graphNode>& lista, int& numVertex) {

	ifstream in(name.c_str());
	int numEdges, src, dst, wgt;

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

		// init graph structure
		for (int i = 1; i <= numVertex; i++) {
			graphNode nodo;
			nodo.index = i;
			vector<arco> vecinos;

			nodo.vecinos = vecinos;

			lista.at(i) = nodo;
		}

		// read file
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

struct lessthan{
	bool operator()(const graphNode& a, const graphNode& b) const{
		return a.valor > b.valor;
	}
};

graphNode pop(vector<graphNode>& ex) {
	pop_heap(ex.begin(), ex.end(), lessthan());
	graphNode result = ex.back();
	ex.pop_back();
	return result;
}

void push(vector<graphNode>& ex, graphNode& v) {
	ex.push_back(v);
	push_heap(ex.begin(), ex.end(), lessthan());
}



void mst(vector<int>& solucion, const int numVertex, vector<graphNode>& lista)
{
	vector<int> dist(numVertex+1, numeric_limits<int>::max());
	vector<int> padre(numVertex+1);
	vector<graphNode> ex;


	ex.push_back(lista.at(1));
	make_heap(ex.begin(), ex.end(), lessthan());

	while (ex.size() > 0)
	{
		graphNode v = pop(ex);
		dist.at(v.index) = numeric_limits<int>::min(); // -dist.at(v.index);
		vector<arco> vecinos(lista.at(v.index).vecinos);

		for (vector<arco>::iterator u(vecinos.begin()); u != vecinos.end(); ++u)
		{
			if (u->weight < dist.at(u->index))
			{
				dist.at(u->index) = u->weight;
				padre.at(u->index) = v.index;
				// cómo usar find() para buscar en una lista de objetos
				// aquellos que sean iguales según cierto criterio?
				// buscar en lista de graphNode un número
				vector<graphNode>::iterator it = find_if(ex.begin(), ex.end(), predicate(u->index));
				if ( it != ex.end()){
					it->valor = u->weight;
					make_heap(ex.begin(), ex.end(), lessthan() );
					// dist.at(u->index) = u->weight;

				}
				else{
					lista.at(u->index).valor = u->weight;
					push(ex, lista.at(u->index));
				}

			}
		}
	}

	solucion = padre;
}


int main() {

	vector<graphNode> lista;
	vector<int> solucion;
	int numVertex;

	string file("/home/juanan/Dropbox/Public/datastructures2/edges.txt");
	readFile(file, lista, numVertex);

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


		 mst(solucion, numVertex, lista);

		 std::ostream_iterator< int > output( cout, " " );
		 std::copy( solucion.begin(), solucion.end(), output );
		 cout << endl << "    ";

		 int total(0);
		 // overall cost of a minimum spanning tree
		for (int i = 2; i <= numVertex; i++) {

			vector<arco> vecinos(lista.at(i).vecinos);

					for (vector<arco>::iterator u(vecinos.begin()); u != vecinos.end(); ++u)
					{
						if (u->index == solucion.at(i)){
							cout << u->weight << " ";
							total += u->weight;
							break;
						}
					}
		 }

		cout << endl << total;
return 0;
}

//typedef std::greater<int> less;
//int main2() {
//int myints[] = { 10, 20, 30, 5, 15 };
//vector<int> v(myints, myints + 5);
//std::ostream_iterator<int> output(cout, " ");
//
//make_heap(v.begin(), v.end(), less());
//cout << "initial max heap   : " << v.front() << endl;
//
//pop_heap(v.begin(), v.end(), less());
//v.pop_back();
//cout << "max heap after pop : " << v.front() << endl;
//
//v.push_back(99);
//push_heap(v.begin(), v.end(), less());
//cout << "max heap after push: " << v.front() << endl;
//
//sort_heap(v.begin(), v.end(), less());
//
//cout << "final sorted range :";
//std::copy(v.begin(), v.end(), output);
//
//cout << endl;
//
//return 0;
//}

