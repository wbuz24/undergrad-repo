/* Will Buziak
 * Lab 9 Part B
 * Shapeshifter
 * ss_solver.cpp
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <sstream>
using namespace std;
using namespace std;

class Shifter {
    public:

        /* Read_Grid_And_Shapes() initializes the grid from argc/argv, and the
           reads from standard input to get the shapes. */

        bool Read_Grid_And_Shapes(int argc, const char **argv);

        /* Apply_Shape() applies the shape in Shapes[index] to the grid,
           starting at row r and column c.  You'll note, if you call
           Apply_Shape twice with the same arguments, you'll end up
           with the same grid as before the two calls. */

        void Apply_Shape(int index, int r, int c);

        /* Find_Solution() is the recursive procedure.  It tries all possible
           starting positions for Shape[index], and calls Find_Solution()
           recursively to see if that's a correct way to use Shape[index].
           If a recursive call returns false, then it "undoes" the shape by
           calling Apply_Shape() again. */

        bool Find_Solution(int index);

        /* This prints the solution on standard output. */

        void Print_Solution() const;

    protected:

        /* This is the grid.  I have this be a vector of 0's and 1's, because it makes
           it easy to print the grid out. */

        vector <string> Grid;

        /* These are the shapes, in the order in which they appear in standard input. */

        vector < vector <string> > Shapes;

        /* These two vectors hold the starting positions of the shapes, both as you
           are finding a solution, and when you are done finding a solution. */

        vector <int> Solution_Rows;
        vector <int> Solution_Cols;
};


bool Shifter::Read_Grid_And_Shapes(int argc, const char** argv)
{
    if (argc < 2) return 0; // error check for not enough arguments
    
    istringstream ss;
    string word = argv[2], l;
    int i;
    size_t s = word.size();
    vector <string> line;


    for (i = 1; i < argc; i++) {
        word = argv[i];
        if (word.size() != s) return 0; // error check size
    //    for (j = 0; j < s; j++) if (argv[i][j] != '0' && argv[i][j] != '1') return 0; // error check 0 or 1
        Grid.push_back(argv[i]); // push the string into Grid
    }
  
    while (getline(cin, word)) {
      ss.clear(); // clear the stream and vector
      line.clear();
      ss.str(word); // pass the line into the stream
      while (ss >> l) line.push_back(l); // parse the stream and insert each string into a vector
      Shapes.push_back(line); // push the vector into Shapes
    }
    return 1;
};

void Shifter::Apply_Shape(int index, int r, int c)
{
   size_t i, j;
   if (r < (int) Grid.size() && c < (int) Grid[0].size() && index < (int) Shapes.size()) {
     for (i = 0; i < Shapes[index].size(); i++) {
       for (j = 0; j < Shapes[index][i].size(); j++) {
          if (Shapes[index][i][j] == '1' && (r + i) < Grid.size() && (c + j) < Grid[0].size()) Grid[r + i][c + j] ^= 1;
       }
     }
   }
};

bool Shifter::Find_Solution(int index)
{
  size_t i, j;
  if (index == (int) Shapes.size()) return 0; // Find_Solution fails

  for (i = 0; i < Grid.size(); i++) {
    for (j = 0; j < Grid[i].size(); j++) {
        Apply_Shape(index, i, j); 
        if (!Find_Solution(index + 1)) Apply_Shape(index, i, j);
        else {
            Solution_Rows.push_back(i);
            Solution_Cols.push_back(j);
        }
    }
  }  
  return 1;
};

void Shifter::Print_Solution() const
{
  size_t i, j;
  for (i = 0; i < Shapes.size(); i++) {
    for (j = 0; j < Shapes[i].size(); j++) {
        cout << Shapes[i][j] << " ";
    }
    cout << Solution_Rows[i] << " " << Solution_Cols[i] << endl;
  }
};

int main(int argc, const char** argv) {
    Shifter shifter;

    if (!shifter.Read_Grid_And_Shapes(argc, argv)) cout << "usage: ss_random_game rows cols nshapes seed(0 for current time) solvable(y|u)\n";

    if (shifter.Find_Solution(0)) shifter.Print_Solution();
    return 0;
}
