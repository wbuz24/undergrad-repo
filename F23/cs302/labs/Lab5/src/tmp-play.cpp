// Will Buziak
// Lab 5
// Play
// Must play by swapping or scoring superball until the game averages atleast 100 points over 100 rounds
#include "disjoint_set.hpp"
#include <iostream>
#include <map>
using namespace std;
using plank::Disjoint_Set;

class Superball {
public:
  Superball(int argc, char **argv);
  int analyze_superball(Disjoint_Set *d);
  void search(int index, Disjoint_Set *d);
  int store(Disjoint_Set *d);
  char move(Disjoint_Set *d);
  void print(char m);
  void ideal_swap(int index, Disjoint_Set *d);
  int ideal_score(Disjoint_Set *d);
  map <int, int> idmap;
  int r;
  int c;
  int mss;
  int empty;
  int rating; 
  vector <int> board;
  vector <int> goals;
  vector <int> colors;
  vector <int> swap; // indices of either swapping or scoring squares
  vector <int> non_scoring; // indices of non_scoring squares
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

int Superball::analyze_superball(Disjoint_Set *d) {
  int i, score;
  non_scoring.clear();

  for (i = 0; i < r*c; i++) {
    if (board[i] != '*' && board[i] != '.') {
      search(i, d); // we know that the given square is not a '*'
      non_scoring.push_back(i); // all colored squares, will later look for an arbitrary swapping square.
    }
  }
  score = store(d); // must wait until after creating the sets to store

  return score;
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

int Superball::store(Disjoint_Set *d) {
  int i, score = 0;
  const vector <int> *sizes;

  sizes = d->Get_Sizes();
  for (i = 0; i < r*c; i++) { // only insert into the map when it is a scoring set with a size greater than the minimum scoring size.
    if (sizes->at(d->Find(i)) >= mss && goals[i] && board[i] != '*') {
      idmap.insert(make_pair(d->Find(i), i));
      if (sizes->at(d->Find(i)) * colors[i] > score) score = sizes->at(d->Find(i)) * colors[i]; // track highest score 
    }

  }
  return score; // return the highest score
}

void Superball::print(char m) { 
  if (m == 'w') {
    printf("SWAP %d %d %d %d\n", swap[0], swap[1], swap[2], swap[3]); 
  }
  if (m == 'c') {
    printf("SCORE %d %d\n", swap[0], swap[1]);
  }
  return;
}

void Superball::ideal_swap(int index, Disjoint_Set *d) {
  size_t i;
  int score = 0, tmp;
  const vector <int> *sizes;

  sizes = d->Get_Sizes();
  if (index == (int) non_scoring.size()) return;
  for (i = index; i < non_scoring.size(); i++) {
    // find an "ideal square"
    // recursive swap
    /*tmp = board[non_scoring[i]];
    board[non_scoring[i]] = board[non_scoring[index]];
    board[non_scoring[index]] = tmp;
    */
    score = sizes->at(d->Find(non_scoring[i]));
    if (score > 0) cout << score << endl;
    if (score > rating) {
      rating = score;
    }

    //ideal_swap(index + 1, d);

   /* tmp = board[non_scoring[i]];
    board[non_scoring[i]] = board[non_scoring[index]];
    board[non_scoring[index]] = tmp; */
  }
}

int Superball::ideal_score(Disjoint_Set *d) {
  map <int, int>::iterator mit;
  const vector <int> *sizes;
  int score = 0, index = 0, lindex, size = 0;

  // check if scoring is legal
  // must have a scoring set
  // must be able to clear enough squares for the incoming 3
  if (idmap.size() > 0) {
    if (empty <= r*c/3) { // if the board is 2/3 full, I will try to score

      sizes = d->Get_Sizes();
      for (mit = idmap.begin(); mit != idmap.end(); mit++) {
        if (colors[board[mit->first]] * sizes->at(mit->first) > score) {
          // highest score
          index = mit->second;
          score = colors[board[mit->first]] * sizes->at(mit->first); // color of the set id should be the same as the color of the index
        }

        if (sizes->at(mit->first) > size) { // largest set
          size = sizes->at(mit->first);
          lindex = mit->second;
        }

      }

      // if your largest scoring set cannot clear enough squares for the incoming 3, make an arbitrary swap and end the game.
      if (r*c <= (int) non_scoring.size() + 3 - size) return 0;
      // if my largest scoring set can clear 
      if (empty < r*c/3) index = lindex;

      swap.clear();
      swap.push_back(index / c);
      swap.push_back(index % c);
    }
  }

  return score;
}

char Superball::move(Disjoint_Set *d) { // this function calls analyze and decides on what move to make
  // play superball by making one move
  // analyze the board
  rating = analyze_superball(d);
  swap.clear();
  // make a move
  // you can either swap or score
  //if (ideal_score(d) > 0) return 'c';
  // if you have fewer than five pieces & cannot score any, you lose: make a final legal swap & the game can end.
  // if you cannot clear enough squares for the incoming new random ones, you lose, make a legal swap or score and the game can end
  ideal_swap(0, d);
  return 'w';
}

int main(int argc, char** argv) {
  Disjoint_Set *d = new Disjoint_Set;
  Superball *s = new Superball(argc, argv);
  char m;

  d->Initialize(s->r * s->c); // initialize the disjoint set

  s->swap.clear();
  m = s->move(d);
  //s->print(m); // print the desired move

  delete d;
  delete s; // delete both class instances
  return 0;
}
