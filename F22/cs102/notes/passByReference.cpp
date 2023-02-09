/* Pass by Value and Pass by Reference */
/* Part 2 - Pass by Reference
   Read this after Pass by Value notes! */

#include <iostream>
#include <vector>
using namespace std;

/* In the last set of notes, we defined incrementCount as follows:

void incrementCount(int count) {
  count = count + 1; // Increments the value of count inside the function.
}
and this passed "count" by value. It made a copy of the argument "number"
when we "plugged in" number for count in the function definition. However,
"count" goes out of scope onces the function is done executing (i.e. the 
memory is destroyed).

Now we will pass "count" by reference! With this way of doing things, we will
have a reference to the OG "number" variable in main by passing the address of "number"
for the parameter "count".
No copy will be made. The OG "number" will be changed in main if the 
function changes it when it's "plugged in."
*/

/* To pass "count" by reference, we use the address-of operator, the ampersand.
  The way you indicate a pass-by-reference parameter is to attach this ampersand sign
  at the end of the parameter type, or before the parameter name.
  (int& count)
  OR 
  (int &count)
*/
void incrementCount(int &count) {
  count = count + 1; // Increments the value of count inside the function.
}

/* Note the difference now between the print statements in this main function
and the passByValue.cpp program. We now print 11 instead of 10 - because we
aren't creating a copy! We are changing number itself since we are passing
it's address. */

int main() {
    int number = 10;

    cout << "Pass by reference" << endl;
    incrementCount(number);
   
    cout << "  Number: ";
    cout << number << endl;      
    return 0;
}
