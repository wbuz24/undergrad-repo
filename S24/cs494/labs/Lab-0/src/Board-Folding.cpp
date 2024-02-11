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

  rv.resize(Grid.size() + 1, 0);
  rv[0] = 1;
  for (i = 1; i < (int) rv.size(); i++) {
    for (j = 1; j < i; j++) {
      if (Grid[i-j] == Grid[i+j] && rv[i-j]) rv[i] = 1; 
      else break;
    }
  }

  return rv;
}

int main() {
  int i, j, k, r, c, tot;
  string row;
  vector <string> grid, cols;
  vector <int> vert, horiz, s, e, iv, ih;
  unordered_map <string, int> v, h; /* Store each string */

  i = 0;
  j = 0;
  r = 0;
  c = 0;
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

    r++;
    j++;
    grid.push_back(row);
  }

  /* Build the horizontal vector of integers for comparison */
  j = 0;
  c = cols.size();
  for (i = 0; i < c; i++) {
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

  tot = 0;

  for (i = 0; i < (int) s.size(); i++) {
    if (s[i]) for (j = i + 1; j < (int) s.size(); j++) {
      if (e[j]) tot++;
    }
  }

  s = starting_places(horiz);
  iv = invert(horiz);
  ih = starting_places(iv);
  e = invert(ih);

  for (i = 0; i < (int) s.size(); i++) {
    if (s[i]) for (j = i+1; j < (int) s.size(); j++) {
      if (e[j]) tot++;
    }
  }


  /* print */
 // for (i = 0; i < (int) s.size(); i++) printf("%d", s[i]);
  //printf("\n\n");
  //for (i = 0; i < (int) e.size(); i++) printf("%d", e[i]);
  //printf("\n\n");

  printf("%d\n", tot);
}
