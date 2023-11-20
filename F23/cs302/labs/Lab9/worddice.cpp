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
    int Letters; // Nodes list of letters
    class Edge* Back; // the edge that brought you to this node
    vector <Node *> Children; // list of children nodes
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
  int i;
  // delete all nodes greater than MinNodes
  for (i = 1; i < MinNodes; i++) {
    Nodes[i]->Children.clear();
  }

  Nodes.resize(MinNodes);
  

  return;
};

int Graph::BFS() {
  /*int i;
  vector <int> stack; // stack of indices  
  
  for (i = 0; i < (int) stack.size(); i++) {
    
  }
*/
  return 0;
}

int Graph::CanSpell() {
  int i;
  // if the BFS function can 
  if (BFS() > 0) {
    Print(); 
  } 
  else {
    printf("Cannot spell ");
    for (i = MinNodes; i < (int) Nodes.size() - 1; i++) printf("%s", Nodes[i]->Word.c_str());
    printf("\n");
  }
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
      n->Letters |= 1 << (words[i] - 'A'); // set the bit of the letter
    }

    Source->Children.push_back(n);
    Nodes.push_back(n);
    MinNodes++; // increment the Id
    //printf("%s\n", words.c_str());
  }

  return;
}

void Graph::ReadWords(string filename) {
  string word;
  int i, j;
  ifstream fin;
  Node* n, *sink;
  Edge *e, *er;
  int count;

  fin.open(filename);
  if (fin.fail()) return;

  sink = new Node;
  sink->Word = "SINK";
  Sink = sink;

  while (fin >> word) {
    count = MinNodes;
    for (i = 0; i < (int) word.size(); i++) {
      n = new Node;
      e = new Edge;
      er = new Edge;
      
      n->Id = count;
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

      n->Children.push_back(Sink);
      Nodes.push_back(n);

      // run through all nodes 1-MinNodes and check if the letter is in the die
      for (j = 1; j < MinNodes + 1; j++) {
        if (Nodes[j]->Letters & (1 << (word[i] - 'A'))) {
          // If my letter is in the die, add an edge
          e = new Edge;

          e->To = n;
          e->From = Nodes[j];
          e->Original = 1;
          e->Residual = 0;

          n->Back = e;
          Nodes[j]->Children.push_back(n);
        }
      }

    }
    Sink->Id = count;
    Nodes.push_back(Sink);
    CanSpell(); // See if you can spell the given word
//    Print();
    DeleteHalf(); // delete each word, but keep the first half of the graph
    //printf("%s\n", word.c_str());
  }

  delete n;
  delete e;
  delete er;
  delete sink;
  return;
}

void Graph::Print() {
  int i, j;

  for (i = 0; i < (int) Nodes.size(); i++) {
    printf("Node %d: %s Edges to", i, Nodes[i]->Word.c_str());
    for (j = 0; j < (int) Nodes[i]->Children.size(); j++) {
      printf(" %d", Nodes[i]->Children[j]->Id);
    }
    cout << endl;
  }
  cout << endl;

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

//  g->Print();

  delete g;
  delete source;
}
