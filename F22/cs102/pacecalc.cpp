// marathon pace calculator
// user enter hours and minutes of goal marathon
// program returns required pace
// 03:30 marathon is 8:01 min/mile pace (M)M:SS
// marathon is 26.2 miles


#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int hr, min, pmin;
	double	ps;

	// collect goal
	cout << "What is your goal - Hours: ";
	cin >> hr;
	cout << "Minutes: ";
	cin >> min;

	// arithmetic
	double s = hr*60*60 + min*60;
	
	ps = s / 26.2; 
	pmin = (int) (ps/60);
	ps = (int)((s/26.2) + .5) % 60;

	printf("Your required pace is %2d:%02d\n", pmin, ps);
	
	




}

