/* using Argc & Argv (Argc - argument count) (Argv - argument values)
 * Use this to force the user to give us specific information on command line
 * when they run the program.
 * This example will force the user to give us the input file name.
 * This will look like: ./raceTimesArgs fileName
 * when they run the program
 * 1. We have previously written main as main()
 *    change this to:
 *	  int main(int argc, char **argv) OR
 *	  int main(int argc, char *argv[])
 *	  NOTE: argv is an array of c-style strings (array of chars)
 *	  needs to be translated to C++ strings
 * 2. Check to see if argc is equal to what the usage calls for 
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argx, char **argv) {
	ifstream fin;
	string last, first;
	int h, m , s;
	vector <string> name, surname;

	if (argc != 2) {
		cout << "usage: ./raceTimesArgs filename" << endl;
		return 1;
	}
	
	// Take argv[1] and set it to filename
	filename = argv[1];
	// string filename(argv[1]) -> another way to auto convert from C to C++

	fin.open("raceTimesHMS.txt");
	if (!fin.is_open()) {
		cout << "Error, raceTimesHMS.txt failed to open" << endl;
		return 1;
	}
	else {
		while (fin >> first >> last >> h >> m >> s) {
			// anything done in the while loop will occur for every line
			name.push_back(first);
			surname.push_back(last);
			cout << "You read: " << last << ", " << first << endl;
	    }

			for (int i = 0; i < surname.size(
						); i++) {
				printf("Person #%d is: %s %s\n", i, name[i], surname[i]);
			}

	
	}fin.close();
	
}
