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
#include <unordered_map>

using namespace std;

unordered_map<int, int> indexs;

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

// 区间查询：查询[L, R]内的最大值
int getMax(vector<int> &tree, int L, int R, int l, int r, int p)
{
    if (L > R)
        return 0;
    if (L <= l && r <= R)
        return tree[p]; // 完全覆盖
    int mid = (l + r) >> 1;
    int res = 0;
    if (L <= mid)
        res = max(res, getMax(tree, L, R, l, mid, p << 1));
    if (R > mid)
        res = max(res, getMax(tree, L, R, mid + 1, r, p << 1 | 1));
    return res;
}

int n;

void func(int curr, int parent, vector<int> &d, vector<vector<int>> &vertices, vector<int> &lis, vector<int> &vec)
{
    int a = indexs[vec[curr]];

    int l = getMax(d, 1, a - 1, 1, n, 1);
    int old = getMax(d, a, a, 1, n, 1);

    lis[curr] = l + 1;
    update(d, a, l + 1, 1, n, 1);

    for (size_t i = 0; i < vertices[curr].size(); i++)
    {
        if (parent != vertices[curr][i])
        {
            func(vertices[curr][i], curr, d, vertices, lis, vec);
        }
    }

    update(d, a, old, 1, n, 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    vector<int> vecA(n + 1, 0);
    vector<int> tmp;
    for (size_t i = 1; i <= n; i++)
    {
        int a;
        cin >> a;

        vecA[i] = a;
        tmp.push_back(a);
    }

    // 去重
    std::sort(tmp.begin(), tmp.end());  // 先对vector进行排序
    auto last = std::unique(tmp.begin(), tmp.end());  // 去除重复的元素
    tmp.erase(last, tmp.end());  // 删除多余的元素

    for (size_t i = 0; i < tmp.size(); i++)
    {
        indexs.insert({tmp[i], i + 1});
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
