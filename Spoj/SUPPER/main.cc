// https://www.spoj.com/problems/SUPPER/

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

const int MAX_N = 100005;

// 合并左右子树的最大值
void push_up(vector<int> &tree, int p)
{
    tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
}

void updateMax(vector<int> &tree, int idx, int c, int l, int r, int p)
{
    if (idx == l && idx == r)
    {
        tree[p] = c;
        return;
    }

    int mid = (l + r) >> 1;
    if (idx <= mid)
        updateMax(tree, idx, c, l, mid, p << 1);
    else
        updateMax(tree, idx, c, mid + 1, r, p << 1 | 1);
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> p(MAX_N, 0);
    vector<int> tree(MAX_N * 4, 0);
    vector<int> lens(MAX_N, 0);
    vector<int> rlens(MAX_N, 0);

    for (size_t iT = 0; iT < 10; iT++)
    {
        int n;
        cin >> n;

        for (size_t j = 0; j < n; j++)
        {
            cin >> p[j];
        }

        tree.assign(tree.size(), 0);
        lens.assign(lens.size(), 0);

        int maxLen = 0;

        for (size_t j = 0; j < n; j++)
        {
            // 获取 1 - (p[j] - 1) 的最长len
            int len = getMax(tree, 1, p[j] - 1, 1, n, 1);
            updateMax(tree, p[j], len + 1, 1, n, 1);
            lens[j] = len + 1;
            if (maxLen < len + 1)
                maxLen = len + 1;
        }

        tree.assign(tree.size(), 0);
        rlens.assign(rlens.size(), 0);

        int cnt = 0;
        vector<int> ans;
        for (int j = n - 1; j >= 0; j--)
        {
            int len = getMax(tree, p[j] + 1, n, 1, n, 1);
            updateMax(tree, p[j], len + 1, 1, n, 1);

            rlens[j] = len + 1;

            if (maxLen + 1 == lens[j] + rlens[j])
            {
                cnt ++;
                ans.push_back(p[j]);
            }
        }

        sort(ans.begin(), ans.end());

        cout << cnt << "\n";
        for (size_t i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
