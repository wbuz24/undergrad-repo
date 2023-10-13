// Will Buziak
// Lab 5
// Play
// Play superball for an average greater than 100 over 100 rounds
#include "disjoint_set.hpp"
#include <iostream>
#include <map>
using namespace std;
using plank::Disjoint_Set;

class Superball {
public:
  Superball(int argc, char **argv);
  int rate(Disjoint_Set *d);
  void analyze_superball(Disjoint_Set *d);
  void move(Disjoint_Set *d);
  void search(int index, Disjoint_Set *d);
  void store(Disjoint_Set *d);
  int score(Disjoint_Set *d);
  bool next_to(int index);
  void swap(Disjoint_Set *d, vector <int> indices);
  void print(int index, int sindex);
  map <int, int> idmap;
  int r;
  int c;
  int mss;
  int rating;
  int empty;
  vector <int> board;
  vector <int> goals;
  vector <int> colors;
  vector <int> squares;
};

void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-read rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  int i, j;
  string s;


  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; (size_t) i < strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);

  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if (s.size() != (size_t) c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i*c+j] = s[j];
      if (board[i*c+j] == '.') empty++;
      if (board[i*c+j] == '*') empty++;
      if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
        goals[i*c+j] = 1;
        board[i*c+j] = tolower(board[i*c+j]);
      }
    }
  }
}

int Superball::rate(Disjoint_Set *d) {
  int rate = 0, i;
  const vector <int> *sizes;
  size_t num; // number of of sets in the disjoint set
  
  num = d->Size();
  sizes = d->Get_Sizes();
  for (i = 0; i < r*c; i++) {
    if (goals[i] && next_to(i)) rate += colors[board[i]];
    if (goals[i]) rate += colors[board[i]];
    if (next_to(i)) rate += 3 * colors[board[i]];
    if (sizes->at(d->Find(i)) > 1 && next_to(i)) { // I am a set & I am not in the map
      rate += sizes->at(d->Find(i)) * colors[board[i]]; // I am not a scoring set
      if (idmap.find(d->Find(i)) != idmap.end() && sizes->at(d->Find(i)) > (int) num) rate += 5 * sizes->at(d->Find(i));
      if (sizes->at(d->Find(i)) > mss) rate += 10 * sizes->at(d->Find(i));
      if (idmap.find(d->Find(i)) != idmap.end()) rate += 15 * sizes->at(d->Find(i)) * colors[board[i]]; // scoring set
    }
    else rate --;
    if (!next_to(i) || sizes->at(d->Find(i)) == 1) rate -= 5;
  }

  if (num < 7) rate += idmap.size(); // reward low number of sets

  return rate;
}

bool Superball::next_to(int index) {
  int i, j;

  i = index / c;
  j = index % c;

  if (i >= 1 && board[index] == board[(i-1)*c + j]) return 1;

  if (i < r - 1 && board[index] == board[(i+1)*c + j]) return 1;

  if (j >= 1 && board[index] == board[i*c + j - 1]) return 1;

  if (j < c - 1 && board[index] == board[i*c + j + 1]) return 1;

  return 0;

}

void Superball::analyze_superball(Disjoint_Set *d) {
  int i;

  for (i = 0; i < r*c; i++) if (board[i] != '*' && board[i != '.']) search(i, d); // we know that the given square is not a '*'

  store(d); // must wait until after creating the sets to store
  return;
}

void Superball::search(int index, Disjoint_Set *d) {

  int i, j;

  i = index / c;
  j = index % c;

  // must check bounds, if the adjacent square is the same color & if it is already a part of the same set.
  if (i >= 1 && board[index] == board[(i-1)*c + j] && d->Find(index) != d->Find((i-1)*c + j)) d->Union(d->Find(index), d->Find((i-1)*c + j));

  if (i < r - 1 && board[index] == board[(i+1)*c + j] && d->Find(index) != d->Find((i+1)*c + j)) d->Union(d->Find(index), d->Find((i+1)*c + j));

  if (j >= 1 && board[index] == board[i*c + j - 1] && d->Find(index) != d->Find(i*c + j - 1)) d->Union(d->Find(index), d->Find(i*c + j - 1));

  if (j < c - 1 && board[index] == board[i*c + j + 1] && d->Find(index) != d->Find(i*c + j + 1)) d->Union(d->Find(index), d->Find(i*c + j + 1));
  return;
}

void Superball::store(Disjoint_Set *d) {
  int i;
  const vector <int> *sizes;

  squares.clear();
  sizes = d->Get_Sizes();
  for (i = 0; i < r*c; i++) { // only insert into the map when it is a scoring set with a size greater than the minimum scoring size.
    if (sizes->at(d->Find(i)) >= mss && goals[i] && board[i] != '*' && board[i] != '.') {
      idmap.insert(make_pair(d->Find(i), i));
    }
    if (board[i] != '*' && board[i] != '.') squares.push_back(i);
  }
  return;
}

void Superball::move(Disjoint_Set *d) {
  vector <int> indices;
  int r, tmp, index = -1, sindex = -1;
  size_t i, j;
  rating = 0;
  indices.clear();
  indices.resize(2, -1);

  index = score(d); // try to score, if you can't this should be -1
  if (index < 0) { // swap
    for (i = 0; i < squares.size(); i++) {
      for (j = i+1; j < squares.size(); j++) {
        tmp = board[squares[i]];
        board[squares[i]] = board[squares[j]];
        board[squares[j]] = tmp;

        analyze_superball(d);
        r = rate(d);

        if (r >= rating) {
          rating = r;
          index = squares[i];
          sindex = squares[j];
        }

        tmp = board[squares[i]];
        board[squares[i]] = board[squares[j]];
        board[squares[j]] = tmp;
      }
    }
  }
  print(index, sindex);

  return;
}

int Superball::score(Disjoint_Set *d) {
  int score = -1, index = -1, lindex = 0, largest = 0;
  const vector <int> *sizes;
  map <int, int>::iterator mit;

  if (idmap.size() > 0 && empty < r*c/3) {
    sizes = d->Get_Sizes(); // sizes of the set ids

    for (mit = idmap.begin(); mit != idmap.end(); mit++) {
      if (sizes->at(mit->first) * colors[board[mit->first]] > score) {
        score = sizes->at(mit->first) * colors[board[mit->first]];
        index = mit->second;
      }
      if (sizes->at(mit->first) > largest) {
        lindex = mit->second;
        largest = sizes->at(mit->first);
      } 
    }

    if (empty < r*c/5) index = lindex;
  }

  return index;
}

void Superball::print(int index, int sindex) { 
  if (sindex < 0) printf("SCORE %d %d", index / c, index % c); // scoring set
  else printf("SWAP %d %d %d %d", index / c, index % c, sindex / c, sindex % c);
  return;
}


int main(int argc, char** argv) {
  Disjoint_Set *d = new Disjoint_Set;
  Superball *s = new Superball(argc, argv);

  d->Initialize(s->r * s->c); // initialize the disjoint set
  s->analyze_superball(d);
  s->move(d);

  delete d;
  delete s; // delete both class instances
  return 0;
}
