
/* mini golf program
   will take in scores from 2 players
*/

#include <iostream> /* input-output stream */
using namespace std;

int main() {
   string name1, name2;
   int num_of_holes = 3;
   int p1holes;
   int p2holes;
   int data;

   cout << "Please enter Player 1's name: ";
   cin >> name1;
   cout << "You entered: " << name1 << endl;

   cout << "Please enter Player 2's name: ";
   cin >> name2;
   cout << "You entered: " << name2 << endl;

   for (int i = 1; i < num_of_holes; i++) {
      cout << "Please enter " << name1 << "'s score for hole" << i << endl;
      cin >> p1holes;

      cout << "Please enter " << name1 << "'s score for hole" << i << endl;
      cin >> p1holes;


   }
}