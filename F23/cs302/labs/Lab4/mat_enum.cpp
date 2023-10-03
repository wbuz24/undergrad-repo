/*
 * Will Buziak
 * Lab 4
 * 09/20/2023
 * Enumeration
 */ 

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Matrix {
public:
  int W;
  int E;
  int P;                      /* This is 'x' or 'h' */
  vector <int> Perm;          /* Permutation of 0 .. (W-1), for the 'X' elements. */
  vector <int> Non_X;         /* This is the row/col id of each of the non-X elements. */
  vector <int> E_ID;          /* This is the row/col id of the E elements */
  void Print();               /* Print the matrix defined by W, Perm and E_ID */
  void Permute(int index);    /* This is the recursive permuting method. */
  void Choose(int index, int e, vector < vector <int> > im);     /* This is the recursive n-choose-k method. */
};


void Matrix::Choose(int index, int e, vector < vector <int> > im) {
  if (e > (int)Non_X.size() - index) return;

  // print the matrix
  if (e == 0) {
    int s;
    for (int i = 0; i < (int)im.size(); i++) {
      s = 0;
      for (int j = 0; j < (int)im[i].size(); j ++) {
        if (P == 'h') {
          if (im[i][j] == 'E' || im[i][j] == 'X') s += 1 << j;
        }
        else printf("%c", im[i][j]);
      }
      if (P == 'h') printf("%x", s);
      cout << endl;
    }
    cout << endl;
    return;
  }

  // enumerate the positions of 'e'
  if (e > 0) {
    im[Non_X[index] / W][Non_X[index] % W] = 'E';
    Choose(index + 1, e - 1, im);
    im[Non_X[index] / W][Non_X[index] % W] = '.';
    Choose(index + 1, e - 1, im);
  }
}

void Matrix::Permute(int index)
{
  int i, j, tmp;


  if (index == (int) Perm.size()) {

    vector < vector <int> > im;// 2D vector for mapping
    im.resize(W);
    for (i = 0; i < W; i++) im[i].resize(W,'.');

    // mapping 'x' positions to matrix
    for (j = 0; j < (int) Perm.size(); j++) im[j][Perm[j] % W] = 'X';


    // finding the '.'
    for (j = 0; j < (int) W; j++) {
      for (i = 0; i < (int) W; i++) {
        if (im[j][i] == '.') Non_X.push_back(j*W + i);
      } 
    }
    // enumerate the matrix with n choose k possible positions for 'e'
    Choose(0, E, im);
    return;
  }

  // recursive call
  for (i = index; i < (int) Perm.size(); i++){
    tmp = Perm[i];
    Perm[i] = Perm[index];
    Perm[index] = tmp;

    Permute(index + 1);

    tmp = Perm[i];
    Perm[i] = Perm[index];
    Perm[index] = tmp;
  }


}


int main(int argc, char ** argv) {
  if (argc != 4) return -1;

  int i;
  Matrix *M = new Matrix;

  M->W = stoi(argv[1]);
  M->E = stoi(argv[2]);
  M->P = atoi(argv[3]);

  // vector of 0,1,2,...w-1
  for (i = 0; i < M->W; i ++) M->Perm.push_back(i);

  // recursive call
  M->Permute(0);

  delete M;
  return 0;
}








