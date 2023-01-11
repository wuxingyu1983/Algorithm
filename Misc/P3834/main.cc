#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define DEBUG 0

bool isOverlap(unsigned int l, unsigned int r, unsigned int idx)
{
    bool ret = true;

    if (r < idx || idx < l)
    {
        ret = false;
    }

    return ret;
}

class Node
{
public:
    unsigned int sum;
    Node * left, * right;

    // range
    unsigned int l, r;

    Node() 
    {
        sum = 0;
        l = r = 0;
        left = right = NULL;
    }

    Node(const Node &nod)
    {
        sum = nod.sum;
        l = nod.l;
        r = nod.r;
        left = nod.left;
        right = nod.right;
    }
};

Node * buildChairmanTree(unsigned int l, unsigned int r)
{
    Node *ret = new Node();
    ret->l = l;
    ret->r = r;
    if (l != r)
    {
        unsigned int mid = l + ((r - l) >> 1);
        ret->left = buildChairmanTree(l, mid);
        if (mid + 1 <= r)
        {
            ret->right = buildChairmanTree(mid + 1, r);
        }
    }

    return ret;
}

Node * updateChairmanTree(Node * pre, unsigned int idx, unsigned int increment)
{
    Node * ret = pre;

    if (isOverlap(pre->l, pre->r, idx))
    {
        ret = new Node(*pre);
        if (pre->left && isOverlap(pre->left->l, pre->left->r, idx))
        {
            ret->left = updateChairmanTree(pre->left, idx, increment);
        }

        if (pre->right && isOverlap(pre->right->l, pre->right->r, idx))
        {
            ret->right = updateChairmanTree(pre->right, idx, increment);
        }

        ret->sum += increment;
    }

    return ret;
}

unsigned int queryChairmanTree(Node * lower, Node * upper, unsigned int k)
{
    unsigned int ret = 0;

    if (lower->l == lower->r)
    {
        ret = lower->l;
        return ret;
    }

    unsigned int x = upper->left->sum - lower->left->sum;
    if (x >= k)
    {
        ret = queryChairmanTree(lower->left, upper->left, k);
    }
    else
    {
        ret = queryChairmanTree(lower->right, upper->right, k - x);
    } 

    return ret;
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, m;
#if DEBUG
    inFile >> n >> m;
#else
    cin >> n >> m;
#endif

    vector<int> inputs(n);
    vector<int> raw(n);

    for (size_t i_n = 0; i_n < n; i_n++)
    {
#if DEBUG
        inFile >> raw[i_n];
#else
        cin >> raw[i_n];
#endif
        inputs[i_n] = raw[i_n];
    }

    // sort
    sort(raw.begin(), raw.end());

    vector<int> nums;

    // duplicate removal
    for (vector<int>::iterator it = raw.begin(), pre = raw.end(); it != raw.end(); it ++)
    {
        if (pre == raw.end() || *pre != *it)
        {
            nums.push_back(*it);
        }

        pre = it; 
    }
    
    // build chairman tree
    Node * ch_tree = buildChairmanTree(0, nums.size() - 1); 

    // update chairman tree
    vector<Node *>roots(n);
    for (size_t i_n = 0; i_n < n; i_n++)
    {
        unsigned int idx = lower_bound(nums.begin(), nums.end(), inputs[i_n]) - nums.begin();
        if (0 == i_n)
        {
            roots[i_n] = updateChairmanTree(ch_tree, idx, 1);
        }
        else
        {
            roots[i_n] = updateChairmanTree(roots[i_n - 1], idx, 1);
        }
    }

    // query
    for (size_t i_m = 0; i_m < m; i_m++)
    {
        unsigned int l, r, k;
#if DEBUG
        inFile >> l >> r >> k;
#else
        cin >> l >> r >> k;
#endif

        l --;
        r --;
        unsigned int idx;
        if (0 == l)
        {
            idx = queryChairmanTree(ch_tree, roots[r], k);
        }
        else
        {
            idx = queryChairmanTree(roots[l - 1], roots[r], k);
        }

        cout << nums[idx] << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
