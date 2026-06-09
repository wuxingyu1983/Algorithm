// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3153

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
#include <utility>

using namespace std;

const int MAX_N = 505;
int lens[MAX_N], rlens[MAX_N];

void deduplication(vector<int> &vec)
{
    sort(vec.begin(), vec.end());               // 先对vector进行排序
    auto last = unique(vec.begin(), vec.end()); // 去除重复的元素
    vec.erase(last, vec.end());                 // 删除多余的元素
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

    vector<int> ks, tmps;
    ks.reserve(MAX_N);
    tmps.reserve(MAX_N);

    vector<int> tree(MAX_N * 5, 0);
    vector<int> rtree(MAX_N * 5, 0);

    for (;;)
    {
        int n;
        cin >> n;

        if (0 == n)
            break;
        
        ks.clear();
        tmps.clear();
        for (size_t i = 0; i < n; i++)
        {
            int k;
            cin >> k;

            ks.push_back(k);
            tmps.push_back(k);
        }

        deduplication(tmps);

        for (size_t i = 0; i < n; i++)
        {
            auto it = lower_bound(tmps.begin(), tmps.end(), ks[i]);
            ks[i] = it - tmps.begin() + 1;
        }
       
        // init
        memset(lens, 0, sizeof(lens));
        memset(rlens, 0, sizeof(rlens));
        tree.assign(tree.size(), 0);
        rtree.assign(rtree.size(), 0);
        int maxIdx = tmps.size();

        int ans = 0;

        for (int i = n - 1; i >= 0; i--)
        {
            int l = getMax(tree, 1, ks[i], 1, maxIdx, 1);
            updateMax(tree, ks[i], l + 1, 1, maxIdx, 1);

            lens[i] = l + 1;

            l = getMax(rtree, ks[i], maxIdx, 1, maxIdx, 1);
            updateMax(rtree, ks[i], l + 1, 1, maxIdx, 1);

            rlens[i] = l + 1;

            ans = max(ans, lens[i] + rlens[i] - 1);
        }

        cout << ans << "\n";
    }

    return 0;
}
