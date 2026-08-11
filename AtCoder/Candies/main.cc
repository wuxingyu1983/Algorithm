// https://atcoder.jp/contests/dp/tasks/dp_m

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
#include <unordered_set>
#include <unordered_map>

using namespace std;

const long long MOD = 1000000007;
const int MAXK = 100001;
const int MAXN = 100;

template <typename T>
class SegmentTree
{
private:
    int n;
    std::vector<T> tree;
    std::vector<T> lazy;

    void push(int node, int start, int end)
    {
        if (lazy[node] != 0)
        {
            // Apply the lazy value to the current node's maximum
            tree[node] += lazy[node];
            tree[node] %= MOD;

            // If it is not a leaf node, propagate the lazy value to children
            if (start != end)
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node] %= MOD;
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 1] %= MOD;
            }
            // Clear the lazy value for the current node
            lazy[node] = 0;
        }
    }

    void update_range(int node, int start, int end, int l, int r, T val)
    {
        // Process pending lazy updates first
        push(node, start, end);

        // Out of bounds: No overlap
        if (start > end || start > r || end < l)
        {
            return;
        }

        // Complete overlap: Current segment is completely within [l, r]
        if (start >= l && end <= r)
        {
            tree[node] += val;
            tree[node] %= MOD;
            if (start != end)
            {
                lazy[2 * node] += val;
                lazy[2 * node] %= MOD;
                lazy[2 * node + 1] += val;
                lazy[2 * node + 1] %= MOD;
            }
            return;
        }

        // Partial overlap: Recurse on children
        int mid = start + (end - start) / 2;
        update_range(2 * node, start, mid, l, r, val);
        update_range(2 * node + 1, mid + 1, end, l, r, val);

        // Merge step: Update current node's maximum using children's actual values
        tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
    }

    T query_range(int node, int start, int end, int l, int r)
    {
        // Out of bounds: No overlap
        if (start > end || start > r || end < l)
        {
            return std::numeric_limits<T>::min();
        }

        // Process pending lazy updates
        push(node, start, end);

        // Complete overlap
        if (start >= l && end <= r)
        {
            return tree[node];
        }

        // Partial overlap: Recurse and return the maximum of both halves
        int mid = start + (end - start) / 2;
        T leftMax = query_range(2 * node, start, mid, l, r);
        T rightMax = query_range(2 * node + 1, mid + 1, end, l, r);

        return std::max(leftMax, rightMax);
    }

public:
    SegmentTree(int size)
    {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void update(int l, int r, T val)
    {
        update_range(1, 0, n - 1, l, r, val);
    }

    T query(int l, int r)
    {
        return query_range(1, 0, n - 1, l, r);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    SegmentTree<int> st(k + 1);

    st.update(0, 0, 1);
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;

        for (int j = k - 1; j >= 0; j--)
        {
            long long v = st.query(j, j);
            
            if (v > 0)
            {
                int l = j + 1;
                int r = min(k, j + a);
                st.update(l, r, v);
            }
        }
    }

    cout << st.query(k, k) << "\n";

    return 0;
}
