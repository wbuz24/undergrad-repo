/* BSTrees are binary search trees. */

#include <vector>
#include <string>

namespace CS202 {

/* These are the nodes of a tree. The keys are strings, and the vals are generic pointers.
   Please see the lecture notes for a more thorough explanation of what a (void *) is. */

class BSTNode {
  friend class BSTree;
  protected:
    BSTNode *left;
    BSTNode *right;
    BSTNode *parent;
    std::string key;
    void *val;
};

class BSTree {
  public:

    /* Constructor, copy constructor, assignment overlead, destructor.
       I am only implementing the constructor and destructor here in the notes.
       You will implement the other two in your lab. */

    BSTree();
    BSTree(const BSTree &t);
    BSTree& operator= (const BSTree &t);
    ~BSTree();

    void Clear();                                      // Turns the tree into an empty tree.
    void Print() const;                                // These are obvious.
    size_t Size() const;
    bool Empty() const;
 
    bool Insert(const std::string &key, void *val);    // Insert the key and val.  Returns success (duplicates are not allowed.
    void *Find(const std::string &key) const;          // Return the val associated with the key.  Returns NULL if key not found.
    bool Delete(const std::string &key);               // Delete the node with the key.  Returns whether there was such a node.

    std::vector <std::string> Ordered_Keys() const;    // Return a vector of sorted keys
    std::vector <void *> Ordered_Vals() const;         // Return a vector of the vals, sorted by the keys.

    /* You'll write these as part of your lab. */

    int Depth(const std::string &key) const;           // Distance from a node to the root.  Returns -1 if the key is not in the tree.
    int Height() const;                                // Returns the depth of the node with maximum depth, plus one.

  protected:
    BSTNode *sentinel;                                 // Like the dlists, there is a sentinel.  Its right points to the root.
    size_t size;                                       // Size of the tree
   
    void recursive_inorder_print(int level, const BSTNode *n) const;          // A helper for Print()
    void recursive_destroy(BSTNode *n);                                       // A helper for Clear()
    void make_val_vector(const BSTNode *n, std::vector<void *> &v) const;     // A helper for Ordered_Vals()

    /* You'll write these as part of your lab. */

    int recursive_find_height(const BSTNode *n) const;                        // A helper for Height()
    void make_key_vector(const BSTNode *n, std::vector<std::string> &v) const; // A helper for Ordered_Keys()
    BSTNode *make_balanced_tree(const std::vector<std::string> &sorted_keys,   // A helper for the copy constructor and assignment overload.
                                const std::vector<void *> &vals,
                                size_t first_index,
                                size_t num_indices) const;
};

};
