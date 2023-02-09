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

    if (argc != 3) {
        cerr << "usage: graycard row cols" << endl;
    } 

    else {
        cout << "P2" << endl;
        row = atoi(argv[1]);
        col = atoi(argv[2]);
        row1 = row / 3;
        row_calc = (2 * row) / 3;

        if ((row % 3) != 0) {
            cerr << "rows must be a multiple of three" << endl;
            return 0;
        }

        else {
            cout << col << "\n" << row << endl;
            cout << 255 << endl;
            for (i = 0 ; i < row; i++) {
                for (j = 0 ; j < col; j++) {
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


