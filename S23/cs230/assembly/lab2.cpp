// rand.cpp
// Template for the random assignment.
// (c) Stephen Marz
// 11-Jan-2023
// COSC230 - University of Tennessee [Knoxville]
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <sstream>
#include <utility>
using namespace std;

// Export get_rand using .global from your .S file.
extern "C" {
    int64_t get_rand(int64_t min_val, int64_t max_val);
}

int main(int argc, char *argv[]) {
    int64_t mn;
    int64_t mx;
    int num_randoms;
    istringstream sin;

    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <num randoms> <min_val> <max_val>\n";
        return -1;
    }

    sin.str(argv[1]);
    if (!(sin >> num_randoms)) {
        cout << "Invalid number of randoms given.\n";
        return -1;
    }
    sin.clear();
    sin.str(argv[2]);
    if (!(sin >> mn)) {
        cout << "Invalid minimum value.\n";
        return -1;
    }
    sin.clear();
    sin.str(argv[3]);
    if (!(sin >> mx)) {
        cout << "Invalid maximum value.\n";
        return -1;
    }
    // Make sure that the minimum is always smaller than
    // the maximum.
    if (mn > mx) {
        swap(mn, mx);
    }
    // We can put anything here, but to ensure the graders
    // get the same numbers as you, we use a deterministic value.
    srand(mx - mn);

    // Your get_rand function is invoked for every random number requested.
    for (int i = 0;i < num_randoms;i++) {
        int64_t r = get_rand(mn, mx);
        cout << r << '\n';
    }
    return 0;
}
