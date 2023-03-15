#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.hpp"
using namespace std;

Bitmatrix::Bitmatrix(int rows, int cols)
{
  if (rows <= 0) throw ((string) "Bad rows"); 
  if (cols <= 0) throw ((string) "Bad cols");
}
           
Bitmatrix::Bitmatrix(const string &fn)
{
  (void) fn;
}
        
Bitmatrix *Bitmatrix::Copy() const
{
  return NULL;
}
                 
bool Bitmatrix::Write(const string &fn) const
{
  (void) fn;
  return false;
}
 
void Bitmatrix::Print(size_t w) const
{
  (void) w;
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
  return -1;
}
                            
int Bitmatrix::Cols() const
{
  return -1;
}
                            
char Bitmatrix::Val(int row, int col) const
{
  (void) row;
  (void) col;
  return 'x';
}
            
bool Bitmatrix::Set(int row, int col, char val)
{
  (void) row;
  (void) col;
  (void) val;
  return false;
}
        
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
  (void) r1;
  (void) r2;
  return false;
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
