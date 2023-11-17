// Will Buziak
// Word Dice
// Lab 9
// CS302
// g++ -Wall -Wextra -o worddice worddice.cpp


#include <vector>
#include <unordered_map>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Node {
  public:
    int Id;
    int Distance; // for BFS, acting as distance and visited field
    string Word;
    vector <class Edge*> Edges; // stack of edges
    int Letters; // Nodes list of letters
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
    void ReadWords(string filename);
    void Print(); // printing helper function for testing
};

void Graph::DeleteHalf() {

  return;
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
  int i;
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
    n->Distance = -1;
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

    n->Letters = 0;
    n->Word = words;
    for (i = 0; i < (int) words.size(); i++) {
      n->Letters |= 1 << i; // set the bit of the letter
    }

    Source->Edges.push_back(e);

    Nodes.push_back(n);
    MinNodes++; // increment the Id
    //printf("%s\n", words.c_str());
  }

  return;
}

void Graph::ReadWords(string filename) {
  string word;
  size_t i;
  ifstream fin;
  Node* n;
  Edge *e, *er;
  int count;

  fin.open(filename);
  if (fin.fail()) return;

  count = 0;
  while (fin >> word) {
    for (i = 0; i < word.size(); i++) {
      n = new Node;
      e = new Edge;
      er = new Edge;
      
      n->Id = MinNodes + count;
      n->Word = word[i];
      count++;
      
      // build edges with the sink
      e->To = Sink;
      e->From = n;
      e->Original = 1;
      e->Residual = 0;

      er->To = n;
      er->From = Sink;
      er->Original = 0;
      er->Residual = 1;
      er->Reverse = e;
      e->Reverse = er;

      Nodes.push_back(n);

    }
    CanSpell(); // See if you can spell the given word
    DeleteHalf(); // delete each word, but keep the first half of the graph
    //printf("%s\n", word.c_str());
  }
  return;
}

void Graph::Print() {
  int i, j;

  for (i = 0; i < (int) Nodes.size(); i++) {
    printf("Node %d: %s Edges to", i, Nodes[i]->Word.c_str());
    for (j = 0; j < (int) Nodes[i]->Edges.size(); j++) {
      printf(" %d", Nodes[i]->Edges[j]->To->Id);
    }
    cout << endl;
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
  source->Distance = -1;
  g->MinNodes++;
  source->Word = "SOURCE";
  g->Source = source;
  g->Nodes.push_back(source);
  g->ReadDice(argv[1]);
  g->ReadWords(argv[2]);

  g->Print();

  delete g;
  delete source;
}
