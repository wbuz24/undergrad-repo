/* Will Buziak
 * CS202
 * LabB
 * AVL Trees
*/ 

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "avltree.hpp"
using namespace std;
using CS202::AVLTree;
using CS202::AVLNode;

AVLTree& AVLTree::operator= (const AVLTree &t)        
{
  this->sentinel = recursive_postorder_copy(t.sentinel->right);
  return *this;
}

/* I simply took Insert and Delete from their binary search tree
   implementations.  They aren't correct for AVL trees, but they are
   good starting points.  */

bool AVLTree::Insert(const string &key, void *val)
{
  AVLNode *parent;
  AVLNode *n;
  int l, r;
  // if (Is_Avl() != "") return 0;

  parent = sentinel;
  n = sentinel->right;

  /* Find where the key should go.  If you find the key, return false. */

  while (n != sentinel) {
    if (n->key == key) return false;
    parent = n;
    if (parent->left != sentinel && parent->right == sentinel) n = parent->right;
    else n = parent->left;
  }

  /* At this point, parent is the node that will be the parent of the new node.
     Create the new node, and hook it in. */

  n = new AVLNode;
  n->key = key;
  n->val = val;
  n->parent = parent;
  n->left = sentinel;
  n->right = sentinel;
  n->height = 1;
  /* Use the correct pointer in the parent to point to the new node. */

  if (parent == sentinel) {
    sentinel->right = n;
  } else if (key < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }

  // return back up the tree and adjust the heights
  while (n != sentinel) {
    l = 0, r = 0;
    if (n->left != sentinel) l = n->left->height;
    if (n->right != sentinel) r = n->right->height;
    n->height = (l > r) ? ++l : ++r;
    n = n->parent;
  }

  /* Increment the size */
  size++;
  return true;
}
    
bool AVLTree::Delete(const string &key)
{
  AVLNode *n, *parent, *mlc;
  string tmpkey;
  void *tmpval;

  /* Try to find the key -- if you can't return false. */

  n = sentinel->right;
  while (n != sentinel && key != n->key) {
    n = (key < n->key) ? n->left : n->right;
  }
  if (n == sentinel) return false;

  /* We go through the three cases for deletion, although it's a little
     different from the canonical explanation. */

  parent = n->parent;

  /* Case 1 - I have no left child.  Replace me with my right child.
     Note that this handles the case of having no children, too. */

  if (n->left == sentinel) {
    if (n == parent->left) {
      parent->left = n->right;
    } else {
      parent->right = n->right;
    }
    if (n->right != sentinel) n->right->parent = parent;
    delete n;
    size--;

  /* Case 2 - I have no right child.  Replace me with my left child. */

  } else if (n->right == sentinel) {
    if (n == parent->left) {
      parent->left = n->left;
    } else {
      parent->right = n->left;
    }
    n->left->parent = parent;
    delete n;
    size--;

  /* If I have two children, then find the node "before" me in the tree.
     That node will have no right child, so I can recursively delete it.
     When I'm done, I'll replace the key and val of n with the key and
     val of the deleted node.  You'll note that the recursive call 
     updates the size, so you don't have to do it here. */

  } else {
    for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
    tmpkey = mlc->key;
    tmpval = mlc->val;
    Delete(tmpkey);
    n->key = tmpkey;
    n->val = tmpval;
    return true;
  }

  return true;
}
               
/* You need to write these two.  You can lift them verbatim from your
   binary search tree lab. */

vector <string> AVLTree::Ordered_Keys() const
{
  vector <string> rv;
  make_key_vector(sentinel->right, rv); // recursize call
  return rv;
}
    
void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const
{
  if (n == sentinel) return; // base case
  make_key_vector(n->left, v); // left recursive call
  v.push_back(n->key); // action
  make_key_vector(n->right, v); // right recursive call
} 

size_t AVLTree::Height() const
{
  AVLNode *n = sentinel->right; // root node
  int height;

  height = n->height; // AVL trees store their height, therefore we just return the root node's height
  return height;
}

/* You need to write this to help you with the assignment overload.
   It makes a copy of the subtree rooted by n.  That subtree is part
   of a different tree -- the copy will be part of the tree that
   is calling the method. */

AVLNode *AVLTree::recursive_postorder_copy(const AVLNode *n) const
{
  if (n->left->height == 0) recursive_postorder_copy(n->left);
  if (n->right->height == 0) recursive_postorder_copy(n->right);
  
  // copy yourself
  AVLNode *copy = new AVLNode;

  copy->left = n->left;
  copy->right = n->right;
  copy->parent = n->parent;
  copy->key = n->key;
  copy->val = n->val;
  copy->height = n->height;
  return n->parent;
}
