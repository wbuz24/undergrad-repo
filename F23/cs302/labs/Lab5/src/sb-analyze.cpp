// Will Buziak
// Lab 5
// Analyze
// Must analyze the superball board and print out scoring sets
#include "disjoint_set.hpp"
#include <iostream>
#include <map>
using namespace std;
using plank::Disjoint_Set;

class Superball {
  public:
    Superball(int argc, char **argv);
    void analyze_superball(Disjoint_Set *d);
    void search(int index, Disjoint_Set *d);
    void store(Disjoint_Set *d);
    void print(Disjoint_Set *d);
    map <int, int> idmap;
    int r;
    int c;
    int mss;
    int empty;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
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

void Superball::analyze_superball(Disjoint_Set *d) {
  int i;

  for (i = 0; i < r*c; i++) if (board[i] != '*') search(i, d); // we know that the given square is not a '*'

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

  sizes = d->Get_Sizes();
  for (i = 0; i < r*c; i++) { // only insert into the map when it is a scoring set with a size greater than the minimum scoring size.
    if (sizes->at(d->Find(i)) >= mss && goals[i] && board[i] != '*') idmap.insert(make_pair(d->Find(i), i));
  }

  return;
}
void Superball::print(Disjoint_Set *d) { 
  map <int, int>::iterator mit; // map is keyed on set id and value is the index
  const vector <int> *sizes;

  sizes = d->Get_Sizes();

  printf("Scoring sets:\n");
  for (mit = idmap.begin(); mit != idmap.end(); mit++) { // parse the map
    printf("  Size: %2d  Char: %c  Scoring Cell: %d,%d\n", sizes->at(mit->first), board[mit->second], mit->second / c, mit->second % c);
  }
  return;
}


int main(int argc, char** argv) {
  Disjoint_Set *d = new Disjoint_Set;
  Superball *s = new Superball(argc, argv);
  
  d->Initialize(s->r * s->c); // initialize the disjoint set
  s->analyze_superball(d);

  s->store(d); // must wait until after creating the sets to store
  s->print(d);
  delete d;
  delete s; // delete both class instances
  return 0;
}
