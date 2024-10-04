// LCA - euler path : https://oi-wiki.org/graph/lca/#%E7%94%A8%E6%AC%A7%E6%8B%89%E5%BA%8F%E5%88%97%E8%BD%AC%E5%8C%96%E4%B8%BA-rmq-%E9%97%AE%E9%A2%98
// Sparse Table : https://oi-wiki.org/ds/sparse-table/

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

int st[MAX_N], ed[MAX_N];

template <typename T>
class SparseTable
{
    using VT = vector<T>;
    using VVT = vector<VT>;
    using func_type = function<T(const T &, const T &)>;

    VVT ST;

    static T default_func(const T &t1, const T &t2) { return max(t1, t2); }

    func_type op;

public:
    SparseTable(const vector<T> &v, func_type _func = default_func)
    {
        op = _func;
        int len = v.size(), l1 = ceil(log2(len)) + 1;
        ST.assign(len, VT(l1, 0));
        for (int i = 0; i < len; ++i)
        {
            ST[i][0] = v[i];
        }
        for (int j = 1; j < l1; ++j)
        {
            int pj = (1 << (j - 1));
            for (int i = 0; i + pj < len; ++i)
            {
                ST[i][j] = op(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r)
    {
        int lt = r - l + 1;
        int q = floor(log2(lt));
        return op(ST[l][q], ST[r - (1 << q) + 1][q]);
    }
};

class Node
{
public:
    int parent;
    vector<int> children;
};

Node nodes[MAX_N];

vector<int> edges[MAX_N];

void buildTree(int curr, int parent)
{
    if (parent)
    {
        nodes[curr].parent = parent;
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

vector<int> euler_path;

void buildEulerPath(int curr)
{
    st[curr] = euler_path.size();
    ed[curr] = euler_path.size();

    euler_path.push_back(curr);

    if (0 < nodes[curr].children.size())
    {
        for (vector<int>::iterator it = nodes[curr].children.begin(); it != nodes[curr].children.end(); it++)
        {
            buildEulerPath(*it);

            ed[curr] = euler_path.size();

            euler_path.push_back(curr);
        }
    }
}

int minSt(const int &a, const int &b)
{
    if (st[a] < st[b])
        return a;
    else
        return b;
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
    buildTree(s, 0);

    // build euler path
    buildEulerPath(s);

    // init ST
    SparseTable<int> stbl(euler_path, minSt);

    for (size_t i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        if (st[a] > st[b])
            swap(a, b);

        if ((st[a] < st[b]) && (ed[b] < ed[a]))
        {
            cout << a << "\n";
        }
        else
        {
            cout << stbl.query(ed[a], st[b]) << "\n";
        }
    }

    return 0;
}
