// https://atcoder.jp/contests/abc165/tasks/abc165_f

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <map>

using namespace std;

#define DEBUG 0

// segment tree func
// 合并左右子树的最大值
void push_up(vector<int> &tree, int p)
{
    tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
}

void update(vector<int> &tree, int idx, int c, int l, int r, int p)
{
    if (idx == l && idx == r)
    {
        tree[p] = c;
        return;
    }

    int mid = (l + r) >> 1;
    if (idx <= mid)
        update(tree, idx, c, l, mid, p << 1);
    else
        update(tree, idx, c, mid + 1, r, p << 1 | 1);
    push_up(tree, p);
}

int getMax(vector<int> &d, int l, int r, int s, int t, int p)
{
    if (l > r)
    {
        return 0;
    }
    if (l <= s && t <= r)
        return d[p];
    int m = s + ((t - s) >> 1);
    int max = 0;
    if (l <= m)
    {
        max = getMax(d, l, r, s, m, p * 2);
    }
    if (r > m)
    {
        int tmp = getMax(d, l, r, m + 1, t, p * 2 + 1);
        if (tmp > max)
        {
            max = tmp;
        }
    }
    return max;
}

int n;

void func(int curr, int parent, vector<int> &d, vector<vector<int>> &vertices, vector<int> &lis, vector<int> &vecA)
{
    int a = vecA[curr];

    int l = getMax(d, 1, a - 1, 1, n, 1);
    int old = getMax(d, a, a, 1, n, 1);

    lis[curr] = l + 1;
    update(d, a, l + 1, 1, n, 1);

#if DEBUG
    for (size_t i = 1; i <= n; i++)
    {
        int l = getMax(d, i, i, 1, n, 1);
        cout << l << " ";
    }
    cout << "\n";
#endif

    for (size_t i = 0; i < vertices[curr].size(); i++)
    {
        if (parent != vertices[curr][i])
        {
            func(vertices[curr][i], curr, d, vertices, lis, vecA);
        }
    }

    update(d, a, old, 1, n, 1);

#if DEBUG
    for (size_t i = 1; i <= n; i++)
    {
        int l = getMax(d, i, i, 1, n, 1);
        cout << l << " ";
    }
    cout << "\n";
#endif
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    vector<int> vecA(n + 1, 0);
    for (size_t i = 1; i <= n; i++)
    {
        int a;
        cin >> a;

        vecA[i] = a;
    }

    vector<vector<int>> vertices(n + 1);
    for (size_t i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;

        vertices[u].push_back(v);
        vertices[v].push_back(u);
    }

    vector<int> lis(n + 1, 0);
    vector<int> d(n * 4 + 10, 0);

    func(1, 0, d, vertices, lis, vecA);

    for (size_t i = 1; i <= n; i++)
    {
        cout << lis[i] << "\n";
    }

    return 0;
}
