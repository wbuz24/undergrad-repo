// map.cpp
// Template file for the map assignment.
// (c) Stephen Marz
// 11-Jan-2023
// COSC230 - University of Tennessee [Knoxville]
#include <vector>
#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

// Make sure you at least export all five of the following from
// your .S file. To export, make them .global.
extern "C" {
    void map(double *values, uint64_t num_values, double (*func)(double left, double right), double map_value);
    double map_add(double left, double right);
    double map_sub(double left, double right);
    double map_min(double left, double right);
    double map_max(double left, double right);
}

int main() {
    vector<double> values;
    string op;
    double val;
    double map_val;

    double (*map_func)(double left, double right);

    cout << "What operation do you want to perform? ";
    cin >> op;

    // Determine the mapping function based on the input.
    // We only accept four operations:
    // + (add)
    // - (sub)
    // ^ (max)
    // v (min)
    if (op == "+") {
        map_func = map_add;
    }
    else if (op == "-") {
        map_func = map_sub;
    }
    else if (op == "^") {
        map_func = map_max;
    }
    else if (op == "v") {
        map_func = map_min;
    }
    else {
        cout << "Invalid operation.\n";
        return -1;
    }

    // The map value is passed to the "right" parameter when
    // the mapping function is called.
    cout << "Enter map value: ";
    cin >> map_val;

    cout << "Enter values (CTRL-D when done)\n";
    while (cin >> val) {
        values.push_back(val);
    }

    // We use cerr here in case your map function seg. faults. This
    // allows you to see where the crash actually happens.
    cerr << "Performing map...";
    map(&values[0], values.size(), map_func, map_val);
    cerr << "done.\n\nPrinting results.\n";

    // Go through all of the mapped values and print them
    // to the screen.
    for (const auto &c : values) {
        cout << c << '\n';
    }

    return 0;
}

