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

AVLTree::AVLTree()
{
  sentinel = new AVLNode;
  sentinel->left = NULL;
  sentinel->right = sentinel;
  sentinel->parent = NULL;
  sentinel->key = "---SENTINEL---";
  sentinel->val = NULL;
  sentinel->height = 0;
  size = 0;
}

AVLTree::AVLTree(const AVLTree &t)       
{
  sentinel = new AVLNode;
  sentinel->left = NULL;
  sentinel->right = sentinel;
  sentinel->parent = NULL;
  sentinel->key = "---SENTINEL---";
  sentinel->val = NULL;
  sentinel->height = 0;
  size = 0;
  *this = t;
}

void *AVLTree::Find(const string &key) const
{
  AVLNode *n;

  n = sentinel->right;
  while (1) {
    if (n == sentinel) return NULL;
    if (key == n->key) return n->val;
    n = (key < n->key) ? n->left : n->right;
  }
}
          
string AVLTree::Is_AVL() const
{
  return recursive_is_avl(sentinel->right);
}

string AVLTree::recursive_is_avl(const AVLNode *n) const
{
  ostringstream oss;
  string rv;

  if (n == sentinel) return "";

  if (n->height <= n->left->height || n->height <= n->right->height) {
    oss << "Node " << n->key 
        << "'s height is less than or equal at least one child's height.";
    return oss.str();
  }

  if (n->left->height+1 != n->height && n->right->height+1 != n->height) {
    oss << "Node " << n->key 
        << "'s height is not exactly one greater than at least one child's height.";
    return oss.str();
  }
  if (n->left->height+2 < n->height || n->right->height+2 < n->height) {
    oss << "Node " << n->key 
        << "'s height is more than two greater than at least one child's height.";
    return oss.str();
  }

  if (n->left->height+2 <= n->right->height || n->right->height+2 <= n->left->height) {
    oss << "Node " << n->key << "'s children's heights differ by more than one.";
    return oss.str();
  }

  rv = recursive_is_avl(n->left);
  if (rv != "") return rv;
  return recursive_is_avl(n->right);
}

size_t AVLTree::Size() const
{
  return size;
}

bool AVLTree::Empty() const
{
  return (size == 0);
}

/* Print() simply calls recursive_inorder_print() on the root node of the tree. */

void AVLTree::Print() const
{
  recursive_inorder_print(0, sentinel->right);
}
                                
/* This does an inorder traversal in reverse order.  The "Action" is printing "level" spaces,
   then the height, and then the key.  You increment the level by two when you 
   make recursive calls. */

void AVLTree::recursive_inorder_print(int level, const AVLNode *n) const
{
  if (n == sentinel) return;
  recursive_inorder_print(level+2, n->right);
  printf("%*s(%lu) %s\n", level, "", n->height, n->key.c_str());
  recursive_inorder_print(level+2, n->left);
}
                
/* This simply calls make_val_vector() on the root.
   That creates the vector rv, so return it. */

vector <void *> AVLTree::Ordered_Vals() const
{
  vector <void *> rv;
  make_val_vector(sentinel->right, rv);
  return rv;
}

/* This does an inorder traversal, which of course visits the nodes
   in sorted order of the keys.  The "action" is pushing the val onto the vector.
   That means that the vals get pushed in the correct order. */
                                       
void AVLTree::make_val_vector(const AVLNode *n, vector<void *> &v) const
{
  if (n == sentinel) return;
  make_val_vector(n->left, v);
  v.push_back(n->val);
  make_val_vector(n->right, v);
}

/* Clear simply calls recursive_destroy on the root of the tree.
   That deletes all of the nodes but the sentinel.  It then sets
   the root of the tree to the sentinel and the size to 0. */

void AVLTree::Clear()
{
  recursive_destroy(sentinel->right);
  sentinel->right = sentinel;
  size = 0;
}
                                      
/* Recursive destroy deletes all of the nodes of a tree.
   It does this with a postorder traversal -- deleting the
   children before deleting the node. */

void AVLTree::recursive_destroy(AVLNode *n)
{
  if (n == sentinel) return;
  recursive_destroy(n->left);
  recursive_destroy(n->right);
  delete n;
}

/* The destructor calls Clear(), which deletes all of the tree but
   the sentinel node.  Therefore, it must also delete the sentinel node. */

AVLTree::~AVLTree()
{
  Clear();
  delete sentinel;
}
