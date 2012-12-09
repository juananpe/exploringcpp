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

//int main(int argc, char **argv) {
//	// leer los vértices
//
//	// generar vector de dist
//
//	// generar vector de parent
//
//
//}


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
 vector<arco> vecinos;
};

void readFile(string name, vector<graphNode>& lista){

	ifstream in(name.c_str());
	int numVertex, numEdges, src, dst, wgt;

	if (not in)
		perror(name.c_str());
	else
	{
		in >> numVertex;
		in >> numEdges;

		cout << numVertex << "************" << endl;
		lista.resize(numVertex+1);

		graphNode dummy;
		dummy.index=0;
		lista[0]=dummy;



		for(int i = 1; i <= numVertex; i++){
			graphNode nodo;
			nodo.index = i;
			vector<arco> vecinos;

			nodo.vecinos = vecinos;

			lista.at(i) =  nodo ;
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

int main () {
	vector<graphNode> lista;

	string file("/home/juanan/Dropbox/Public/datastructures2/edgesj.txt");
	readFile(file, lista);

//	std::ostream_iterator< int > output( cout, " " );

	cout << "------------------------" << endl;

	for ( vector<graphNode>::iterator it(lista.begin()+1); it != lista.end(); ++it ){
		cout << it->index << " ";

		vector<arco> vecinos( it->vecinos);
		for ( vector<arco>::iterator vec (vecinos.begin()); vec != vecinos.end(); ++vec){
			 cout << vec->index << " ";
		}

		cout << endl;
	}

	// std::copy( lista.begin(), lista.end(), output );

}


int main2 () {
  int myints[] = {10,20,30,5,15};
  vector<int> v(myints,myints+5);
  std::ostream_iterator< int > output( cout, " " );

  typedef std::greater<int> less;

  make_heap (v.begin(),v.end(), less());
  cout << "initial max heap   : " << v.front() << endl;

  pop_heap (v.begin(),v.end(), less()); v.pop_back();
  cout << "max heap after pop : " << v.front() << endl;

  v.push_back(99); push_heap (v.begin(),v.end(), less());
  cout << "max heap after push: " << v.front() << endl;

  sort_heap (v.begin(),v.end(),less());

  cout << "final sorted range :";
  std::copy( v.begin(), v.end(), output );


  cout << endl;

  return 0;
}

