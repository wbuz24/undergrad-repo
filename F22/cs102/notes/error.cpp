// Error checking
// read in doubles and if user types anything else,
// refuse entry
// notes 9-15-2022
// cs 102

#include <iostream>
#include <limits>
using namespace std;

void ignoreLine() {

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	// (number of characters to ignor (X), exactraction operator)
	// we ignore X number of characters or until we see the exactraction operator

}

int main() {
	
	while (true) // Loop until user enters a valid input
	{
	
		cout << "Enter a double value: ";
		double x;
		cin >> x;

		if (!cin) // has a previous extraction failed?
		{
			//handle failure
			cin.clear(); // put us back in 'normal' operation mode (clears the stack)
			ignoreLine(); // remove bad input
			cout << "Fail" << endl;
		}
		else 
		{
			ignoreLine();
			printf("%.2f\n", x);
			break;
		}

	}


}
