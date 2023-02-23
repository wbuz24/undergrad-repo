/* Will Buziak
 * Lab 4
 * hash202.cpp
 * Implement the hash202 class with open addressing
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include "hash_202.hpp"
using namespace std;

string Last7(const string &key, const int &Coll) {
    istringstream ss;
    string key7 = "";
    int k;
    
    for (size_t i = key.size() - 1; i >= 0; i--) {
        if (key7.size() == 7) i = 0;
        else {
        
        }
    }

    ss.clear();
    ss.str(key7);

    ss >> hex >> k; // converts string to hex

    if (Coll == 'L') {
        
    }

    else {
    
    }
}

string Xor(const string &key, const int &Coll) {
    if (Coll == 'L') {

        
    }
    else {
    
    }
}

string Hash_202::Set_Up(size_t table_size, const string &fxn, const string &collision) {
    if (Nkeys > 0) return "Hash table already set up";
    if (table_size == 0) return "Bad table size";
    if (fxn != "Last7" && fxn != "Xor") return "Bad hash function";
    if (collision != "Linear" && collision != "Double") return "Bad collision resolution strategy";

    else {
        Keys.resize(table_size, "");
        Vals.resize(table_size, "");
        Nkeys = 0;

        if (fxn == "Last7") Fxn = 'L';
        else if (fxn == "Xor") Fxn = 'L';

        if (collision == "Linear") Coll = 'L';
        else if (collision == "Double") Coll = 'L';

        return "";
    }
}

string Hash_202::Add(const string &key, const string &val) {
    if (Keys.size() == 0) return "Hash table not set up";
    if (key == "") return "Empty key";
    for (size_t i = 0; i < key.size(); i++) if (key[i] > 'f' || key[i] < 0) return "Bad Key (not all hex digits)";
    if (val == "") return "Empty val";
    if (Nkeys == Keys.size() - 1) return "Hash table full";

    if (Find(key) != "") return "Key already in table";

    else {
        string ret;
        if (Fxn == 'L') {
            // Last7 hash function
            ret = Last7(key, Coll);
            return ret;
        }
            else if (Fxn == 'X') {
            ret = Xor(key, Coll);
            return ret;
        }
    }
}

string Hash_202::Find(const string &key) {
    if (Nkeys == 0) return "";
}

void Hash_202::Print() const {
    if (Keys.size() != 0) {
        /*
        int index = Find();
        printf("%5d\n", index); */
    }
}

size_t Hash_202::Total_Probes() {

}
