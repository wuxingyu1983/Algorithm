#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>

using namespace std;

/*
 * Definition for a binary tree node.
 */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    int getMaxLayerSum(TreeNode *root)
    {
        int ret = 0;

        return ret;
    }
};

int main()
{
    TreeNode * root = NULL;

    Solution s;
    cout << s.getMaxLayerSum(root) << endl;

    return 0;
}
