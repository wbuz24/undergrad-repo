/* Will Buziak
 * Lab 0
 * gold.cpp
 * cs202
 * 01/30/2023
 * search a text file and parse the inputs
*/

#include <iostream>

using namespace std;

int main() {
    char input, a = 'A';
    int ounces = 0;
    
    while (cin >> input) {
        if (input != '.' && input != '-'){
            ounces += (input - a) + 1;
        }
        else {
            ounces += 0;
        }
    }
    cout << ounces << endl;
}
