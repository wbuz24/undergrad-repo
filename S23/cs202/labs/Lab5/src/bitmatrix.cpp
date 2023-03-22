/* Will Buziak
 * Lab 5
 * Bitmatrix.cpp
 * implement the bitmatrix methods, a hash table and a PGM
 */ 

#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <bitset>
#include "bitmatrix.hpp"
using namespace std;

unsigned int djb_hash(const string &s) { // djb hash function from Dr. Plank's class notes
    size_t i;
    unsigned int h;

    h = 5381;

    for (i = 0; i < s.size(); i++) {
        h = (h << 5) + h + s[i];
    }
    return h;
}



Bitmatrix::Bitmatrix(int rows, int cols)
{   // constructor passing rows and columns  
    int i = 0, j = 0;
    string str = "";

    if (rows <= 0) throw ((string) "Bad rows"); 
    if (cols <= 0) throw ((string) "Bad cols");

    for (; i < cols; i++) { // create an empty string of zeros
        str += "0";
    }

    for (; j < rows; j++) { // create a matrix of rows size with the string
        M.push_back(str);
    }
}

Bitmatrix::Bitmatrix(const string &fn)
{ // constructor passing a file name
    ifstream fin;
    fin.open(fn.c_str());
    string line, str = "";

    if (fin.fail()) throw ((string) "Can't open file");
    while (getline(fin, line)) { // read each line of the file
        if (!line.empty()) {
            for (size_t i = 0; i < line.size(); i++) { // check each character to be whitespace, 0 or 1
                if (line[i] != '0'&& line[i] != '1' && isspace(line[i]) == 0){
                    throw ((string) "Bad file format");
                    break;
                }
            }

            for (size_t i = 0; i < line.size(); i++) {
                if (!isspace(line[i])) { // if line[i] is not a string
                    str += line[i];
                }
            }
            M.push_back(str); // push vector with the string
            str = "";
        }
    }
    fin.close();
}

Bitmatrix *Bitmatrix::Copy() const
{
    Bitmatrix *copy = new Bitmatrix(M.size(), M[0].size()); // construct a new empty matrix
    copy->M = this->M;
    return copy;
}

bool Bitmatrix::Write(const string &fn) const
{
    ofstream ofile;
    ofile.open(fn.c_str());
    bool ret = 1;

    for (size_t i = 0; i < M.size(); i++) {
        for (size_t j = 0; j < M[i].size(); j++) { // return zero if not 0 or 1
            if (M[i][j] != '0' && M[i][j] != '1' && M[i][j] != 0 && M[i][j] != 1) {
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
    size_t i = 0, k = 0, j;
    if (w <= 0) { // print with no spaces or empty lines
        for (; k < M.size(); k++) {
            cout << M[k] << endl;
        }
    }
    else { // print according to format
        for (; i < M.size(); i++) {
            for (j = 0; j < M[i].size(); j++) {
                cout << M[i][j];
                if ((j + 1) % w == 0 && j != (M[i].size() - 1)) cout << " ";

            }
            if ((i + 1) % w == 0 && i != (M.size() - 1)) cout << endl;

            cout << endl;
        } 
    }
}
bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
    ofstream ofile;
    ofile.open(fn.c_str());
    int rows, cols, curr_pix, i, j , k, b;

    if (M.size() == 0 || M[0].size() == 0) return false;
    if (p <= 0) return false;
    //if ((border * M.size()) > (255 - M.size() * p) || (border * M[0].size()) > (255 - M[0].size() * p)) return false; 
    if (border < 0) border = 0;

    cols = M[0].size() * p + border * (M[0].size() + 1);
    rows = M.size() * p + border * (M.size() + 1);
    ofile << "P2\n" << cols << " " << rows << "\n" << "255\n"; // PGM header

    for (j = 0; j < border; j++) { // produce a border on the top
        for (k = 0; k < (int)(border * (M[0].size() + 1) + (p * M[0].size())); k++) {
            ofile << "0 ";
        }
        ofile << endl;
    }
    ofile << endl;

    for (i = 0; i < (int) M.size(); i++) { // loop through bitmatrix vector
        for (j = 0; j < p; j++) { // repeat for p rows
            for (k = 0; k < (int) M[0].size(); k++) { // produce a row
                //ofile << endl;
                for (b = 0; b < border; b++) { // margin border
                    ofile << "0 ";

                }
                for (b = 0; b < p; b++) { // print M[i][kk] p times
                    if (M[i][k] == '1') curr_pix = 100; // set value
                    else curr_pix = 255;
                    ofile << curr_pix << " ";
                }
                if (k == (2 * p - 1)) ofile << endl;
                if (k == (int)M[0].size() - 1) {
                    for (b = 0; b < border; b++) { // border
                        ofile << "0 ";
                    }
                    ofile << endl;
                }
                
            } 
            //if (i == p - 1) ofile << endl; 
        }
        for (int z = 0; z < border; z++) { // bottom border
            for (j = 0; j < (int)(border * (M[0].size() + 1) + (p * M[0].size())); j++) {
                ofile << "0 ";
            }
            ofile << endl;
        }

    }
    /*
       for (i = 0; i < border; i++) { // bottom border
       for (j = 0; j < (int)(border * (M[0].size() + 1) + (p * M[0].size())); j++) {
       ofile << "0 ";
       } 
       ofile << endl;
       }*/
    ofile.close();
    return true;
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
    if (val == 0) val = '0';
    if (val == 1) val = '1';
    if (val != '0' && val != '1') return false;  
    if (row < 0 || col < 0) return false;
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
    string str = "";
    int re;

    if (r1 >= (int) M.size() || r2 >= (int) M.size()) return false;
    else {
        for (int i = 0; i < (int) M[r1].size(); i++) { // add two binary strings
            re = 0;
            if (M[r1][i] == '1') re++;
            if (M[r2][i] == '1') re++;
            if (re == 2 || re == 0) str += '0';
            else str += '1';
        }

        M[r1] = str;

        return true;        
    }
}


Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
    //    Bitmatrix *result = new Bitmatrix;
    if (a1->Rows() != a2->Rows()) return NULL;
    else {
        Bitmatrix *result = new Bitmatrix(a1->Rows(), a1->Cols());
        int re;
        for (int i = 0; i < a1->Rows(); i++) {
            for (int j = 0; j < a1->Cols(); j++) {
                re = 0;
                if (a1->Val(i, j) == '1') re++;
                if (a2->Val(i, j) == '1') re++;
                if (re % 2 == 0) result->Set(i, j, '0');
                else result->Set(i, j, '1');
            }
        }
        return result;
    }
}

Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
    if (a1->Cols() != a2->Rows()) return NULL;
    Bitmatrix *result = new Bitmatrix(a1->Rows(), a2->Cols());
    int a, b, sum;
    for (int i = 0; i < a1->Rows(); i++) {
        for (int j = 0; j < a2->Cols(); j++) {
            sum = 0;
            for (int k = 0; k < a2->Rows(); k++) {
                a = 0; 
                b = 0;
                if (a1->Val(i, k) == '1') a = 1; // test if each value is 1 or 0
                if (a2->Val(k, j) == '1') b = 1;
                sum += a * b; // sum of products
            }
            result->Set(i, j, sum % 2); // set the result
        }
    }
    return result;
}

Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
    if (rows.size() == 0) return NULL;
    for (size_t i = 0; i < rows.size(); i++) {
        if (rows[i] > a1->Rows()) return NULL;
    }

    Bitmatrix *result = new Bitmatrix(rows.size(), a1->Cols());

    for (size_t i = 0; i < rows.size(); i++) {
        for (int j = 0; j < a1->Cols(); j++) {
            result->Set(i, j, a1->Val(rows[i], j)); // create a new bitmatrix consisting only of the specified rows
        } 
    }
    return result;
}

