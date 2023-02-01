/* class notes
 * ASCII table
 */

#include <iostream>
using namespace std;

char lowToUp (char c) {
    char result;
    if (c < 'A' || c > 'Z') {
        cout << "not an uppercase letter" << endl;

        return c;
    }
    result = c + 32;
    return result; 
}

int main() {
    char lower;

    cout << "Enter an uppercase letter: ";
    cin >> lower;

    cout << lowToUp(lower) << endl;

}
