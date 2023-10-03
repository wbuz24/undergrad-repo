/*
 * Will Buziak
 * CS302
 * Lab 4
 * Enumeration through permutation
 * Credit to the student Mung-Shu, although I often work with Mung-Shu, this lab was particularly influenced by my conversations with him.
 */ 

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Matrix { // class definition, I had to slightly alter from Dr. Plank's
public:
  int W;
  int E;
  char h;
  vector <int> Perm;

  void Choose(int e, int index, vector <int> Non_X, vector < vector < char > > &im); // I was only able to get this to work by passing these vectors instead of having access through the class
  void Permute(int index);
};

void Matrix::Permute(int index) { // permutation by recursion
  int i, j, tmp;

  if (index == (int) Perm.size()) {
    vector < vector < char > > m; // must declare vectors here or code breaks
    vector <int> Non_X;
    m.resize(W);
    for (i = 0; i < W; i++) m[i].resize(W,'.'); // create 2D vector

    // mapping 'x' positions to matrix
    for (j = 0; j < (int) Perm.size(); j ++) m[j][Perm[j]%W] = 'X'; // insert X's

    // finding the '.'
    for (i = 0; i < (int) W; i++) {
      for (j = 0; j < (int) W; j++)	{
        if (m[i][j] == '.') {
          Non_X.push_back((i*W+j));
        }
      } 
    }
    // enumerate the matrix with d.size possible positions for 'e'
    Choose(E, 0, Non_X, m);
    return;
  }

  // recursive call
  for (i = index; i < (int) Perm.size(); i ++) {
    tmp = Perm[i];
    Perm[i] = Perm[index];
    Perm[index] = tmp;

    Permute(index + 1 );

    tmp = Perm[i];
    Perm[i] = Perm[index];
    Perm[index] = tmp;
  }
}

void Matrix::Choose(int e, int index, vector <int> Non_X, vector <vector < char > > &im) { //recursive n choose k
  if ((int)Non_X.size() - index < e) return;
  int H;
  // print the matrix
  if (e == 0) {
    for (int i = 0; i < (int)im.size(); i++) {
      H = 0;
      for (int j = 0; j < (int)im[i].size(); j ++) {
        if (h == 'h') {
          if (im[i][j] == 'E' || im[i][j] == 'X') H += 1 << j; // shift the appropriate amount of bits to print as hex
        }
        else printf("%c", im[i][j]); // print the matrix regularly
      }
      if (h == 'h') printf("%x", H);
      printf("\n");
    }
    printf("\n");
    return;
  }

  // enumerate the positions of 'e'
  im[Non_X[index] / W][Non_X[index] % W] = 'E';
  Choose(e-1,index + 1, Non_X, im); // recursive calls
  im[Non_X[index] / W][Non_X[index] % W] = '.';
  Choose(e,index + 1, Non_X, im);
}

int main(int argc, char ** argv) {
  if (argc == 4) {
    int i;
    Matrix *M = new Matrix;

    M->W = stoi(argv[1]);
    M->E = stoi(argv[2]);
    M->h = argv[3][0];

    // vector to permute
    for (i = 0; i < M->W; i ++) M->Perm.push_back(i);

    // double recursive call
    M->Permute(0);
    delete M;
  }
  return 0;
}
