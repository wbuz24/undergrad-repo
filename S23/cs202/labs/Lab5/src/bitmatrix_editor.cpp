#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "bitmatrix.hpp"
using namespace std;

void usage()
{
  cerr << "usage: bitmatrix_editor [prompt]\n";
  cerr << endl;
  cerr << "EMPTY rows cols Sets the current matrix to a new bit-matrix whose values are all zeros." << endl;
  cerr << "READ fn         Reads a matrix from the file, and sets the current matrix to be this matrix." << endl;
  cerr << "SET row col val Sets the given element of the current matrix to the given value" << endl;
  cerr << "VAL row col     Returns the value of the given element." << endl;
  cerr << "SWAP r1 r2      Swaps the given rows of the current matrix using Swap_Rows()." << endl;
  cerr << "+= r1 r2        Sets r1 of the current matrix equal to r1+r2 using the R1_Plus_Equals_R2() method." << endl;
  cerr << "WRITE fn        Calls the Write() method to write the current matrix to the specified file." << endl;
  cerr << "PRINT [w]       Calls Print(w) -- w is zero if unspecified." << endl;
  cerr << "PGM fn pixels b Calls the PGM() method to create a PGM picture of the current matrix." << endl;
  cerr << "STORE key       Makes a copy of the current matrix and stores it into the hash table with the key." << endl;
  cerr << "RECALL key      This will set the current matrix to a copy of the bit-matrix stored in the hash table." << endl;
  cerr << "ALL key         This calls All() and prints out each key, along with the dimensions of the bit-matrix stored there." << endl;
  cerr << "SUM k1 k2       This adds the two matrices stored with the given keys and puts the sum into the current matrix." << endl;
  cerr << "PRODUCT k1 k2   This multiplies the two matrices stored with the given keys and puts the product into the current matrix." << endl;
  cerr << "SUB r1 r2 ...   This replaces the current matrix with a submatrix of the specified rows." << endl;
  cerr << "INVERT          This inverts the current matrix and replaces it with the inverse." << endl;
  cerr << "?               Prints the commands." << endl;
  cerr << "QUIT            Quits." << endl;
}
   
vector <string> StoSVec(string &s)
{
  istringstream ss;
  string t;
  vector <string> rv;

  ss.str(s);
  while (ss >> t) rv.push_back(t);
  return rv;
}

