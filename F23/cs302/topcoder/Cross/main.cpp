#include "Cross.cpp"

int main(int argc, char **argv)
{
    int i;
    class Cross TheClass;
    string retval;
    vector <string> board;
    string s;

    if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

    if (strcmp(argv[1], "-") == 0) {
        while (cin >> s) board.push_back(s);
    }
    else {
        /*
          board = ;
        */

        if (atoi(argv[1]) == 0) {
            board.push_back(".##");
            board.push_back("###");
            board.push_back("##.");
        }

        if (atoi(argv[1]) == 1) {
            board.push_back(".##");
            board.push_back("###");
            board.push_back("#..");
        }

        if (atoi(argv[1]) == 2) {
            board.push_back("######");
            board.push_back("######");
            board.push_back("######");
            board.push_back("######");
            board.push_back("######");
            board.push_back("######");
            board.push_back("######");
        }

        if (atoi(argv[1]) == 3) {
            board.push_back(".#.#");
            board.push_back("#.#.");
            board.push_back(".#.#");
            board.push_back("#.#.");
        }

        if (atoi(argv[1]) == 4) {
            board.push_back(".#.#");
            board.push_back("###.");
            board.push_back(".###");
            board.push_back("#.#.");
        }
    }

    retval = TheClass.exist(board);
    cout << retval << endl;

    exit(0);
}

