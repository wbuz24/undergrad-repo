/*
 * Basic Reading in Files - using File Streams
 * 1. Include <fstream> header file
 * 2. Declare a file variable (ifstream: stands for input file stream. ofstream: stands for output file stream) and name it (typically fin, fout)
 * 3. Open the file connecting the variable to the actual file and failure check
 * 4. Do work on file.
 * 5. Close the file.
*/
#include <iostream>
#include <fstream>
using namespace std;

int main(){
	ifstream fin;
	int a, b, c;
	fin.open("FR1.txt");
	if (!fin.is_open()) {
		cout << "Could not open FR1.txt" << endl;
		return 1;
	}
	//fin >> a >> b >> c;

	//getline(STREAM, STRING);
	string line;
	getLine(fin, line); // this will place 3 10 15 in a string
	
	fin.close(); // .open is the link b/t my program and the file. >close de-links it

	cout << "Verifying the integers read in: " << endl;
	cout << a << " " << b << " " << c << endl;
}
