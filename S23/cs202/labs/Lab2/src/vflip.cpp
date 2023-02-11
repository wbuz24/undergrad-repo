/* Will Buziak
 * cs202
 * vflip.cpp
 * lab 2
 * read a pgm file and print the vertical flip
 */ 

#include <iostream>
#include <vector>
using namespace std;

void printPGM(vector < vector < int> > curr_vec, int row, int col) { // print vertical flip of 2d vector
    cout << "P2" << endl << col << " " << row << endl << 255 << endl;

    for (int i = row - 1; i >= 0; i--) {
        for ( int j = 0; j < col; j++) {
            cout << curr_vec[i][j] << endl;
        }
    }
}

int main() {
    string p2;
    bool os = 1;
    int pixel = 0, col, row, curr_val, two55;
    vector <int> curr_row;
    vector < vector < int > > vflip;

    cin >> p2;
    if (p2 != "P2") { // read and check P2 as starting word
        os = 0;
        cerr << ("Bad PGM file -- first word is not P2") << endl;
        return 0;
    }

    cin >> col;

    if (cin.fail() || col <= 0) { // error check to read columns
        cerr << "Bad PGM file -- No column specification" << endl;
        os = 0;
        return 0;
    }

    cin >> row;

    if (cin.fail() || row <= 0) { // error check for rows
        cerr << "Bad PGM file -- No row specification" << endl;
        os = 0;
        return 0;
    }

    cin >> two55;

    if (two55 != 255) { // error check for 255
        cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;
        os = 0;
        return 0;
    }

    while (os) {
        cin >> curr_val; // read current pixel

        if (cin.eof()) { // check for end of file
            os = 0;
            printPGM(vflip, row, col); // print PGM
            return 0;
        }

        else if (curr_val > 255 || curr_val < 0) { // error check for pixel to fall within 0-255
            cerr << "Bad PGM file -- pixel " << pixel << " is not a number between 0 and 255" << endl;
            os = 0;
            return 0;
        }

        else if (pixel > (row * col)) { // error check size of file
            cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
            os = 0;
            return 0;
        }

        else { // the magic happens here
            curr_row.push_back(curr_val); // append vector with current pixel
            pixel++;

            if ((pixel % (col)) == 0) { // if end of row
                vflip.push_back(curr_row); // append 2d vector with current row
                curr_row.clear(); // clear row vector
            }
        }
    }
}
