/* Will Buziak
 * cs202
 * Lab 6
 * Keno.cpp
 * Use fraction.cpp to calculate the probability of winning money in the game of keno
*/ 

#include "fraction.hpp"
#include <iostream>
using namespace std;

int main() {
  int nballs, i;
  double bet;

  cin >> bet;
  cin >> nballs;
  
  printf("Bet: %2f\nBalls Picked: %d\n", bet, nballs);
  for (i = 3; i <= nballs; i++) {

    printf("Probability of catching %d of %d: %d -- Expected return: %f", i, nballs, bet);
  }
  
}
