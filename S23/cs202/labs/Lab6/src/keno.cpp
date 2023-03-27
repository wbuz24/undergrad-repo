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
    int nballs, cat;
    double bet, res = 0, payout;

    cin >> bet;
    cin >> nballs;

    Fraction curr; // initiate the fraction class
    printf("Bet: %.2f\nBalls Picked: %d\n", bet, nballs);
    while (cin >> cat >> payout) { // read each pair from stdin  
        curr.Multiply_Binom(80 - nballs, 20 - cat); // equation from write up
        curr.Multiply_Binom(nballs, cat);
        curr.Divide_Binom(80, 20);
        cout << "  Probability of catching "<< cat <<" of " << nballs << ": "<< curr.Calculate_Product() << " -- Expected return: " << curr.Calculate_Product() * payout << endl;
        res += curr.Calculate_Product() * payout; // collect each expected return
        curr.Clear(); // clear for next iteration
    }
    printf("Your return per bet: %.2f\nNormalized: %.2f\n", res - bet, (res - bet) / bet);
    return 0;
}
