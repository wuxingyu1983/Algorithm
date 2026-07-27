// https://codeforces.com/contest/1216/problem/F

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

const int MAXN = 200010;
char rooms[MAXN];

// segment tree func
// 合并左右子树的最大值
void push_up(vector<long long> &tree, int p)
{
    tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
}

void update(vector<long long> &tree, int idx, long long c, int l, int r, int p)
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
long long getMax(vector<long long> &tree, int L, int R, int l, int r, int p)
{
    if (L > R)
        return 0;
    if (L <= l && r <= R)
        return tree[p]; // 完全覆盖
    int mid = (l + r) >> 1;
    long long res = 0;
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

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++)
    {
        cin >> rooms[i];
    }

    vector<long long> dp(n * 4 + 10, 0);

    for (long long i = 1; i <= n; i++)
    {
        if ('0' == rooms[i])
        {
            long long before = 0;
            if (1 < i)
            {
                before = getMax(dp, i - 1, i - 1, 1, n, 1);
            }

            long long now = getMax(dp, i, i, 1, n, 1);

            if (0 == now || before + i < now)
            {
                update(dp, i, before + i, 1, n, 1);
            }
        }
        else
        {
            // '1' == rooms[i]

        }
    }

    return 0;
}
