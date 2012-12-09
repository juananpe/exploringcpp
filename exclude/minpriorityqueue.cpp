#include <iostream>
#include <queue>
using namespace std;

class Node
{
private:
    int value;

public:
    Node( int v )  : value( v ) {}
    int Val() const { return value; }
};

struct CompareNode : public std::binary_function<Node*, Node*, bool>
{
  bool operator()(const Node* lhs, const Node* rhs) const
  {
     return lhs->Val() < rhs->Val();
  }
};

int main()
{
    priority_queue<Node*,vector<Node*>, CompareNode > pq;

    pq.push( new Node( 111 ) );
    pq.push( new Node( 1111 ) );
    pq.push( new Node( 1011 ) );
    pq.push( new Node( 100 ) );
    pq.push( new Node( 1110 ) );
    pq.push( new Node( 101 ) );

    while ( !pq.empty() )
    {
        Node* n = pq.top();
        cout << n->Val() << endl;
        pq.pop();

        // Delete pointer that vector contains
        delete n;
    }
    cin.get();
}
