/*
	Program adding sensors to a watch/fitness device
	Heart Rate monitor, speed/cadence, Power
*/


#include <iostream>
using namespace std;

int main() {
	int sensor;

	cout << "What sensor would you like to add 1 - HR, 2 - S/C, 3 -Power?: ";
	cin >> sensor;

	switch (sensor) {
		case 1:
			cout << "Heart Rate connected." << endl;
			break;
		case 2:
			cout << "Speed/Cadence is connected." << endl;
			break;
		case 3:
			cout << "Power is connected." << endl;
			break;
		default:
			cout << "Sensor not recognized." << endl;
	}
}

