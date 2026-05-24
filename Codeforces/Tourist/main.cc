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
#include <utility>

using namespace std;

const int MAX_N = 100005;

class Event 
{
public:
    int x, t;
    long long a, b;
    int ai, bi;
};

bool cmp(Event &a, Event &b)
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

bool cmp1(Event &a, Event &b)
{
    bool bRet = false;
 
    if (a.ai < b.ai)
    {
        bRet = true;
    }
    else if (a.ai == b.ai)
    {
        if (a.bi < b.bi)
        {
            bRet = true;
        }
    }

    return bRet;
}

void deduplication(vector<long long> &xs)
{
    sort(xs.begin(), xs.end());               // 先对vector进行排序
    auto last = unique(xs.begin(), xs.end()); // 去除重复的元素
    xs.erase(last, xs.end());                 // 删除多余的元素
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
    events.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        int x, t;
        cin >> x >> t;

        Event e;
        e.x = x;
        e.t = t;

        events.push_back(e);
    }
    
    long long v;
    cin >> v;

    sort(events.begin(), events.end(), cmp);

    vector<long long> as, bs;
    as.reserve(n);
    bs.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        events[i].a = v * (long long)(events[i].t) - events[i].x;
        events[i].b = v * (long long)(events[i].t) + events[i].x;

        as.push_back(events[i].a);
        bs.push_back(events[i].b);
    }

    // a, b 去重
    deduplication(as);
    deduplication(bs);

    // 离散化
    for (size_t i = 0; i < n; i++)
    {
        auto it = lower_bound(as.begin(), as.end(), events[i].a);
        events[i].ai = it - as.begin() + 1;

        it = lower_bound(bs.begin(), bs.end(), events[i].b);
        events[i].bi = it - bs.begin() + 1; 
    }

    sort(events.begin(), events.end(), cmp1);

    vector<int> tree1(MAX_N * 4, 0);
    vector<int> tree2(MAX_N * 4, 0);
    
    int rslt1 = 0;
    int rslt2 = 0;

    for (size_t i = 0; i < n; i++)
    {
        int pre = getMax(tree1, 1, events[i].bi, 1, n, 1);

        if (0 < pre)
        {
            pre += 1;
        }
        else
        {
            // 0 == pre
            if (0 <= events[i].a && 0 <= events[i].b)
            {
                pre = 1;
            }
        }

        updateMax(tree1, events[i].bi, pre, 1, n, 1);

        if (rslt1 < pre)
        {
            rslt1 = pre;
        }

        pre = getMax(tree2, 1, events[i].bi, 1, n, 1);
        pre += 1;

        updateMax(tree2, events[i].bi, pre, 1, n, 1);

        if (rslt2 < pre)
        {
            rslt2 = pre;
        }
    }

    cout << rslt1 << " " << rslt2 << "\n";

    return 0;
}
