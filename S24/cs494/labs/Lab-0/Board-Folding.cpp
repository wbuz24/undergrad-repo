/* Will Buziak
 * CS494
 * Board Folding
 * February 2024 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector <int> starting_places(vector <string> &Grid);

int main() {
  int i, j;
  string row;
  vector <string> grid;
  vector <int> vert, horiz; 
  unordered_map <string, int> v, h; /* Store each string */

  i = 0;

  /* Store each string in a map with a unique integer identifier */
  while (cin >> row) {
    if (v.find(row) == v.end()) {
      v.insert(make_pair(row, i));
      vert.push_back(i);
      i++;
    }
    else {
      vert.push_back(v.find(row)->second);
    }
    grid.push_back(row);
  }

  for (i = 0; i < (int) grid.size(); i++) printf("%s\n", grid[i].c_str());
}
