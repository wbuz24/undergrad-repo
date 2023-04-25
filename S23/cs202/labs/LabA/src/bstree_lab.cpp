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
  int depth = 0;
  BSTNode *n = sentinel;
  while (n->key != key) {
    if (n->left != NULL) {
      n = n->left; // only traverses to the left
      depth++;
    }
  }
  return depth;
}
           
int BSTree::Height() const
{
  return recursive_find_height(sentinel);
}

vector <string> BSTree::Ordered_Keys() const
{
  vector <string> rv;
  return rv;
}
    
BSTree::BSTree(const BSTree &t)        
{
  (void) t;
}

BSTree& BSTree::operator= (const BSTree &t) 
{
  (void) t;
  return *this;
}

int BSTree::recursive_find_height(const BSTNode *n) const
{
  if (n->left == NULL && n->right == NULL) return Depth(n->key) + 1; // depth of node with max depth plus one
  if (n->left != NULL) recursive_find_height(n->left);
  if (n->right != NULL) recursive_find_height(n->right);
}

void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const
{
  (void) n;
  (void) v;
}

BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, 
                            const vector<void *> &vals,
                            size_t first_index,
                            size_t num_indices) const
{
  (void) sorted_keys;
  (void) vals;
  (void) first_index;
  (void) num_indices;
  return NULL;
}
