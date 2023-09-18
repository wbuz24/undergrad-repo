#include "SwapAndArithmetic.cpp"

int main(int argc, char **argv)
{
    int i;
    class SwapAndArithmetic TheClass;
    string retval;
    vector <int> x;
    string arg;

    if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

    arg = argv[1];

    if (arg == "-") {
        while (cin >> i) x.push_back(i);
    }
    else {

        if (atoi(argv[1]) == 0) {
            x.push_back(3);
            x.push_back(1);
            x.push_back(2);
        }

        if (atoi(argv[1]) == 1) {
            x.push_back(1);
            x.push_back(2);
            x.push_back(4);
        }

        if (atoi(argv[1]) == 2) {
            x.push_back(1);
            x.push_back(1);
            x.push_back(1);
            x.push_back(1);
            x.push_back(1);
            x.push_back(1);
        }

        if (atoi(argv[1]) == 3) {
            x.push_back(1000);
            x.push_back(704);
            x.push_back(1);
        }

        if (atoi(argv[1]) == 4) {
            x.push_back(7);
            x.push_back(3);
            x.push_back(11);
            x.push_back(5);
            x.push_back(1);
            x.push_back(9);
        }
    }

    retval = TheClass.able(x);
    cout << retval << endl;

    exit(0);
}

