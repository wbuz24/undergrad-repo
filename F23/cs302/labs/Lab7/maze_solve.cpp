// Will Buziak
// CS302
// Lab 7
// Maze Solver
// Use depth first search to solve a Maze

#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
using namespace std;

class Node {
  public:
    int id; // index of the node
    list <int> edges; // all edges connected to the node
    bool visited;
};

class Graph {
  public:
    int row;
    int col;
    vector <Node *> nodes; // graph of nodes
    void print() const;
    void maze_solve(int index); // index and component number
};

void Graph::print() const {

  return;
}

void Graph::maze_solve(int index) { // perform DFS to find the end

  list <int>::iterator lit;
  // base case 1: check the visited field
  if (nodes[index]->visited) return;

  // base case 2: I am the last cell
  if (index == row*col - 1)

  // set my visited field to true
  nodes[index]->visited = true;
  // call maze_solve on all of my edges
  // I should only be connected to my adjacent neighbors without walls
  for (lit = nodes[index]->edges.begin(); lit != nodes[index]->edges.end(); lit++) {
    maze_solve(*lit);
  }
  
  return;
}

int main() {
  string word;
  int r, c, i;
  Graph *g = new Graph;
  Node *n;

  cin >> word >> g->row >> word >> g->col;

  cout << "ROWS " << g->row << " COLS " << g->col << endl;

  // initialize the graph, every node is connected to every node around it
  for (i = 0; i < g->row*g->col; i++) {
    n = new Node;
    n->id = i;
    n->visited = -1;

    g->nodes.push_back(n);
  }

  for (i = 0; i < g->nodes.size(); i++) {
    
    if (i > 0) g->nodes[i]->edges.push_back(i-1);
    if (i > g->col - 1) g->nodes[i]->edges.push_back(i-g->col);
    if (i < g->row*g->col - 1) g->nodes[i]->edges.push_back(i + 1);
    if (i < g->row*g->col - g->col - 1) g->nodes[i]->edges.push_back(i + g->col);
  }

  while (cin >> word >> r >> c) { // insert walls inbetween each index, these nodes are no longer connected
    g->nodes[r]->edges.erase(find(g->nodes[r]->edges.begin(), g->nodes[r]->edges.end(), c)); // remove the column from the row node
    g->nodes[c]->edges.erase(find(g->nodes[c]->edges.begin(), g->nodes[c]->edges.end(), r)); // this effectively disconnects the two nodes
    cout << word << " " << r << " " << c << endl;
  }

  // solve the maze
  g->maze_solve(0);

  return 1;
}
