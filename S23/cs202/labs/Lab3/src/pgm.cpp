/* Will Buziak
 * Lab 3 
 * More Fun with PGMs
 * src/pgm.cpp
 * cs202
 * Write methods declared from the header file to manipulate PGM files
 */ 

#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool Pgm::Read(const std::string &file){
    ifstream fin;
    string s;
    size_t i, j, r, c, v;

    fin.open(file.c_str());
    if (fin.fail()) return false;

    if (!(fin >> s)) return false;
    if (s != "P2") return false;
    if (!(fin >> c) || c <= 0) return false;
    if (!(fin >> r) || r <= 0) return false;
    if (!(fin >> i) || i != 255) return false;

    Pixels.resize(r);
    for (i = 0; i < r; i++) {
        Pixels[i].clear();
        for (j = 0; j < c; j++) {
            if (!(fin >> v) || v > 255) return false;
            Pixels[i].push_back(v);
        }
    }
    if (fin >> s) return false;
    fin.close();
    return true;
}

bool Pgm::Write(const std::string &file) const {
    size_t rows = Pixels.size(), cols = Pixels[0].size();
    int iter = 0;

    if (rows == 0 || cols == 0 || file.length() == 0) { // error checking for proper PGMs
        return false;
    }
    else {
        ofstream ofile(file.c_str()); // write to given output string
        ofile << "P2\n" << cols << " " << rows << endl; 
        ofile << "255\n"; // PGM header

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                ofile << Pixels[i][j]; // read each element 
                iter++;
                if (iter % 20 == 0) { // create rows of 10 elements
                    ofile << "\n";
                }
                else if ((size_t) iter == (rows * cols)) {
                    ofile << "\n"; 
                    i = rows;
                    j = cols;
                }
                else {
                    ofile << " ";
                }
            }
        }
        ofile.close();
        return true;
    }
};

bool Pgm::Create(size_t r, size_t c, size_t pv) {
    vector <int> p;

    if (pv > 255) {
        return false; // error check proper input value
    }

    else { // create a vector with the value pv in every element
        for (size_t i = 0; i < r; i++) {
            for (size_t j = 0; j < c; j++) {
                p.push_back(pv);
            }
            Pixels.push_back(p); // push the row vector into a 2D vector
            p.clear();
        }
        return true;
    }
}

bool Pgm::Clockwise() {
    size_t rows = Pixels.size(), cols = Pixels[0].size();
    vector < vector < int > > cw;

    if (rows == 0 || cols == 0) { // check for invalid PGMs
        return false;
    }
    else {
        cw.resize(cols); // resize because seg fault bad
        for (int i = rows - 1; i >= 0; i--) {
            for (size_t j = 0; j < cols; j++) {
                cw[j].push_back(Pixels[i][j]); // push each row with one element at a time starting from the bottom of Pixels
            }
        }
        Pixels.clear();
        Pixels = cw;
        return true;
    }
}

bool Pgm::Cclockwise() {
    size_t rows = Pixels.size(), cols = Pixels[0].size();
    vector < vector < int > > ccw;

    if (rows == 0 || cols == 0) {
        return false;
    }
    else {        
        ccw.resize(cols);
        for (size_t i = 0; i < rows; i++) { // start from the top and store into columns starting from bottom
            int iter = cols - 1;
            for (size_t j = 0; j < cols; j++) {
                ccw[iter].push_back(Pixels[i][j]);
                iter--;
            }
        } 
        Pixels.clear();
        Pixels = ccw;

        return 1;
    }
}

bool Pgm::Pad(size_t w, size_t pv) {
    if (pv < 256) {
        vector < vector < int > > Pad;
        Pad.resize((2 * w + Pixels.size()));
        for (size_t i = 0; i < (2 * w + Pixels.size()); i++) { // increase the size of the vector and push with pv unless within the bounds of the PGM
            for (size_t j = 0; j < (2 * w + Pixels[0].size()); j++) {
                if (i < w || j < w || i >= (w + Pixels.size()) || j >= (w + Pixels[0].size())) {
                    Pad[i].push_back(pv);
                }
                else {
                    Pad[i].push_back(Pixels[i-w][j-w]); // indices must be offset by w
                }
            }
        }

        Pixels.clear();
        Pixels = Pad;
        return true;
    }

    else {
        return false;
    }
}

bool Pgm::Panel(size_t r, size_t c) {
    if (Pixels.size() > 0 && Pixels[0].size() > 0) {
        vector < vector < int > > panel;

        panel.resize((r * Pixels.size()));
        for (size_t i = 0; i < (r * Pixels.size()); i++) { // create a r * rows : c * cols vector and use the mod operator to repeat the pgm based on indices
            for (size_t j = 0; j < (c * Pixels[0].size()); j++) {
                panel[i].push_back(Pixels[i % Pixels.size()][j % Pixels[0].size()]); 
            }        
        }  
        Pixels.clear();
        Pixels = panel;
        return true;
    }
    else {
        return false;
    }
}

bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols) {
    vector < vector < int > > crop;
    int iter = 0; 

    crop.resize(rows);
    if (rows >= Pixels.size() || cols >= Pixels[0].size()) { // error check for proper inputs
        return false; 
    }
    else if ((r + rows) >= Pixels.size() || (c + cols) >= Pixels[0].size()) {
        return false;
    }
    else {
        for (size_t i = r; i < (r + rows); i++) {
            for (size_t j = c; j < (c + cols); j++) { // only copy elements that fall within the range 
                crop[iter].push_back(Pixels[i][j]);
            }
            iter++;
        }
        Pixels.clear();
        Pixels = crop;
        return true;
    }
}
