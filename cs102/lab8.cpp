/*
 * Will Buziak
 * wbuziak
 * 000510519
 * lab 8
 * create the bitset date type
 * use bitwise operations to execute functions
*/ 


#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
using namespace std;


class BITSET {
    vector<int> mSets;
public:
    BITSET();
    bool Test(int index) const;
    void Set(int index);
    void Clear(int index);
    int GetNumSets() const;
    int GetSet(int index) const;
};
string ToBinary(int bit_set, int spacing=4);
int main() {
    BITSET sets;
    string command;
    int which;
    do {
        cout << "> ";
        if (!(cin >> command) || "q" == command) {
            // If cin fails for any reason, it usually means
            // an EOF state, break and quit.
            break;
        }
        // Handle the commands here
        if ("t" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            }
            else {
                cout << sets.Test(which) << '\n';
            }
        }
        else if ("s" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            }
            else {
                sets.Set(which);
            }
        }
        else if ("g" == command) {
            int spacing;
            string line;
            getline(cin, line);
            istringstream sin {line};
            if (!(sin >> which)) {
                cout << "Invalid index\n";
            }
            else {
                if (!(sin >> spacing)) {
                    spacing = 4;
                }
                cout << ToBinary(sets.GetSet(which), spacing) << '\n';
            }
        }
        //
        else if ("c" == command) {
            if (!(cin >> which)) {
                cout << "Invalid index\n";
            }
            else {
                sets.Clear(which);
            }
        }
        //
        else if ("n" == command) {
            cout << sets.GetNumSets();
        }
        else {
            cout << "Unknown command '" << command << "'\n";
        }
    } while (true);
    return 0;
}
// Write the function body for ToBinary:
string ToBinary(int bit_set, int spacing) {
    string ret;
    // 
    for (int i = 31;i >= 0;i--) {
        // 
        if (((bit_set >> i) & 1) != 0) {
            ret += '1';
        }
        else {
            ret += '0';
        }
        //
        if (((i + 1) % spacing) == 0 && i != 31 && i != 0) {
            ret += ' ';
        }
    }
    return ret;
}

// BITSET Class Members
BITSET::BITSET() :
   mSets(1, 0)
{}

bool BITSET::Test(int index) const {
    int which_set = (index - (index % 32)) / 32 ; // 32 bit numbers 
    int which_bit = index % 32 ; // remainder (determines bit from index
    if (which_set >= GetNumSets()) {
        // The BITSET is an "infinite" set, so if the requested set
        // is bigger than what we are storing, that means it's a 0.
        return false;
    }
    // shift which_set by which_bit spaces & return the value
    bool set;
    if (((mSets.at(which_set) >> which_bit) & 1) == 1){
        set = 1;
    }
    return (set);
}

void BITSET::Set(int index) {
    int which_set = (index - (index % 32)) / 32 ; 
    int which_bit = index % 32 ; 
    // TODO: You might need to expand the Set to accommodate the index
     
    if (which_set + 1 > GetNumSets()) {
        mSets.resize(which_set + 1, 0);
    } 
    // left shift desired bit and | with the given set
    mSets.at(which_set) = (1 << which_bit | which_set);
}

void BITSET::Clear(int index) {
    int which_set = (index - (index % 32)) / 32 ; 
    int which_bit = index % 32 ;
    if (which_set < GetNumSets()) {
        // NOT desired bit with 1 then AND with index to clear the set
        mSets.at(which_set) = ~(1 << which_bit) & index; 

    for (int i = mSets.size() - 1; i >= 0 ; i--) {
        if (mSets.at(i) == 0) {
            mSets.resize(mSets.size() - 1);
        }
        else {
        break;
        }
    }
}
}

int BITSET::GetNumSets() const {
    return static_cast<int>(mSets.size());
}

int BITSET::GetSet(int index) const {
    // use GetNumSets() to determine # of sets
    int which_set = (index - (index % 32)) / 32;
    int nums = GetNumSets();
    if (which_set > nums) {
        return false;
    }

    return mSets.at(index);
}
