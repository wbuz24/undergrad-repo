/* Will Buziak
 * cs202
 * hflip.cpp
 * lab 2
 * read a pgm file and print the horizontal flip
 */ 

#include <iostream>
#include <vector>
using namespace std;

vector <int> reversePGM(vector <int> curr_col) { // return reverse of a vector
    vector <int> result;
    int i = curr_col.size() - 1;

    for (; i >= 0; i--) {
        result.push_back(curr_col[i]);
    } 

    return result;
} 

void printPGM(vector < vector < int > > hflipped, int row, int col) { // prints flipped PGM
    cout << "P2" << endl << col << " " << row << endl << 255 << endl;
    
    // print 2d vector
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << hflipped[i][j] << endl;
        }
    }
}


int main() {
    string p2;
    bool os = 1;
    int pixel = 0, col, row, curr_val, two55;
    vector < vector < int > > hflip;
    vector <int> curr_row, rev_row;


    cin >> p2;
    if (p2 != "P2") { // read and check P2 as starting word
        os = 0;
        cerr << ("Bad PGM file -- first word is not P2") << endl;
        return 0;
    }

    cin >> col;

    if (cin.fail() || col < 0) { // error check to read columns
        cerr << "Bad PGM file -- No column specification" << endl;
        os = 0;
        return 0;
    }

    cin >> row;

    if (cin.fail() || row < 0) { // error check for rows
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

    //hflip.resize(row); // resize the new picture to (row, col) elements

    while (os) {
        cin >> curr_val; // read current pixel

        if (cin.eof()) { // check for end of file
            os = 0;
            printPGM(hflip, row, col); // print PGM
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

        else { // track pixels and row/col
            curr_row.push_back(curr_val); // append vector with current pixel

            if ((pixel % (col - 1)) == 0 && pixel != 0) {
                rev_row = reversePGM(curr_row); // reverse current column
                
                hflip.push_back(rev_row); // append 2d vector with reversed column
                curr_row.clear(); // clear row vectors
                rev_row.clear();
            }
            pixel++;
        }
    }
}
