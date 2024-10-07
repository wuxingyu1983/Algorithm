// LCA - euler path : https://oi-wiki.org/graph/lca/#%E7%94%A8%E6%AC%A7%E6%8B%89%E5%BA%8F%E5%88%97%E8%BD%AC%E5%8C%96%E4%B8%BA-rmq-%E9%97%AE%E9%A2%98
// 倍增法 binary lifting

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
#include <functional>

using namespace std;

#define MAX_N 500001
#define MAX_LOGN 20

class Node
{
public:
    int depth;
    int fa[MAX_LOGN];
    vector<int> children;
};

Node nodes[MAX_N];

vector<int> edges[MAX_N];

void buildTree(int curr, int parent)
{
    if (parent)
    {
        nodes[curr].depth = nodes[parent].depth + 1;

        nodes[curr].fa[0] = parent;

        for (int i = 1; i < MAX_LOGN; ++i)
        {
            nodes[curr].fa[i] = nodes[nodes[curr].fa[i - 1]].fa[i - 1];
        }
    }

    for (vector<int>::iterator it = edges[curr].begin(); it != edges[curr].end(); it++)
    {
        if (*it != parent)
        {
            nodes[curr].children.push_back(*it);
            buildTree(*it, curr);
        }
    }
}

int lca(int u, int v)
{
    if (nodes[u].depth < nodes[v].depth)
        swap(u, v); // 保证u是深度较大的哪一个

    for (int i = 19; i >= 0; --i)
    {
        if (nodes[nodes[u].fa[i]].depth >= nodes[v].depth)
            u = nodes[u].fa[i]; // 将u一直向上跳直到跳到v的同一层
    }

    if (u == v)
        return u; // 可能存在这种情况：v就是u的祖先，那么v就是u,v的lca

    for (int i = 19; i >= 0; --i)
    {
        if (nodes[u].fa[i] != nodes[v].fa[i])
        {
            u = nodes[u].fa[i], v = nodes[v].fa[i]; // 这里u和v一定可以跳跃到lca的刚好下一层邻接层
        }
    }

    return nodes[u].fa[0]; // 由于u在lca的下一层，因此我们只需要再向上取2^0层就是lca了
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, s;
    cin >> n >> m >> s;

    for (size_t i = 1; i < n; i++)
    {
        int x, y;
        cin >> x >> y;

        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    // build tree
    nodes[s].depth = 1;
    buildTree(s, 0);
    
    for (size_t i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        cout << lca(a, b) << "\n";
    }

    return 0;
}
