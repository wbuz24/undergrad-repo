#include <cstdio>
#include <iostream>
using namespace std;

struct MyStruct {
    int i;
    short j;
    long k;
};

extern "C" {
    long get_long(const MyStruct *ms, int index);
}

int main() {
    MyStruct ms[10];

    ms[3].k = -1111;

    cout << get_long(ms, 3) << '\n';
}
