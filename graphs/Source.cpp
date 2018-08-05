#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <stack>
using namespace std;


/*
graph notes:
* graph G=(V,E) consists of a set of vertices, V, and a set of edges, E
* each edge is a a pair (v,w) where v,w are elements in V
* directed graph = ordered pair
* undirected graph = unordered pair
* adjacency: w is adjacent to v iff (v,w) is in E (directed)
in undirected w is adjacent to v and v is adjacent to w bc (w,v)=(v,w)
* path: sequence of vertices where pre vertex is adjacent to 
next vertex for all vertices in path
* length of path: number of edges in path
* simple path: path such that all vertices are distinct, except
that first and last could be the same 
* cycle: some number of vertices connected in a closed chain

*adjacency matrix: each edge (u,v) set A[u][v]=true else entry in array is false
with weight set A[u][v]=weight/cost 
appropriate representation if graph is dense |E| = O(|V^2|)
number of edges is large
*advantages: adding/removing edge, checking if edge exists
*cons: space complexity of O(v^2)

*adjacency list: an array of linked lists
index of array reps vertex and each element in linked list reps 
other vertices that form an edge with vertex
appropriate representation if graph is sparse |E| = O(|V|)
*advantages: efficient in terms of storage, space complexity of O(v)

*breadth first search: visiting all nodes by going broad
so first arb node = front of queue, mark as visited, queue its neighbors (if any)
dequeue first, visit new front of queue, mark as visited, queue ITS neighbors 
(if any), dequeue next, continue this until queue is empty

*depth first search: visiting all nodes by going deep 
mark all vertices as unvisited, create stack for DFS, push source onto stack
while stack not empty, source = stack top, print source, pop source, print source, mark as visited 
get all adj nodes of source and push to stack
continue cycle until stack is empty and all nodes are visited

*/

class graphMatrix {
private:
	bool** adjMatrix;
	int numVertices;
public:
	graphMatrix(int numVertices) {
		this->numVertices = numVertices;
		adjMatrix = new bool*[numVertices];
		for (int i = 0; i < numVertices; i++) {
			adjMatrix[i] = new bool[numVertices];
			for (int j = 0; j < numVertices; j++)
				adjMatrix[i][j] = false;
		}
	}

	void addEdge(int i, int j) {
		adjMatrix[i][j] = true;
		adjMatrix[j][i] = true;
	}

	void removeEdge(int i, int j) {
		adjMatrix[i][j] = false;
		adjMatrix[j][i] = false;
	}

	bool isEdge(int i, int j) {
		return adjMatrix[i][j];
	}

	void toString() {
		for (int i = 0; i < numVertices; i++) {
			cout << i << " : ";
			for (int j = 0; j < numVertices; j++)
				cout << adjMatrix[i][j] << " ";
			cout << "\n";
		}

	}

	~graphMatrix() {
		for (int i = 0; i < numVertices; i++)
			delete[] adjMatrix[i];
		delete[] adjMatrix;
	}
};

class graphAdj
{
	int numVertices;
	list<int> *adjlists;
	bool *visited;
public:
	graphAdj(int V) {
		//cout << "test " << endl;
		numVertices = V;
		adjlists = new list<int>[V];
		visited = new bool[V];
	}
	void addEdge(int src, int dest) {
		//cout << "test " << endl;
		adjlists[src].push_front(dest);
		//adjlists[dest].push_back(src);
	}
	void BFS(int start)
	{
		//cout << "test " << endl;
		//visited = new bool[numVertices];
		for (int i = 0; i < numVertices; i++)
			visited[i] = false;
		
		queue<int> queue;
		visited[start] = true;
		queue.push(start);
		//cout << "test " << endl;

		while (!queue.empty())
		{
			int top = queue.front();
			//cout << "test " << endl;
			std::cout << top << " " << std::endl;
			queue.pop();
			for (list<int>::iterator i = adjlists[top].begin(); i != adjlists[top].end(); ++i)
			{
				//cout << "test " << endl;
				int adjVertex = *i;
				if (!visited[adjVertex])
				{
					visited[adjVertex] = true;
					queue.push(adjVertex);
				}
			}
		}
	}


	void DFS(int start)
	{
		vector<bool> visited(numVertices, false);

		stack<int> stack;

		stack.push(start);

		while (!stack.empty())
		{
			start = stack.top();
			stack.pop();

			if (!visited[start])
			{
				cout << start << " ";
				visited[start] = true;
			}

			for (auto i = adjlists[start].begin(); i != adjlists[start].end(); ++i)
				if (!visited[*i])
					stack.push(*i);

		}
	}
};

int main() {
	/*graphMatrix g1(4);

	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(1, 2);
	g1.addEdge(2, 0);
	g1.addEdge(2, 3);

	g1.toString();
	/* Outputs
	0: 0 1 1 0
	1: 1 0 1 0
	2: 1 1 0 1
	3: 0 0 1 0
	*/

	graphAdj g2(5);
	/*g2.addEdge(0, 1);
	g2.addEdge(0, 2);
	g2.addEdge(1, 2);
	g2.addEdge(2, 0);
	g2.addEdge(2, 3);
	g2.addEdge(3, 3);
	g2.BFS(2);*/

	g2.addEdge(1, 0);
	g2.addEdge(0, 2);
	g2.addEdge(2, 1);
	g2.addEdge(0, 3);
	g2.addEdge(1, 4);
	g2.DFS(0);
	system("pause");
	return 0;
}