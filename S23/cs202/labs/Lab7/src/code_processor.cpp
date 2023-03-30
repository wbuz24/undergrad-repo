/* Will Buziak
 * Lab 7
 * cs202
 * Code Processing lab
 * implement a mock server that keeps track of rewards with web and cell phone support
 */
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "code_processor.hpp"
using namespace std;

unsigned int djb_hash(const string &s)
{ // djb_hash() function copied from random_codes.cpp
    size_t i;
    unsigned int h;

    h = 5381;

    for (i = 0; i < s.size(); i++) {
        h = (h << 5) + h + s[i];
    }
    return h;
}

bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity)
{
    if (Prizes.find(id) != Prizes.end()) return false;
    if (points <= 0) return false; // error checking
    if (quantity <= 0) return false;
    Prize *nprize = new Prize; // create a new prize instance
    nprize->id = id; // initialize prize parameters
    nprize->description = description;
    nprize->points = points;
    nprize->quantity = quantity;
    Prizes.insert(make_pair(id, nprize)); // insert into the map
    return true;
};

bool Code_Processor::New_User(const string &username, const string &realname, int starting_points)
{
    if (Names.find(username) != Names.end()) return false;  // error checking
    if (starting_points < 0) return false;
    User *newname = new User; // new class instance
    newname->username = username; // populate User member parameters
    newname->realname = realname;
    newname->points = starting_points;
    Names.insert(make_pair(username, newname)); // insert into the map
    return true;
};

bool Code_Processor::Delete_User(const string &username)
{
    if (Names.find(username) == Names.end()) return false;
    vector <string> phones;
    unordered_map<string, User*>::const_iterator nit = Names.find(username);
    set<string>::const_iterator sit;
    size_t i;

    for (sit = nit->second->phone_numbers.begin(); sit != nit->second->phone_numbers.end(); sit++) phones.push_back(*sit); // grabs every phone number
    delete nit->second;
    Names.erase(nit); // erase the user from Names
    for (i = 0; i < phones.size(); i++) Phones.erase(Phones.find(phones[i])); // erase all of the user's phones
    return true; 
};

bool Code_Processor::Add_Phone(const string &username, const string &phone)
{
    unordered_map<string, User*>::const_iterator nit;
    nit = Names.find(username);
    if (nit == Names.end()) return false; // searches for the name and ensures phone has not been added
    if (Phones.find(phone) != Phones.end()) return false;
    Phones.insert(make_pair(phone, nit->second)); // inserts into phone map
    nit->second->phone_numbers.insert(phone); // adds phone to users profile
    return true;
};

bool Code_Processor::Remove_Phone(const string &username, const string &phone)
{
    if (Names.find(username) == Names.end()) return false;
    unordered_map<string, User*>::const_iterator nit;
    set<string>::const_iterator sit;

    for (nit = Names.begin(); nit != Names.end(); nit++) { 
        if (nit->second->phone_numbers.find(phone) != nit->second->phone_numbers.end() && nit != Names.find(username)) return false; // phone number is regerstered with another user 
    }
    nit = Names.find(username);
    for (sit = nit->second->phone_numbers.begin(); sit != nit->second->phone_numbers.end(); sit++) {
        if (*sit == phone) { // if you find the number in the user's phone numbers, remove it
            nit->second->phone_numbers.erase(phone);
            //      delete Phones.find(phone)->second;
            Phones.erase(Phones.find(phone));
            return true;
        }
    }
    return false; 
};

string Code_Processor::Show_Phones(const string &username) const
{
    set<string>::const_iterator sit;
    unordered_map<string, User*>::const_iterator nit = Names.find(username);
    if (nit == Names.end()) return "BAD USER"; // user does not exist
    if (nit->second->phone_numbers.size() == 0) return ""; // no phones for that user
    string result = "";
    for (sit = nit->second->phone_numbers.begin(); sit != nit->second->phone_numbers.end(); sit++) {
        result += *sit + "\n"; // create string of phone numbers
    }
    return result; 
};

