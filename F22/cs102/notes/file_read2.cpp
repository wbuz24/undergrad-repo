/* reading in an unknown amt of lines w a known column organization
 * 1. include <fstream> header
 * 2. declare a file variable (ifstream for reading - input) (ofstream for writing - output)
 *
 *
 */

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
	ifstream fin;
	int a, b, c;
	vector <vector <int>> linesVector;
	string filename = "FR2.txt";
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Could not open FR2.txt" << endl;
		return 1;

	}

	// Read in multiple lines of data
	while (fin >> a >> b >> c) {
		cout << "Verifying - you read: ";
		cout << a << " " << b << " " << c << endl;
		vector <int> triplet;
		triplet.push_back(a);
		triplet.push_back(b);
		triplet.push_back(c);
		linesVector.push_back(triplet);
	}

	for (int i = 0; i < linesVector.size(); i++) {
		for (int j = 0; j < linesVector[0].size(); j++) {
			cout << linesVector[i][j] << " ";
		}
		cout << endl;
	}

	fin.close();
}
