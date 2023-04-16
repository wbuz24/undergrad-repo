/* Will Buziak
 * cs202
 * Lab 9 Part A
 * enum.cpp
 * enumerate all strings of a given length on standard output in sorted order
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void do_enumeration(string &s, int index, int n_ones, int zeros)
{
    if (zeros > 0) { // fill zeroes
        s[index] = '0';
        do_enumeration(s, index + 1, n_ones, zeros - 1);
    }
    if (n_ones > 0) { // fill ones
        s[index] = '1';
        do_enumeration(s, index + 1, n_ones - 1, zeros);
    }

    if (n_ones + zeros == 0) { // base case 
        if (n_ones == 0) {
        printf("%s\n", s.c_str());
        }
    }
};

int main(int argc, char** argv) 
{
    string s = "";
    int i, ones = stoi(argv[2]);
    
    (void) argc;
    for (i = 0; i < stoi(argv[1]); i++) s += '-'; // string of dashes (uninitialized)

    do_enumeration(s, 0, ones, stoi(argv[1]) - ones); // recursive call

    return 1;
}
