// triangle.cpp
// Template for the triangle assignment.
// (c) Stephen Marz
// 11-Jan-2023
// COSC230 - University of Tennessee [Knoxville]
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

struct RightTriangle {
    float s0;
    float s1;
    float hypotenuse;

    float theta0;
    float theta1;

    // Add the insertion operator so we can cout this RightTriangle structure.
    friend ostream &operator<<(ostream &out, const RightTriangle &rt) {
        ostringstream sout;

        // All angles are in radians, but we want to print them out
        // in degrees.
        float angle0 = rt.theta0 * 180.0 / M_PI;
        float angle1 = rt.theta1 * 180.0 / M_PI;

        sout << fixed << setprecision(2);
        sout << "S0: " << rt.s0 << ", S1: " << rt.s1 << ", HYP: " << rt.hypotenuse;
        sout << " Angles: (90, " << angle0 << ", " << angle1 << ")";

        // Check to see if all angles add up to 180 degrees.
        if (fabs(angle0 + angle1 - 90.0) < 0.1) {
            sout << " [VALID]";
        }
        else {
            sout << " [INVALID]";
        }

        return out << sout.str();
    }
};

// Export the make_triangle by making its label .global.
extern "C" {
    RightTriangle make_triangle(float side0, float side1);
}

int main(int argc, char *argv[]) {
    istringstream sin;
    float s0;
    float s1;

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <side0> <side1>\n";
        return -1;
    }

    sin.str(argv[1]);
    if (!(sin >> s0)) {
        cout << "Error extracting side 0\n";
        return -1;
    }
    sin.clear();
    sin.str(argv[2]);
    if (!(sin >> s1)) {
        cout << "Error extracting side 1\n";
        return -1;
    }

    // Here is where your make_triangle is invoked from your .S file.
    cout << make_triangle(s0, s1) << '\n';

    return 0;
}