int Code_Processor::Enter_Code(const string &username, const string &code)
{
    if (Codes.find(code) != Codes.end()) return -1;
    if (Names.find(username) == Names.end()) return -1;
    unsigned int hash = djb_hash(code);
    if (hash % 13 != 0 && hash % 17 != 0) return 0; // check if code is valid
    Codes.insert(code); // insert into the set
    if (hash % 17 == 0) {   // increment points
        Names.find(username)->second->points += 10;
        return 10;
    }
    else { // increment user points
        Names.find(username)->second->points += 3;
        return 3;
    }
};

int Code_Processor::Text_Code(const string &phone, const string &code)
{
    if (Codes.find(code) != Codes.end()) return -1;
    if (Phones.find(phone) == Phones.end()) return -1;
    unsigned int hash = djb_hash(code);
    if (hash % 13 != 0 && hash % 17 != 0) return 0; // check if the code is valid
    Codes.insert(code); // insert into the set
    unordered_map<string, User*>::const_iterator nit = Phones.find(phone); // find the user from their phone
    if (hash % 17 == 0) { // increment the user's points
        Names.find(nit->second->username)->second->points += 10;
        return 10;
    }
    else {
        Names.find(nit->second->username)->second->points += 3;
        return 3;
    }
};

bool Code_Processor::Mark_Code_Used(const string &code)
{
    if (Codes.find(code) != Codes.end()) return false; 
    unsigned int hash = djb_hash(code);
    if (hash % 17 != 0 && hash % 13 != 0) return false;  // check if code is invalid
    Codes.insert(code); // insert into the set
    return true;
};

int Code_Processor::Balance(const string &username) const
{
    if (Names.find(username) == Names.end()) return -1;
    unordered_map <string, User*>::const_iterator nit;
    nit = Names.find(username); // find the user
    return nit->second->points;  
};

bool Code_Processor::Redeem_Prize(const string &username, const string &prize)
{
    if (Names.find(username) == Names.end()) return false;
    if (Prizes.find(prize) == Prizes.end()) return false;
    unordered_map<string, Prize*>::const_iterator nit = Prizes.find(prize); 
    if (nit->second->points > Names.find(username)->second->points) return false; // error checking
    Names.find(username)->second->points -= nit->second->points; // decrement the user's points by the reward value
    if (nit->second->quantity == 0) delete nit->second; // delete the prize if there aren't any left
    else nit->second->quantity--; // otherwise decrement the quantity
    return true;

};

Code_Processor::~Code_Processor()
{
    unordered_map<string, User*>::const_iterator nit;
    unordered_map<string, Prize*>::const_iterator pit;

    for (nit = Names.begin(); nit != Names.end(); nit++) delete nit->second;
    for (pit = Prizes.begin(); pit != Prizes.end(); pit++) delete pit->second; // delete all class instances from Prizes and Names
};

bool Code_Processor::Write(const string &filename) const
{
    ofstream ofile;
    ofile.open(filename);
    if (ofile.fail()) return false; 

    unordered_map<string, Prize*>::const_iterator it; // declare iterators
    unordered_map<string, User*>::const_iterator nit;
    set<string>::const_iterator sit;
    unordered_set<string>::const_iterator cit;

    for (it = Prizes.begin(); it != Prizes.end(); it++) { // ADD_PRIZES
        ofile << "PRIZE " << it->second->id << " " << it->second->points << " " <<  it->second->quantity << " " << it->second->description << "\n";
    }

    for (nit = Names.begin(); nit != Names.end(); nit++) { // ADD_USERS
        ofile << "ADD_USER " << nit->second->username << " " << nit->second->points << " " <<  nit->second->realname << "\n";
        for (sit = nit->second->phone_numbers.begin(); sit != nit->second->phone_numbers.end(); sit++) ofile << "ADD_PHONE " << nit->first << " " << *sit << "\n";

    }

    for (cit = Codes.begin(); cit != Codes.end(); cit++) { // MARK_USED
        ofile << "MARK_USED " << *cit << "\n";
    }
    return true;
};

