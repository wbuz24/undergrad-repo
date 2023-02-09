/*
 * Read given txt file
 * create vectors of first & last names
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
using namespace std;

int main() {
	ifstream fin;
	string last, first;
	int h, m , s;


	fin.open("racetimesHMS.txt");
	if (!fin.is_open()) {
		cout << "racetimesHMS.txt failed to open" << endl;
		return 1;
	}

	vector <string> name, surname;

	while (fin >> first >> last >> h >> m >> s) {
		// anything done in the while loop will occur for every line
		name.push_back(first);
		surname.push_back(last);
		cout << "You read: " << last << ", " << first << endl;
	}
	
	for (int i = 0; i < surname.size(); i++) {
		printf("Person #%d is: %s %s\n", i, name[i], surname[i]); 
	}

	fin.close();

}
