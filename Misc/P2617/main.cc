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

#define DEBUG   0
#define MAX_NM  100005

class Op
{
public:
    char op;

    int l, r, k;
    int x, y;

    Op()
    {
        op = 0;
        l = r = k = 0;
        x = y = 0;
    }
};

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
};

void updateTree(Node &rot, int idx, int val)
{
    rot.sum += val;
    if (rot.l != rot.r)
    {
        unsigned int mid = rot.l + ((rot.r - rot.l) >> 1);
        if (idx <= mid)
        {
            // left
            if (NULL == rot.left)
            {
                rot.left = new Node();
                rot.left->l = rot.l;
                rot.left->r= mid;
            }

            updateTree(*(rot.left), idx, val);
        }
        else
        {
            // right
            if (NULL == rot.right)
            {
                rot.right = new Node();
                rot.right->l = mid + 1;
                rot.right->r= rot.r;
            }

            updateTree(*(rot.right), idx, val);
        }
    }
}

// 树状数组
vector<Node> tree_arr(MAX_NM);

int lowbit(int x)
{
    return x & (-x);
}

void update(int n, int len, int idx, int val)
{
    for (int i = idx; i <= n; i += lowbit(i))
    {
        // update tree
//        tr[i] += val;
        if (0 == tree_arr[i].l && 0 == tree_arr[i].r)
        {
            // init
            tree_arr[i].l = 1;
            tree_arr[i].r = len;
        }
    }
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

    vector<int> inputs;
    vector<int> as;

    inputs.push_back(-1);
    as.push_back(-1);

    for (size_t i = 1; i <= n; i++)
    {
        int a;
#if DEBUG
        inFile >> a;
#else
        cin >> a;
#endif
        inputs.push_back(a);
        as.push_back(a);
    }

    vector<Op> ops(m);
    for (size_t i = 0; i < m; i++)
    {
        char op;
#if DEBUG
        inFile >> op;
#else
        cin >> op;
#endif

        ops[i].op = op;

        if ('C' == op)
        {
            int x, y;
#if DEBUG
            inFile >> x >> y;
#else
            cin >> x >> y;
#endif
            ops[i].x = x;
            ops[i].y = y;
            as.push_back(y);
        }
        else
        {
            // Q
            int l, r, k;
#if DEBUG
            inFile >> l >> r >> k;
#else
            cin >> l >> r >> k;
#endif
            ops[i].l = l;
            ops[i].r = r;
            ops[i].k = k;
        }
    }

    sort(as.begin(), as.end());

    unsigned int len = unique(as.begin(), as.end()) - as.begin() - 1;

    // build
    for (size_t i = 1; i <= n; i++)
    {
        int idx = lower_bound(as.begin(), as.begin() + len + 1, inputs[i]) - as.begin();
        update(n, len, idx, 1);
    }

    for (size_t i = 0; i < m; i++)
    {
        if ('C' == ops[i].op)
        {
            int x = inputs[ops[i].x];
            if (x != ops[i].y)
            {
                int idx = lower_bound(as.begin(), as.begin() + len + 1, x) - as.begin();
                update(n, len, idx, -1);

                idx = lower_bound(as.begin(), as.begin() + len + 1, y) - as.begin();
                update(n, len, idx, 1);
            }
        }
        else
        {
            // Q
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
