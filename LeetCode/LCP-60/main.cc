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
        // init
        max = INT_MIN;
        memset(layers, 0, sizeof(layers));
        initLayers(root, 0);

        for (size_t l = 0; l < 100000; l++)
        {
            if (max < layers[l])
            {
                max = layers[l];
            }
        }
        


        return max;
    }

private:
    int max;
    int layers[100000];

    void initLayers(TreeNode * node, int ly)
    {
        if (node)
        {
            layers[ly] += node->val;

            if (node->left)
            {
                initLayers(node->left, ly + 1);
            }

            if (node->right)
            {
                initLayers(node->right, ly + 1);
            }
        }
    }
};

int main()
{
    TreeNode * root = NULL;

    Solution s;
    cout << s.getMaxLayerSum(root) << endl;

    return 0;
}
