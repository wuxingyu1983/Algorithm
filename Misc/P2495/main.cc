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
vector<unsigned int> minwgt(2 * MAX_N * 4);  // min weight, segment tree
vector<unsigned int> lazyminwgt(2 * MAX_N * 4);  // min weight, segment tree
vector<unsigned int> firsInPath(MAX_N);      // first in path
map<unsigned long long, unsigned int> weights;
vector< vector<unsigned int> > roads(MAX_N);

class Node
{
public:
    unsigned int idx;
    unsigned int depth;

    Node()
    {
        idx = depth = 0;
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
    d[p] = d[p * 2] + d[p * 2 + 1];
}

unsigned long long getMin(vector<unsigned int>& d, vector<unsigned int>& b, int l, int r, int s, int t, int p)
{
    if (l <= s && t <= r)
        return d[p];
    int m = s + ((t - s) >> 1);
    if (b[p])
    {
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p];
        b[p] = 0;
    }
    unsigned int min = MAX_N;
    if (l <= m)
        min = getMin(d, b, l, r, s, m, p * 2);
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
    path[idx] = node;

    // update depth
    update(heights, lazyheights, idx, idx, depth, 1, n, 1);

    for (vector<unsigned int>::iterator it = roads[node].begin(); it != roads[node].end(); it++)
    {
        if (parent != *it)
        {
            buildPath(*it, node, depth + 1, ++idx);

            path[++ idx] = node;

            // update depth
            update(heights, lazyheights, idx, idx, depth, 1, n, 1);

            // update weight
            unsigned int key = getKey(path[idx], path[idx - 1]);
            unsigned int w = weights[key];

            update(minwgt, lazyminwgt, idx, idx, w, 1, n, 1);
        }
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

    // init path
    update(minwgt, lazyminwgt, 1, 1, MAX_N + 1, 1, n, 1);

    unsigned int idxInPath = 1;
    buildPath(1, 0, 1, idxInPath);



#if DEBUG
    fclose(fp);
#endif

    return 0;
}
