// Error checking w/ ints
// .good(), .fail(), are good to use,
// .eof() is tricky


// 1. wrapping cin inside a while or if statement - we want a true/false if cin worked
// 2. If it failed, we:
//	a. clear the state of cin
//	b. ignore the input
// 3. (optional) We ask again. repeatedly until the input is satisfied

#include <iostream>
#include <limits>
using namespace std;

int main() {
	cout << "Enter two integers: " << endl;
	int input1, input2;
	cin >> input1 >> input2;

	while (!cin.good())
	{
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		// ask again
		cout << "FAILED" << endl;
		cout << "Enter two integers: " << endl;
		cin >> input1 >> input2;
	}

	cout << "You entered: " << input1 << " " << input2 << endl;

}
