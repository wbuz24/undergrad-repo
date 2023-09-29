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
  Perm.clear(); // reset vector for permutations
  Perm.resize(W, '.'); // resize vector with .'s

  if (index == W) { // base case, print
    Print();
    return;  
  }


  Perm[index] = 'X'; // insert X at the index

  im.push_back(Perm); // push vector into 2D vector
  Permute(index+1); // recursive call
  Perm[index] = '.'; // replace

  for (i = 0; i < im.size(); i++) {
    for (j = 0; j < im[i].size(); j++) {
      if (im[i][j] != 'X') Non_X.push_back(i*W + j);
    }
  } 

  Choose(index); // n choose k call
}

void Matrix::Choose(int index) {

  if (E == E_ID.size()) return; // there are no more E's to enumerate

  if ((size_t)E > E_ID.size() - index) return; // second base case

  im[index][Non_X[index] % index*W] = 'E'; // im[index][j]
  E_ID.push_back(Non_X[index]); // push index*w + j onto E_ID
  Choose(index+1);

  Choose(index+1);
}

int main(int argc, char** argv) {
  Matrix* M = new Matrix;
  int i;


  if (argc == 4) { // Gather all command line arguments
    M->W = atoi(argv[1]);
    M->E = atoi(argv[2]);
    M->P = atoi(argv[3]);

    M->Permute(0); // permutation call
  }
  delete M; // clear for memory
  return 0;
}
