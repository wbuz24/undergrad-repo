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
    ofstream ofile;
    ofile.open("file");
    ofile << "P2\n" << 
    return 0;
};

bool Pgm::Create(size_t r, size_t c, size_t pv) {
    return 0;
}

bool Pgm::Clockwise() {
    return 0;
}

bool Pgm::Cclockwise() {
    return 0;
}

bool Pgm::Pad(size_t w, size_t pv) {
    return 0;
}

bool Pgm::Panel(size_t r, size_t c) {
    return 0;
}

bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols) {
    return 0;
}
