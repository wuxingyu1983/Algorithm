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
const int RES_INIT = 0;

class node_y
{
public:
    int l, r;
    int res1, res2;

    node_y * lson;
    node_y * rson;

    node_y(int _l, int _r) : l(_l), r(_r)
    {
        lson = rson = NULL;
        res1 = res2 = RES_INIT;
    }

    node_y()
    {
        l = r = 0;
        lson = rson = NULL;
        res1 = res2 = RES_INIT;
    }

    void init()
    {
        l = r = 0;
        lson = rson = NULL;
        res1 = res2 = RES_INIT;
    }
};

vector<node_y> pooly;
int idxy;

node_y * getNodeY()
{
    node_y * ret = NULL;

    ret = &(pooly[idxy ++]);
    ret->init();

    return ret;
}

// 内层线段树
class tree_y
{
public:
    node_y root;

    tree_y(int _m) : root(1, _m)
    {
    }

    tree_y()
    {
    }

    void update(node_y * now, int y, int k1, int k2)
    {
        if (now->l == now->r)
        {
            now->res1 = max(now->res1, k1);
            now->res2 = max(now->res2, k2);
            return;
        }
        int mid = (now->l + now->r) >> 1;
        if (y <= mid)
        {
            if (NULL == now->lson)
            {
                now->lson = getNodeY();
                now->lson->l = now->l;
                now->lson->r = mid;
            }
            update(now->lson, y, k1, k2);
        }
        else
        {
            if (NULL == now->rson)
            {
                now->rson = getNodeY();
                now->rson->l = mid + 1;
                now->rson->r = now->r;
            }
            update(now->rson, y, k1, k2);
        }

        push_up(now);
    }

    pair<int, int> query(node_y * now, int l, int r)
    {
        if (NULL == now)
            return {RES_INIT, RES_INIT};
        if (now->l >= l && now->r <= r)
            return {now->res1, now->res2};
        int mid = (now->l + now->r) >> 1;
        if (r <= mid)
            return query(now->lson, l, r);
        else if (l > mid)
            return query(now->rson, l, r);
        else
        {
            pair<int, int> ls = query(now->lson, l, mid);
            pair<int, int> rs = query(now->rson, mid + 1, r);
            return {max(ls.first, rs.first), max(ls.second, rs.second)};
        }
    }

private:
    void push_up(node_y * now)
    {
        if (now)
        {
            if (now->lson)
            {
                now->res1 = now->lson->res1;
                now->res2 = now->lson->res2;
            }

            if (now->rson && now->res1 < now->rson->res1)
            {
                now->res1 = now->rson->res1;
            }

            if (now->rson && now->res2 < now->rson->res2)
            {
                now->res2 = now->rson->res2;
            }
        }
    }
};

class node_x
{
public:
    int l, r;
    tree_y tr;
    node_x * lson;
    node_x * rson;

    node_x(int _l, int _r, int _y) : l(_l), r(_r), tr(_y)
    {
        lson = rson = NULL;
    }

    node_x(){}

    void init()
    {
        l = r = 0;
        lson = rson = NULL;

    }
};

vector<node_x> poolx;
int idxx;

node_x * getNodeX()
{
    node_x * ret = NULL;

    ret = &(poolx[idxx ++]);
    ret->init();

    return ret;
}

class tree_x
{
public:
    node_x root;
    int maxy;

    tree_x(int _maxx, int _maxy) : root(1, _maxx, _maxy)
    {
        maxy = _maxy;
    }

    void update(node_x * now, int x, int y, int k1, int k2)
    {
        now->tr.update(&(now->tr.root), y, k1, k2);
        if (now->l == now->r)
            return;
        int mid = (now->l + now->r) >> 1;
        if (x <= mid)
        {
            if (NULL == now->lson)
            {
                now->lson = getNodeX();
                now->lson->l = now->l;
                now->lson->r = mid;
                now->lson->tr.root.init();
                now->lson->tr.root.l = 1;
                now->lson->tr.root.r = maxy;
            }
            update(now->lson, x, y, k1, k2);
        }
        else
        {
            if (NULL == now->rson)
            {
                now->rson = getNodeX();
                now->rson->l = mid + 1;
                now->rson->r = now->r;
                now->rson->tr.root.init();
                now->rson->tr.root.l = 1;
                now->rson->tr.root.r = maxy;
            }
            update(now->rson, x, y, k1, k2);
        }
    }

    pair<int, int> query(node_x * now, int lx, int rx, int ly, int ry)
    {
        if (NULL == now)
            return {RES_INIT, RES_INIT};
        if (now->l >= lx && now->r <= rx)
        {
            return now->tr.query(&(now->tr.root), ly, ry);
        }
        int mid = (now->l + now->r) >> 1;
        if (rx <= mid)
            return query(now->lson, lx, rx, ly, ry);
        else if (lx > mid)
            return query(now->rson, lx, rx, ly, ry);
        else
        {
            pair<int, int> ls = query(now->lson, lx, mid, ly, ry);
            pair<int, int> rs = query(now->rson, mid + 1, rx, ly, ry);
            return {max(ls.first, rs.first), max(ls.second, rs.second)};
        }
    }
};

class Event 
{
public:
    int x, t;
    long long a, b;
    int ai, bi;
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

void deduplication(vector<long long> &xs)
{
    sort(xs.begin(), xs.end());               // 先对vector进行排序
    auto last = unique(xs.begin(), xs.end()); // 去除重复的元素
    xs.erase(last, xs.end());                 // 删除多余的元素
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    pooly.resize(10000000);
    poolx.resize(600000);

    int n;
    cin >> n;

    vector<Event> events;

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

    sort(events.begin(), events.end(), myfunc);

    vector<long long> as, bs;
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
    
    int rslt1 = 0;
    int rslt2 = 0;

    // 情况 1
    {
        idxy = 0;
        idxx = 0;

        tree_x tree(MAX_N, MAX_N);

        for (size_t i = 0; i < n; i++)
        {
            pair<int, int> pre = tree.query(&(tree.root), 1, events[i].ai, 1, events[i].bi);
            pair<int, int> now;
            if (0 < pre.first)
            {
                now.first = pre.first + 1;
            }
            else
            {
                // 0 == pre
                if (0 <= events[i].a && 0 <= events[i].b)
                {
                    now.first = 1;
                }
            }

            now.second = pre.second + 1;

            tree.update(&(tree.root), events[i].ai, events[i].bi, now.first, now.second);

            if (rslt1 < now.first)
            {
                rslt1 = now.first;
            }

            if (rslt2 < now.second)
            {
                rslt2 = now.second;
            }
        }
    }

    cout << rslt1 << " " << rslt2 << "\n";

    return 0;
}
