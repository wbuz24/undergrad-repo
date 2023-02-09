/* Pass by Value and Pass by Reference */
/* Part 1 - Pass by Value 
   Read this before Pass by Reference notes! */

#include <iostream>
#include <vector>
using namespace std;

/*  Up until this point, we have kind of used the word "parameter"
    and "argument" as synonyms, but there is actually a slight difference
    to these words. To make pass-by-value and pass-by-reference very clear,
    I'm going to clarify their true definitions:

1. The FORMAL PARAMETERS for a function are listed in the function declaration
    and are used in the body of the function defintion. A formal parameter (of any sort)
    is a place holder that is filled in with something when the function is called.

2. An ARGUMENT is something that is used to fill in a formal parameter.
    When you make a function call, the arguments are listed in parentheses 
    after the function name. When the function call is executed, the arguments
    are "plugged in" for the formal paramenters.
*/

/* In the function definition below, count is the FORMAL PARAMETER. */
void incrementCount(int count)
{
  count = count + 1; // Increments the value of count inside the function.
}

/* When a function is called, its arguments are substitued for the formal
   parameters in the function definition (i.e. we "plug in" the values).

   There are two different ways of doing this substitution process...
   1. we can make COPIES of the value to "plug into" the function
   OR
   2. we can reference the value's actual spot in memory - no copies used.

   The first way is called pass-by-value (passing copies) (the default way in C++)
   and the second way is called pass-by-reference.

   You might also hear this as call-by-value and call-by-reference.
*/

/*
   To relate this back to the example function above,
   incrementCount is passing the parameter "count" by-value.
   "number" in the main function (see below) is the argument in the function call.
*/

/* Run the program below and see the comments below main. */
int main() {
    int number = 10;

    cout << "Pass by value" << endl;
    incrementCount(number);
   
    cout << "  Number: ";
    cout << number << endl;      
    return 0;
}

/* Number doesn't change!!! It's still 10. Why is that? Doesn't the function add 1?
   Shouldn't it be 11?
   It's because we passed it "by-value".
   Let's say "number" is located at memory address 0x01. 
   
   When we pass number (the value 10), we make a copy of what's in "number" at address 0x01
   and place that copy in a different address, let's say 0xF3.

   The copy in 0xF3 gets passed into the function to be "plugged in".
   Inside incrementCount, the copy of the integer 10 located at 0xF3 in memory
   gets incremented to 11. Then the function is over and the copy is destroyed.

   We come back to main, and print out number - the OG -(located at 0x01) and the OG
   hasn't changed a bit.

   This is passing-by-value (it's what C++ does by default)!
   Because the function is defined this way:
   void incrementCount(int count)
   we say "count is passed by value".

   Passing-by-reference (passing the OG by passing the address-of the argument)
   will be denoted using the & in the parameter list. Move onto passByReference.cpp notes next!
*/