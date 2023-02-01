/* Will Buziak
 * checkerboard.cpp
 * Lab 1 part 1
 * CS202
 * 01-26-2023
 * Read cin and print a checkerboard of characters that fits the specs from cin, including a WxW matrix 
 *
 */

#include <iostream>
using namespace std;


int main() {
    //initialize
    int row, col, cycle_size, width;
    char start_char, curr_char;

    cin >> row >> col >> start_char >> cycle_size >> width;
    // read from cin, no output text yet

    for (int i = 0; i < row; i++) { // row loop
        for ( int r = 0; r < width; r++) { // reproduces rows 'width' # of times  
            for (int j = 0; j < col; j++) { // column loop
                for ( int k = 0; k < width; k++) { // reproduces char width times making a square matrix
                    curr_char = start_char + (i + j) % cycle_size; // calculates current char
                    cout << curr_char; // prints current character
                }
            }
            cout << endl;
        }
    }
}
