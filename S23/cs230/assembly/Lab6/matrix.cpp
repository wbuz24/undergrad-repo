// Will Buziak
// matrix extra credit assignment
// cpp file implementing Matrix class methods

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

// 1x4 vector
struct Vector {
  float v[4] = {.75, .5, .25, 1};
};

// 4x4 matrix
struct Matrix {
  float m[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
}

extern "C" {
  Matrix scale(const Matrix &orig, float sc, float sy, float sz);
  Matrix translate (const Matrix &orig, float tx, float ty, float tz);
  Vector mul(const Matrix &m, const Vector &v);
  Vector norm(const Vector &v);
}

int main() {
  string op;
  float x, y, z;

  Matrix m;
  Vector v;
  
  while (true) {
    cout << "> ";
    cin >> op;

    if (op == "scale") {
      m = scale(m, x, y, z);
    }

  }

}
