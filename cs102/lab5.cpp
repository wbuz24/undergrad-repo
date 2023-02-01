/*
 * Will Buziak
 * Lab 5
 * 000510519
 * wbuziak
 * speeding ticket calculator
 * read a given file name & output fine, citation #, and date in
 * a given date range input from the console

*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;

int main() {

	// initialize variables
	string months[12] = {"Jan", "Feb", "Mar", "Apr", "May",
		"Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; // constant string array
	const double imul = 5.2341, hmul = 9.4826, rmul = 17.1544, namul = 12.8334; // constant doubles
	double result; //dummy vars for stored dates
	int fine, speed, limit, smonth, sday, syr, emonth, eday, eyr, month, day, year, nsdate, nedate, ndate;
	char type; // type of road
	string citation, cmon; // ticket id # & temp var for 3-char month

	// prompt for a ticket file
	string file;
	cout << "Enter a ticket file: ";
	cin >> file;

	// open file reader
	ifstream fin;
	fin.open(file); // read in file name

	// check that file opens properly
	if (!fin.is_open()) {
		cout << "Unable to open " << file << endl;
		return 1;
	}

	else {
		// prompt for start/end dates
		cout << "Enter a report start date (mm dd yyyy): ";
		cin >> smonth >> sday >> syr;
		cout << "Enter a report end date (mm dd yyyy): ";
		cin >> emonth >> eday >> eyr;

		// correct yy -> yyyy
		if (syr < 100) {
			syr = syr + 2000;
		}
		if (eyr < 100) {
			eyr = eyr + 2000;
		}

		// main code, only if all parameters are read
		// read, stores, and manipulates each line
		while (fin >> citation >> month >> day >> year >> speed >> limit >> type) {

			if (year < 100) {
				year = year + 2000;
			}

			// convert date to number for comparison
			nsdate = syr * 10000 + smonth * 100 + sday;
			nedate = eyr * 10000 + emonth * 100 + eday;
		
			ndate = year * 10000 + month * 100 + day;

			// turn on/off reader
			if (ndate >= nsdate && ndate <= nedate) {

				// store 3 char month in dummy variable
				for (int i = 1; i < 13; i++) { 
					if (i == month) {
						cmon = months[i - 1]; // indexing requires to i - 1
					}
				}

				fine = speed - limit;

				if (fine < 0) {
					fine = 0;
				}
				// calculate fine
				switch (type){
					case 'I':
					case 'i':
						result = double(fine) * imul;
						break;
					case 'R':
					case 'r':
						result = double(fine) * rmul;
						break;
					case 'H':
					case 'h':
						result = double(fine) * hmul;
						break;
					default:
						result = double(fine) * namul;
						break;
				}

				// standard output
				cout << left << setw(10) << citation;
				cout << right<< setw(2) << setfill('0') << day << "-" << cmon << "-" << year << " $";
				cout << setw(9) << setfill(' ') << fixed << setprecision(2) << result << endl;

			}


		}
	}
	fin.close();


}
