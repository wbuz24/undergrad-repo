#include "TheBrickTowerMediumDivTwo.cpp"

int main(int argc, char **argv)
{
    int i;
    class TheBrickTowerMediumDivTwo TheClass;
    vector <int> retval;
    vector <int> heights;
    string arg;

    if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

    arg = argv[1];
    if (arg == "-") {
        while (cin >> i) heights.push_back(i);
    }
    else {

        if (atoi(argv[1]) == 0) {
            heights.push_back(4);
            heights.push_back(7);
            heights.push_back(5);
        }

        if (atoi(argv[1]) == 1) {
            heights.push_back(4);
            heights.push_back(4);
            heights.push_back(4);
            heights.push_back(4);
            heights.push_back(4);
            heights.push_back(4);
            heights.push_back(4);
        }

        if (atoi(argv[1]) == 2) {
            heights.push_back(2);
            heights.push_back(3);
            heights.push_back(3);
            heights.push_back(2);
        }

        if (atoi(argv[1]) == 3) {
            heights.push_back(13);
            heights.push_back(32);
            heights.push_back(38);
            heights.push_back(25);
            heights.push_back(43);
            heights.push_back(47);
            heights.push_back(6);
        }
    }

    retval = TheClass.find(heights);
    if (retval.size() == 0) {
      printf("{ }\n");
      exit(0);
    }
    printf("{ %d", retval[0]);
    for (i = 1; i < retval.size(); i++) printf(", %d", retval[i]);
    printf(" }\n");

    exit(0);
}

