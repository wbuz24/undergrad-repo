#include <vector>
#include <string>

namespace CS202 {

/* AVL Tree nodes are just like binary search tree nodes, but we maintain the height
   in each node. */

class AVLNode {
  public:
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;
    std::string key;
    void *val;
    size_t height;
};

class AVLTree {
  public:

    /* Constructor, copy constructor, assignment overlead, destructor.
       I am only implementing the constructor and destructor here in the notes.
       You will implement the other two in your lab. */

    AVLTree();
    AVLTree(const AVLTree &t);
    AVLTree& operator= (const AVLTree &t);
    ~AVLTree();

    void Clear();                                      // Turns the tree into an empty tree.
 
    bool Insert(const std::string &key, void *val);    // Insert the key and val.  Returns success (duplicates are not allowed.
    void *Find(const std::string &key) const;          // Return the val associated with the key.  Returns NULL if key not found.
    bool Delete(const std::string &key);               // Delete the node with the key.  Returns whether there was such a node.

    void Print() const;                                // These are obvious.
    size_t Size() const;
    bool Empty() const;
    size_t Height() const;
    std::string Is_AVL() const;                        // This double-checks to make sure that the tree is an AVL tree.
                                                       // It returns an empty string if it is, and an error string if it is not.

    std::vector <std::string> Ordered_Keys() const;    // Return a vector of sorted keys
    std::vector <void *> Ordered_Vals() const;         // Return a vector of the vals, sorted by the keys.

  protected:
    AVLNode *sentinel;                                 // Like the bstrees, there is a sentinel.  Its right points to the root.
    size_t size;                                       // Size of the tree

    void recursive_inorder_print(int level, const AVLNode *n) const;           // A helper for Print()
    void recursive_destroy(AVLNode *n);                                        // A helper for Clear()
    AVLNode *recursive_postorder_copy(const AVLNode *n) const;                 // A helper for the assignment overload
    void make_key_vector(const AVLNode *n, std::vector<std::string> &v) const; // A helper for Ordered_Keys()
    void make_val_vector(const AVLNode *n, std::vector<void *> &v) const;      // A helper for Ordered_Vals()
    std::string recursive_is_avl(const AVLNode *n) const;                      // A helper for Is_AVL()
};

};
