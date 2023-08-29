#include "Cryptography.cpp"

int main(int argc, char **argv)
{
  int i;
  class Cryptography TheClass;
  long long retval;
  vector <int> numbers;
  string a;

  if (argc != 2) { fprintf(stderr, "usage: a.out num (or - to read from standard input)\n"); exit(1); }

  
 a = argv[1];
 if (a == "-") {
   while (cin >> i) numbers.push_back(i);
 } else {

   if (atoi(argv[1]) == 0) {
      numbers.push_back(1);
      numbers.push_back(2);
      numbers.push_back(3);
    }
  
   if (atoi(argv[1]) == 1) {
      numbers.push_back(1);
      numbers.push_back(3);
      numbers.push_back(2);
      numbers.push_back(1);
      numbers.push_back(1);
      numbers.push_back(3);
    }
  
   if (atoi(argv[1]) == 2) {
      numbers.push_back(1000);
      numbers.push_back(999);
      numbers.push_back(998);
      numbers.push_back(997);
      numbers.push_back(996);
      numbers.push_back(995);
    }
  
   if (atoi(argv[1]) == 3) {
      numbers.push_back(1);
      numbers.push_back(1);
      numbers.push_back(1);
      numbers.push_back(1);
    }

  }

  retval = TheClass.encrypt(numbers);
  cout << retval << endl;

  exit(0);
}
