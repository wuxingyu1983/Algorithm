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

#define DEBUG 1
#define MAX_NM 100005

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
    Node *left, *right;

    // range
//    unsigned int l, r;

    Node()
    {
        sum = 0;
//        l = r = 0;
        left = right = NULL;
    }
};

void updateTree(Node &rot, int l, int r, int idx, int val)
{
    rot.sum += val;
    if (l != r)
    {
        unsigned int mid = l + ((r - l) >> 1);
        if (idx <= mid)
        {
            // left
            if (NULL == rot.left)
            {
                rot.left = new Node();
            }

            updateTree(*(rot.left), l, mid, idx, val);
        }
        else
        {
            // right
            if (NULL == rot.right)
            {
                rot.right = new Node();
            }

            updateTree(*(rot.right), mid + 1, r, idx, val);
        }
    }
}

// 树状数组
vector<Node> tree_arr(MAX_NM);

int lowbit(int x)
{
    return x & (-x);
}

void update(int n, int i_n, int len, int idx, int val)
{
    for (int i = i_n; i <= n; i += lowbit(i))
    {
        updateTree(tree_arr[i], 1, len, idx, val);
    }
}

int query(vector<Node *> &lower, vector<Node *> &upper, int l, int r, int k)
{
    int ret = 0;

    if (l == r)
    {
        return l;
    }

    int sum_l = 0;
    for (size_t i = 0; i < lower.size(); i++)
    {
        Node *nd = lower[i];
        if (nd->left)
        {
            sum_l += nd->left->sum;
        }
    }

    int sum_u = 0;
    for (size_t i = 0; i < upper.size(); i++)
    {
        Node *nd = upper[i];
        if (nd->left)
        {
            sum_u += nd->left->sum;
        }
    }

    unsigned int mid = l + ((r - l) >> 1);
    unsigned int x = sum_u - sum_l;
    if (x >= k)
    {
        // left
        vector<Node *> l_left;
        for (size_t i = 0; i < lower.size(); i++)
        {
            Node *nd = lower[i];
            if (nd->left)
            {
                l_left.push_back(nd->left);
            }
        }

        vector<Node *> u_left;
        for (size_t i = 0; i < upper.size(); i++)
        {
            Node *nd = upper[i];
            if (nd->left)
            {
                u_left.push_back(nd->left);
            }
        }

        ret = query(l_left, u_left, l, mid, k);
    }
    else
    {
        // right
        vector<Node *> l_right;
        for (size_t i = 0; i < lower.size(); i++)
        {
            Node *nd = lower[i];
            if (nd->right)
            {
                l_right.push_back(nd->right);
            }
        }

        vector<Node *> u_right;
        for (size_t i = 0; i < upper.size(); i++)
        {
            Node *nd = upper[i];
            if (nd->right)
            {
                u_right.push_back(nd->right);
            }
        }

        ret = query(l_right, u_right, mid + 1, r, k - x);
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
        update(n, i, len, idx, 1);
    }

    for (size_t i = 0; i < m; i++)
    {
        if ('C' == ops[i].op)
        {
            int x = inputs[ops[i].x];
            if (x != ops[i].y)
            {
                int idx = lower_bound(as.begin(), as.begin() + len + 1, x) - as.begin();
                update(n, ops[i].x, len, idx, -1);

                idx = lower_bound(as.begin(), as.begin() + len + 1, ops[i].y) - as.begin();
                update(n, ops[i].x, len, idx, 1);

                inputs[ops[i].x] = ops[i].y;
            }
        }
        else
        {
            // Q
            vector<Node *> ql;
            vector<Node *> qr;

            if (1 < ops[i].l)
            {
                for (int i_l = ops[i].l - 1; i_l > 0; i_l -= lowbit(i_l))
                {
                    ql.push_back(&(tree_arr[i_l]));
                }
            }

            for (int i_r = ops[i].r; i_r > 0; i_r -= lowbit(i_r))
            {
                qr.push_back(&(tree_arr[i_r]));
            }

            int rt_idx = query(ql, qr, 1, len, ops[i].k);

            cout << as[rt_idx] << endl;
        }
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
