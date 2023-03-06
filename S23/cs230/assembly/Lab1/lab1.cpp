// first_asm_from_cpp.cpp
// Template for your first assembly program.
// (c) Stephen Marz
// 11-Jan-2023
// COSC230 - University of Tennessee [Knoxville]

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>
using namespace std;

// Import sum_prod from your .S file. This file will not compile unless
// you at least have the label sum_prod exported as a .global symbol.
extern "C" {
    int sum_prod(const int *values, uint64_t num_values, int &product);
}

int main() {
    vector<int> values;
    int product;
    int sum;

    // v will be the integer values from the user
    int v;

    // CTRL-D is the EOF key, meaning hold the control key and press d.
    cout << "Enter values as integers (CTRL-D to stop):\n";
    while (cin >> v) {
        values.push_back(v);
    }

    // There is nothing to be done if there were no values entered.
    if (values.size() == 0) {
        cout << "No values entered.\n";
        return -1;
    }

    // This is where your sum_prod is invoked. You can change this around
    // to debug, but remember you only submit your .S file. You are graded
    // on how your .S file interacts with this pristine template.
    sum = sum_prod(&values[0], values.size(), product);

    cout << "Sum     = " << sum << '\n';
    cout << "Product = " << product << '\n';

    return 0;
}

