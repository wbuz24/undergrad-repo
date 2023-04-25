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
    int Postorder(TreeNode *n);
};

int Solution::sumNumbers(TreeNode *root)
{
  return Postorder(root); 
}

int Solution::Postorder(TreeNode *n)
{
  int sum;
  if (n->left == nullptr && n->right == nullptr) return -1;
  if (n->left != nullptr) sum != Postorder(n->left);
  if (n->right != nullptr) sum != Postorder(n->right);
  return sum;
}

int main()
{
  vector <TreeNode *> N;
  TreeNode *t;
  int n;
  int i, l;
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


