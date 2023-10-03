// Will Buziak
// CS302
// Lab 4
// Enumeration

#include <iostream>
#include <cstdio>
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
  vector < vector <int> > im;
  void Print();               /* Print the matrix defined by W, Perm and E_ID */
  void Permute(int index);    /* This is the recursive permuting method. */
  void Choose(int index);     /* This is the recursive n-choose-k method. */
};

void Matrix::Print() {
  size_t i, j;
  //int s;
  vector <int> tmp;

  for (i = 0; i < im.size(); i++) {
    for (j = 0; j < im[i].size(); j++) { 
      printf("%c", im[i][j]);
    } 
    printf("\n");
  }
  cout << endl;
  return;
}

void Matrix::Permute(int index) {
  int tmp;
  size_t i, j;

  if ((size_t) index == Perm.size()) { // base case
    
    im.resize(W);
    for (i = 0; i < W; i++) im[i].resize(W, '.'); // 2D vector map

    for (i = 0; i < Perm.size(); i++) im[i][Perm[i] % W] = 'X';

    for (i = 0; i < im.size(); i++) { // find all instances of .
      for (j = 0; j < im[i].size(); j++) if (im[i][j] == '.') Non_X.push_back(i*W + j);
    }


    Choose(0); // n choose k call
    return;
  }

  for (i = index; i < Perm.size(); i++) {
    tmp = Perm[i];
    Perm[i] = Perm[index];
    Perm[index] = tmp;

    Permute(index + 1);
    tmp = Perm[i];
    Perm[i] = Perm[index];
    Perm[index] = tmp;
  }
}

void Matrix::Choose(int index) {


  if (E > Non_X.size() - index) return; // if there is more eligible spaces than E's left to place, return

  if (E == 0) { // first base case, nothing left to place
    Print();
    return;
  }

  im[Non_X[index] / W][Non_X[index] % W] = 'E';
  Non_X.pop_back();
  E--;
  Choose(index + 1);

  im[Non_X[index] / W][Non_X[index] % W] = '.';
  Choose(index + 1);
}

int main(int argc, char** argv) {
  Matrix* M = new Matrix;
  size_t i;

  if (argc == 4) { // Gather all command line arguments
    M->W = atoi(argv[1]);
    M->E = atoi(argv[2]);
    M->P = atoi(argv[3]);
    
    M->Perm.clear(); // initialize Perm vector
    for (i = 0; i < M->W; i++) M->Perm.push_back(i);
    
    M->Permute(0); // permutation call
  }
  delete M; // clear for memory
  return 0;

}
