#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include "bitmatrix.hpp"
using namespace std;

Bitmatrix::Bitmatrix(int rows, int cols)
{  
    int i = 0, j = 0;
    string str = "";

    if (rows <= 0) throw ((string) "Bad rows"); 
    if (cols <= 0) throw ((string) "Bad cols");

    for (; i < cols; i++) {
        str += "0";
    }

    for (; j < rows; j++) {
        M.push_back(str);
    }

}

Bitmatrix::Bitmatrix(const string &fn)
{
    ifstream fin;
    fin.open(fn.c_str());
    string line, str = "";

    if (fin.fail()) throw ((string) "Can't open file");
    while (getline(fin, line)) { // read each line of the file
        
        for (size_t i = 0; i < line.size(); i++) { // check each character to be whitespace, 0 or 1
            if (line[i] != '0'&& line[i] != '1' && isspace(line[i]) == 0){
                throw ((string) "Bad file format");
                break;
            }
        }

        for (size_t i = 0; i < line.size(); i++) {
            if (isspace(line[i]) == 0 && isblank(line[i]) == 0) { // if line[i] is not a string
                str += line[i];
            }
        }
        M.push_back(str); // push vector with the string
        str = "";
    }

    fin.close();
}

Bitmatrix *Bitmatrix::Copy() const
{
    Bitmatrix *copy = new Bitmatrix(M.size(), M[0].size()); // construct a new empty matrix
    *copy = *this; // copy matrix
    return copy;
}

bool Bitmatrix::Write(const string &fn) const
{
    ofstream ofile;
    ofile.open(fn.c_str());
    bool ret = 1;
    
    for (size_t i = 0; i < M.size(); i++) {
        for (size_t j = 0; j < M[i].size(); j++) { // return zero if not 0 or 1
            if (M[i][j] != '0' && M[i][j] != '1') {
                j = M[i].size();
                i = M.size();
                ret = 0;
            }
        }
        ofile << M[i] << endl; // write each line of the matrix
    }

    ofile.close();

    return ret;
}

void Bitmatrix::Print(size_t w) const 
{
    if (w <= 0) {
        for (size_t k = 0; k < M.size(); k++) {
            cout << M[k] << endl;
        }
    }
    else {
        for (size_t i = 0; i < M.size(); i++) {
            for (size_t j = 0; j < M[i].size(); j++) {
                cout << M[i][j];
                if ((j + 1) % w == 0) cout << " ";

            }
            if ((i + 1) % w == 0) cout << endl;

            cout << endl;
        } 
    }
}
bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
    (void) fn;
    (void) p;
    (void) border;
    return false;
}

int Bitmatrix::Rows() const
{
    return M.size();
}

int Bitmatrix::Cols() const
{
    return M[0].size();
}

char Bitmatrix::Val(int row, int col) const
{
    if (row >= (int) M.size() || col >= (int) M[0].size()) return 'x';
    if (M[row][col] == '0' || M[row][col] == '1') return M[row][col];
    else return 'x';
}

bool Bitmatrix::Set(int row, int col, char val)
{
    if (val != '0' && val != '1') return false;  
    else if (row >= (int) M.size() || col >= (int) M[0].size()) return false;

    else {
        M[row][col] = val;
        return true;
    }
}

bool Bitmatrix::Swap_Rows(int r1, int r2)
{
    if (r1 >= (int) M.size() || r2 >= (int) M.size()) return false; 
    else {
        string sub;
        sub = M[r1];
        M[r1] = M[r2];
        M[r2] = sub;

        return true;
    }
}

bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
    (void) r1;
    (void) r2;
    return false;
}


Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
    (void) a1;
    (void) a2;
    return NULL;
}

Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
    (void) a1;
    (void) a2;
    return NULL;
}

Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
    (void) a1;
    (void) rows;
    return NULL;
}

Bitmatrix *Inverse(const Bitmatrix *m)
{
    (void) m;
    return NULL;
}



BM_Hash::BM_Hash(int size)
{
    (void) size;
}

bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
    (void) key;
    (void) bm;
    return false;
}

Bitmatrix *BM_Hash::Recall(const string &key) const
{
    (void) key;
    return NULL;
}

vector <HTE> BM_Hash::All() const
{
    vector <HTE> rv;

    return rv;
}
