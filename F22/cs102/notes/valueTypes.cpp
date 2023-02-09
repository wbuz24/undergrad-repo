#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Dog {
    public:
        string name;
        string breed;
        int age;
};



int main() {
    Dog d1, d2; // creating an object does not require "new"
    d1.name = "Rover";
    d2 = d1;

    cout << d1.name << endl;
    cout << d2.name << endl;

    d2.name = "Smokey";


}
