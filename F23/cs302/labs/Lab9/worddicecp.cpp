#include <cstdio>
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

typedef enum {SOURCE, SINK, DICE, WORD} Node_Type;

class Node{
	public:
		Node();								// Constructor
		int id;								// node's position in Graph.nodes[]
		Node_Type type;					// enum
		vector <bool> letters;			// a vector that holds all the letters of the alphabet, but only the ones that the node has are true
		int visited;						// used in BFS()
		vector <class Edge *> adj;		// list of edges from the node
		Edge *backedge;					// used in BFS
};

class Edge {
	public:
		Node *to;			// node this edge goes to
		Node *from;			// node this edge comes from
		Edge *reverse;		// a pointer the edge that goes in the opposite direction
		int original;
		int residual;
};

class Graph {
	public:
		vector <Node *> nodes;					// holds the nodes
		int BFS();									// Breadth First Search
		int canISpell();							//calls BFS an returns a 1 if you can or a 0 if your cant
		vector <int> spellingIDs;				// used to print
		void deleteHalfGraph();					// deletes the word nodes and the sink and all the edges between them
		int minNodes;								// number of nodes that you need to keep between words. (Source + Dice)
};

void connectNodes(Node *n1, Node *n2);

int main (int argc, char **argv) {
	Graph g;									// my Graph object
	ifstream dfile, wfile;				// input files
	string s;								// used for file input
	Node *n;									// used when making the nodes
	int i, j;								// iterators
	int index;								// used when adding the letters to a node
	int id = 0;								// used for setting a node's id
	Node *n1, *n2;							// used when making the edges

	// errors checks I don't actually need, but is good to have
	if (argc != 3) {
		printf("usage\n");
		return -1;
	}

	dfile.open(argv[1]);
	if (dfile.fail()) {
		printf("dfile failed to open\n");
		return -1;
	}

	wfile.open(argv[2]);
	if (wfile.fail()) {
		printf("file failed to open\n");
		return -1;
	}

	// creating the source node
	n = new Node;
	n->id = id;
	n->type = SOURCE;
	n->letters.resize(0);
	n->letters.resize(26, true);
	g.nodes.push_back(n);

	// read in the Dice and add them to g.Nodes
	while (dfile >> s) {		
		//build a node and add it to g
		id++;
		n = new Node;
		n->id = id;
		n->type = DICE;
		
		for (i = 0; i < s.size(); i++) {
			index = s[i] - 'A';
			
			if (!(n->letters[index])) {
				n->letters[index] = true;
			}
		}

		g.nodes.push_back(n);

	}

	// sets minNodes
	g.minNodes = id + 1;
	
	// add the edges from the source to the dice
	n1 = g.nodes[0];
	for (i = 1; i < g.minNodes; i++) {
		n2 = g.nodes[i];

		connectNodes(n1, n2);
	}

	// read in the Word and make nodes for each letter
	while (wfile >> s) {
		id = g.minNodes - 1;
		for (i = 0; i < s.size(); i++) {
			index = s[i] - 'A';
			id++;
			n = new Node;
			n->id = id;
			n->type = WORD;
			n->letters[index] = true;
			g.nodes.push_back(n);
		}

		// add the sink at the very end of g.nodes
		n = new Node;
		n->id = id + 1;
		n->type = SINK;
		n->letters.resize(0);
		n->letters.resize(26, true);
		g.nodes.push_back(n);


		// add the edges from the dice to the word
		for (i = 1; i < g.minNodes; i++) {
			n1 = g.nodes[i];
			for (j = g.minNodes; j < g.nodes.size() - 1; j++) {
				n2 = g.nodes[j];
				for (int k = 0; k < 26; k++) {
					if (n1->letters[k] and n2->letters[k]) {
						//make an edge

						connectNodes(n1, n2);
					}
				}
			}
		}

		// add the edges from the word to the sink
		n2 = g.nodes[g.nodes.size() - 1];
		for (i = g.minNodes; i < g.nodes.size() - 1; i++) {
			n1 = g.nodes[i];

			connectNodes(n1, n2);
		}

		// find if there is a way to arrange the dice to form the word
		if (g.canISpell()) {
			printf("%d", g.spellingIDs[0] - 1);
			for (i = 1; i < g.spellingIDs.size(); i++) {
				printf(",%d", g.spellingIDs[i] - 1);
			}
			printf(": %s\n", s.c_str());
		} else {
			printf("Cannot spell %s\n", s.c_str());
		}

		// deletes the right half of the Graph
		g.deleteHalfGraph();
	}


}

