// https://codeforces.com/problemset/problem/486/E

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

const int MOD = 100000007;
const int MAX_N = 100007;
int cnt;
int root[MAX_N + 1], ls[MAX_N * 18], rs[MAX_N * 18];
long long sum[MAX_N * 18];

// 用法：update(root, 1, n, x, f); 其中 x 为待修改节点的编号
void updateSum(int &p, int s, int t, int x, long long f)
{ // 引用传参
    if (!p)
        p = ++cnt; // 当结点为空时，创建一个新的结点
    if (s == t)
    {
        sum[p] += f;
        sum[p] %= MOD;
        return;
    }
    int m = s + ((t - s) >> 1);
    if (x <= m)
        updateSum(ls[p], s, m, x, f);
    else
        updateSum(rs[p], m + 1, t, x, f);
    sum[p] = sum[ls[p]] + sum[rs[p]]; // pushup
    sum[p] %= MOD;
}

// 用法：getSum(root, 1, n, l, r);
long long getSum(int p, int s, int t, int l, int r)
{
    if (!p)
        return 0; // 如果结点为空，返回 0
    if (s >= l && t <= r)
        return sum[p];
    long long ans = 0;
    int m = s + ((t - s) >> 1);
    if (l <= m)
        ans += getSum(ls[p], s, m, l, r);
    if (r > m)
        ans += getSum(rs[p], m + 1, t, l, r);
    ans %= MOD;
    return ans;
}

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

    int n;
    cin >> n;

    vector<int> nums;
    for (size_t i = 0; i < n; i++)
    {
        int a;
        cin >> a;

        nums.push_back(a);
    }

    // 计算 LIS 以及 个数
    vector<int> d(MAX_N * 18, 0);
    int maxLen = 0;
    vector<int> lens(n, 0);
    vector<long long> counts(n, 0);

    for (size_t i = 0; i < n; i++)
    {
        int idx = nums[i];

        // 获取 1 - (idx - 1) 的最长len
        int len = getMax(d, 1, idx - 1, 1, MAX_N, 1);
        updateMax(d, idx, len + 1, 1, MAX_N, 1);

        lens[i] = len + 1;

        maxLen = max(maxLen, len + 1);

        // 更新 sum
        long long preSum = getSum(root[len], 1, MAX_N, 1, idx - 1);
        if (0 == preSum)
        {
            preSum = 1;
        }
        updateSum(root[len + 1], 1, MAX_N, idx, preSum);

        counts[i] = preSum;
    }

    long long total = getSum(root[maxLen], 1, MAX_N, 1, MAX_N);

    cnt = 0;
    memset(root, 0, sizeof(root));
    memset(ls, 0, sizeof(ls));
    memset(rs, 0, sizeof(rs));
    memset(sum, 0, sizeof(sum));

    vector<int> ret(n, 0);

    d.assign(MAX_N * 18, 0);
    vector<int> rlens(n, 0);
    vector<long long> rcounts(n, 0);

    for (int i = n - 1; i >= 0; i--)
    {
        int idx = nums[i];

        // 获取 (idx + 1) - n 的最长len
        int len = getMax(d, idx + 1, MAX_N, 1, MAX_N, 1);
        updateMax(d, idx, len + 1, 1, MAX_N, 1);

        rlens[i] = len + 1;

        // 更新 sum
        long long aftSum = getSum(root[len], 1, MAX_N, idx + 1, MAX_N);
        if (0 == aftSum)
        {
            aftSum = 1;
        }
        updateSum(root[len + 1], 1, MAX_N, idx, aftSum);

        rcounts[i] = aftSum;

        if (maxLen + 1 == lens[i] + rlens[i])
        {
            if (total == ((counts[i] * rcounts[i]) % MOD))
            {
                ret[i] = 3;
            }
            else
            {
                ret[i] = 2;
            }
        }
        else
        {
            ret[i] = 1;
        }
    }
   
    for (size_t i = 0; i < n; i++)
    {
        cout << ret[i];
    }
    cout << "\n";

    return 0;
}
