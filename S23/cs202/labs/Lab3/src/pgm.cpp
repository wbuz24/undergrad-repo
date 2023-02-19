#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool Pgm::Read(const std::string &file)
{
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
    ofstream ofile(file.c_str());

    try {
        if (rows == 0 || cols == 0 || file.length() == 0) {
            throw ((string) "WRITE failed");
        }
        else {
            ofile << "P2\n" << cols << " " << rows << endl; 
            ofile << "255\n";

            for (size_t i = 0; i < rows; i++) {
                for (size_t j = 0; j < cols; j++) {
                    ofile << Pixels[i][j];
                    iter++;
                    if (iter % 20 == 0) {
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
        }
    }
    catch (const string estring) {
        printf("%s\n", estring.c_str());
    }

    ofile.close();
    return 1;
};

bool Pgm::Create(size_t r, size_t c, size_t pv) {
    vector <int> p;

    try {
        if (pv > 255) {
            throw ((string) "CREATE failed");
        }
        else {
            for (size_t i = 0; i < r; i++) {
                for (size_t j = 0; j < c; j++) {
                    p.push_back(pv);
                }
                Pixels.push_back(p);
                p.clear();
            }
        }
    }
    catch (const string estring) {
        printf("%s\n", estring.c_str());
    }
    return 1;
}

bool Pgm::Clockwise() {
    size_t rows = Pixels.size(), cols = Pixels[0].size();
    vector < vector < int > > cw;

    cw.resize(cols);
    for (int i = rows - 1; i >= 0; i--) {
        for (size_t j = 0; j < cols; j++) {
            cw[j].push_back(Pixels[i][j]);
        }
    }
    Pixels.clear();
    Pixels = cw;
    return 1;

}

bool Pgm::Cclockwise() {
    size_t rows = Pixels.size(), cols = Pixels[0].size();
    vector < vector < int > > ccw;

    ccw.resize(cols);
    for (size_t i = 0; i < rows; i++) {
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

bool Pgm::Pad(size_t w, size_t pv) {


    return 1;
}

bool Pgm::Panel(size_t r, size_t c) {
    return 1;
}

bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols) {
    vector < vector < int > > crop;
    int iter = 0; 

    crop.resize(rows);
    try {
        if (rows <= Pixels.size() && cols <= Pixels[0].size()) {
            for (size_t i = r; i < (r + rows); i++) {
                for (size_t j = c; j < (c + cols); j++) {
                    crop[iter].push_back(Pixels[i][j]);
                }
                iter++;
            }
            Pixels.clear();
            Pixels = crop;
        }
    }
    catch (const string estring) {
        printf("%s\n", estring.c_str());
    }
    return 1;
}
