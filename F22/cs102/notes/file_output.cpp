
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
	ofstream fout;
	fout.open("myOutput.txt"); // creates OR overwrites myOutput.txt

	string s1 = "this is my new file\n";
	string s2 = "welcome\n";
	double a = 10.55556;
	
	fout << s1;
	fout << s2;
	fout << left << fixed << setprecision(2) << setw(5) << a;
	
	fout.close();

}

