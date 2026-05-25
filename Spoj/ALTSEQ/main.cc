// https://www.spoj.com/problems/ALTSEQ/

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

    vector<int> vec(n);
    vector<int> negt, post;
    negt.reserve(n);
    post.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> vec[i];
        if (0 < vec[i])
            post.push_back(vec[i]);
        else
            negt.push_back(0 - vec[i]);
    }

    // 去重
    {
        sort(negt.begin(), negt.end());               // 先对vector进行排序
        auto last = unique(negt.begin(), negt.end()); // 去除重复的元素
        negt.erase(last, negt.end());                 // 删除多余的元素

        sort(post.begin(), post.end());          // 先对vector进行排序
        last = unique(post.begin(), post.end()); // 去除重复的元素
        post.erase(last, post.end());            // 删除多余的元素
    }

    

    int ans = 0;

    cout << ans << "\n";

    return 0;
}
