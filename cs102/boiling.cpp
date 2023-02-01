/*
 * Will Buziak
 * 000510519
 * wbuziak
 * lab 5
 * boiling.cpp
 * calculate boiling point by elevation (given city)
 */

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

// functions to calculate pressure & boiling point
double pressure(int alt) {
    double result;

    result = 29.921 * pow(1 - .0000068753 * alt, 5.2559);

    return result;
}

double boil(double pres) {
    double result;

    result = 49.161 * log(pres) + 44.932;

    return result;
}

int main(int argc, char* argv[]) {
    // initialize
    string filename, state, city, elevation, word = "";
    vector <string> cityNames;
    vector <int> elevations;
    int i = 1, nums, index;
    double press, result;


    // main code block, if proper input usage
    if (argc == 2) {
        // store filename from array of chars
        filename = argv[1];
        // open file & error check
        ifstream fin;
        fin.open(filename);

        if (!fin.is_open()) {
            cout << "File failed to open." << endl;
            return 1;
        }
        // main loop
        while (getline(fin, word, '\n')){
            istringstream ss(word);            
            // skip first line
            if (i != 1) {
                // read each "word", parse and store in vectors
                getline(ss, city, ',');
                cityNames.push_back(city);

                getline(ss, state, ',');

                getline(ss, elevation, 'n');
                nums = stoi(elevation);
                elevations.push_back(nums);
            }
            i++;
        }
        // print results
        if (fin.is_open()) {
            cout << "Boiling Point at Altitude Calculator" << endl;
            for (int j = 0; j < cityNames.size(); j++) {
                cout << j + 1<< ": " << cityNames[j] << endl;
            }
            cout << "Enter city number: ";
            cin >> index;

            // call functions
            press = pressure(elevations[index - 1]);
            result = boil(press);

            cout << fixed << setprecision(3) << "The boiling point at " << cityNames[index - 1] 
                << " is " << result << " degrees Fahrenheit." << endl;


        }fin.close();       
    }

    else {
        cout << "usage: ./boiling filename" << endl;
        return 0;
    }
}
