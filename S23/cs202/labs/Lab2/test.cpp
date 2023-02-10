#include <iostream>
#include <vector>
using namespace std;

int main() {
vector <int> test = {1, 2, 3, 4, 5};
vector <int> out;
/*
for (int i = 5; i <= 0 ; i--) {
    cout << test[i]; 
}*/

for (int j = test.size() - 1; j >= 0; j--) {
    cout << test[j] << endl;
}
return 0;
}

