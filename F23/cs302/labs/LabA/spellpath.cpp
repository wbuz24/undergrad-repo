// Will Buziak
// Lab AB
// CS302
// Spellpath
// g++ -Wall -Wextra -o spellpath spellpath.cpp

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

class Grid {
public:
  vector < vector < char > > Board; // the full game board
  int Rows; // max rows of the board
  int Cols; // max cols
};

int MaxPathLen(int row, int col, Grid *g) {
  int i, max;
  vector <int> l; // temporary array to store the return values of the recursive calls
  char tmp;

  if (g->Board[row][col] == '-') return 0;
  max = 0;
  // all values are initialized to zero, if there are no viable calls, this will be incremented to 1
  l.resize(16, 0);
  // do nothing if I am a hyphen - return 0
  // store the value in a temporary variable
  tmp = g->Board[row][col]; /* VERY tricky here, since you place the value in tmp, you must compare to tmp*/
  g->Board[row][col] = '-';

  // go through all possible adjacent cells and store their return values 
  if (row + 1 < g->Rows) {
    if (tmp - 1 == g->Board[row + 1][col]) l[0] = MaxPathLen(row + 1, col, g);
    if (tmp + 1 == g->Board[row + 1][col]) l[1] = MaxPathLen(row + 1, col, g);
  }
  if (row - 1 >= 0) {
    if (tmp - 1 == g->Board[row - 1][col]) l[2] = MaxPathLen(row - 1, col, g);
    if (tmp + 1 == g->Board[row - 1][col]) l[3] = MaxPathLen(row - 1, col, g);
  }
  if (col + 1 < g->Cols) {
    if (tmp - 1 == g->Board[row][col + 1]) l[4] = MaxPathLen(row, col + 1, g);
    if (tmp + 1 == g->Board[row][col + 1]) l[5] = MaxPathLen(row, col + 1, g);
  }
  if (col - 1 >= 0) {
    if (tmp - 1 == g->Board[row][col - 1]) l[6] = MaxPathLen(row, col - 1, g);
    if (tmp + 1 == g->Board[row][col - 1]) l[7] = MaxPathLen(row, col - 1, g);
  }
  // if col is even
  if (col % 2 == 0) {
    if (row + 1 < g->Rows && col + 1 < g->Cols) {
      if (tmp - 1 == g->Board[row + 1][col + 1]) l[8] = MaxPathLen(row + 1, col + 1, g);
      if (tmp + 1 == g->Board[row + 1][col + 1]) l[9] = MaxPathLen(row + 1, col + 1, g);
    }
    if (row + 1 < g->Rows && col - 1 >= 0) {
      if (tmp + 1 == g->Board[row + 1][col - 1]) l[10] = MaxPathLen(row + 1, col - 1, g);
      if (tmp - 1 == g->Board[row + 1][col - 1]) l[11] = MaxPathLen(row + 1, col - 1, g);
    }
  }
  // if col is odd
  if (col % 2 != 0) {
    if (row - 1 >= 0 && col + 1 < g->Cols) {
      if (tmp - 1 == g->Board[row - 1][col + 1]) l[12] = MaxPathLen(row - 1, col + 1, g);
      if (tmp + 1 == g->Board[row - 1][col + 1]) l[13] = MaxPathLen(row - 1, col + 1, g);
    }
    if (row - 1 >= 0 && col - 1 >= 0) {
      if (tmp - 1 == g->Board[row - 1][col - 1]) l[14] = MaxPathLen(row - 1, col - 1, g);
      if (tmp + 1 == g->Board[row - 1][col - 1]) l[15] = MaxPathLen(row - 1, col - 1, g);
    }
  }

  // place the value back into the grid
  g->Board[row][col] = tmp;
  // find the maximum path length
  for (i = 0; i < 16; i++) {
    if (l[i] > max) max = l[i];
  }
  // increment the maximum value
  max++;
  return max;
}

int main() {
  string word;
  int i, j, index, max;
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


  max = 0;
  // run through the entire board
  for (i = 0; i < (int) g->Board.size(); i++) {
    for (j = 0; j < (int) g->Board[i].size(); j++) {
      index = MaxPathLen(i, j, g); // call on each cell
      if (index > max) max = index; // find the maximum path
    }
  }

  // magic
  cout << max << endl;

  return 1;
}
