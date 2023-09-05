/* Header file for CS302 Lab 2: Binary search.
 *
 * James S. Plank
 */

/* ------------------------------------------------------------------------------------------ */

/* You are to write the first three functions.  In the first, I have chosen a number
   between 0 and 2^64 - 1.  Your job is to return that number using binary search. */

unsigned long long whats_my_number_ll();

/* In the second, I have chosen a random double between 0 and 1,000,000,000.
   Your job is to return this number to within a tolerance of 10^{-9} using binary
   search */

double whats_my_number_d();

/* In the third, I have defined a function func(x) whose domain is composed of the integers
   from 0 to 2^{32} - 1.  The function fits one of three profiles:

   1. It is monotonically increasing.
   2. It is monotonically decreasing.
   3. It increases monotonically to a maximum, and then it monotonically decreases.

   Your job is to return the value of x for which func(x) is maximum.  You are guaranteed
   that if (x != y), then (func(x) != func(y)). */

unsigned int optimal();

/* ------------------------------------------------------------------------------------------ */

/* These three functions are written for you in lab_2_driver.cpp.  You call the first
   of these in whats_my_number_ll().  It will return whether v is greater than the
   chosen number. */

bool am_i_greater_ll(unsigned long long v);

/* You call the second in whats_my_number_d().  It will return whether v is greater than the
   chosen number. */

bool am_i_greater_d(double v);

/* You call the third in optimal().  It returns func(x). */

double func(unsigned int x);
