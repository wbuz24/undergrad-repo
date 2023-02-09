/* Will Buziak
 * cs202
 * pgminfo.cpp
 * lab 2
 * read a pgm file and print the rows, columns, pixel # & average pixels
 */ 

#include <iostream>
#include <vector>
using namespace std;

int main() {
    string p2;
    bool os = 1;
    int pixel = 0, col, row, curr_val, two55;
    double average; 

    cin >> p2;

    if (p2 != "P2") { // read and check P2 as starting word
        os = 0;
        cerr << ("Bad PGM file -- first word is not P2") << endl;
        return 0;
    }

    cin >> col;

    if (cin.fail() || col < 0) { // read columns
        cerr << "Bad PGM file -- No column specification" << endl;
        os = 0;
        return 0;
    }

    cin >> row;

    if (cin.fail() || row < 0) {
        cerr << "Bad PGM file -- No row specification" << endl;
        os = 0;
        return 0;
    }

    cin >> two55;

    if (two55 != 255) {
        cerr << "Bad PGM file -- No 255 following the rows and columns" << endl;;
        os = 0;
        return 0;
    }


    while (os) {
        cin >> curr_val;

        if (curr_val > 255 || curr_val < 0) { // check for pixel to fall within 0-255
            cerr << "Bad PGM file -- pixel " << pixel << " is not a number between 0 and 255" << endl;
            os = 0;
            return 0;
        }
        
        if (pixel > (row * col)) { // check size of file
            cerr << "Bad PGM file -- Extra stuff after the pixels" << endl;
            os = 0;
            return 0;
        }


        if (cin.eof() && pixel == (row * col)) { // if file ends, print
            os = 0;
            average = average / pixel;
            printf("# Rows:%12d\n# Columns:%9d\n# Pixels:%10d\nAvg Pixel:%9.3f\n", row, col, pixel, average);
        }


         else { // track pixels and # of pixels
            pixel++;
            average += curr_val;
        }
    }
}
