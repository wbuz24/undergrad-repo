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

  cout << "Printing: " << endl; 
  /*  for (j = 0; j < Perm.size(); j++) printf("%c", Perm[j]);
  cout << endl;
*/
  for (i = 0; i < im.size(); i++) {
    for (j = 0; j < im[i].size(); j++) {
      printf("%c", im[i][j]);
    }
    printf("\n");
    printf("\n");
  }
  return;
}

void Matrix::Permute (int index) {
  size_t i, j;

  //cout << "Index: " << index << endl;
  if (index == W) { // base case, print
    //Print();
    return;
  }

  Perm.clear();
  Perm.resize(W, '.'); // resize vector with .'s

  for (i = index; i < Perm.size(); i++) {
    Perm[index] = 'X'; // insert X at the index
    im.push_back(Perm);
    Permute(index+1); // recursive call
    Perm[index] = '.';
  }


  for (i = 0; i < Perm.size(); i++) {
    if (Perm[i] != 'X') Non_X.push_back(index*W + i);
  } 
  cout << "Non_x size: " << Non_X.size() << endl;

  Choose(index); // n choose k call
}

void Matrix::Choose(int index) {

  if (E == E_ID.size()) {
    return; // there are no more E's to enumerate
  }

  if (Non_X.size() == 0) { // no more spots to choose from
    Print();
    return; // second base case
  }
  Perm[Non_X[index] % index*W] = 'E';
  Non_X.pop_back();
  cout << "Non_x pop: " << Non_X.size() << endl;
  im.push_back(Perm);
  E_ID.push_back(Non_X[index] % index*W); // push index*w + j onto E_ID
  Choose(index+1);

}

int main(int argc, char** argv) {
  Matrix* M = new Matrix;
  int i;


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
