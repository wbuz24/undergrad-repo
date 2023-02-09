/* dogcare.cpp
 * Have a database of dogs to keep track of their stats and another
 * dog they get along with.
 */

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Dog {
    public:
        string name;
        string breed;
        int age;
        Dog *bff;
};

int main() {
    Dog *d;
    vector <Dog *> database;

    d = new Dog;
    d->name = "Iris"; // Note using -> to access public fields/methods in a class because "d" is a pointer
    d->breed = "Aussie";
    d->age = 2;
    
    database.push_back(d);
    
    /*
     * If you did not save the information before writing over 
     * the information you would have a memory leak losing contact 
     * with previous information
    */

    d = new Dog;
    d->name = "Murphy";
    d->breed = "Bassett";
    d->age = 4;
    d->bff = database[0];
    database.push_back(d);

    for (int i = 0; i < database.size(); i++) {
        cout << "Dog " << i << " is named: " << database[i]->name << endl;
        cout << " and is a: " << database[i]->bff->breed << endl;
    }
    d = new Dog;
    d->name = "Rover";
    d->breed = "Lab";
    d->age = 2;


/*
    dog rover;
    rover.name = "Rover";
    rover.name = "Roo";
    d -> name = "Rocky";

    cout << d -> name << endl;
    cout << d -> age << endl;
    cout << d -> breed << endl;
    cout << d -> bff << endl;
*/
    }
