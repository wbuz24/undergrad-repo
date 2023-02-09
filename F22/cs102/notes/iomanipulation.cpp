	
#include <iostream>
#include <iomanip>
using namespace std;

int main() {

	// in java: System.out.format("My grade is %d", grade
	// in c++: equivalent is printf
	// d = int
	// f = double
	// s = strings
	// c = chars

	
	double grade;
	string name;

	cout << fixed << setprecision(2);
	cout << "Enter a grade and dog's name: ";
	cin >> grade >> name;

	printf("My dog is %s\n", name.c_str());
	printf("My grade is %.2f\n", grade);

	// If you wanted to print using cin/cout
	cout << "My grade is " << grade << endl;
	/*
		fixed, scientific, hex
		setprecision(_)
		setw(_) -> only manipulator not "persistent"
		setfill(_) -> place a character ., 0 , spaces

		left
		right -> default

		cout << left << setw(10) << "Hello" << "World";
			would create a 10 char. left justified
			field to print "Hello", then, "World" 
			printed afterwards
		   "Hello     World"
		
	*/
	


}
