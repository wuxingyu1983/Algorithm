// https://codeforces.com/problemset/problem/165/E

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;

#define MAX_N 1000000
#define MAX_A 4000002

#define ST_BITS 1
#define ST_MASK 1

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

class Node
{
public:
    Node *ptr0;
    Node *ptr1;
    unsigned int val;

    Node()
    {
        ptr0 = NULL;
        ptr1 = NULL;
        val = 0;
    }
};

Node root;
int n;
vector<int> as;
int cmpNums[MAX_A];

int func(Node *curr, int a, int pos)
{
    int ret = -1;

    if (0 < curr->val)
    {
        ret = curr->val;
        return ret;
    }

    if (a < (1 << pos))
    {
        // 已经超过了 a 的最高位，找第一个符合要求的 val
        while ((ret = curr->val) == 0)
        {
            if (curr->ptr1)
            {
                curr = curr->ptr1;
            }
            else if (curr->ptr0)
            {
                curr = curr->ptr0;
            }
        }
    }
    else
    {
        if (getVal4St(a, pos, ST_BITS, ST_MASK))
        {
            // 1
            // 找 0 的路径
            if (curr->ptr0)
            {
                ret = func(curr->ptr0, a, pos + 1);
            }
        }
        else
        {
            // 0
            // 先找 1 的路径
            if (curr->ptr1)
            {
                ret = func(curr->ptr1, a, pos + 1);
            }

            // 再尝试 0 的路径
            if (0 > ret && curr->ptr0)
            {
                ret = func(curr->ptr0, a, pos + 1);
            }
        }
    }

    return ret;
}

int main()
{
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        as.push_back(a);
    }

    // init
    memset(cmpNums, 0, sizeof(cmpNums));

    // build tree
    for (size_t i = 0; i < n; i++)
    {
        int a = as[i];

        Node *curr = &root;
        for (size_t pos = 0; pos < 22; pos++)
        {
            if (getVal4St(a, pos, ST_BITS, ST_MASK))
            {
                // 1
                if (NULL == curr->ptr1)
                {
                    curr->ptr1 = new Node();
                }

                curr = curr->ptr1;

                if (a < (1 << (pos + 1)))
                {
                    // pos 已经是最高位了
                    curr->val = a;
                    break;
                }
            }
            else
            {
                // 0
                if (NULL == curr->ptr0)
                {
                    curr->ptr0 = new Node();
                }
                curr = curr->ptr0;
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        int a = as[i];
        if (0 == cmpNums[a])
        {
            cmpNums[a] = func(&root, a, 0);

            if (0 < cmpNums[a])
            {
                // 相互的
                cmpNums[cmpNums[a]] = a;
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        cout << cmpNums[as[i]] << ' ';
    }
    cout << endl;

    return 0;
}
