// Will Buziak
// Word Dice
// Lab 9
// CS302
// g++ -Wall -Wextra -o worddice worddice.cpp


#include <vector>
#include <unordered_map>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

class Node {
  public:
    int Id;
    int Visited; // for BFS
    vector <bool> Letters; // Nodes list of edges
    class Edge* Back; // the edge that brought you to this node
};

class Edge {
  public:
    Node *To;
    Node *From;
    Edge* Reverse; // think of it as a backlink
    int Original;
    int Residual;
};

class Graph { // This will still be 
  public:
    int MinNodes; // minimum number of nodes to help delete half the graph
    Node *Source;
    Node *Sink;
    vector <Node *> Nodes; // vector of words from the list
    int BFS(); // Breadth-First Search
    int CanSpell(); // Can I spell the given word
    void DeleteHalf(); // delete half the graph
    void ReadDice(string filename); // This will read the dice file and construct the graph
};

int Graph::BFS() {

  return 1;
}

int Graph::CanSpell() {
  // calls BFS

  return 1;
}

void Graph::ReadDice(string filename) {
  ifstream fin;
  string words;
  Node *n;
  Edge *e, *er;

  fin.open(filename);
  if (fin.fail()) return;
  
  while (fin >> words) {
    // For each node, you need an edge and a reverse edge
    n = new Node;
    e = new Edge;
    er = new Edge;

    // set up the new dice node
    n->Id = MinNodes;
    e->To = n; // create the reverse edge
    e->From = Source;
    e->Original = 1;
    e->Residual = 0;
    n->Back = e; // all die are connected to the source

    er->To = Source;
    er->From = n;
    er->Original = 0;
    er->Residual = 1;
    er->Reverse = e; // each edge points to it's own reverse edge
    e->Reverse = er;

    MinNodes++; // increment the Id
    printf("%s\n", words.c_str());
  }

  return;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("usage - ./worddice Dice.txt Words.txt\n");
    return 1;
  }

  Node *source = new Node;
  Graph *g = new Graph;

  g->MinNodes = 0;
  source->Id = g->MinNodes;
  g->MinNodes++;
  g->Source = source;
  g->ReadDice(argv[1]);


  delete g;
  delete source;
}
