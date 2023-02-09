/* Will Buziak
 * moonglow.cpp
 * cs202
 * 1/26/2023
 *
 */ 

#include <iostream>
#include <vector>
using namespace std;


double calcAverage(vector <double> nums) {
    double result = 0;
    unsigned int i = 0;
    unsigned int n = nums.size();

    if (n > 0) {
        for ( ; i < n; i++) {
            result += nums[i];
        }
        result = result / n;
    }
    return result;
}



int main() {
    string name = "", word;
    double score = 0, num, average = 0;
    bool os = 1, is = 0;
    
    while (os) { 
        cin >> num; // attempt to read a double
        
        if (!cin.fail()) {
            score += num; // if a double is read, add to score
        }

        else if (cin.eof()) {
            os = 0; // if end of file, end loop
        }

        else { // cin is not a double
            cin.clear(); // clear fail state
            cin >> word; // read a string
            
            if (word == "NAME") { // if string is "NAME"
                cin >> name; // read name
            }

            else if (word == "AVERAGE") { // if string is "AVERAGE"
                vector <double> numbers;
                is = 1; // turn on 'average loop'
                while (is) { // loop reads until not a double

                    cin >> num; // attempt to read a double
                    
                    if (!cin.fail()) {
                        numbers.push_back(num); // if double, append to vector
                    }

                    else if (cin.eof()) {
                        average = calcAverage(numbers);
                        score += average;
                        is = 0;  // end of file ends main loop
                        os = 0;
                    }

                    else {
                        cin.clear(); // if cin fails, exit loop
                        average = calcAverage(numbers);
                        score += average;
                        is = 0;
                    }

                }
            }
        }
    }

    cout << name << " " << score << endl; // all the magic, baby: print statement
    return 0;

}

