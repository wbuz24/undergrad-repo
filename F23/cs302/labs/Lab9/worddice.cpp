// Will Buziak
// Lab 9
// Edmunds-Karp Algorithm to find Maximum Flow

#include <cstdio>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;

typedef enum {SOURCE, SINK, DICE, WORD} Node_Type;

class Node{
	public:
		int Id;								  // node's position
		Node_Type type;					// enum
		int Letters;			      // bit arithmetic to track letters
		int Distance;
		vector <class Edge *> Edges;
		Edge *Back;					
};

class Edge {
	public:
		Node *To;	
		Node *From;
		Edge *Reverse;
		int Flow;
		int Residual;
};

class Graph {
	public:
		vector <Node *> Nodes;			
		int BFS();									// Breadth First Search
		int CanSpell();							// calls BFS to determine if you can spell
		vector <int> Ids;				    // used to print
		void DeleteHalf();					// delete half of the graph  
    void ReadDice(string filename);
    void ReadWords(string filename);
		int MinNodes;								// number of nodes for deleting half 
    Node *Source;
    Node *Sink;
};

// Breadth First Search
int Graph::BFS() {
	int i;
	Node *n;
	list <Node *> stack;

	// resets the Backs and Distance fields
	for (i = 0; i < (int) Nodes.size(); i++) {
		Nodes[i]->Back = NULL;
		Nodes[i]->Distance = 0;
	}

  // start with the source
	n = Source;
	stack.push_back(n);

	while (stack.size() > 0) {
		// pops the first item off the stack
		n = stack.front();
		stack.pop_front();

		// if it finds the sink
		if (n == Sink) return 1;

		// push all children nodes onto the stack
		for (i = 0; i < (int) n->Edges.size(); i++) {
			if (!n->Edges[i]->To->Distance && n->Edges[i]->Flow) {
				n->Edges[i]->To->Back = n->Edges[i];
				n->Edges[i]->To->Distance = 1;
				stack.push_back(n->Edges[i]->To);
			}
		}
	}

	return 0;
}

int Graph::CanSpell() {
	Node *n;
	Edge *e;
	int i, j;
	int ret = 1;		// return value


	while(BFS()) {
		// sets n to the sink
		n = Nodes[Nodes.size() - 1];

		while (n != Nodes[0]) {
			e = n->Back;

			e->Flow = 0;
			e->Residual = 1;
			e->Reverse->Flow = 1;
			e->Reverse->Residual = 0;

			n = e->From;
		}
	}

  n = Sink;
	Ids.resize(0);
	
	for (i = 0; i < (int) n->Edges.size(); i++) {
		if (n->Edges[i]->Reverse->Residual == 0) ret = 0;
	}

	// builds Ids with the Dice Nodes that spell the word
	if (ret) {
		for (i = MinNodes; i < (int) Nodes.size() - 1; i++) {
			n = Nodes[i];

			for (j = 0; j < (int) n->Edges.size(); j++) {
				if (n->Edges[j]->To->type == DICE && n->Edges[j]->Flow == 1) {
					Ids.push_back(n->Edges[j]->To->Id);
				}
			}
		}
	}

	return ret;
}

void Graph::DeleteHalf() {
	int i, j;	
	Node *n;

	// deletes the edges from the dice to the word Nodes
	for (i = 1; i < MinNodes; i++) {
		n = Nodes[i];
		for (j = 0; j < (int) n->Edges.size(); j++) {
			if (n->Edges[j]->To->type == WORD) {
				delete n->Edges[j];
			}
		}
		n->Edges.resize(1);
	}

	// resets all the edges from the source to the dice
	n = Nodes[0];
	for (i = 0; i < (int) Nodes[0]->Edges.size(); i++) {
		n->Edges[i]->Flow = 1;
		n->Edges[i]->Residual = 0;
		n->Edges[i]->Reverse->Flow = 0;
		n->Edges[i]->Reverse->Residual = 1;
	}

	for (i = MinNodes; i < (int) Nodes.size(); i++) {
		n = Nodes[i];
    // delete all edges
		for (j = 0; j < (int) n->Edges.size(); j++) {
			delete n->Edges[j];
		}
    // delete the node itself
		delete n;
	}

	// resets Nodes vector size
	Nodes.resize(MinNodes);
}