Bitmatrix *Inverse(const Bitmatrix *m)
{
    if (m->Rows() != m->Cols()) return NULL;
    Bitmatrix *Inv = new Bitmatrix(m->Rows(), m->Cols());
    Bitmatrix *copy = m->Copy();
    bool s = 1;

    for (int i = 0; i < m->Rows(); i++)  Inv->Set(i, i, '1'); // create an identity matrix
    for (int i = 0; i < m->Rows(); i++) {
        if (copy->Val(i, i) != '1') {
            for (int j = i + 1; j < m->Rows(); j++) {
                if (copy->Val(j, i) == '1') { // set diagonals
                    Inv->Swap_Rows(i, j);
                    copy->Swap_Rows(i, j);
                    s = 0;
                    break;
                }
            }
            if (s) return NULL;
	}

        for (int j = i + 1; j < m->Rows(); j++) { // upper triangular matrix 
            if (copy->Val(j, i) == '1') {
                Inv->R1_Plus_Equals_R2(j, i);
                copy->R1_Plus_Equals_R2(j, i);
		s = 0;
            }
        }
	if (s) return NULL;
      
    }

    for (int i = m->Rows() - 2; i >= 0; i--) { // lower triangular matrix
        for (int j = i + 1; j < m->Rows(); j++) {
            if (copy->Val(i, j) == '1') {
                Inv->R1_Plus_Equals_R2(i, j);
                copy->R1_Plus_Equals_R2(i, j);
            }
        }
    }
    return Inv;
}

BM_Hash::BM_Hash(int size)
{
    if (size <= 0) throw ((string) "Bad size");
    else Table.resize(size); // create a hash table
}

bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
    // djb_hash() and separate chaining as conflict resolution
    //if (Table.size() == 0) return false;
    unsigned int hash = djb_hash(key) % Table.size(); // find hash index
    if (Table[hash].size() != 0 ) { // see if hash index has any contents
        for (size_t i = 0; i < Table[hash].size(); i++) { // check if key is already stored
            if (Table[hash][i].key.compare(key) == 0) return false;
        }
    }
    // store entry in hash table
    HTE *entry = new HTE; 
    entry->key = key;
    entry->bm = bm;
    Table[hash].push_back(*entry);
    return true;
}

Bitmatrix *BM_Hash::Recall(const string &key) const
{
    //if (Table.size() == 0) return NULL; // table has not been set up yet;
    unsigned int hash = djb_hash(key) % Table.size();
    if (Table[hash].size() == 0) return NULL; // no entries at hash index
    for (size_t i = 0; i < Table[hash].size(); i++) { // search for key
        if (Table[hash][i].key.compare(key) == 0) return Table[hash][i].bm;
    }
    return NULL; // cannot find the bitmatrix
}

vector <HTE> BM_Hash::All() const
{
    vector <HTE> rv;
    for (size_t i = 0; i < Table.size(); i++) {
        if (Table[i].size() != 0) {
            for (size_t j = 0; j < Table[i].size(); j++) rv.push_back(Table[i][j]);
        } 
    }
    return rv;
}
