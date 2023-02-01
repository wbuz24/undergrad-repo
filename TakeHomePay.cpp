/*
 * Will Buziak
 * 000510519
 * wbuziak
 * TakeHomePay.cpp
 * calculate the yearly and monthly taxes on a given salary
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	// initialize variables and prompt for salary
	double salary, taxes, tax_rate, itaxed, sres, mres,
		   sstax = .062, mtax = .0145;

	cout << "Enter a salary: $";
	cin >> salary;

	cout << setfill('-') << setw(36) << " " << endl; // create a dashed line

	// if statement rejects salaries less than min wage
	if (salary < 15080) {
		cout << "This is less than minimum wage for a yearly salary." << endl;
		return 0;
	}
	else {
		// calculate taxes
		
		sres = sstax * salary;
		mres = mtax * salary;
		double taxes, tax_rate;		
		
		// increment up to salary, keeping track of tax brackets totals
		// would be ideal to create function to keep track of taxes
		for (int i = 0; i < salary; i++) {
			if (i < 10275) {
				tax_rate = .1;
				taxes = taxes + 1 * tax_rate; // repeated code
			}
			else if (i < 41775) {
				tax_rate = .12;
				taxes = taxes + 1 * tax_rate;
				
			}
			else if (i < 89075) {
				tax_rate = .22;
				taxes = taxes + 1 * tax_rate;
								
			}
			else if (i < 170050) {
				tax_rate = .24;
				taxes = taxes + 1 * tax_rate;

				
			}
			else if (i < 215950) {
				tax_rate = .32;
				taxes = taxes + 1 * tax_rate;

				
			}
			else if (i < 539900) {
				tax_rate = .35;
				taxes = taxes + 1 * tax_rate;
				
				
			}
			else {
				tax_rate = .37;
				taxes = taxes + 1 * tax_rate;	
				
			
			}

		}
		

		//print 
		itaxed = salary - taxes - mres - sres;
		double monthly = itaxed / 12;
		cout << fixed;

		// format defined by lab write-up
		
		cout << left << setfill(' ') << setw(25) 
			<< "Yearly Salary:" << "$" <<  right << setw(9) << setprecision(2)
			<< salary << endl;		
		cout << left << setw(25) << "Social Security Tax:" << "$" <<  right
			<< setw(9) << sres << endl;
		cout << left << setw(25) << "Medicare Tax:" << "$" << right
            << setw(9) << mres << endl;
		cout << left << setw(25) << "Income Tax:" << "$" << right
            << setw(9) << taxes << endl;
		cout << setfill('-') << setw(36) << " " << endl;
		cout << setfill(' ') << left << setw(25) << "Take Home Salary:" <<
			"$" << right << setw(9) << itaxed << endl;
		cout << left << setw(25) << "Monthly Take Home Pay:" << "$" << right
            << setw(9) << monthly << endl;


		}
	}


