// Will Buziak
// CS302
// Lab 4
// Enumeration with recursion

#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Matrix {
public:
  int W;
  int E;
  int P;                      /* This is 'x' or 'h' */
  vector <int> Perm;          /* Permutation of 0 .. (W-1), for the 'X' elements. */
  vector <int> Non_X;         /* This is the row/col id of each of the non-X elements. */
  vector <int> E_ID;          /* This is the row/col id of the E elements */
  vector <vector <int> > im;  // vector of vectors to map the permutations
  void Print();               /* Print the matrix defined by W, Perm and E_ID */
  void Permute(int index, vector <vector <int> > im);    /* This is the recursive permuting method. */
  void Choose(int index, vector <vector <int> > im);     /* This is the recursive n-choose-k method. */
};

void Matrix::Print() {
  return;
}

void Matrix::Permute (int index, vector <vector <int> > im) {
  size_t i;
  int tmp;

  /* Base case -- we're done - print out the vector */

  if (index == Perm.size()) {
    Print();
    return;  
  }

  /* Otherwise, for each element of the vector, swap it with the element
     in index, call Permute() recursively on the remainder of the
     vector, and then swap it back. */

  for (i = index; i < Perm.size(); i++) {

    tmp = Perm[i];         /* Swap Perm[index] with Perm[i] */
    Perm[i] = Perm[index];
    Perm[index] = tmp;

    Permute(index+1, im);  

    tmp = Perm[i];          /* Swap back */
    Perm[i] = Perm[index];
    Perm[index] = tmp;
  }

  Choose(index, im); // n choose k call
}

void Matrix::Choose(int index, vector <vector <int> > im) {
  size_t i;

  /* Base case -- if there are no more people to add, 
     print out the team and return */

  if (index == E) return;

  /* This is a second base case -- if there are fewer people left to add
     than there are places left on the team, then it's impossible to finish,
     so simply return.  Ask yourself why this is better than testing whether
     index is equal to people.size(), and returning if so. */

  if (W > Perm.size() - index) return;

  /* Now, put the person in people[index] onto the team, and call GenTeams()
     recursively.  Afterwards, take the person off of the team. */

  Perm[index];
  Choose(index+1, im);
  Non_X.pop_back();

  /* Finally, call GenTeams() recursively without putting
     people[index] on the team. */

  Choose(index+1, im);
}

int main(int argc, char** argv) {
  Matrix* M = new Matrix;
  size_t i, j;


  if (argc == 4) {
    M->W = atoi(argv[1]);
    M->E = atoi(argv[2]);
    M->P = atoi(argv[3]);

    M->im.resize(M->W);
    for (i = 0; i < M->W; i++) M->im[i].resize(M->W);

    M->Permute(0, M->im);
  

  }
  return 0;
}
