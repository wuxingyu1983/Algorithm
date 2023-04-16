// https://www.luogu.com.cn/problem/P4103
// Virtual Tree : https://oi-wiki.org/graph/virtual-tree/
// LCA : https://cp-algorithms.com/graph/lca.html#the-idea-of-the-algorithm
// Segment Tree : https://oi-wiki.org/ds/seg/

#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
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

using namespace std;

#define DEBUG   0
#define MAX_N   1000001

unsigned int n;
vector< vector<unsigned int> > roads(MAX_N);
vector<unsigned int> path(2 * MAX_N);            // path island index
vector<unsigned int> heights(2 * MAX_N * 4);     // path island height, segment tree
vector<unsigned int> lazyheights(2 * MAX_N * 4); // path island height, segment tree
vector<unsigned int> firsInPath(MAX_N);          // first in path
vector< vector<unsigned int> > hIdx(MAX_N);

unsigned int flags[MAX_N];
unsigned int dpMax[MAX_N];
unsigned int dpMin[MAX_N];
unsigned long long dpSum[MAX_N];

class Node
{
public:
    unsigned int idx;
    unsigned int depth;
    unsigned int flag;
    unsigned int dfs;
    unsigned int cnt;   // count of key node

    vector<unsigned int> children;

    Node()
    {
        idx = depth = flag = dfs = cnt = 0;
    }

    Node(unsigned int _idx, unsigned int _depth)
        : idx(_idx), depth(_depth)
    {
        flag = dfs = cnt = 0;
    }
};

Node nodes[MAX_N];

// segment tree func
void update(vector<unsigned int> &d, vector<unsigned int> &b, int l, int r, unsigned int c, int s, int t, int p)
{
    if (l <= s && t <= r)
    {
        d[p] += (t - s + 1) * c, b[p] += c;
        return;
    }
    int m = s + ((t - s) >> 1);
    if (b[p] && s != t)
    {
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];
        b[p] = 0;
    }
    if (l <= m)
        update(d, b, l, r, c, s, m, p * 2);
    if (r > m)
        update(d, b, l, r, c, m + 1, t, p * 2 + 1);
    if (d[p * 2] < d[p * 2 + 1])
        d[p] = d[p * 2];
    else
        d[p] = d[p * 2 + 1];
}

unsigned int getMin(vector<unsigned int> &d, vector<unsigned int> &b, int l, int r, int s, int t, int p)
{
    if (l <= s && t <= r)
    {
        return d[p];
    }
    int m = s + ((t - s) >> 1);
    if (b[p])
    {
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];
        b[p] = 0;
    }
    unsigned int min = MAX_N;
    if (l <= m)
    {
        min = getMin(d, b, l, r, s, m, p * 2);
    }
    if (r > m)
    {
        unsigned int tmp = getMin(d, b, l, r, m + 1, t, p * 2 + 1);
        if (tmp < min)
        {
            min = tmp;
        }
    }
    return min;
}

void buildPath(unsigned int node, unsigned int parent, unsigned int depth, unsigned int &idx)
{
    // fist access
    nodes[node].idx = node;
    nodes[node].depth = depth;
    firsInPath[node] = idx;
    nodes[node].dfs = idx;
    path[idx] = node;
    hIdx[depth].push_back(idx);

    // update depth
    update(heights, lazyheights, idx, idx, depth, 1, 2 * n - 1, 1);

    for (vector<unsigned int>::iterator it = roads[node].begin(); it != roads[node].end(); it++)
    {
        if (parent != *it)
        {
            buildPath(*it, node, depth + 1, ++idx);

            path[++idx] = node;
            hIdx[depth].push_back(idx);

            // update depth
            update(heights, lazyheights, idx, idx, depth, 1, 2 * n - 1, 1);
        }
    }
}

inline bool cmp(Node *x, Node *y)
{
    return x->dfs < y->dfs;
}

unsigned int getLca(unsigned int x, unsigned int y)
{
    unsigned int l = firsInPath[x];
    unsigned int r = firsInPath[y];

    if (l > r)
    {
        swap(l, r);
    }

    unsigned int minDepth = getMin(heights, lazyheights, l, r, 1, 2 * n - 1, 1);
    vector<unsigned int>::iterator idx = lower_bound(hIdx[minDepth].begin(), hIdx[minDepth].end(), l);

    return path[*idx];
}


vector<unsigned int> stk(MAX_N, 0);
vector<Node *> tmps(MAX_N, NULL);

unsigned int minDep[MAX_N];
unsigned int maxDep[MAX_N];

