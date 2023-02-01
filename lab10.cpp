/*
 *  Will Buziak
 *  cs102
 *  000510519
 *  lab 10
 *  12-5-2022
 *  make vectors from scratch using dynamic allocation
*/ 
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

class doublevector {
    static constexpr double DOUBLE_DEFAULT_VALUE = -5.55;
    double *mValues;
    int mNumValues;
public:
    doublevector();
    ~doublevector();
    void resize(int new_size, double initial_value=DOUBLE_DEFAULT_VALUE);
    void push_back(double value);
    double &at(int index);
    const double &at(int index) const;
    unsigned long size() const;
};
void print_all(const doublevector &v)
{
    if (v.size() == 0) {
        cout << "Vector is empty.\n";
    }
    else {
        unsigned long i;
        for (i = 0;i < v.size();i++) {
            cout << "[" << setfill('0') << right << setw(3) << i
                << "] = " << fixed << setprecision(4) << v.at(i)
                << '\n';
        }
    }
}
int main()
{
    doublevector v;
    do {
        string command;
        cout << "Enter a command ('quit' to quit): ";
        if (!(cin >> command) || command == "quit") {
            break;
        }
        else if (command == "push_back") {
            double value;
            cin >> value;
            v.push_back(value);
            cout << "Pushed back "
                << fixed << setprecision(4)
                << value << '\n';
        }
        else if (command == "resize") {
            string line;
            int new_size;
            double initial;
            cin >> new_size;
            getline(cin, line);
            istringstream sin(line);

            if (sin >> initial)
                v.resize(new_size, initial);
            else
                v.resize(new_size);
        }
        else if (command == "size") {
            cout << v.size() << '\n';
        }
        else if (command == "print") {
            print_all(v);
        }
        else if (command == "get") {
            int index;
            cin >> index;
            try {
                cout << "Value at " << index << " = "
                    << setprecision(4) << fixed
                    << v.at(index) << '\n';;
            }
            catch(out_of_range &err) {
                cout << err.what() << '\n';
            }
        }
        else if (command == "set") {
            double d;
            int index;
            cin >> index >> d;
            try {
                v.at(index) = d;
                cout << "SET: " << index << " = "
                    << setprecision(4) << fixed
                    << v.at(index) << '\n';;
            }
            catch(out_of_range &err) {
                cout << err.what() << '\n';
            }
        }
        else if (command == "clear") {
            v.resize(0);
        }
        else {
            cout << "Invalid command '" << command << "'\n";
        }
    } while(true);
    cout << endl;
    return 0;
}
//Write your class members below here.
// initialize pointer to double array
doublevector::doublevector() {
    mNumValues = 0;
    mValues = new double[mNumValues];
    mValues = nullptr;
}

// deletes array and sets # of values to zero
doublevector::~doublevector() {
    if (mValues != NULL) {
        delete [] mValues;
        mNumValues = 0;    
    }
}

 
void doublevector::resize(int new_size, double initial_value) {
    // creates new array for copying
    double *copy = new double[new_size];
    if (new_size < 0 || new_size == mNumValues) {
        return;
    }
    if (new_size == 0) {
        delete[] mValues;
        mNumValues = 0;
        mValues = nullptr;
    }
    // copies values and truncates mValues
    else if (new_size < mNumValues) {
        for (int i = 0; i < new_size; i++) {
            copy[i] = mValues[i];
            
        }
        // check if mValues is null
        if (mValues != nullptr) {
            delete[] mValues;
        }
        // assign mValues to copy 
        mValues = copy;
        mNumValues = new_size;
    }
    else if (new_size > mNumValues) {
        for (int i = 0; i < new_size; i++) {
            // copies values to mNumValues
            if (i < mNumValues) {
                copy[i] = mValues[i];
            }
            // places initial_value in new memory spaces
            else if (i >= mNumValues) {
                copy[i] = initial_value;
            }
        }
        // checks for null pointer 
        if (mValues != nullptr){
            delete[] mValues;
        }
        // assigns mValues to copy
        mValues = copy;
        mNumValues = new_size;
    }


}

// calls the resize function to resize with one greater element
void doublevector::push_back(double value) { 
    resize(mNumValues + 1, value);
}

// returns the dereferenced memory that mValues points to at a given index
double& doublevector::at(int index) { 
    if (index >= mNumValues) {
       ostringstream sout;
       sout << "Invalid index #" << index;
       throw out_of_range(sout.str());
    }
    else {
        return mValues[index];
    }
}

// overloaded function with different use instances, this one is read only
const double& doublevector::at(int index) const { 
     if (index >= mNumValues) {
       ostringstream sout;
       sout << "Invalid index #" << index;
       throw out_of_range(sout.str());
    }
    else {
        return mValues[index];
    }

}

// returns the length of the array
unsigned long doublevector::size() const {
    unsigned long result;
    result = (unsigned long)mNumValues;
    return result;
}
