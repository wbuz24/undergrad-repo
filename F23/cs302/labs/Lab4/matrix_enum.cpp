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
  vector <vector <char> > im;  // vector of vectors to map the permutations
  void Print();               /* Print the matrix defined by W, Perm and E_ID */
  void Permute(int index);    /* This is the recursive permuting method. */
  void Choose(int index);     /* This is the recursive n-choose-k method. */
};

void Matrix::Print() {
  size_t i, j;

  for (i = 0; i < im.size(); i++) {
    for (j = 0; j < im[i].size(); j++) {
      printf("%c", im[i][j]);
    }
    printf("\n");
  }
  return;
}

void Matrix::Permute (int index) {
  size_t i, j;

  /* Base case -- we're done*/

  if (index == W) {
    return;  
  }

  /* Otherwise, for each element of the vector, swap it with the element
     in index, call Permute() recursively on the remainder of the
     vector, and then swap it back. */

  for (i = index; i < Perm.size(); i++) {

    Perm[i] = 'X';
    
    Permute(index+1);

    Perm[i] = '.';

 }

  
  for (i = 0; i < im.size(); i++) {
    for (j = 0; j < im[i].size(); j++) {
      if (im[i][j] != 'X') Non_X.push_back(i*W + j);
    }
  }


  Choose(index); // n choose k call
}

void Matrix::Choose(int index) {

  /* Base case -- if there are no more people to add, 
     print out the team and return */

  if (index == 0) {
    Print();
    return;
  }

  /* This is a second base case -- if there are fewer people left to add
     than there are places left on the team, then it's impossible to finish,
     so simply return.  Ask yourself why this is better than testing whether
     index is equal to people.size(), and returning if so. */

  if ((size_t)W > Perm.size() - index) return;

  /* Now, put the person in people[index] onto the team, and call GenTeams()
     recursively.  Afterwards, take the person off of the team. */

  Perm[index];
  Choose(index+1);
  Non_X.pop_back();

  /* Finally, call GenTeams() recursively without putting
     people[index] on the team. */

  Choose(index+1);
}

int main(int argc, char** argv) {
  Matrix* M = new Matrix;
  int i;


  if (argc == 4) {
    M->W = atoi(argv[1]);
    M->E = atoi(argv[2]);
    M->P = atoi(argv[3]);

    M->im.resize(M->W);
    M->Perm.resize(M->W, '.');
    for (i = 0; i < M->W; i++) M->im[i].resize(M->W, '.');
    
    M->Permute(0);
  }
  return 0;
}
