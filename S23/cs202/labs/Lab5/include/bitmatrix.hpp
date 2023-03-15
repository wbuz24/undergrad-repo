#pragma once

#include <string>
#include <vector>

class Bitmatrix {
  public:

    /* Bitmatrix creation constructors / methods. */

    Bitmatrix(int rows, int cols);           /* Create an empty bitmatrix with the given size. 
                                                Throw the string "Bad rows" if (rows <= 0).
                                                Throw the string "Bad cols" if (cols <= 0). */

    Bitmatrix(const std::string &fn);        /* Read the bitmatrix from a file.  
                                               Throw "Can't open file" if you can't open the file.
                                               Throw "Bad file format" if you can't read the file. */

    Bitmatrix *Copy() const;                 /* Create a new bitmatrix using new, which is a copy of the 
                                                caller's bitmatrix, and return a pointer to it. */

    /* Bitmatrix storage methods. */

    bool Write(const std::string &fn) const; /* Write to a file.  You will print one line per row of the 
                                                bitmatrix, and each line is only composed of 0's and 1's.
                                                Return true if successful and false if not. */

    void Print(size_t w) const;               /* Print on standard output.  You will print one line per row
                                                of the bitmatrix.  Each line is composed of 0's and 1's, and
                                                there will be a space after every w characters (don't put a
                                                space at the end if the number of columns is a multiple of w).
                                                Also put a blank line after every w rows (except the last,
                                                if the number of rows is a multiple of w). */
                           
    bool PGM(const std::string &fn,          /* Create a PGM file. Each entry is a p by p square, */
             int p,                          /* which is white for zero and 100 for gray.  If border is */ 
             int border) const;              /* greater than zero, then there should be a black border
                                                of that many pixels separating each square and around 
                                                the whole matrix.  Return true if successful and false 
                                                if not. */

    /* Bitmatrix access methods. */

    int Rows() const;                            /* Return the number of rows */
    int Cols() const;                            /* Return the number of columns */
    char Val(int row, int col) const;            /* Return the specified element ('0' or '1').
                                                    Return 'x' if row or col is bad. */

    /* Bitmatrix modification methods. */

    bool Set(int row, int col, char val);        /* Set the specified element to val.
                                                    Val must be 0, 1, '0' or '1'.
                                                    If val is 0 or 1, store '0'/'1' in the matrix.
                                                    Return true if successful and false if not. */
    bool Swap_Rows(int r1, int r2);              /* Swap these rows.  Return true 
                                                    if successful and false if not. */
    bool R1_Plus_Equals_R2(int r1, int r2);      /* Set the row r1 to the sum of row r1 and r2. 
                                                    Return true if successful and false if not. */

  protected:
    std::vector <std::string> M;                 /* The matrix.  Elements are '0' or '1'. */
};

/* These four procedures will allocate and create a new bitmatrix from other bitmatrices.
   They must be written using the methods of the Bitmatrix class above. They should return NULL
   if they are unsuccessful. */

Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2);
Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2);
Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const std::vector <int> &rows);
Bitmatrix *Inverse(const Bitmatrix *m);

/* We are also going to support storage and retrieval of bitmatrices through a hash table. */

class HTE {                              /* This is a "hash table entry".  Our hash table stores */
  public:                                /* vectors of pointers to these, using separate chaining. */
    std::string key;
    Bitmatrix *bm;
};

class BM_Hash {                                           /* This is our bitmatrix hash table. */
  public:
    BM_Hash(int size);                                    /* You specify the table size in the constructor. 
                                                             Throw the string "Bad size" if (size <= 0). */
    bool Store(const std::string &key, Bitmatrix *bm);    /* Store a bitmatrix with the given key. 
                                                             Return true if successful and false if not. 
                                                             Return false if the key is already there. */
    Bitmatrix *Recall(const std::string &key) const;      /* Retrieve a bitmatrix with the given key. 
                                                             Return NULL if unsuccessful. */
    std::vector <HTE> All() const;                        /* Return all of the hash table entries. */
  protected:
    std::vector < std::vector <HTE> > Table;              /* This is the hash table. */
};
