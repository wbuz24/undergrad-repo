
#include <iostream>
using namespace std;


int main () {
	string first, middle, street, type, city;
	int age, num, new_age, new_num; 
	
		// read inputs using iostream 
	cout << "Enter your first and middle names: ";
	cin >> first >> middle;
	
	cout << "Enter your age: ";
	cin >> age;

	cout << "Enter your street number, name, and type: ";
	cin >> num >> street >> type;

	cout << "Enter your city of birth: ";
	cin >> city;
		// arithmetic: utilize mod operator and simple arithmetic operators, store to new vars
	new_age = 3*(num % age);
	new_num = (age*425)/num;
		// std output stream
	cout << "Your pen name is " << city << " " << street << endl;
	cout << "You will write as a " << new_age << " year old" << endl;
	cout << "Your address is " << new_num << " " << middle << " " << type << endl;


}

