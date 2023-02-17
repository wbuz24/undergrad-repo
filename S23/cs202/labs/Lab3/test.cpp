#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string file;

    cout << "Enter a file: ";

    cin >> file;

    ofstream ofile(file);

    ofile << "file" << endl;
    return 0;
}
