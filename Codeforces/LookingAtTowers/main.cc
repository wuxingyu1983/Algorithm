// https://codeforces.com/contest/2144/problem/E2
// https://codeforces.com/contest/2144/problem/E1

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

const long long MOD = 998244353;
const int MAXN = 300000;

long long pw2[MAXN + 1];


template <typename T>
class SegmentTree {
private:
    int n;
    std::vector<T> tree;
    std::vector<T> lazy;

    // Helper function to push pending updates down to children
    void push(int node, int start, int end)
    {
        if (lazy[node] != 0)
        {
            int mid = start + (end - start) / 2;

            // Update left child
            tree[2 * node] += (mid - start + 1) * lazy[node];
            lazy[2 * node] += lazy[node];

            // Update right child
            tree[2 * node + 1] += (end - mid) * lazy[node];
            lazy[2 * node + 1] += lazy[node];

            // Clear current node's lazy value
            lazy[node] = 0;
        }
    }

    void update_range(int node, int start, int end, int ql, int qr, T val)
    {
        // No overlap
        if (qr < start || ql > end)
            return;

        // Total overlap
        if (ql <= start && end <= qr)
        {
            tree[node] += (end - start + 1) * val;
            if (start != end)
            { // Not a leaf
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }

        // Partial overlap: push down, update children, and recalculate parent
        push(node, start, end);
        int mid = start + (end - start) / 2;
        update_range(2 * node, start, mid, ql, qr, val);
        update_range(2 * node + 1, mid + 1, end, ql, qr, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    T query_range(int node, int start, int end, int ql, int qr)
    {
        // No overlap
        if (qr < start || ql > end)
            return 0;

        // Total overlap
        if (ql <= start && end <= qr)
            return tree[node];

        // Partial overlap: push down updates before reading children
        push(node, start, end);
        int mid = start + (end - start) / 2;
        T leftSum = query_range(2 * node, start, mid, ql, qr);
        T rightSum = query_range(2 * node + 1, mid + 1, end, ql, qr);
        return leftSum + rightSum;
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void update(int l, int r, T val) {
        update_range(1, 0, n - 1, l, r, val);
    }

    T query(int l, int r) {
        return query_range(1, 0, n - 1, l, r);
    }
};

int func(vector<int> &a, vector<long long> &out)
{
    int highest = 0;

    vector<int> lis;
    lis.push_back(a[0]);
    highest = a[0];
    for (int i = 1; i < a.size(); i++)
    {
        if (highest < a[i])
        {
            lis.push_back(a[i]);
            highest = a[i];
        }
    }

    vector<long long> dp(a.size(), 0);          // dp[i] 在 lis 中第一次出现的数目
    unordered_map<int, int> pos;                // lis 中的某一位在 lis 中出现的位置
    vector<int> preCnt(a.size(), 0);            // preCnt[i] 表示 a[0 - i] 之间小于等于a[i]的个数
    SegmentTree<int> segTree(highest + 1);      // 线段树，用于计算 preCnt

    for (int i = 0; i < a.size(); i++)
    {
        int idx = lower_bound(lis.begin(), lis.end(), a[i]) - lis.begin();
        if (a[i] == lis[idx])
        {
            // a[i] 元素在 lis 中出现


        }
        else
        {

        }
    }

    return highest;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // init
    {
        pw2[0] = 1;
        for (int i = 1; i <= MAXN; i++)
        {
            pw2[i] = (pw2[i - 1] * 2) % MOD;
        }
    }

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vector<int> a, tmp;

        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            a.push_back(x);
            tmp.push_back(x);
        }

        // 去重
        sort(tmp.begin(), tmp.end());
        auto it = unique(tmp.begin(), tmp.end());
        tmp.erase(it, tmp.end());

        // vector a 序列化
        for (int i = 0; i < n; i++)
        {
            a[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin() + 1;
        }

        vector<long long> out(n, 0);
        int highest = func(a, out);

        reverse(a.begin(), a.end());
        vector<long long> rout(n, 0);
        func(a, rout);


    }

    return 0;
}
