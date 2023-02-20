#pragma once 
#include <vector>
#include <string>

class Hash_202 {

  public:
    /* There is no constructor or destructor here.  This allows you to simple declare
       these as variables, and not worry about memory allocation. */

    /* You must call Set_Up() to set up the table before using it.  This method 
       takes the hash table size, a name of a hash function (either "Last7" or "XOR"), and
       the name of a collision resolution strategy (either "Linear" or "Double").  
 
       You should error check your input, and look for the following errors, in the following
       order.  If you see one of these errors, return the string specified:

       - Table already set up:                "Hash table already set up"
       - Bad table size:                      "Bad table size"
       - Bad hash function:                   "Bad hash function"
       - Bad collision resolution strategy:   "Bad collision resolution strategy" */

    std::string Set_Up(size_t table_size, const std::string &fxn, const std::string &collision);

    /* Add() adds the given key/val pair to the hash table.  If successful, it should return
       an empty string.  Add should test for the following errors, in this order,
       and return the given strings:

           - Table not set up:                "Hash table not set up"
           - Empty string for the key:        "Empty key"
           - Key not composed of hex digits:  "Bad key (not all hex digits)"
           - Empty string for the val:        "Empty val"
           - The hash table is full:          "Hash table full"
           - Cannot insert key:               "Cannot insert key"
           - The key is already in the table  "Key already in the table"
     */

    std::string Add(const std::string &key, const std::string &val);

    /* Find() returns the val associated with the given key.  If the hash table has not been 
       set up yet, or if the key is not in the hash table, or if the key is not composed of
       all hex digits, it should return an empty string. 

       Find() is not const, because it sets the variable Nprobes to equal the number of
       probes that it took to find the answer. */

    std::string Find(const std::string &key);

    /* Print() prints all non-empty slots in the hash table, one per line. 
       The index should be printed first, right justified and padded to five characters. 
       Then a space, the key, a space, and the val. This should do nothing if the hash
       table has not been set up yet. */

    void Print() const;

    /* Total_Probes() should traverse the hash table, and for every key, caculcate how many probes
       it takes find that key.  It should return the total number of probes.  It should
       return 0 if the hash table has not been set up yet.  It is not const, because it 
       uses Find() to find the number of probes for each key. */

    size_t Total_Probes();

  /* Obviously, you can use these however you want, but here is how I used them.  You may
     not modify or add to this header file, so you need to be able to implement the lab with
     just these member variables. */

  protected:
    std::vector <std::string> Keys;   // The hash table of keys.
    std::vector <std::string> Vals;   // The Vals[i] is the val associated with Keys[i]
    size_t Nkeys;                     // This is the number of keys that have been inserted.
    int Fxn;                          // The hash function.  I have 0 = "Xor" and 1 = "Last7".
    int Coll;                         // The collision resolution strategy.  'L' = Linear. 'D' = Double
    size_t Nprobes;                   // When I call Find(), I set this value to the number of probes.
};
