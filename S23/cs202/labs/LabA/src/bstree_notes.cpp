#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;

BSTree::BSTree()
{
  sentinel = new BSTNode;
  sentinel->left = NULL;
  sentinel->right = sentinel;
  sentinel->parent = NULL;
  sentinel->key = "---SENTINEL---";
  sentinel->val = NULL;
  size = 0;
}

bool BSTree::Insert(const string &key, void *val)
{
  BSTNode *parent;
  BSTNode *n;

  parent = sentinel;
  n = sentinel->right;

  /* Find where the key should go.  If you find the key, return false. */

  while (n != sentinel) {
    if (n->key == key) return false;
    parent = n;
    n = (key < n->key) ? n->left : n->right;
  }

  /* At this point, parent is the node that will be the parent of the new node.
     Create the new node, and hook it in. */

  n = new BSTNode;
  n->key = key;
  n->val = val;
  n->parent = parent;
  n->left = sentinel;
  n->right = sentinel;

  /* Use the correct pointer in the parent to point to the new node. */

  if (parent == sentinel) {
    sentinel->right = n;
  } else if (key < parent->key) {
    parent->left = n;
  } else {
    parent->right = n;
  }

  /* Increment the size and return success. */

  size++;
  return true;
}
    
/* This is a standard search on a binary search tree. */

void *BSTree::Find(const string &key) const
{
  BSTNode *n;

  n = sentinel->right;
  while (1) {
    if (n == sentinel) return NULL;
    if (key == n->key) return n->val;
    n = (key < n->key) ? n->left : n->right;
  }
}
          
bool BSTree::Delete(const string &key)
{
  BSTNode *n, *parent, *mlc;
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
  }

  return true;
}
               
/* Size and empty are trivial */

size_t BSTree::Size() const
{
  return size;
}

bool BSTree::Empty() const
{
  return (size == 0);
}


/* Print() simply calls recursive_inorder_print() on the root node of the tree. */

void BSTree::Print() const
{
  recursive_inorder_print(0, sentinel->right);
}
                                
/* This does an inorder traversal in reverse order.  The "Action" is printing "level" spaces,
   and then the key.  You increment the level by two when you make recursive calls. */

void BSTree::recursive_inorder_print(int level, const BSTNode *n) const
{
  if (n == sentinel) return;
  recursive_inorder_print(level+2, n->right);
  printf("%*s%s\n", level, "", n->key.c_str());
  recursive_inorder_print(level+2, n->left);
}
                
/* This simply calls make_val_vector() on the root.
   That creates the vector rv, so return it. */

vector <void *> BSTree::Ordered_Vals() const
{
  vector <void *> rv;
  make_val_vector(sentinel->right, rv);
  return rv;
}

/* This does an inorder traversal, which of course visits the nodes
   in sorted order of the keys.  The "action" is pushing the val onto the vector.
   That means that the vals get pushed in the correct order. */
                                       
void BSTree::make_val_vector(const BSTNode *n, vector<void *> &v) const
{
  if (n == sentinel) return;
  make_val_vector(n->left, v);
  v.push_back(n->val);
  make_val_vector(n->right, v);
}

/* Clear simply calls recursive_destroy on the root of the tree.
   That deletes all of the nodes but the sentinel.  It then sets
   the root of the tree to the sentinel and the size to 0. */

void BSTree::Clear()
{
  recursive_destroy(sentinel->right);
  sentinel->right = sentinel;
  size = 0;
}
                                      
/* Recursive destroy deletes all of the nodes of a tree.
   It does this with a postorder traversal -- deleting the
   children before deleting the node. */

void BSTree::recursive_destroy(BSTNode *n)
{
  if (n == sentinel) return;
  recursive_destroy(n->left);
  recursive_destroy(n->right);
  delete n;
}

/* The destructor calls Clear(), which deletes all of the tree but
   the sentinel node.  Therefore, it must also delete the sentinel node. */

BSTree::~BSTree()
{
  Clear();
  delete sentinel;
}