// connects the nodes n1 and n2 by creating an edge and reverse edge between them
void connectNodes(Node *n1, Node *n2) {
	Edge *e1, *e2;

	e1 = new Edge;
	e2 = new Edge;

	e1->to = n2;
	e1->from = n1;
	e1->reverse = e2;
	e1->original = 1;
	e1->residual = 0;
	n1->adj.push_back(e1);

	e2->to = n1;
	e2->from = n2;
	e2->reverse = e1;
	e2->original = 0;
	e2->residual = 1;
	n2->adj.push_back(e2);
}

// Node constructor
Node::Node() {
	letters.resize(26, false);
	visited = 0;
}

// Breadth First Search
int Graph::BFS() {
	int i;												// for loop iterator
	Node *n;												// used for pulling things off the queue
	Node *sink = nodes[nodes.size() - 1];		// pointer to the sink
	queue <Node *> q;									// BFS queue

	// resets the backedges and visited fields
	for (i = 0; i < nodes.size(); i++) {
		nodes[i]->backedge = NULL;
		nodes[i]->visited = 0;
	}

	// seeds the BFS queue
	n = nodes[0];
	q.push(n);

	// BFS algorithm
	while (q.size() != 0) {
		// pulls the first itme off the queue
		n = q.front();
		q.pop();

		// if it find the sink
		if (n == sink) {
			return 1;
		}

		// adds the nodes that n can go to
		for (i = 0; i < n->adj.size(); i++) {
			if ((n->adj[i]->to->visited == 0) and (n->adj[i]->original == 1)) {
				n->adj[i]->to->backedge = n->adj[i];
				n->adj[i]->to->visited = 1;
				q.push(n->adj[i]->to);
			}
		}
	}

	// if there was no path
	return 0;
}

// calls BFS() until it cant find a path, then checks if I am able to spell the word
int Graph::canISpell() {
	Node *n;					// pointer to a node
	Edge *e;					// pointer to an edge
	int i, j;				// for loop iterators
	int retval = 1;		// return value


	// repeatedly call BFS() until it returns 0
	while(BFS()) {
		// sets n to the sink
		n = nodes[nodes.size() - 1];

		// from the sink the the source, traces the backedges and flips the flows so BFS() doesn't use those edges again
		while (n != nodes[0]) {
			e = n->backedge;

			e->original = 0;
			e->residual = 1;
			e->reverse->original = 1;
			e->reverse->residual = 0;

			n = e->from;
		}
	}

	// resets n back to the sink
	n = nodes[nodes.size() - 1];
	spellingIDs.resize(0);
	
	// checks if we were able to spell the word
	for (i = 0; i < n->adj.size(); i++) {
		if (n->adj[i]->reverse->residual == 0) retval = 0;
	}

	// builds spellingIDs with the Dice Nodes that spell the word
	if (retval) {
		for (i = minNodes; i < nodes.size() - 1; i++) {
			n = nodes[i];

			for (j = 0; j < n->adj.size(); j++) {
				if ((n->adj[j]->to->type == DICE) and (n->adj[j]->original == 1)) {
					spellingIDs.push_back(n->adj[j]->to->id);
				}
			}
		}
	}

	return retval;
}

// deletes half the graph to set it up for another word to check
void Graph::deleteHalfGraph() {
	int i, j;		// for loop iterators
	Node *n;			// pointer for a Node

	// deletes the edges from the dice to the word nodes
	for (i = 1; i < minNodes; i++) {
		n = nodes[i];
		for (j = 0; j < n->adj.size(); j++) {
			if (n->adj[j]->to->type == WORD) {
				delete n->adj[j];
			}
		}
		n->adj.resize(1);
	}

	// resets all the edges from the source to the dice
	n = nodes[0];
	for (i = 0; i < nodes[0]->adj.size(); i++) {
		n->adj[i]->original = 1;
		n->adj[i]->residual = 0;
		n->adj[i]->reverse->original = 0;
		n->adj[i]->reverse->residual = 1;
	}

	// deletes all the edges of the word nodes and the sink and then deletes the nodes themselves
	for (i = minNodes; i < nodes.size(); i++) {
		n = nodes[i];
		for (j = 0; j < n->adj.size(); j++) {
			delete n->adj[j];
		}
		delete n;
	}

	// resets nodes size
	nodes.resize(minNodes);
}