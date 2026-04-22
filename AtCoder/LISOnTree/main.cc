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

    vector<int> children(n + 1, 0);
    stack<int> currs, parents, olds;
    currs.push(1);
    parents.push(0);

    // 初始化 root(1)
    lis[1] = 1;
    update(d, indexs[vecA[1]], 1, 1, n, 1);
    olds.push(0);

    while (currs.size() > 0)
    {
        int curr = currs.top();
        int parent = parents.top();

        int child = children[curr];

        if (child >= vertices[curr].size())
        {
            // 该节点 curr 的所有子节点都已经处理完了
            int a = indexs[vecA[curr]];

            int old = olds.top();
            update(d, a, old, 1, n, 1);

            olds.pop();
            currs.pop();
            parents.pop();
        }
        else
        {
            // 下一个要处理的子节点 child + 1
            children[curr] = child + 1;
            if (parent != vertices[curr][child])
            {
                int a = indexs[vecA[vertices[curr][child]]];
                int l = getMax(d, 1, a - 1, 1, n, 1);
                int old = getMax(d, a, a, 1, n, 1);
                olds.push(old);

                lis[vertices[curr][child]] = l + 1;
                update(d, a, l + 1, 1, n, 1);

                currs.push(vertices[curr][child]);
                parents.push(curr);
            }
        }
    }

    for (size_t i = 1; i <= n; i++)
    {
        cout << lis[i] << "\n";
    }

    return 0;
}
