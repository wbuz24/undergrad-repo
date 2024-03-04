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
	string color, s, mstr;
	int maxd;
  map <string, int>::iterator nit, mit;
	char buf[1000];

	ofile.open("jgr/Music-Of-The-Day.jgr");

	ofile << "newgraph\n\n";
	ofile << "xaxis\n  min 1805 max 2020\n  mhash 0\n  hash 10\n shash 0\n  size 6\n  label : Decade\n";
	ofile << "yaxis\n  min 0 max 40\n  grid_lines grid_gray .7\n  size 3.5\n  mhash 2\n  hash 5\n  label : Number of Occurances\n";

	/* Create a bar graph of decades */
	maxd = 0;
	ofile << "newline pts 1805 0 2020 0\n";
	ofile << "newcurve marktype xbar cfill color 0 0 1";	
	ofile << "\n  marksize 8.5\n\n";
	ofile << "\n         pts";
	for (nit = Decades.begin(); nit != Decades.end(); nit++) {
		sprintf(buf, " %s %d", nit->first.c_str(), nit->second);
		if (nit->second > maxd) {
			maxd = nit->second;
			mstr = nit->first;
		}
		s = buf;
		ofile << s;
	}
	ofile << endl;

	ofile << "newstring hjl vjt x 1975 y 29\n";
	ofile << "          font Times-Italic fontsize 20 : " << mstr;
	ofile << endl;

  /* Plot the highest decade */
	ofile << "newcurve marktype xbar cfill color 1 0 0";
	ofile << "\n  marksize 8.5\n\n";
	ofile << "\n         pts";
	sprintf(buf, " %s %d\n", mstr.c_str(), maxd); 
	ofile << buf << endl;

	ofile << "newcurve marktype circle linetype solid label : Individual Years";
	ofile << "\n         pts";

	/* Plot the individual years */
	maxd = 0;
	for (mit = Dates.begin(); mit != Dates.end(); mit++) {
		sprintf(buf, " %s %d", mit->first.c_str(), mit->second);
		if (mit->second > maxd) {
			maxd = mit->second;
			mstr = mit->first;
		}
		s = buf;
		ofile << s;
	}
	ofile << endl;




	/* Legend defaults */

	ofile << "legend defaults x 1970 y 45 font Times-Italic fontsize 18\n\n\n\n";
	ofile.close();
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
	if (strcmp(date.c_str(), "1000") == 0 || strcmp(date.c_str(), "1800") == 0) return 0;

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

/* remove xxxx's & xxxx. */
bool isFiveorSix(string word) {
  if (word.length() == 5) {
		if (word[4] == '.' || word[4] == ':' || word[4] == ',' || word[4] == ')') return 1;
	}
	if (word.length() == 6) {
		if (word[4] == '\'' && word[5] == 's') return 1;	
	}
	return 0;
}

/* make sure the string is a four digit number */
bool isFourDigits(string word) {
	int i, d;
	char c[1];
	/* Check that the length is four */
	if (word.length() != 4) return 0;
	/* Make sure each character is a digit */
	for (i = 0; i < 4; i++) {
		c[0] = word[i];
		if (sscanf(c, "%d", &d) != 1) return 0;
	}

	return 1;
}

bool Jgraph::dateSearch(string word) {
	int i;
	string yr;

	/* I am counting multiple performances */
	/* For classical performances, I count the year of the performance */

  /* check for 's and periods */
	if (isFiveorSix(word)) {
		/* just grab the first four characters */
		yr = "";
		for (i = 0; i < 4; i++) yr += word[i];
		word = yr;
	}

	if (isFourDigits(word)) {
			/* I assume Dr. Plank only listens to music from year 1000 to 2014 */
			if (oldManMusic(word)) { return 1; }
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

    /* Franz Liszt */
		line = "1853";
		jgraph->oldManMusic(line);
    /* Johannes Brahms */
		line = "1867";
		jgraph->oldManMusic(line);
    /* Ludwig von Beethoven 7th symphony */
		line = "1811";
		jgraph->oldManMusic(line);




		jgraph->make_jgraph();

	}
	return 1;
}
