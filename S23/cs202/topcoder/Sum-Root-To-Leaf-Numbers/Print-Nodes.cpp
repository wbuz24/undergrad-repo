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
};

/* We're not going to solve the problem.  Instead, we're going to simply print
   out each node and the vals of its two children (-1 if the child is nullptr). */

int Solution::sumNumbers(TreeNode *root)
{
  printf("Node: %d   Left: %d    Right: %d\n", 
          root->val,
          (root->left == nullptr) ? -1 : root->left->val,
          (root->right == nullptr) ? -1 : root->right->val);
   
  if (root->left != nullptr) (void) sumNumbers(root->left);
  if (root->right != nullptr) (void) sumNumbers(root->right);
  return 0;
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


