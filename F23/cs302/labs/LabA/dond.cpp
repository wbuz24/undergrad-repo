// Will Buziak
// CS302
// Lab AA
// dond.cpp
// Find the probability of a contestant rolling the die t more times successfully
// g++ -Wall -Wextra -o dond dond.cpp


#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

class DiceOrNoDice {
public:
  double Probability(int t, int l); // recursive function
  int S; // # of sides on the dice
  int T; // # of times to roll the dice
  int Last; // last roll, if -1, print the probability of rolling T times
  vector < vector < double >> Cache;
};

double DiceOrNoDice::Probability(int t, int l) {
  // Find the probability of rolling t times

  // You will have to find the probability with each call
  // First, sum each recursively decided chance of winning and divide by s
  int chance, i;
  double prob;

  chance = 0; // track the die from the last roll

  if (l >= 0 && Cache[t-1][l] != -1) return Cache[t-1][l];

  if (l >= 0) { // turn "off" the bit that represents the last roll +- 1
    chance |= 1 << (l - 1);
    chance |= 1 << l;
    chance |= 1 << (l + 1);
  }

  prob = 0;
  for (i = 0; i < S; i++) { // run through all sides
    if (!(chance & 1 << i)) { // if the die is in play
      if (t == 1) prob += 1; // probability of any side being rolled
      else prob += Probability(t-1, i);
    }
  }

  Cache[t-1][l] = prob / S; // store the value in the cache

  return prob / S;
}

int main(int argc, char** argv) {
  size_t i;

  if (argc != 4) {
    printf("Command Line Usage - ./dond s t last-roll\n");
    return 0;
  }
  
  DiceOrNoDice *d = new DiceOrNoDice;

  // set values from command line args
  d->S = atoi(argv[1]);
  d->T = atoi(argv[2]);
  d->Last = atoi(argv[3]);

  // resize the cache
  d->Cache.resize(d->T);
  for (i = 0; i < d->Cache.size(); i++) d->Cache[i].resize(d->S, -1);

  // return the probability of winning at the given time
  cout << d->Probability(d->T, d->Last) << endl;
  return 1;
}
