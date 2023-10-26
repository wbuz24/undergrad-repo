// Will Buziak
// CS302
// Lab 7
// Maze Solver
// Use depth first search to solve a Maze
// each time I parse a nodes edge, it is O(E), but there will only be a max of four edges for any node

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
    int visited;
};

class Graph {
  public:
    int row;
    int col;
    vector <Node *> nodes; // graph of nodes
    void print(int index) const;
    void maze_solve(int index); // index and component number
};

void Graph::print(int index) const {
  
  list <int>::iterator lit;
  if (nodes[index]->visited < 1) return; // not part of the right path
 
  printf("PATH %d\n", index);
  nodes[index]->visited = 0; // I have now printed myself and can remove from my path
  for (lit = nodes[index]->edges.begin(); lit != nodes[index]->edges.end(); lit++) { // search the edges
    if (nodes[*lit]->visited > 0) print(*lit); // only make a recursive call if this edge is a part of my path
  }
  return;
}

void Graph::maze_solve(int index) { // perform DFS to find the end

  list <int>::iterator lit;
  // base case 1: check the visited field
  if (nodes[index]->visited >= 0) {
    return;
  }

  // set my visited field to true
  // visited field of 1 means I am a part of my path.
  nodes[index]->visited = 1;

  // base case 2: I am the last cell
  if (index == row*col - 1) {
    print(0); // recursively print the path
    return;
  }

  // call maze_solve on all of my edges
  // I should only be connected to my adjacent neighbors without walls
  for (lit = nodes[index]->edges.begin(); lit != nodes[index]->edges.end(); lit++) {
    maze_solve(*lit); // recursively search each of my edges
  }

  nodes[index]->visited = 0; // if I return from all of my edges, I must not be a part of my path.
  
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
    n->visited = -1; // -1 is not visited

    g->nodes.push_back(n);
  }

  for (i = 0; i < g->nodes.size(); i++) { // each node is connected to each surrounding node
    
    if (i < g->row*g->col - g->col) g->nodes[i]->edges.push_back(i + g->col);
    if (i < g->row*g->col - 1 && i % g->col < g->col - 1) g->nodes[i]->edges.push_back(i + 1);
    if (i % g->col > 0) g->nodes[i]->edges.push_back(i - 1);
    if (i > g->col - 1) g->nodes[i]->edges.push_back(i - g->col);
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
