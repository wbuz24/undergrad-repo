#include "MiddleCode.cpp"
#include <cstring>

int main(int argc, char **argv)
{
    int i;
    class MiddleCode TheClass;
    string retval;
    string s;

    if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

    /*
      s = ;
    */

    if (strcmp(argv[1], "-") == 0) {
        cin >> s;
    }
    else {

        if (atoi(argv[1]) == 0) {
            s = "word";
        }

        if (atoi(argv[1]) == 1) {
            s = "aaaaa";
        }

        if (atoi(argv[1]) == 2) {
            s = "abacaba";
        }

        if (atoi(argv[1]) == 3) {
            s = "shjegr";
        }

        if (atoi(argv[1]) == 4) {
            s = "adafaaaadafawafwfasdaa";
        }
    }

    retval = TheClass.encode(s);
    cout << retval << endl;

    exit(0);
}
