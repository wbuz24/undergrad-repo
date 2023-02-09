/* Time Zone Conversion Calculator */

/* convert from pacific to eastern
 
*/


#include <iostream>
#include <iomanip>

int main() {
	// 3 hr difference
	// time (int hours, int min)
	// convert time to eastern - mod operator
	// print time as HH:MM
	// "The time converted to Eastern time is HH:MM <- setfill, setwidth
	
	std::cout << std::fixed << std::setprecision(2);

	int hour, minute, newhour;
	std::cout << "Enter the time - hours: ";
	std::cin >> hour;
	std::cout << "Minutes: ";
	std::cin >> minute;
	newhour = (hour + 3) % 12;
	if (newhour == 0) {
		newhour = 12;
	}

	std::cout << "The time converted to Eastern time is " << newhour << ":" << minute << std::endl;

}

