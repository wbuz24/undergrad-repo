
/* How to read a file
 * 1. Include <fstream> 
 * 2. Declare a file variable (ifstream for reading - ofstream for output
 *    and name it, typically, fin/fout
 * 3. a. Open the file connecting the variable to the 
 * 4. Do the work on the intended file
 * 5. Close the file
*/

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;


int main() {
	ifstream fin("readingCSV.csv");


	// check for failure to open
	if (!fin.is_open()) {
		cout << "File failed to open." << endl;
		return 1;
	}

	string line, first, last, temp, tempage;
	int age;
	vector <vector <string> > data_table;

	cout << "Read file by string stream:" << endl;
	while (getline(fin, line)) { // getline(stream(required), string (required), char (optional))
		vector <string> person; // read as a vector
		
		istringstream ss(line); // read using stringstream


		getline(ss, first, ',');
		person.push_back(first);

		getline(ss, last, ',');
		person.push_back(last);
		
		getline(ss, temp, ',');

		getline(ss, tempage, ' ');
		person.push_back(tempage);
		
		age = stoi(tempage);
		
		cout << first << ", " << last << ": " << age << " years old." << endl;
		data_table.push_back(person);

	}

	cout << " --------------------------" << endl;
	cout << " Read file by vectors: " << endl;
	for (int i = 0; i < data_table.size(); i++) {
		for (int j = 0; j < data_table[0].size(); j++) {
			cout << data_table[i][j] << " ";
		}
	}

	fin.close();
	
}

