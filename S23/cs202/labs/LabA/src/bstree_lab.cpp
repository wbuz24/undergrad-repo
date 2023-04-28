#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;

/* ---------------------------------------------- */
/* Will Buziak
 * CS202 
 * Lab 9 A
 * Binary search tree
 *
*/

int BSTree::Depth(const string &key) const
{
  if (Find(key) == NULL) return -1; // key is not in the tree
  
  int depth = -1; // start at sentinel
  BSTNode *n;
  n = sentinel;

  while (1) { // continue to search for the key
    if (key == n->key) return depth;
    depth++;
    n = (key < n->key) ? n->left : n->right;
  }
}
           
int BSTree::Height() const
{
  return recursive_find_height(sentinel);
}

vector <string> BSTree::Ordered_Keys() const
{
  vector <string> rv;
  make_key_vector(sentinel->right, rv); // recursive call
  return rv;
}
    
BSTree::BSTree(const BSTree &t)
{
  sentinel = new BSTNode; // create a new sentinel
  sentinel->val = NULL; // set sentinel's values
  sentinel->key = "---SENTINEL---";
  sentinel->left = NULL;
  sentinel->parent = NULL;
  vector <string> ks = t.Ordered_Keys(); // create an ordered vector of keys
  vector <void*> vs = t.Ordered_Vals(); // create an ordered vector of vals
  sentinel->right = make_balanced_tree(ks, vs, 0, t.Size()); // create a balanced tree
  size = t.Size();
}


BSTree& BSTree::operator= (const BSTree &t) 
{
  Clear();
  vector <string> ks = t.Ordered_Keys(); // create an ordered vector of keys
  vector <void*> vs = t.Ordered_Vals(); // create an ordered vector of vals
  sentinel->right = make_balanced_tree(ks, vs, 0, t.Size()); // create a balanced tree
  size = t.Size();

  return *this;
}

int BSTree::recursive_find_height(const BSTNode *n) const
{
  int left = 0, right = 0;
  if (n->left == sentinel && n->right == sentinel) return Depth(n->key) + 1; // base case
  if (n->left != sentinel && n->left != NULL) left = recursive_find_height(n->left); // left call
  if (n->right != sentinel && n->right != NULL) right =  recursive_find_height(n->right); // right recursive call
  if (left > right) return left;
  return right;
}

void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const
{
  if (n == sentinel) return; // base case
  make_key_vector(n->left, v); // left recursive call
  v.push_back(n->key); // action
  make_key_vector(n->right, v); // right recursive call
}

BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, 
                            const vector<void *> &vals,
                            size_t first_index,
                            size_t num_indices) const
{
  if (num_indices == 0) return sentinel;
  
  size_t index = num_indices / 2; // index
  // if (index % 2 == 0) index++; // check if even or odd
  
  BSTNode *l = new BSTNode; // create parent node

  l->key = sorted_keys[index + first_index];
  l->val = vals[index + first_index]; // set values

  l->left = make_balanced_tree(sorted_keys, vals, first_index, index); // recursive calls
  l->right = make_balanced_tree(sorted_keys, vals, (index + first_index) + 1, num_indices - (index + 1));
  
  l->left->parent = l; // set the parent nodes
  l->right->parent = l;

  return l;
}
