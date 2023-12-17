// Will Buziak
// Lab AB
// CS302
// Spellpath
// g++ -Wall -Wextra -o spellpath spellpath.cpp

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdio>
using namespace std;

class Path { // path class
public:
  int Length;
  int R;
  int C;
  string Key; // key for memoization cache, represents the grid
  Path *Next; // pointer to the next node in the path, otherwise, NULL
};

class Grid {
public:
  vector < vector < char > > Board; // the full game board
  map <string, Path *> Cache;
  int Rows; // max rows of the board
  int Cols; // max cols

  string buildKey(int r, int c, string key); // build the key for cache lookup
  Path *Solve(int r, int c); // returns a pointer to a path
};


string Grid::buildKey(int r, int c, string key) {
  
  if (key[r*c] == '-') key[r*c] = 'O';

  // perform a DFS to find all nodes reachable 
  if (r + 1 < Rows && key[(r+1)*c] == '-') {
    if (Board[r][c] - 1 == Board[r + 1][c] || Board[r][c] + 1 == Board[r + 1][c]) key = buildKey(r+1, c, key);
  }
  if (r - 1 >= 0 && key[(r-1)*c] == '-') {
    if (Board[r][c] - 1 == Board[r - 1][c] || Board[r][c] + 1 == Board[r - 1][c]) key = buildKey(r-1, c, key);
  }
  if (c + 1 < Cols && key[r*(c+1)] == '-') {
    if (Board[r][c] - 1 == Board[r][c + 1] || Board[r][c] + 1 == Board[r][c + 1]) key = buildKey(r, c + 1, key);
  }
  if (c - 1 >= 0 && key[r*(c-1)] == '-') {
    if (Board[r][c] - 1 == Board[r][c - 1] || Board[r][c] + 1 == Board[r][c - 1]) key = buildKey(r, c - 1, key);
  }
  // if c is even
  if (c % 2 == 0) {
    if (r + 1 < Rows && c + 1 < Cols && key[(r+1)*(c+1)] == '-') {
      if (Board[r][c] - 1 == Board[r + 1][c + 1] || Board[r][c] + 1 == Board[r + 1][c + 1]) key = buildKey(r+1, c+1, key);
    }
    if (r + 1 < Rows && c - 1 >= 0 && key[(r+1)*(c-1)] == '-') {
      if (Board[r][c] - 1 == Board[r + 1][c - 1] || Board[r][c] + 1 == Board[r + 1][c - 1]) key = buildKey(r+1, c-1, key);
    }
  }
  // if c is odd
  if (c % 2 != 0) {
    if (r - 1 >= 0 && c + 1 < Cols && key[(r-1)*(c+1)] == '-') {
      if (Board[r][c] - 1 == Board[r - 1][c + 1] || Board[r][c] + 1 == Board[r - 1][c + 1]) key = buildKey(r-1, c+1, key);
    }
    if (r - 1 >= 0 && c - 1 >= 0 && key[(r-1)*(c-1)] == '-') {
      if (Board[r][c] - 1 == Board[r - 1][c - 1] || Board[r][c] + 1 == Board[r - 1][c - 1]) key = buildKey(r-1, c-1, key);
    }
  }

  return key;
};

Path* Grid::Solve(int r, int c) {
  Path *p;
  string key;
  int i, index, max;
  vector <Path *> l;
  char tmp;

  key = "";
  for (i = 0; i < Rows * Cols; i++) key += '-';
  key[r*c] = 'X';
  // build key
  key = buildKey(r, c, key);

  // try to find the key in the cache
  if (Cache.find(key) != Cache.end()) return Cache.find(key)->second;

  p = new Path;

  // create a new path node pointer
  p->R = r;
  p->C = c;
  p->Key = key;

  if (Board[r][c] == '-') {
    p->Next = NULL;
    p->Length = 0;
    Cache.insert(make_pair(p->Key, p));
    return p;
  }

  // swap the board value
  tmp = Board[r][c];
  Board[r][c] = '-';

  // go through all possible adjacent cells and store their return values 
  if (r + 1 < Rows) {
    if (tmp - 1 == Board[r + 1][c] || tmp + 1 == Board[r + 1][c]) l.push_back(Solve(r + 1, c));
  }
  if (c + 1 < Cols) {
    if (tmp - 1 == Board[r][c + 1] || tmp + 1 == Board[r][c + 1]) l.push_back(Solve(r, c + 1));
  }
  if (r - 1 >= 0) {
    if (tmp - 1 == Board[r - 1][c] || tmp + 1 == Board[r - 1][c]) l.push_back(Solve(r - 1, c));
  }
  if (c - 1 >= 0) {
    if (tmp - 1 == Board[r][c - 1] || tmp + 1 == Board[r][c - 1]) l.push_back(Solve(r, c - 1));
  }
  // if c is even
  if (c % 2 == 0) {
    if (r + 1 < Rows && c + 1 < Cols) {
      if (tmp - 1 == Board[r + 1][c + 1] || tmp + 1 == Board[r + 1][c + 1]) l.push_back(Solve(r + 1, c + 1));
    }
    if (r + 1 < Rows && c - 1 >= 0) {
      if (tmp + 1 == Board[r + 1][c - 1] || tmp - 1 == Board[r + 1][c - 1]) l.push_back(Solve(r + 1, c - 1));
    }
  }
  // if c is odd
  else {
    if (r - 1 >= 0 && c + 1 < Cols) {
      if (tmp - 1 == Board[r - 1][c + 1] || tmp + 1 == Board[r - 1][c + 1]) l.push_back(Solve(r - 1, c + 1));
    }
    if (r - 1 >= 0 && c - 1 >= 0) {
      if (tmp - 1 == Board[r - 1][c - 1] || tmp + 1 == Board[r - 1][c - 1]) l.push_back(Solve(r - 1, c - 1));
    }
  } 

  index = -1; // index into l for max path length
  max = -1; // max path length value

  // find the longest path from each recursive call
  for (i = 0; i < (int) l.size(); i++) {
    if (l[i]->Length > max) {
      max = l[i]->Length;
      index = i;
    }
  }

  Board[r][c] = tmp;

  // set the next value to the longest path
  if (index >= 0) {
    p->Next = l[index];
    p->Length = p->Next->Length++;
  }
  else {
    p->Next = NULL;
    p->Length = 1;
  }

  l.clear();

  Cache.insert(make_pair(p->Key, p));

  return p;
}

void Print(Path *p) {
  // recursive print function
  cout << p->R << " " << p->C << endl;
  if (p->Next == NULL) return; // if there is no next path node
  Print(p->Next);

  return;
}

int main() {
  string word;
  int i, j, index, max;
  Path *p, *mp;
  Grid *g;

  g = new Grid;

  index = 0;
  while (cin >> word) { // read each line of the input file
    g->Board.resize(index+1); // increment the size of the board
    for (i = 0; i < (int) word.size(); i++) {
      g->Board[index].push_back(word[i]); // read in the board
    }
    index++;
  }

  // set the bounds of the board
  g->Rows = g->Board.size();
  g->Cols = g->Board[0].size();


  max = -1;
  // run through the entire board
  for (i = 0; i < (int) g->Board.size(); i++) {
    for (j = 0; j < (int) g->Board[i].size(); j++) {
      cout << g->Board[i][j];
      p = g->Solve(i, j);
      //cout << p->R << " " << p->C << " "<< p->Length << endl;
      if (p->Length > max) {
        max = p->Length;
        mp = p;
      }
    }
    cout << endl;
  }

  cout << "PATH" << endl;

  Print(mp);
  // chase the next pointers for the cell with the longest path 

  return 1;
}
