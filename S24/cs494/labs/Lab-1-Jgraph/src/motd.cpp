/* Will Buziak */
/* CS494 */
/* Lab 1 Jgraph */
/* Dr. James Plank's Music of The Day */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

class Jgraph {
public:
	bool dateSearch(string word); // string search
	bool oldManMusic(string date); // find appropriate dates
  void splitLine(string line); // split lines into words
	void make_jgraph(); // print to a jgr file
	map <string, int> Decades; // map keyed on decade with the value being number of occurrances
	map <string, int> Dates; // map keyed on decade with the value being number of occurrances
};

string color_picker() {
  string s;
  char buf[100];
  double r, g, b;

  r =  rand() %  11;
  g =  rand() %  11;
  b =  rand() %  11;

  r /= 10;
  g /= 10;
  b /= 10;

  if (r == g && g == b && b == 0) s = color_picker();
  else {
   sprintf(buf, "color %.1lf %.1lf %.1lf ", r, g, b);
   s = buf;
   }
  return s;
}


/* Construct the jgr file */
void Jgraph::make_jgraph() {
	ofstream ofile;
	string color, s;
  map <string, int>::iterator nit;
	char buf[1000];

	ofile.open("Music-Of-The-Day.jgr");

	ofile << "newgraph\n\n";
	ofile << "xaxis\n  min 1000 max 2020\n  label : Decade\n";
	ofile << "yaxis\n  min 0 max 12\n  label : Number of Occurances\n";

	for (nit = Decades.begin(); nit != Decades.end(); nit++) {
		color = color_picker();
		sprintf(buf, "label : %s", nit->first.c_str());
    s = buf;
	  ofile << "newcurve " << color << s;	
		ofile << "\n         pts ";
		sprintf(buf, "%s %d\n", nit->first.c_str(), nit->second);
		s = buf;
		ofile << s;
	}
}

/* Dr. Plank, if youre reading this I am sorry ab the funct name it's just the way it is */
bool Jgraph::oldManMusic(string date) {
	int i;
	string decade;
	map <string, int>::iterator nit, mit;

	/* 2000+ */
	if (date[0] == '2') {
		/* 2020+*/
		if (date[2] == '2') return 0;
		/* 2015-2019*/
		if (date[2] == '1') {
			if (date[3] == '5') return 0;
		} 
	}

	/* Construct the decade */
  decade = "";
	for (i = 0; i < 3; i++) decade += date[i];
	decade += '0';

	/* Insert into the map */
	nit = Decades.find(decade);
	mit = Dates.find(date);
	if (nit == Decades.end()) Decades.insert(make_pair(decade, 1));
	else nit->second++;

	if (mit == Dates.end()) Dates.insert(make_pair(date, 1));
	else mit->second++;

	return 1;
}

/* make sure the string is a four digit number */
bool isFourDigits(string word) {
	int i, d;
	char c[1];
	if (word.length() != 4) return 0;
	for (i = 0; i < 4; i++) {
		c[0] = word[i];
		if (sscanf(c, "%d", &d) != 1) return 0;
	}

	return 1;
}

bool Jgraph::dateSearch(string word) {
	string yr;

	/* I am counting multiple performances */
	/* For classical performances, I count the year of the performance */

	if (isFourDigits(word)) {
			/* I assume Dr. Plank only listens to music from year 1000 to 2014 */
			if (oldManMusic(word)) {
				return 1;
			}
	}
  
	return 0;
}

/* read each line word by word */
void Jgraph::splitLine(string line) {
	string subs;
	istringstream iss(line);
	
	/* Split each line into individual words and try to only grab one date per new line */
	while (iss >> subs) {
		if (dateSearch(subs)) return;
	}

}

int main(int argc, char** argv) {
  ifstream fin;
	string line;
	Jgraph *jgraph;

  /* error check args, shouldn't be a concern */
  if (argc != 2) { printf("./bin/motd music-of-the-day.txt\n"); exit(0); }

  /* open the input file, should just be Music-Of-The-Day.txt, but take it from args anyways */
	fin.open(argv[1]);
	if (fin.is_open()) {

		jgraph = new Jgraph;
		/* Read past the preamble */
		getline(fin, line);
    while (line[0] != '-') getline(fin, line);
		getline(fin, line);

		
		/* Read the entire file and process each line */
		while (getline(fin, line)) {
			jgraph->splitLine(line);
		}

		jgraph->make_jgraph();

	}
	return 1;
}
