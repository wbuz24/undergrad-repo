/* Will Buziak
 * Lab 4
 * hash_202.cpp
 * Implement the hash202 class with open addressing
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include "hash_202.hpp"
using namespace std;

int Xor(const string &key);

string Last7(const string &key);

int read_as_hex (const string &key);

int collision_res(const int &hnum, const string &key, const int &Coll, const vector <string> &Keys, const int &Fxn) {
    int iter = hnum % Keys.size(), tmp = iter; // hnum is your base;
    bool searching = true;
    if (Coll == 'L') { // linear
        while (Keys[iter].compare("") != 0) {
            iter = (iter + 1) % Keys.size();
        }
        return iter;
    }
    else { // double hashing
        int i = 0;
        while (searching) {
            if (Fxn == 'L') {
                iter += (Xor(key) * i) % Keys.size();
            }
            else {
                iter += (read_as_hex(Last7(key)) * i) % Keys.size();
            }

            if (iter == 0) iter = 1;

            if(Keys[tmp].compare("") != 0 && tmp == iter) searching = 0; // cannot find key

            if (Keys[iter].compare("") == 0) {
                searching = 0;
            }
            i++;
        }
        return iter;
    }
}

int read_as_hex (const string &key) { // returns an int from the hex key
    istringstream ss;
    int result;

    ss.clear();
    ss.str(key);
    ss >> hex >> result; 
    return result;
}

string Last7(const string &key) { // last7 helper function
    string key7 = "";

    for (size_t i = key.size() - 8; i < key.size(); i++) {
        key7 += key[i];
    }
    return key7;

}
int Xor(const string &key) {
    size_t i = 0, j = 0;
    vector <string> vec;
    int hnum1, hnum2;
    string tmp = "";

    for (; i < key.size(); i++) {
        tmp += key[i];

        if (tmp.size() == 7) {
            vec.push_back(tmp);
            tmp = "";
        }
    }

    hnum1 = 0;
    for (; j < vec.size(); j++) {
        hnum2 = read_as_hex(vec[j]);
        hnum1 = hnum1 ^ hnum2;    
    }
    return hnum1;
}

string Hash_202::Set_Up(size_t table_size, const string &fxn, const string &collision) {
    if (Keys.size() > 0) return "Hash table already set up";
    if (table_size == 0) return "Bad table size";
    if (fxn.compare("Last7") != 0 && fxn.compare("Xor") != 0) return "Bad hash function";
    if (collision.compare("Linear") != 0 && collision.compare("Double") != 0) return "Bad collision resolution strategy";

    else {
        Keys.resize(table_size, "");
        Vals.resize(table_size, "");
        Nkeys = 0;

        if (fxn.compare("Last7") == 0) Fxn = 'L';
        else if (fxn.compare("Xor") == 0) Fxn = 'X';

        if (collision.compare("Linear") == 0) Coll = 'L';
        else if (collision.compare("Double") == 0) Coll = 'D';

        return "";
    }
}

string Hash_202::Add(const string &key, const string &val) {
    if (Keys.size() == 0) return "Hash table not set up";
    if (key.compare("") == 0) return "Empty key";
    for (size_t i = 0; i < key.size(); i++) {
        if (key[i] > 'f' && key[i] < '0' && key[i] > 'F' && key[i] < 'A' && key[i] > '9') {
            i = key.size();
            return "Bad Key (not all hex digits)";

        }
    }
    if (val.compare("") == 0) return "Empty val";
    if (Nkeys == Keys.size() - 1) return "Hash table full";
    if (Find(key).compare("") == 0) return "Key already in table";

      else {
        string hash, ret;
        int hnum, iter;
        if (Fxn == 'L') { // Last7 hash function
        hash = Last7(key); // returns last7 hash
        hnum = read_as_hex(hash); // read hash as hex
        iter = collision_res(hnum, key, Coll, Keys, Fxn);
        if (Keys[iter].compare("") != 0) return "Cannot insert key";
        else {
        Keys[iter] = key;
        Vals[iter] = val;
        Nkeys++;

        return "";
        }
        }
        else { // Xor hash function
        hnum = Xor(key); // return xor hash
        iter = collision_res(hnum, key, Coll, Keys, Fxn); // collision resolution
        if (Keys[iter].compare("") != 0) return "Cannot insert key";
        else {
        Keys[iter] = key;
        Vals[iter] = val;
        Nkeys++;     
        return "";
        } 

        }
        }
}

string Hash_202::Find(const string &key) {
    /*  int index;
        bool searching = true;
        Nprobes = 0;
        for (size_t i = 0; i < key.size(); i++) { // characters are not hex digits
        if (key[i] > 'f' && key[i] < 0 && key[i] < 'a' && key[i] > 'F' && key[i] < 'A' && key[i] > '9') {
        i = key.size();
        return "";
        }
        }

        if (Keys.size() == 0) return ""; // hash table has not been set up
        else {
        if (Fxn == 'L') { // Last7 index
        string tmp = Last7(key);
        index = read_as_hex(tmp);
        }
        else if (Fxn == 'X') index = Xor(key); // Xor index

        if (Coll == 'L') { // Linear collision resolution strategy
        while (searching) { 
        if (Keys[index].compare(key) == 0) {
        return Vals[index];
        searching = 0;
        }
        else searching = false;        

        Nprobes++;
        }
        }
        else { // double hashing 
        bool searching = true;
        while (searching) {
        int iter = index;
        if (Fxn == 'L') {
        iter += Xor(key) * Nprobes % Keys.size();
        }
        else {
        iter += read_as_hex(Last7(key)) * Nprobes % Keys.size();
        }

        if (Keys[index].compare("") != 0 && iter == index) {
        searching = false;
        return "";
        }
        else if (Keys[iter].compare(key) == 0) {
        searching = false;
        return Vals[iter];
        }
        Nprobes++;
        }

        }
        }*/
}


void Hash_202::Print() const {
    /*  if (Keys.size() != 0) {
        for (size_t i = 0; i < Keys.size(); i++) {
        if (Keys[i].compare("") != 0) {
        printf("%5d %s %s", (int) i, Keys[i].c_str(), Vals[i].c_str());
        }  
        } 
        }*/
}

size_t Hash_202::Total_Probes() {
    /* size_t tprobes = 0;
       for (size_t i = 0; i < Keys.size(); i++) {
       if (Keys[i].compare("") != 0) {
       string tmp = Find(Keys[i]);
       tprobes += Nprobes;
       }
       }
       return tprobes;*/
}
