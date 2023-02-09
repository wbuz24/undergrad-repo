#include <sstream>

int main (int argc, char ** argv) {
	ifstream fin;
	ofstream fout;
	string fname,lname, time, pace, ifile_name, ofile_name;
	int hrs, min, s;

	if (argc!=3) {
		cerr << "usage: ./rt3 ifile_name.txt ofile_name.txt\n";
		return 1;
	}

	input_file = argc[1];
	output_file = argv[2];

	/* Connecting the file input stream with the file
	 * and making sure it opens correctly */


	fin.open(inputFile);
	if (!fin.is_open()) {
		cerr << "Could not open file. Check permissions or filename .\n";
		return 1;
	}

	/* Create a output file to place the newly formatted data */


}
