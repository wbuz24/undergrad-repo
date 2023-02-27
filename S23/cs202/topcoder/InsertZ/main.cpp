#include "InsertZ.cpp"
#include <cstring>
int main(int argc, char **argv)
{
  int i;
  class InsertZ TheClass;
  string retval;
  string init;
  string goal;

  if (argc != 2) { fprintf(stderr, "usage: a.out num or - to put the problem on stdin.\n"); exit(1); }

  if (strcmp(argv[1], "-") == 0) {
    if (!(cin >> init >> goal)) {
      fprintf(stderr, "Bad stdin.\n");
      exit(1);
    }
  } else {


    if (atoi(argv[1]) == 0) {
       init = "fox";
       goal = "fozx";
    }

    if (atoi(argv[1]) == 1) {
       init = "fox";
       goal = "zfzoxzz";
    }

    if (atoi(argv[1]) == 2) {
       init = "foon";
       goal = "foon";
    }

    if (atoi(argv[1]) == 3) {
       init = "topcoder";
       goal = "zopzoder";
    }

    if (atoi(argv[1]) == 4) {
       init = "aaaaaaaaaa";
       goal = "a";
    }

    if (atoi(argv[1]) == 5) {
       init = "mvixrdnrpxowkasufnvxaq";
       goal = "mvizzxzzzrdzznzrpxozzwzzkazzzszzuzzfnvxzzzazzq";
    }

    if (atoi(argv[1]) == 6) {
       init = "opdlfmvuicjsierjowdvnx";
       goal = "zzopzdlfmvzuicjzzsizzeijzowvznxzz";
    }
  }

  retval = TheClass.canTransform(init, goal);
  cout << retval << endl;

  exit(0);
}
