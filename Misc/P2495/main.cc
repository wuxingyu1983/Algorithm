// https://www.luogu.com.cn/problem/P2495
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

#define DEBUG 0
#define MAX_N 250001

unsigned int n;
vector<unsigned int> path(2 * MAX_N);    // path island index
vector<unsigned int> heights(2 * MAX_N * 4); // path island height, segment tree
vector<unsigned int> lazyheights(2 * MAX_N * 4); // path island height, segment tree
vector<unsigned int> firsInPath(MAX_N);      // first in path
map<unsigned long long, unsigned int> weights;
vector< vector<unsigned int> > roads(MAX_N);
vector< vector<unsigned int> > hIdx(MAX_N);
vector<unsigned int> me(MAX_N, MAX_N);  // path 1 -- n, min weight
unsigned long long dp[MAX_N];

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
    :idx(_idx), depth(_depth)
    {
        flag = dfs = 0;
    }
};

Node nodes[MAX_N];

inline unsigned long long getKey(unsigned int u, unsigned int v)
{
    unsigned long long key;

    if (u < v)
    {
        key = u;
        key <<= 32;
        key += v;
    }
    else
    {
        key = v;
        key <<= 32;
        key += u;
    }

    return key;
}

// segment tree func
void update(vector<unsigned int>& d, vector<unsigned int>& b, int l, int r, unsigned int c, int s, int t, int p)
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

unsigned int getMin(vector<unsigned int>& d, vector<unsigned int>& b, int l, int r, int s, int t, int p)
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

    if (1 < node)
    {
        unsigned long long key = getKey(node, parent);
        unsigned int w = weights[key];

        if (w < me[parent])
        {
            me[node] = w;
        }
        else
        {
            me[node] = me[parent];
        }
    }

    // update depth
    update(heights, lazyheights, idx, idx, depth, 1, 2 * n - 1, 1);
    
    for (vector<unsigned int>::iterator it = roads[node].begin(); it != roads[node].end(); it++)
    {
        if (parent != *it)
        {
            buildPath(*it, node, depth + 1, ++idx);

            path[++ idx] = node;
            hIdx[depth].push_back(idx);

            // update depth
            update(heights, lazyheights, idx, idx, depth, 1, 2 * n - 1, 1);
        }
    }
    
}

inline bool cmp(Node * x, Node * y)
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

void dpFunc(unsigned int idx)
{
    if (0 == dp[idx])
    {
        unsigned long long tmp = 0;

        for (vector<unsigned int>::iterator it = nodes[idx].children.begin(); it != nodes[idx].children.end(); it++)
        {
            dpFunc(*it);
            tmp += dp[*it];
        }

        if (tmp < me[idx])
        {
            dp[idx] = tmp;
        }
        else
        {
            dp[idx] = me[idx];
        }
    }
}

vector<unsigned int> stk(MAX_N, 0);

void func(vector<unsigned int> &hs, int m)
{
    memset(dp, 0, sizeof(unsigned long long) * (n + 1));

    // sort by dfs
    vector<Node *> tmps;
    
    for (vector<unsigned int>::iterator it = hs.begin(); it != hs.end(); it++)
    {
        nodes[*it].flag = m;
        nodes[*it].children.clear();
        tmps.push_back(&(nodes[*it]));

        dp[*it] = me[*it];
    }

    sort(tmps.begin(), tmps.end(), cmp);

    // build virtual tree
    int top = 0;
    stk[top] = 1;   // push node 1 first
    nodes[1].children.clear();
    nodes[1].flag = m;

    for (vector<Node *>::iterator it = tmps.begin(); it != tmps.end(); it++)
    {
        unsigned int lca = getLca((*it)->idx, stk[top]);

        if (lca == stk[top])
        {
            // push to stack
            stk[++top] = (*it)->idx;
            if (m != nodes[(*it)->idx].flag)
            {
                nodes[(*it)->idx].flag = m;
                nodes[(*it)->idx].children.clear();
            }
        }
        else
        {
            while (nodes[lca].dfs < nodes[stk[top - 1]].dfs)
            {
                // connect stk[top] and stk[top - 1]
                nodes[stk[top - 1]].children.push_back(stk[top]);

                // pop from stack;
                top --;
            }
            
            if (nodes[lca].dfs > nodes[stk[top - 1]].dfs)
            {
                // connect lca and stk[top]
                if (m != nodes[lca].flag)
                {
                    nodes[lca].flag = m;
                    nodes[lca].children.clear();
                }
                nodes[lca].children.push_back(stk[top]);

                // pop
                top --;

                stk[++ top] = lca;

                stk[++ top] = (*it)->idx;
            }
            else
            {
                // ==
                // connect stk[top] and stk[top - 1]
                nodes[stk[top - 1]].children.push_back(stk[top]);
                
                // pop from stack;
                top --;
                
                stk[++ top] = (*it)->idx;
            }
        }
    }

    while (0 < top)
    {
        // conect stk[top] and stk[top - 1]
        nodes[stk[top - 1]].children.push_back(stk[top]);

        top --;
    }

    // dp
    dpFunc(1);

    printf("%llu\n", dp[1]);
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
        unsigned int u, v, w;
#if DEBUG
        fscanf(fp, "%u %u %u", &u, &v, &w);
#else
        scanf("%u %u %u", &u, &v, &w);
#endif

        roads[u].push_back(v);
        roads[v].push_back(u);

        unsigned long long key = getKey(u, v);
        weights.insert(pair<unsigned long long, unsigned int>(key, w));
    }

    unsigned int idxInPath = 1;
    buildPath(1, 0, 1, idxInPath);

    unsigned int m;
#if DEBUG
    fscanf(fp, "%u", &m);
#else
    scanf("%u", &m);
#endif

    for (size_t i = 1; i <= m; i++)
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

        func(hs, i);
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
