/*
 *
 * 
*/

#include <iostream>
#include <string> // getline
#include <sstream>
using namespace std;

int main() {
	string data = "10 20.5 30";
	string data2 = "data file";
	int a, c;
	double b;

	istringstream sin(data);
	//	sin >> a >> b >> c; // one way to place string "data" into the stream
	sin.str(data); // .str(string_param) with sin will place the string into the stream 

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;

	sin.clear(); // if we reuse sin, then we need to clear before re-use

	sin.str(data2); // placed a different string in the stream (ignored if .clear() is not run first)
	
	string s1, s2;
	sin >> s1 >> s2;

	cout << s1 << ", " << s2 << endl;

	cout << "----------------------" << endl;

	// ---------------------------- //
	
	ostringstream sout;
	string output;

	sout << a << " " << b << " " << c << " ";
	output = sout.str(); // returns the string created (.str() with sout)
	cout << output << endl;

	sout << 40 << " " << 50; // does not reset stream, just adds onto it;                       
	cout << output << endl;

	sout.str(""); // resets sout
	sout << 40 << " " << 50;
	output = sout.str();
	cout << output << endl;


}

