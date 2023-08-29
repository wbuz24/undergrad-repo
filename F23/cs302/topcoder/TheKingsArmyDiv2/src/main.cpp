#include "TheKingsArmyDiv2.cpp"

int main(int argc, char **argv)
{
    int i;
    class TheKingsArmyDiv2 TheClass;
    int retval;
    vector <string> state;
    string arg, s;

    if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

    arg = argv[1];
    if (arg == "-") {
        while (cin >> s) state.push_back(s);
    }
    else {

        if (atoi(argv[1]) == 0) {
            state.push_back("SSSSS");
            state.push_back("SSHHS");
            state.push_back("SSSSS");
        }

        if (atoi(argv[1]) == 1) {
            state.push_back("SSSSS");
            state.push_back("SSHSH");
            state.push_back("HSSSS");
        }

        if (atoi(argv[1]) == 2) {
            state.push_back("SSS");
            state.push_back("SSS");
            state.push_back("SSS");
        }

        if (atoi(argv[1]) == 3) {
            state.push_back("HSHSHSH");
            state.push_back("SSSHSSS");
            state.push_back("SSHSHSS");
            state.push_back("SHSHSHS");
        }

        if (atoi(argv[1]) == 4) {
            state.push_back("HHSH");
            state.push_back("HHHS");
            state.push_back("HSSS");
            state.push_back("SHSH");
            state.push_back("HHHS");
            state.push_back("HSHH");
            state.push_back("SSSH");
        }
    }

    retval = TheClass.getNumber(state);
    cout << retval << endl;

    exit(0);
}

