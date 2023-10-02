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
  /*for (i = 0; i < Perm.size(); i++) printf("%c", Perm[i]); 
  cout << endl;
*/
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
  vector <int> tmp;
  //size_t i;

    cout << index << endl;
  if ((size_t) index == Perm.size()) {
    Print();
    return;
  }


  //for (i = index; i < Perm.size(); i++) {
    tmp = Perm;
    Perm[index] = 'X';
    im.push_back(Perm);
    Perm = tmp;

    Permute(index + 1);
    tmp = Perm;
    Perm[index] = '.';
    im.push_back(Perm);
    Perm = tmp;
  //}

  Choose(index);

}

void Matrix::Choose(int index) {
  (void) index;
  return;
}

int main(int argc, char** argv) {
  Matrix* M = new Matrix;


  if (argc == 4) { // Gather all command line arguments
    M->W = atoi(argv[1]);
    M->E = atoi(argv[2]);
    M->P = atoi(argv[3]);
    M->Perm.resize(M->W, '.');
    M->Permute(0); // permutation call
  }
  delete M; // clear for memory
  return 0;

}