void Graph::ReadWords (string filename) {
  ifstream fin;
  int count, i, j;
  Node *n, *n1, *n2;
  Edge *e, *er;
  string words;

  fin.open(filename);
	// read in eacg word and make nodes for each letter
	while (fin >> words) {
		count = MinNodes - 1;
		for (i = 0; i < (int) words.size(); i++) {
			count++;
			n = new Node;
			n->Id = count;
      n->Distance = 0;
      n->Letters = 0;
			n->type = WORD;
			n->Letters |= 1 << (words[i] - 'A');
			Nodes.push_back(n);
		}

		// add the sink at the very end of Nodes vector
		n = new Node;
		n->Id = count + 1;
		n->type = SINK;
    n->Distance = 0;
    n->Letters = 0;
    Sink = n;
		Nodes.push_back(n);

		// add the edges from the dice to the word
		for (i = 1; i < MinNodes; i++) {
			n1 = Nodes[i];
			for (j = MinNodes; j < (int) Nodes.size() - 1; j++) {
				n2 = Nodes[j];
				for (int k = 0; k < 26; k++) {
					if (n1->Letters & (1 << k) && n2->Letters & (1 << k)) {
						//make an edge

            e = new Edge;
            er = new Edge;
  	        e->To = n2;
	          e->From = n1;
	          e->Reverse = er;
	          e->Flow = 1;
	          e->Residual = 0;
	          n1->Edges.push_back(e);

	          er->To = n1;
	          er->From = n2;
	          er->Reverse = e;
	          er->Flow = 0;
	          er->Residual = 1;
	          n2->Edges.push_back(er);
					}
				}
			}
		}

		// add the edges to the sink
		for (i = MinNodes; i < (int) Nodes.size() - 1; i++) {
			n = Nodes[i];

      e = new Edge;
      er = new Edge;
  	  e->To = Sink;
	    e->From = n;
	    e->Reverse = er;
	    e->Flow = 1;
	    e->Residual = 0;
	    n->Edges.push_back(e);

	    er->To = n;
	    er->From = Sink;
	    er->Reverse = e;
	    er->Flow = 0;
	    er->Residual = 1;
	    Sink->Edges.push_back(er);
		}

		// find if there is a way to arrange the dice to spell the word
		if (CanSpell()) {
			printf("%d", Ids[0] - 1);
			for (i = 1; i < (int) Ids.size(); i++) {
				printf(",%d", Ids[i] - 1);
			}
			printf(": %s\n", words.c_str());
		} else {
			printf("Cannot spell %s\n", words.c_str());
		}

		// deletes the right half of the Graph
		DeleteHalf();
	}
}

void Graph::ReadDice (string filename) {
  Node *n;
  Edge *e, *er;
  int i;
  string dice;
  ifstream fin;

  fin.open(filename);


  MinNodes = 0;
	// creating the source node
	n = new Node;
	n->Id = MinNodes;
	n->type = SOURCE;
  n->Letters = 0;
  n->Distance = 0;
	Nodes.push_back(n);
  Source = n;

	// read in the Dice and add them To g.Nodes
	while (fin >> dice) {		
		//build a node
    MinNodes++;
		n = new Node;
		n->Id = MinNodes;
    n->Letters = 0;
    n->Distance = 0;
		n->type = DICE;
		
		for (i = 0; i < (int) dice.size(); i++) {
			
			if (!(n->Letters & 1 << (dice[i] - 'A'))) {
				n->Letters |= 1 << (dice[i] - 'A');
			}
		}

		Nodes.push_back(n);

	}

	// sets MinNodes
  MinNodes++;
	
	// add the edges from the source to the dice
	for (i = 1; i < MinNodes; i++) {
		n = Nodes[i];

    e = new Edge;
    er = new Edge;
  	e->To = n;
	  e->From = Source;
	  e->Reverse = er;
	  e->Flow = 1;
	  e->Residual = 0;
	  Source->Edges.push_back(e);

	  er->To = Source;
	  er->From = n;
	  er->Reverse = e;
	  er->Flow = 0;
	  er->Residual = 1;
	  n->Edges.push_back(er);
	}

}

int main (int argc, char **argv) {
	Graph *g;	

  (void) argc;
  g = new Graph;

  g->ReadDice(argv[1]);
  g->ReadWords(argv[2]);

  delete g;
}
