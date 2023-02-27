/* Will Buziak
 * Lab 4
 * Hashing lab
 * cs202
*/


#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
#include "hash_202.hpp"
#include <cstdio>
using namespace std;

int read_as_hex (const string &key) { // returns an int from the hex key
    istringstream ss;
    int result;

    ss.clear();
    ss.str(key);
    ss >> hex >> result; 
    return result;
}

int Last7(const string &key) {
    string key7 = "";
    size_t i;

    if (key.size() > 7) {
        for (i = key.size() - 7; i < key.size(); i++) {
            key7 += key[i];
        }
    }
    else {
        for (i = 0; i < key.size(); i++) {
            key7 += key[i];
        }
    }

    return read_as_hex(key7);
}

int Xor(const string &key) {
    size_t i = 0, j = 0;
    vector <string> vec;
    int hnum1, hnum2;
    string tmp = "";

    for (; i < key.size(); i++) {

        if (tmp.size() == 7) {
            vec.push_back(tmp);
            tmp = "";
        }
        tmp += key[i];
    }

    if (tmp.size() > 0) vec.push_back(tmp);

    hnum1 = 0;
    for (; j < vec.size(); j++) {
        hnum2 = read_as_hex(vec[j]);
        hnum1 = hnum1 ^ hnum2;
    }
    return hnum1;
}

int collision_res(const int &hnum, const string &key, const int &Coll, const vector <string> &Keys, const int &Fxn) {
    int iter = hnum % Keys.size(); // base is hex # mod table size
    //cout << "Coll res begin" << endl;
    if (Coll == 'L') { // Linear probing
        while (Keys[iter].compare("") != 0) { // while not empty
            iter = (iter + 1) % Keys.size(); // increment by one and mod with table size
        }
        //cout << "Coll res ends with linear probing" << endl;
        return iter;
    }

    else { // double hashing
        size_t i = 1, tmp;
        while (true) {
            if (Keys[iter].compare("") == 0) { // if empty space found, close loop
                break;
            }
            else { 
                if (Fxn == 'L') { // if original hash fxn is Last7
                    tmp = Xor(key); // Xor hash
                    if (tmp == 0 || tmp % Keys.size() == 0) tmp = 1; // if second hash fxn is 0, make it 1
                    iter = (iter + tmp) % Keys.size(); // increment base by hash * i mod with table size
                }
                else { 
                    tmp = Last7(key); // if original hash fxn is Xor, find Last7 hash
                    if (tmp == 0 ||tmp % Keys.size() == 0) tmp = 1; // correct second hash fxn if 0
                    // cout << tmp << " " << Keys.size() << " " << iter << " " << key << endl;
                    iter = (iter + tmp) % Keys.size(); // increment by hash * i mod by table size        
                }
            }
            if ( iter == (hnum % Keys.size())) {
                iter = -1;
                break;
            }
            i++;
        }
        //cout << "Coll Res ends" << endl;

        return iter;     
    }
}

string Hash_202::Set_Up(size_t table_size, const string &fxn, const string &collision) {
    if (Keys.size() > 0) return "Hash table already set up";
    else if (table_size == 0) return "Bad table size";
    else if (fxn.compare("Last7") !=0 && fxn.compare("XOR") != 0) return "Bad hash function";
    else if (collision.compare("Linear") != 0 && collision.compare("Double") != 0) return "Bad collision resolution strategy";

    else {
        Keys.resize(table_size, "");
        Vals.resize(table_size, "");
        Nkeys = 0;

        if (fxn.compare("Last7") == 0) Fxn = 'L';
        else Fxn = 'X';

        if (collision.compare("Linear") == 0) Coll = 'L';
        else Coll = 'D';

        return "";
    }
}