void dpFunc(unsigned int idx, int m)
{
    if (m == flags[idx])
    {
        // key node
        nodes[idx].cnt = 1;
        minDep[idx] = nodes[idx].depth;
        maxDep[idx] = nodes[idx].depth;
    }
    else
    {
        nodes[idx].cnt = 0;
        minDep[idx] = 0;
        maxDep[idx] = 0;
    }

    for (vector<unsigned int>::iterator it = nodes[idx].children.begin(); it != nodes[idx].children.end(); it++)
    {
        dpFunc(*it, m);

        // max
        if (dpMax[idx] < dpMax[*it])
        {
            dpMax[idx] = dpMax[*it];
        }

        if (0 == maxDep[idx])
        {
            maxDep[idx] = maxDep[*it];
        }
        else
        {
            unsigned int tmp = (maxDep[idx] - nodes[idx].depth) + (maxDep[*it] - nodes[idx].depth);
            if (tmp > dpMax[idx])
            {
                dpMax[idx] = tmp;
            }

            if (maxDep[*it] > maxDep[idx])
            {
                maxDep[idx] = maxDep[*it];
            }
        }

        // min
        if (dpMin[idx] > dpMin[*it])
        {
            dpMin[idx] = dpMin[*it];
        }

        if (m == flags[idx])
        {
            // key node
            unsigned int tmp = minDep[*it] - minDep[idx];
            if (tmp < dpMin[idx])
            {
                dpMin[idx] = tmp;
            }
        }
        else
        {
            if (0 == minDep[idx])
            {
                minDep[idx] = minDep[*it];
            }
            else
            {
                unsigned int tmp = (minDep[idx] - nodes[idx].depth) + (minDep[*it] - nodes[idx].depth);
                if (tmp < dpMin[idx])
                {
                    dpMin[idx] = tmp;
                }

                if (minDep[*it] < minDep[idx])
                {
                    minDep[idx] = minDep[*it];
                }
            }
        }

        // sum
    }
}

unsigned int root = 1;

void func(vector<unsigned int> &hs, int k, int m)
{
    // sort by dfs
    for (size_t i = 0; i < k; i++)
    {
        nodes[hs[i]].flag = m;
        nodes[hs[i]].children.clear();
        tmps[i] = &(nodes[hs[i]]);

        flags[hs[i]] = m;   // key node

        dpMin[hs[i]] = MAX_N * 2;
        dpMax[hs[i]] = 0;
        dpSum[hs[i]] = 0;
    }

    sort(tmps.begin(), tmps.begin() + k, cmp);

    // build virtual tree
    int top = 0;
    stk[top] = root; // push node 1 first
    nodes[root].children.clear();
    nodes[root].flag = m;
    dpMin[root] = MAX_N * 2;
    dpMax[root] = 0;
    dpSum[root] = 0;

    for (size_t i = 0; i < k; i++)
    {
        if (1 == tmps[i]->idx)
        {
            continue;
        }
        
        unsigned int lca = getLca(tmps[i]->idx, stk[top]);

        if (lca == stk[top])
        {
            // push to stack
            stk[++top] = tmps[i]->idx;
            if (m != nodes[tmps[i]->idx].flag)
            {
                nodes[tmps[i]->idx].flag = m;
                nodes[tmps[i]->idx].children.clear();

                dpMin[tmps[i]->idx] = MAX_N * 2;
                dpMax[tmps[i]->idx] = 0;
                dpSum[tmps[i]->idx] = 0;
            }
        }
        else
        {
            while (nodes[lca].dfs < nodes[stk[top - 1]].dfs)
            {
                // connect stk[top] and stk[top - 1]
                nodes[stk[top - 1]].children.push_back(stk[top]);

                // pop from stack;
                top--;
            }

            if (nodes[lca].dfs > nodes[stk[top - 1]].dfs)
            {
                // connect lca and stk[top]
                if (m != nodes[lca].flag)
                {
                    nodes[lca].flag = m;
                    nodes[lca].children.clear();

                    dpMin[lca] = MAX_N * 2;
                    dpMax[lca] = 0;
                    dpSum[lca] = 0;
                }
                nodes[lca].children.push_back(stk[top]);

                // pop
                top--;

                stk[++top] = lca;

                stk[++top] = tmps[i]->idx;
            }
            else
            {
                // ==
                // connect stk[top] and stk[top - 1]
                nodes[stk[top - 1]].children.push_back(stk[top]);

                // pop from stack;
                top--;

                stk[++top] = tmps[i]->idx;
            }
        }
    }

    while (0 < top)
    {
        // conect stk[top] and stk[top - 1]
        nodes[stk[top - 1]].children.push_back(stk[top]);

        top--;
    }

    // dp
    dpFunc(root, m);

    printf("%llu %u %u\n", dpSum[root], dpMin[root], dpMax[root]);
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif

#if DEBUG
    fscanf(fp, "%u", &n);
#else
    scanf("%u", &n);
#endif

    for (size_t i = 0; i < n - 1; i++)
    {
        unsigned int a, b;
#if DEBUG
        fscanf(fp, "%u %u", &a, &b);
#else
        scanf("%u %u", &a, &b);
#endif

        roads[a].push_back(b);
        roads[b].push_back(a);
    }

    unsigned int idxInPath = 1;
    buildPath(1, 0, 1, idxInPath);

    unsigned int q;
#if DEBUG
    fscanf(fp, "%u", &q);
#else
    scanf("%u", &q);
#endif

    for (size_t i = 1; i <= q; i++)
    {
        unsigned int k;

#if DEBUG
        fscanf(fp, "%u", &k);
#else
        scanf("%u", &k);
#endif

        vector<unsigned int> hs;

        for (size_t j = 0; j < k; j++)
        {
            unsigned int h;
#if DEBUG
            fscanf(fp, "%u", &h);
#else
            scanf("%u", &h);
#endif

            hs.push_back(h);
        }

        func(hs, k, i);
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
