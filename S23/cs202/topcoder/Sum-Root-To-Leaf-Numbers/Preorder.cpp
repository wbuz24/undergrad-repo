#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
  public:
    int sumNumbers(TreeNode *root);
    int Preorder(TreeNode *n, int parent_number);
};

/* This calls Preorder() on the root, and returns the solution: */

int Solution::sumNumbers(TreeNode *root)
{
  return Preorder(root, 0);
}

/* Here's the preorder traversal.  Calculate the node's number, and then either
   return it (if you have no children). Or sum the values of your children. */

int Solution::Preorder(TreeNode *n, int parent_number)
{
  int number, rv;

  /* Calculate the number and return it if you are a leaf node. */

  number = parent_number * 10 + n->val;
  if (n->left == nullptr && n->right == nullptr) return number;

  /* Otherwise, sum the numbers of your children and return that. */

  rv = 0;
  if (n->left != nullptr) rv += Preorder(n->left, number);
  if (n->right != nullptr) rv += Preorder(n->right, number);
  return rv;
}

int main()
{
  vector <TreeNode *> N;
  TreeNode *t;
  int n;
  int i, l, k;
  bool rv;
  Solution s;

  while (cin >> n) {
    if (n >= 0) {
      t = new TreeNode(n);
      N.push_back(t);
    } else {
      N.push_back(nullptr);
    }
  }
  k = n;

  for (i = 0; i < N.size(); i++) {
    if (N[i] != nullptr) {
      l = 2*i + 1;
      if (l < N.size()) N[i]->left = N[l];
      l++;
      if (l < N.size()) N[i]->right = N[l];
    }
  }

  cout << (s.sumNumbers(N[0])) << endl;
  return 0;
}


