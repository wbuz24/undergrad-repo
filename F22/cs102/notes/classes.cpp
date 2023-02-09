// classes notes
// cs 102
// 9/15/2022

#include <iostream>
using namespace std;

class Marathon {
	string total_time; // dont need to declare private, classes are private by default
	int sec;
	public: 
		int hours, mins;
}; // must have semicolon after the class brace

struct Location {
	// struct in C can hold attriutes, but in C++ it's basically a class but public by default
	string state;
	string city;
};


int main() {
	Marathon boston; // "boston" is an instance of the class "Marathon"
	Location raceLocation;
	raceLocation.city = "Boston";
	raceLocation.state = "MA";
	cout << "Enter your hours for the boston marathon: " << endl;
	
	
	cin >> boston.hours; // using the dot operator to access public memory
	boston.mins = 30; // cannot access private memory in main

	cout << "Your marathon time is: " << boston.hours << ":" << boston.mins << endl;
}