int main(int argc, char **argv)
{
  BM_Hash *ht;
  Bitmatrix *bm, *bm2, *bm3, *bm4;
  size_t i;
  int r, c, w, p, b;
  string s;
  vector <string> sv;
  istringstream ss;
  string prompt = "";
  vector <HTE> all;
  vector <int> ind;

  if (argc > 2) {
    cerr << "usage: matrix_editor [prompt]\n";
    exit(1);
  }
  if (argc == 2) prompt = argv[1];
  if (prompt.size() > 0) prompt += " ";
  bm = NULL;

  ht = new BM_Hash(10000);
  while (1) {

    cout << prompt;
    cout.flush();

    if (!getline(cin, s)) exit(0);
    sv = StoSVec(s);
    if (sv.size() > 0 && sv[0][0] != '#') {
      if (sv[0] == "EMPTY") {
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1) {
          printf("Should be: EMPTY rows cols\n");
        } else {
          try {
            bm2 = new Bitmatrix(r, c);
            if (bm != NULL) delete bm;
            bm = bm2;
          } catch (const string s) {
            printf("%s\n", s.c_str());
          }
        }
      } else if (sv[0] == "SET") {
        if (sv.size() != 4 || sscanf(sv[1].c_str(), "%d", &r) != 1 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1) {
          printf("Should be: SET r c 0|1\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else if (!bm->Set(r, c, sv[3][0])) {
          printf("Failed.\n");
        }
      } else if (sv[0] == "VAL") {
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 ||
                              sscanf(sv[2].c_str(), "%d", &c) != 1) {
          printf("Should be: VAL r c\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else {
          p = bm->Val(r, c);
          printf("%c\n", bm->Val(r, c));
        }
      } else if (sv[0] == "SWAP") {
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || 
                              sscanf(sv[2].c_str(), "%d", &c) != 1) {
          printf("Should be: SWAP r1 r2\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else if (!bm->Swap_Rows(r, c)) {
          printf("Failed\n");
        }
      } else if (sv[0] == "+=") {
        if (sv.size() != 3 || sscanf(sv[1].c_str(), "%d", &r) != 1 || 
                              sscanf(sv[2].c_str(), "%d", &c) != 1) {
          printf("Should be: += r1 r2\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else if (!bm->R1_Plus_Equals_R2(r, c)) {
          printf("Failed\n");
        }
      } else if (sv[0] == "PRINT") {
        w = 0;
        if (sv.size() > 2 || (sv.size() == 2 && sscanf(sv[1].c_str(), "%d", &w) != 1)) {
          printf("Should be: PRINT [w]\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else {
          bm->Print(w);
        }
      } else if (sv[0] == "WRITE") {
        if (sv.size() != 2) {
          printf("Should be: WRITE filename\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else if (!bm->Write(sv[1])) {
          printf("Could not open file.\n");
        }
      } else if (sv[0] == "PGM") {
        if (sv.size() != 4) {
          printf("Should be: PGM filename pixels border\n");
        } else if (sscanf(sv[2].c_str(), "%d", &p) == 0) {
          printf("Should be: PGM filename pixels border\n");
        } else if (sscanf(sv[3].c_str(), "%d", &b) == 0) {
          printf("Should be: PGM filename pixels border\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else if (!bm->PGM(sv[1], p, b)) {
          printf("Failed\n");
        }
      } else if (sv[0] == "READ") {
        if (sv.size() != 2) {
          printf("Should be: READ filename\n");
        } else {
          try {
            bm2 = new Bitmatrix(sv[1]);
            if (bm == NULL) delete bm;
            bm = bm2;
          } catch (const string s) {
            printf("%s\n", s.c_str());
          }
        }
      } else if (sv[0] == "STORE") {
        if (sv.size() != 2) {
          printf("Should be: STORE key\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else {
          bm2 = bm->Copy();
          if (!ht->Store(sv[1], bm2)) {
            printf("Failed\n");
            delete bm2;
          }
        }
      } else if (sv[0] == "RECALL") {
        if (sv.size() != 2) {
          printf("Should be: RECALL key\n");
        } else {
          bm2 = ht->Recall(sv[1]);
          if (bm2 == NULL) {
            printf("No matrix with key %s\n", sv[1].c_str());
          } else {
            if (bm != NULL) delete bm;
            bm = bm2->Copy();
          }
        }
      } else if (sv[0] == "ALL") {
        if (sv.size() != 1) {
          printf("Should be: ALL\n");
        } else {
          all = ht->All();
          for (i = 0; i < all.size(); i++) {
            printf("%-30s %3d X %3d\n", all[i].key.c_str(), all[i].bm->Rows(), all[i].bm->Cols());
          }
        }
      } else if (sv[0] == "SUM" || sv[0] == "PRODUCT") {
        if (sv.size() != 3) {
          printf("Should be: SUM key1 key2\n");
        } else {
          bm2 = ht->Recall(sv[1]);
          bm3 = ht->Recall(sv[2]);
          if (bm2 == NULL) {
            printf("No matrix %s\n", sv[1].c_str());
          } else if (bm3 == NULL) {
            printf("No matrix %s\n", sv[2].c_str());
          } else {
            bm4 = (sv[0] == "SUM") ? Sum(bm2, bm3) : Product(bm2, bm3);
            if (bm4 == NULL) {
              printf("Failed\n");
            } else {
              if (bm != NULL) delete bm;
              bm = bm4;
            }
          }
        }
      } else if (sv[0] == "SUB") {
        if (sv.size() < 2) {
          printf("Should be: SUB rows...\n");
        } else if (bm == NULL) {
          printf("No current matrix.\n");
        } else {
          ind.clear();
          for (i = 1; i < sv.size(); i++) {
            if (sscanf(sv[i].c_str(), "%d", &r) != 1) {
              printf("Bad row %s. Should be a number\n", sv[i].c_str());
              i = sv.size() + 10;
            } else {
              ind.push_back(r);
            }
          }
          if (i == sv.size()) {
            bm2 = Sub_Matrix(bm, ind);
            if (bm2 == NULL) {
              printf("Failed\n");
            } else {
              delete bm;
              bm = bm2;
            }
          }
        }
      } else if (sv[0] == "INVERT") {
        if (sv.size() != 1) {
          printf("Should be: INVERT\n");
        } else  if (bm == NULL) {
          printf("No current matrix.\n");
        } else {
          bm2 = Inverse(bm);
          if (bm2 == NULL) {
            printf("Matrix not invertible.\n");
          } else {
            delete bm;
            bm = bm2;
          }
        }
      } else if (sv[0] == "QUIT") {
        return 0;
      } else if (sv[0] == "?") {
        usage();
      } else { 
        printf("Unknown command %s\n", sv[0].c_str());
      }
    }
  }
}
