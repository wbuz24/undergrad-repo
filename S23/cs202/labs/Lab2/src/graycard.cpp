/* Will Buziak
 * Lab 2 part 2
 * Graycard.cpp
 * 02/09/2023
 * read two command line arguments and generate a gray card
 */
#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char** argv) {
    int row, row1, col, i, j, num = 0, row_calc;

    col = atoi(argv[2]); // read row and column from command line
    row = atoi(argv[1]);


    if (argc != 3 || row <= 0 || col <= 0) { // error check proper inputs
        cerr << "usage: graycard rows cols" << endl;
    } 

    else {
        row1 = row / 3;
        row_calc = (2 * row) / 3;

        if ((row % 3) != 0) { // error check proper row #
            cerr << "rows must be a multiple of three" << endl;
            return 0;
        }

        else { // print PGM grey card
            cout << "P2" << endl;
            cout << col << "\n" << row << endl;
            cout << 255 << endl;
            for (i = 0 ; i < row; i++) { // row loop
                for (j = 0 ; j < col; j++) { // column loop
                    if (i < row1) {
                        cout << 0;
                    }

                    else if (i >= row1 && i < row_calc) {
                        cout << 209;
                    }

                    else {
                        cout << 255;
                    }

                    cout << endl;
                }
            }
        }

    }
}


