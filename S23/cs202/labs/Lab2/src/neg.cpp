/* Will Buziak
 * cs202
 * neg.cpp
 * lab 2
 * read a pgm file and print the negative
 */ 

#include <iostream>
#include <vector>
using namespace std;

int main() {
    string p2;
    bool os = 1;
    int pixel = 0, col, row, curr_val, two55, neg_val; 

    cin >> p2;

    if (p2 != "P2") { // read and check P2 as starting word
        os = 0;
        cerr << ("Bad PGM file -- first word is not P2") << endl;
        return 0;
    }

    cin >> col;

    if (cin.fail() || col < 0) { // error check columns
        cerr << "Bad PGM file -- No column specification" << endl;
        os = 0;
        return 0;
    }

    cin >> row;

    if (cin.fail() || row < 0) { // error check rows
        cerr << "Bad PGM file -- No row specification" << endl;
        os = 0;
        return 0;
    }

    cin >> two55;

    if (two55 != 255) { // error check 255
        cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;;
        os = 0;
        return 0;
    }

    cout << "P2" << endl;
    cout << col << " " << row << endl << 255 << endl;

    while (os) {
        cin >> curr_val;
        if (cin.eof()) { // check for end of file
            os = 0;
            return 0;
        }

        else if (curr_val > 255 || curr_val < 0) { // error check for pixel to fall within 0-255
            cerr << "Bad PGM file -- pixel " << pixel << " is not a number between 0 and 255" << endl;
            os = 0;
            return 0;
        }
        
        else if (pixel >= (row * col)) { // error check size of file
            cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
            os = 0;
            return 0;
        }

        else{ // print "negative" version of the current pixel
             neg_val = curr_val - 255;

             neg_val = neg_val * -1; // if statement not necessary, (0 * -1 = 0)
             pixel++;
             cout << neg_val << endl;
        }
    }
}
