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


bool imbalance(const AVLNode *n) {	
  int l = n->left->height, r = n->right->height;
	if (abs(l - r) > 1) return 0; // imbalance returns a false
	return 1;
}

void fix_height(AVLNode *n)
{
	if (n->height == 0) return;
	
  int nheight;
  // check which child is higher, and increment the value for the new height
  if (n->left->height > n->right->height) nheight = n->left->height;
  else nheight = n->right->height;
  nheight++;
  n->height = nheight;
}

void rotate(AVLNode *n) {
	if (n->height == 0) return;

	AVLNode *middle;
	AVLNode *parent = n->parent;
	AVLNode *grandparent = n->parent->parent;

	if (parent->left == n) { // left node rotate
		middle = n->right;
		parent->left = middle; // middle becomes parent's left
		n->right = parent; // my right is parent
	}

	else if (parent->right == n) { // right node rotate
		middle = n->left;
		parent->right = middle; // middle becomes parents right
		n->left = parent; // my left is parent
	}

  // fix parents and grandparents
	if (grandparent->left == n->parent) grandparent->left = n;
	else if (grandparent->right == n->parent) grandparent->right = n;
	n->parent = grandparent;
	parent->parent = n;
	middle->parent = parent;

	// fix heights
	fix_height(parent);
	fix_height(n);
}

void fix_imbalance(AVLNode *n) {
	if (n->left->height > n->right->height) { // left case
		if (n->left->right->height > n->left->left->height) rotate(n->left->right); // zig-zag
		
    rotate(n->left); // zig-zig
	}

	else if (n->right->height > n->left->height) { // right case
		if (n->right->left->height > n->right->right->height) rotate(n->right->left); // zig-zig

		rotate(n->right); // zig-zag
	}

}

AVLTree& AVLTree::operator= (const AVLTree &t) {
	Clear(); // clear the tree
	size = t.size; // copy the size
	sentinel->right = recursive_postorder_copy(t.sentinel->right); // recursive call
	sentinel->right->parent = sentinel; // set the parent
	return *this;
}

bool AVLTree::Insert(const string &key, void *val) {
	AVLNode *parent;
	AVLNode *n;

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

	n = new AVLNode;
	n->key = key;
	n->val = val;
	n->parent = parent;
	n->height = 1;
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

	
	while (n->parent != sentinel) { // postorder traversal
		n = n->parent;
		fix_height(n);
		if (imbalance(n) == 0) fix_imbalance(n);
	}
	/* Increment the size */
	size++;
	return true;
}

bool AVLTree::Delete(const string &key) {
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

	fix_height(parent);
	while (parent != sentinel) { // n has been deleted, so you must use the parent
		fix_height(parent);
		if (imbalance(parent) == 0) fix_imbalance(parent); // fix_imbalance fixes heights as well
		parent = parent->parent;
	}

	return true;
}

vector <string> AVLTree::Ordered_Keys() const {
	vector <string> rv;
	make_key_vector(sentinel->right, rv);
	return rv;
}

void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const {
	if (n != sentinel) {
		make_key_vector(n->left, v);
		v.push_back(n->key);
		make_key_vector(n->right, v);
	}
}

size_t AVLTree::Height() const {
	return sentinel->right->height;  
}

/* You need to write this to help you with the assignment overload.
   It makes a copy of the subtree rooted by n.  That subtree is part
   of a different tree -- the copy will be part of the tree that
   is calling the method. */

AVLNode *AVLTree::recursive_postorder_copy(const AVLNode *n) const {
	if (n->height == 0) return sentinel;
	AVLNode *copy = new AVLNode;

	copy->left = recursive_postorder_copy(n->left);
	copy->right = recursive_postorder_copy(n->right);

	copy->height = n->height;

	copy->key = n->key;
	copy->val = n->val;
	copy->left->parent = copy;
	copy->right->parent = copy;
	return copy;
}