string Hash_202::Add(const string &key, const string &val) {
    if (Keys.size() == 0) return "Hash table not set up";
    if (key.compare("") == 0) return "Empty key";
    for (size_t i = 0; i < key.size(); i++) { // characters are not hex digits
        if (isxdigit((int) key[i]) == 0) {
            i = key.size();
            return "Bad key (not all hex digits)";
        }
    }
    if (val.compare("") == 0) return "Empty val";
    if (Nkeys == Keys.size()) return "Hash table full";

    else {
        string hash;
        int hnum, iter;

        if (Fxn == 'L') { // Add with Last7

            hnum = Last7(key);
            iter = collision_res(hnum, key, Coll, Keys, Fxn);
            if (iter == -1) return "Cannot insert key";
            if (Keys[iter].compare(key) == 0) return "Key already in the table";
            else {
                Keys[iter] = key;
                Vals[iter] = val;
                Nkeys++;
                return "";
            }
        }
        else { // Xor
            hnum = Xor(key);

            iter = collision_res(hnum, key, Coll, Keys, Fxn);

            if (iter == -1) return "Cannot insert key";
            if (Keys[iter].compare(key) == 0) return "Key already in the table";

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
    int index, tmp;
    //cout << "Find starts" << endl;

    Nprobes = 0;
    string ret;
    for (size_t i = 0; i < key.size(); i++) { // characters are not hex digits
        if (isxdigit((int) key[i]) == 0) {
            i = key.size();
            return "";
        }
    }
    
    if (Keys.size() ==  0) ret = "";
    else { // hash table has been set up
        if (Fxn == 'L') { // Last7 index
            index = Last7(key) % Keys.size();
        }
        else if (Fxn == 'X') index = Xor(key) % Keys.size(); // Xor index

        if (Coll == 'L') { // Linear collision resolution strategy
            tmp = index;
            Nprobes = 0;
            while (true) { 
                if (Keys[index % Keys.size()].compare(key) == 0) { // find key
                    ret = Vals[index % Keys.size()];
                    break;
                }
                else {
                    Nprobes++;
                    index = (index + 1) % Keys.size();
                    if (index == tmp && Keys[index].compare(key) != 0) { // back to beginning & can't find key
                        ret = "";
                        break;
                    } 
                }
            }
            return ret;
        }
        else { // double hashing 
            Nprobes = 0;
            int iter = index; // index == base
            while (true) {
                if (Keys[iter].compare(key) == 0) { // if key is found
                    ret = Vals[iter]; // return value at index
                    break;
                }

                if (Fxn == 'L') { // Last7 hash function
                    tmp = Xor(key); // calls XOR as second hash
                    if (tmp == 0 || tmp % Keys.size() == 0) tmp = 1; // catch second hash % table_size == 0
                    iter = (iter + tmp) % Keys.size(); // increment iter
                    Nprobes++;
                    //                    cout << Nprobes << " " << iter << " " << Vals[iter] << endl;
                }
                else {
                    tmp = Last7(key); // XOR hash function calls Last7 for second hash
                    if (tmp == 0 || tmp % Keys.size() == 0) tmp = 1;
                    iter = (tmp + iter) % Keys.size(); // increment index
                    Nprobes++;
                    //                  cout << Nprobes << " " << iter << " " << Vals[iter] << endl;
                }

                if (iter == index ) { // if index == base, break and return
                    ret = "";
                    break;
                }
            }
            //cout << "Find ends" << endl;
        }
    }
    return ret;
}



void Hash_202::Print() const {
    if (Keys.size() > 0) {
        for (size_t i = 0; i < Keys.size(); i++) {
            if (Keys[i].compare("") != 0) {
                printf("%5d %s %s\n", (int) i, Keys[i].c_str(), Vals[i].c_str());
            }  
        } 
    }
}

size_t Hash_202::Total_Probes() {
    size_t tprobes = 0;
    for (size_t i = 0; i < Keys.size(); i++) {
        if (Keys[i].compare("") != 0) {
            string tmp = Find(Keys[i]);
            tprobes += Nprobes;
        }
    }
    return tprobes;
}
