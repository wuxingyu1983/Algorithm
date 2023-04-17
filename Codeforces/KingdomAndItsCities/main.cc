// https://codeforces.com/contest/613/problem/D
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
#define MAX_N   100001

unsigned int n;
vector< vector<unsigned int> > roads(MAX_N);
vector<unsigned int> path(2 * MAX_N);            // path island index
vector<unsigned int> heights(2 * MAX_N * 4);     // path island height, segment tree
vector<unsigned int> lazyheights(2 * MAX_N * 4); // path island height, segment tree
vector<unsigned int> firsInPath(MAX_N);          // first in path
vector< vector<unsigned int> > hIdx(MAX_N);

unsigned int flags[MAX_N];

class Node
{
public:
    unsigned int idx;
    unsigned int depth;
    unsigned int flag;
    unsigned int dfs;

    vector<unsigned int> children;

    Node()
    {
        idx = depth = flag = dfs = 0;
    }

    Node(unsigned int _idx, unsigned int _depth)
        : idx(_idx), depth(_depth)
    {
        flag = dfs = 0;
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

void func(vector<unsigned int> &hs, int k, int m)
{
    int cnt = 0;
    // sort by dfs
    for (size_t i = 0; i < k; i++)
    {
        nodes[hs[i]].flag = m;
        nodes[hs[i]].children.clear();
        tmps[i] = &(nodes[hs[i]]);

        flags[hs[i]] = m;   // key node
    }

    sort(tmps.begin(), tmps.begin() + k, cmp);

    // build virtual tree
    int top = 0;
    stk[top] = hs[0]; // push first node

    for (size_t i = 1; i < k; i++)
    {
        unsigned int lca = getLca(tmps[i]->idx, stk[top]);

        if (lca == stk[top])
        {
            // push to stack
            stk[++top] = tmps[i]->idx;
            if (m != nodes[tmps[i]->idx].flag)
            {
                cnt ++;
                nodes[tmps[i]->idx].flag = m;
                nodes[tmps[i]->idx].children.clear();
            }
        }
        else
        {
            while (nodes[lca].dfs < nodes[stk[top - 1]].dfs)
            {
                // connect stk[top] and stk[top - 1]
                if (m == flags[stk[top - 1]] && m == flags[stk[top]])
                {
                    if (nodes[stk[top - 1]].depth + 1 == nodes[stk[top]].depth)
                    {
                        cnt = 0;
                        goto finish;
                    }
                    else
                    {
                        cnt ++;
                    }
                }
                nodes[stk[top - 1]].children.push_back(stk[top]);

                // pop from stack;
                top--;
            }

            if (nodes[lca].dfs > nodes[stk[top - 1]].dfs)
            {
                // connect lca and stk[top]
                if (m != nodes[lca].flag)
                {
                    cnt ++;
                    nodes[lca].flag = m;
                    nodes[lca].children.clear();
                }

                if (m == flags[lca] && m == flags[top])
                {
                    if (nodes[lca].depth + 1 == nodes[stk[top]].depth)
                    {
                        cnt = 0;
                        goto finish;
                    }
                    else
                    {
                        cnt ++;
                    }
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
                if (m == flags[stk[top - 1]] && m == flags[stk[top]])
                {
                    if (nodes[stk[top - 1]].depth + 1 == nodes[stk[top]].depth)
                    {
                        cnt = 0;
                        goto finish;
                    }
                    else
                    {
                        cnt ++;
                    }
                }
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
        if (m == flags[stk[top - 1]] && m == flags[stk[top]])
        {
            if (nodes[stk[top - 1]].depth + 1 == nodes[stk[top]].depth)
            {
                cnt = 0;
                goto finish;
            }
            else
            {
                cnt++;
            }
        }
        nodes[stk[top - 1]].children.push_back(stk[top]);

        top--;
    }

finish:
    if (0 == cnt)
    {
        printf("-1\n");
    }
    else
    {
        printf("%i\n", cnt);
    }
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
        unsigned int u, v;

#if DEBUG
        fscanf(fp, "%u %u", &u, &v);
#else
        scanf("%u %u", &u, &v);
#endif

        roads[u].push_back(v);
        roads[v].push_back(u);
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
