/* Will Buziak
 * Lab 9 Part B
 * Shapeshifter
 * ss_solver.cpp
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include "enum.cpp"
using namespace std;

/* Read_Grid_And_Shapes() initializes the grid from argc/argv, and the
   reads from standard input to get the shapes. */

Shifter::bool Read_Grid_And_Shapes(int argc, const char **argv);
{
 if (argc != 6) return 0;
  
};
/* Apply_Shape() applies the shape in Shapes[index] to the grid,
   starting at row r and column c.  You'll note, if you call
   Apply_Shape twice with the same arguments, you'll end up 
   with the same grid as before the two calls. */

void Shifter::Apply_Shape(int index, int r, int c)
{
    
};

/* Find_Solution() is the recursive procedure.  It tries all possible
   starting positions for Shape[index], and calls Find_Solution() 
   recursively to see if that's a correct way to use Shape[index].
   If a recursive call returns false, then it "undoes" the shape by
   calling Apply_Shape() again. */

bool Shifter::Find_Solution(int index)
{
    
};

/* This prints the solution on standard output. */

void Shifter::Print_Solution() const
{
     
};            


