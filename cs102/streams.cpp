/* string streams notes
 *
 * string steam class is used for insertion and extraction of 
 * data to/from strings. It acts as a stream for the string object.
 *
 * Similar to cin/cout, fin/fout.
 * the stream is just from a different source.
 * source for cin/cout - console
 * source for fin/fout - file
 * source for sin/sout - string

 getline() on HMS text file with a string line

 Program will take 3 arguments on the command line:
 1. Program name (the executable)
 2. Input file (racetimeHMS.txt)
 3. Output file (a new file, but we give it a name here)


*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;




string formatTime(int h, int m, int s) {
    ostringstream sout; // creats the string format using sout

    sout << setfill('0') << setw(2) <<  h << ":" << setw(2) <<  m << ":" << setw(2) <<  s;

    return sout.str(); // creates a string

}

string calcPace (int h, int m, int s) {
	ostringstream sout;
	int ts;
	double marathon_dist;

	ts = m*60 + h*3600;

	double pace_in_s = (ts / marathon_dist);

	int pmin = (int) (pace_in_s / 60);
	int ps = (((int) (pace_in_s +.5)) % 60);
	
	sout << setfill('0') << setw(2) << pmin << ":" << setw(2) << ps;
	return sout.str();
}

int main (int argc, char** argv) {
    ifstream fin;
    ofstream fout;
    string fname,lname, time, pace, ifile_name, ofile_name;
    int hrs, min, sec;

    if (argc!=3) {
        cerr << "usage: ./rt3 input_file_name.txt output_file_name.txt\n";
        return 1;
    }

    
    /* Connecting the file input stream with the file
     * and making sure it opens correctly */


    fin.open(ifile_name);
    if (!fin.is_open()) {
        cerr << "Could not open file. Check permissions or filename .\n";
        return 1;
    }
	
	fout.open(ofile_name);
	while (fin >> fname >> lname >> hrs >> min >> sec) {
		fout << fname << " " << lname << endl;
		
		time = formatTime(hrs, min, sec);
		fout << " Marathon Time: " << time << endl;
		fout << " Average Pace: " << calcPace(hrs, min, sec) << endl;
	}
}
