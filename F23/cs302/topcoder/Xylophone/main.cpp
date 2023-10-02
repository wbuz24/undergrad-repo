#include "Xylophone.cpp"

int main(int argc, char **argv)
{
  int i;
  class Xylophone TheClass;
  int retval;
  vector <int> keys;

  if (argc != 2) { fprintf(stderr, "usage: a.out num|-\n"); exit(1); }

  if (((string)argv[1]) == "-") {
    while (cin >> i) keys.push_back(i);
  } else {

   if (atoi(argv[1]) == 0) {
      keys.push_back(1);
      keys.push_back(8);
      keys.push_back(3);
    }
  
   if (atoi(argv[1]) == 1) {
      keys.push_back(7);
      keys.push_back(3);
      keys.push_back(2);
      keys.push_back(4);
      keys.push_back(1);
      keys.push_back(5);
      keys.push_back(6);
    }
  
   if (atoi(argv[1]) == 2) {
      keys.push_back(1);
      keys.push_back(8);
      keys.push_back(15);
    }
  
   if (atoi(argv[1]) == 3) {
      keys.push_back(25);
      keys.push_back(1);
      keys.push_back(17);
      keys.push_back(9);
      keys.push_back(8);
    }
  
   if (atoi(argv[1]) == 4) {
      keys.push_back(11);
      keys.push_back(11);
      keys.push_back(11);
      keys.push_back(11);
      keys.push_back(11);
      keys.push_back(11);
      keys.push_back(11);
      keys.push_back(11);
      keys.push_back(11);
      keys.push_back(11);
      keys.push_back(11);
    }
  
   if (atoi(argv[1]) == 5) {
      keys.push_back(50);
      keys.push_back(10);
      keys.push_back(20);
      keys.push_back(30);
      keys.push_back(11);
      keys.push_back(30);
      keys.push_back(24);
      keys.push_back(38);
      keys.push_back(5);
      keys.push_back(2);
      keys.push_back(9);
    }
  }

  retval = TheClass.countKeys(keys);
  cout << retval << endl;

  exit(0);
}

