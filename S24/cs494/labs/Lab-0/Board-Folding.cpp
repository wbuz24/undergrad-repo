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
 
vector <int> invert(vector <int> &v) {
  int i;
  vector <int> rv;

  for (i = (int) v.size() - 1; i >= 0; i--) {
    rv.push_back(v[i]);
  }
  return rv;
}

vector <int> starting_places(vector <int> &Grid) {
  vector <int> rv;
  string w1, w2;
  int i, j;

  // First row is always a starting row

  rv.resize(Grid.size() + 1);
  rv[0] = 1;
  for (i = 0; i < (int) Grid.size(); i++) {
    for (j = 1; j < i; j++) {
      
    }
  }

  return rv;
}

int main() {
  int i, j, k;
  string row;
  vector <string> grid, cols;
  vector <int> vert, horiz, s, e, iv, ih;
  unordered_map <string, int> v, h; /* Store each string */

  i = 0;
  j = 0;
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

    if (j == 0) {
      cols.resize(row.length());
    }
    for (k = 0; k < (int) row.length(); k++) cols[k] += row[k];

    j++;
    grid.push_back(row);
  }

  /* Build the horizontal vector of integers for comparison */
  j = 0;
  for (i = 0; i < (int) cols.size(); i++) {
    if (h.find(cols[i]) == h.end()) {
      h.insert(make_pair(cols[i], j));
      horiz.push_back(j);
      j++;
    }
    else {
      horiz.push_back(h.find(cols[i])->second);
    }
  }

  s = starting_places(vert);
  iv = invert(vert); 
  ih = starting_places(iv);
  e = invert(ih);




  /* print */
  for (i = 0; i < (int) grid.size(); i++) printf("%s\n", grid[i].c_str());


  printf("\n\n");
  for (i = 0; i < (int) vert.size(); i++) printf("%d", e[i]);
  printf("\n\n");
  for (i = 0; i < (int) horiz.size(); i++) printf("%d", e[i]);
  printf("\n\n");
}
