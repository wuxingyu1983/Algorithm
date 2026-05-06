// https://codeforces.com/contest/76/problem/F

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

const int MAX_N = 100000;

class Event 
{
public:
    int x, t;
};

bool myfunc(Event &a, Event &b)
{
    bool bRet = false;

    if (a.t < b.t)
    {
        bRet = true;
    }
    else if (a.t == b.t)
    {
        if (a.x < b.x)
        {
            bRet = true;
        }
    }

    return bRet;
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

    vector<Event> events;
    vector<long long> xs;
    for (size_t i = 0; i < n; i++)
    {
        int x, t;
        cin >> x >> t;

        Event e;
        e.x = x;
        e.t = t;

        events.push_back(e);
        xs.push_back(x);
    }
    
    long long v;
    cin >> v;

    // sort
    sort(events.begin(), events.end(), myfunc);

    // x 去重
    sort(xs.begin(), xs.end());               // 先对vector进行排序
    auto last = unique(xs.begin(), xs.end()); // 去除重复的元素
    xs.erase(last, xs.end());                 // 删除多余的元素

    unordered_map<long long, int> xToIdx;
    for (size_t i = 0; i < xs.size(); i++)
    {
        xToIdx.insert({xs[i], i + 1});
    }

    vector<int> tree(MAX_N * 17, 0);

    int rslt = 0;
    for (size_t i = 0; i < n; i++)
    {
        long long x = events[i].x;
        long long t = events[i].t;

        long long l = x - t * v;
        long long r = x + t * v;

        // l >=
        int idxL = 0;
        {
            auto it = lower_bound(xs.begin(), xs.end(), l);
            idxL = it - xs.begin() + 1;
        }

        // < r
        int idxR = 0;
        {
            auto it = upper_bound(xs.begin(), xs.end(), r);
            if (it != xs.end())
            {
                idxR = it - xs.begin();
            }
            else
            {
                idxR = xs.size();
            }
        }

        int preRstl = getMax(tree, idxL, idxR, 1, MAX_N, 1);
        if (0 < preRstl)
        {
            preRstl ++;
        }
        else if (0 >= l && 0 <= r)
        {
            preRstl = 1;
        }

        if (0 < preRstl)
        {
            updateMax(tree, xToIdx[events[i].x], preRstl, 1, MAX_N, 1);
            if (rslt < preRstl)
            {
                rslt = preRstl;
            }
        }
    }
    
    cout << rslt << " ";

    tree.assign(MAX_N * 17, 0);
    rslt = 0;

    for (size_t i = 0; i < n; i++)
    {
        long long x = events[i].x;
        long long t = events[i].t;

        long long l = x - t * v;
        long long r = x + t * v;

        // l >=
        int idxL = 0;
        {
            auto it = lower_bound(xs.begin(), xs.end(), l);
            idxL = it - xs.begin() + 1;
        }

        // < r
        int idxR = 0;
        {
            auto it = upper_bound(xs.begin(), xs.end(), r);
            if (it != xs.end())
            {
                idxR = it - xs.begin();
            }
            else
            {
                idxR = xs.size();
            }
        }

        int preRstl = getMax(tree, idxL, idxR, 1, MAX_N, 1);
        preRstl++;

        updateMax(tree, xToIdx[events[i].x], preRstl, 1, MAX_N, 1);
        if (rslt < preRstl)
        {
            rslt = preRstl;
        }
    }

    cout << rslt << "\n";

    return 0;
}
