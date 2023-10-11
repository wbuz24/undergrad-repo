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
  void analyze_superball(Disjoint_Set *d);
  void search(int index, Disjoint_Set *d);
  void store(Disjoint_Set *d);
  char move(Disjoint_Set *d);
  void print(char m);
  int ideal_swap(Disjoint_Set *d);
  int ideal_score(Disjoint_Set *d);
  map <int, int> idmap;
  int r;
  int c;
  int mss;
  int empty;
  vector <int> board;
  vector <int> goals;
  vector <int> colors;
  vector <int> swap;
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

  for (i = 0; i < r*c; i++) if (board[i] != '*' && board[i] != '.') search(i, d); // we know that the given square is not a '*'

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

  sizes = d->Get_Sizes();
  for (i = 0; i < r*c; i++) { // only insert into the map when it is a scoring set with a size greater than the minimum scoring size.
    if (sizes->at(d->Find(i)) >= mss && goals[i] && board[i] != '*') idmap.insert(make_pair(d->Find(i), i));
    //if (goals[i] && board[i] != '*') board[i] = toupper(board[i]); // return scoring cells to upper case
  }

  return;
}

void Superball::print(char m) { 
  if (m == 'w') {
    printf("Move is: SWAP %d %d %d %d\n", swap[0], swap[1], swap[2], swap[3]); 
  }
  if (m == 'c') {
    printf("Move is: SCORE %d %d\n", swap[0], swap[1]);
  }
  return;
}

int Superball::ideal_swap(Disjoint_Set *d) {
  int i, j, bsize = 0, bindex = 0, index, sindex = 0;
  const vector <int> *sizes;
  vector <int> squares; // vector to keep track of eligible swapping squares
  // find the ideal indices to swap
  // what is the best swap?
  // connecting two groups
  // adding to a set: you want to add to the largest set
  // turn a set into a scoring set: a set is near a scoring square, but not found in the map.
  squares.clear(); // squares holds the valid squares for swapping
  sizes = d->Get_Sizes();
  if (empty > r*c/3) { // if there is mostly empty spaces
    
    // Next, find an index to take from: this will be a non-scoring square from a negligible set (not found in the scoring sets)
    // I want the color to be the same as the desired index
    
    for (i = 0; i < r; i++) {
      for (j = 0; j < c; j++) {
        if (idmap.find(d->Find(i*c+j)) == idmap.end() && board[i*c+j] != '.') { // if I am not a part of a scoring set and I am not a dot
          if (i >= 1 && idmap.find(d->Find((i-1)*c+j)) != idmap.end()) bindex = i*c+j;
          if (j >= 1 && idmap.find(d->Find(i*c+j-1)) != idmap.end()) bindex = i*c+j;
          if (i < r - 1 && idmap.find(d->Find((i+1)*c+j)) != idmap.end()) bindex = i*c+j;
          if (j < c - 1 && idmap.find(d->Find(i*c+j + 1)) != idmap.end()) bindex = i*c+j;
          if (goals[i*c+j] && board[i*c+j == '*']) bindex = i*c+j;
          if (!goals[i*c+j]) squares.push_back(i*c+j); // gather all eligible swapping squares
        }
      }
    } 

    sindex = squares[0];
    for (i = 0; (size_t) i < squares.size(); i++) {
      if (board[squares[i]] != board[bindex]) sindex = squares[i]; // if the colors match, grab the index from the vector
    }
    index = bindex;
    swap.clear();
    swap.push_back(bindex / c); // store the desired cell
    swap.push_back(bindex % c); 
    swap.push_back(sindex / c);
    swap.push_back(sindex % c);
    return index;
  }
  return -1;
}

int Superball::ideal_score(Disjoint_Set *d) {
  map <int, int>::iterator mit;
  const vector <int> *sizes;
  int biggest = 0, bindex = 0, sindex = 0, score = 0, cscore = 0, index = 0;

  sizes = d->Get_Sizes();
  if (idmap.size() > 0) { // it is ideal to score
    // find the ideal set to score
    for (mit = idmap.begin(); mit != idmap.end(); mit++) {
      if (sizes->at(mit->first) > biggest) { // track the largest set
        biggest = sizes->at(mit->first);
        bindex = mit->second; // store the index
      }
      cscore = sizes->at(mit->first) * colors[board[mit->second]]; // size of the set * points for the color
      if (cscore > score) { // track largest scoring set
        score = cscore;
        sindex = mit->second; // track scoring set index
      }
    }

    // choose which way to score
    if (empty < r*c/3) index = bindex; // less than 1/3 of the board open, score larger set
    else index = sindex; // otherwise, score based on higher scoring set

    swap.clear();
    swap.push_back(index / c); // store the row in the vector
    swap.push_back(index % c); // store the column in the vector
    return index;
  }

  return -1;
}

char Superball::move(Disjoint_Set *d) { // this function calls analyze and decides on what move to make
  // play superball by making one move
  // analyze the board
  analyze_superball(d);
  // make a move
  // you can either swap or score
  if (idmap.size() == 0 || empty >= r*c / 3) {
    // swap
    // find the ideal swap
    if (ideal_swap(d) != -1) { // if it is ideal to swap, return
      return 'w';
    }
    ideal_score(d); // otherwise, call ideal score instead
    return 'c'; // 'w' for swap, 'c' for score
  }

  else {
    // find the ideal score
    if (ideal_score(d) != -1) { // if it is ideal to score, return
      return 'c'; // score
    }
    ideal_swap(d); // otherwise, swap instead
    return 'w';
  }
  // if you have fewer than five pieces & cannot score any, you lose: make a final legal swap & the game can end.
  // if you cannot clear enough squares for the incoming new random ones, you lose, make a legal swap or score and the game can end
}

int main(int argc, char** argv) {
  Disjoint_Set *d = new Disjoint_Set;
  Superball *s = new Superball(argc, argv);

  d->Initialize(s->r * s->c); // initialize the disjoint set

  s->swap.clear();
  s->print(s->move(d)); // print the desired move

  delete d;
  delete s; // delete both class instances
  return 0;
}
