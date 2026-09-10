// https://codeforces.com/contest/1077/problem/F1

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


template <typename T>
class SegmentTree {
private:
    int n;
    std::vector<T> tree;
    std::vector<T> lazy;
    std::vector<bool> has_lazy; // Tracks if a lazy value is pending

    void push(int node) {
        if (has_lazy[node]) {
            // Pass the assignment value to the left child
            tree[2 * node] = lazy[node];
            lazy[2 * node] = lazy[node];
            has_lazy[2 * node] = true;

            // Pass the assignment value to the right child
            tree[2 * node + 1] = lazy[node];
            lazy[2 * node + 1] = lazy[node];
            has_lazy[2 * node + 1] = true;

            // Clear the lazy flag for the current node
            has_lazy[node] = false;
        }
    }

    void update_range(int node, int start, int end, int l, int r, T val) {
        if (r < start || end < l) {
            return; // No overlap
        }
        if (l <= start && end <= r) {
            // Complete overlap: update node value and mark it lazy
            tree[node] = val;
            lazy[node] = val;
            has_lazy[node] = true;
            return;
        }
        // Partial overlap: push pending updates down, then recurse
        push(node);
        int mid = start + (end - start) / 2;
        update_range(2 * node, start, mid, l, r, val);
        update_range(2 * node + 1, mid + 1, end, l, r, val);
        
        // Merge step: parent maximum is the max of its children
        tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
    }

    T query_range(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return std::numeric_limits<T>::min(); // No overlap return minimum infinity
        }
        if (l <= start && end <= r) {
            return tree[node]; // Complete overlap
        }
        // Partial overlap: resolve lazy evaluations before moving down
        push(node);
        int mid = start + (end - start) / 2;
        T left_res = query_range(2 * node, start, mid, l, r);
        T right_res = query_range(2 * node + 1, mid + 1, end, l, r);
        
        return std::max(left_res, right_res);
    }

public:
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        has_lazy.assign(4 * n, false);
    }

    void update(int l, int r, T val) {
        update_range(1, 0, n - 1, l, r, val);
    }

    T query(int l, int r) {
        return query_range(1, 0, n - 1, l, r);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, x;
    cin >> n >> k >> x;

    vector<long long> a(n + 1, 0);
    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }

    long long ans = -1;
    if (n == x)
    {
        ans = sum;
    }
    else
    {
        vector<SegmentTree<long long>> segTrees(2, SegmentTree<long long>(n + 1));

        // init
        segTrees[0].update(0, n, -1);
        segTrees[0].update(0, 0, 0);
        int act = 1;

        for (int j = 1; j <= x; j++)
        {
            segTrees[act].update(0, n, -1);

            for (int i = j; i <= n; i++)
            {
                int lpos = max(0, i - k);

                long long max_val = segTrees[1 - act].query(lpos, i - 1);
                if (max_val != -1)
                {
                    if (j < x)
                    {
                        segTrees[act].update(i, i, max_val + a[i]);
                    }

                    if (j == x && i + k > n)
                    {
                        ans = max(ans, max_val + a[i]);
                    }
                }
                else
                {
                    break;
                }
            }

            act = 1 - act;
        }
    }

    cout << ans << "\n";

    return 0;
}
