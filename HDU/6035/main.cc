// http://acm.hdu.edu.cn/showproblem.php?pid=6035
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
#define MAX_N   200001

unsigned int n;
vector< vector<unsigned int> > colors;
vector< vector<unsigned int> > hIdx;
vector< vector<unsigned int> > roads;
vector<unsigned int> path(2 * MAX_N);            // path island index
vector<unsigned int> heights(2 * MAX_N * 4);     // path island height, segment tree
vector<unsigned int> lazyheights(2 * MAX_N * 4); // path island height, segment tree
vector<unsigned int> firsInPath(MAX_N);          // first in path
vector<unsigned int> flags(MAX_N);

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

void dpFunc(unsigned int idx, int m, int &cnt)
{
    if (m == flags[idx])
    {
        // key node
        for (vector<unsigned int>::iterator it = nodes[idx].children.begin(); it != nodes[idx].children.end(); it++)
        {
            dpFunc(*it, m, cnt);
            
            if (m == flags[*it])
            {
                cnt ++;
            }
        }
    }
    else
    {
        unsigned int tmp = 0;
        for (vector<unsigned int>::iterator it = nodes[idx].children.begin(); it != nodes[idx].children.end(); it++)
        {
            dpFunc(*it, m, cnt);
            
            if (m == flags[*it])
            {
                tmp ++;
            }
        }

        if (1 < tmp)
        {
            cnt ++;
        }
        else if (1 == tmp)
        {
            flags[idx] = m;
        }
    }
}

unsigned long long func(vector<unsigned int> &hs, int k, int m)
{
    unsigned long long ret = 0;
    int cnt = -1;
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
    stk[top] = 1; // push node 1 first
    nodes[1].children.clear();

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
    
    cnt = 0;
    dpFunc(1, m, cnt);

    return ret;
}

int main()
{
#if DEBUG
    FILE *fp = fopen("input.txt", "r");
#endif
    
    unsigned int testcase = 1;
#if DEBUG
    while (fscanf(fp, "%u", &n))
#else
    while (scanf("%u", &n))
#endif
    {
        // init
        colors.clear();
        colors.resize(n + 1);
        roads.clear();
        roads.resize(n + 1);
        hIdx.clear();
        hIdx.resize(n + 1);
        path.assign(2 * (n + 1), 0);
        heights.assign(2 * 4 * (n + 1), 0);
        lazyheights.assign(2 * 4 * (n + 1), 0);
        firsInPath.assign(n + 1, 0);
        flags.assign(n + 1, 0);

        for (size_t i = 1; i <= n; i++)
        {
            unsigned int c;
#if DEBUG
            fscanf(fp, "%u", &c);
#else
            scanf("%u", &c);
#endif

            colors[c].push_back(i);
        }

        for (size_t i = 1; i < n; i++)
        {
            unsigned int x, y;
#if DEBUG
            fscanf(fp, "%u %u", &x, &y);
#else
            scanf("%u %u", &x, &y);
#endif
            roads[x].push_back(y);
            roads[y].push_back(x);
        }

        unsigned int idxInPath = 1;
        buildPath(1, 0, 1, idxInPath);

        unsigned long long colorCnt = 0;
        unsigned long long ans = 0;

        for (size_t i = 1; i <= n; i++)
        {
            if (0 < colors[i].size())
            {
                colorCnt ++;

                ans += func(colors[i], colors[i].size(), (unsigned int)colorCnt);
            }
        }

        ans = colorCnt * n * (n - 1) / 2 - ans;

        printf("Case #%u: %llu\n", testcase ++, ans);
    }

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
