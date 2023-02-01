/*
*	9/14/2022
 *	Will Buziak
 *	wbuziak
 *	take user inputs & error check
 */
#include <limits>
#include <iostream>
#include <iomanip>
using namespace std;

void res(int x) { // result print function (repeated code)
	cout << "Result = " << x << endl; 
}


int main(){
	
	char operation;
	int L, R, result;

	
	// std in/out gather values & operand
	cout << "Enter left operand: ";
	cin >> L;
	// error check left
	if (cin.fail()){
		cout << "Invalid left operand." << endl;
	}
	// if L is int
	else {
		cout << "Enter operation: ";
		cin >> operation;
		// provided line to prevent unwanted characters
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (operation){	// order of code runs this if abs is entered before asking for right operand
			case 'B':
			case 'b':
			case '|':
				if (L > 0) { // if statement nested in switch statement to return abs value
					result = L;
					res(result); // call result print function with result as input
				}
				else {
					result = L * -1;
					res(result); 
				}	
			break; // code is aborted if abs is selected, returning just abs of left operand

			default: // default case executes rest of code if abs is not selected
	
			cout << "Enter right operand: ";
			cin >> R;
			// check if right is int
			if (cin.fail()) {
			cout << "Invalid right operand." << endl;
			}	 
			// if both L & R are ints, code executes
			else {
				// switch statement defining which operation returning correct result 
				switch(operation) {
					case 'A':
					case 'a':
					case '+':
						result = L + R;
						res(result);
						break;
					case 'S':
					case 's':
					case '-':
						result = L - R;
						res(result);
						break;
					case 'M':
					case 'm':
					case 'x':
					case '*':
						result = L * R;
						res(result);
						break;
					case 'D':
					case 'd':
					case '/':
						result = L / R;
						res(result);
						break;
					case 'C':
					case 'c':
					case '%':
						result = L % R;
						res(result);
						break;
					default:
						cout << "Unknown operation." << endl;
						return 0;
				}
		
		}

	}
	}
}
