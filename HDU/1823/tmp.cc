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
#include <map>

using namespace std;

class node_y
{
public:
    int l, r;
    int res;

    node_y * lson;
    node_y * rson;

    node_y()
    {
        lson = rson = NULL;
        l = r = 0;
        res = -1;
    }
};

// 内层线段树
class tree_y
{
public:
    node_y root;

    void init(int m)
    {
        root.l = 1;
        root.r = m;
    }

    void update(node_y * now, int y, int k)
    {
        if (now->l == now->r)
        {
            now->res = max(now->res, k);
            return;
        }
        int mid = (now->l + now->r) >> 1;
        if (y <= mid)
        {
            if (NULL == now->lson)
            {
                now->lson = new node_y();
                now->lson->l = now->l;
                now->lson->r = mid;
            }
            update(now->lson, y, k);
        }
        else
        {
            if (NULL == now->rson)
            {
                now->rson = new node_y();
                now->rson->l = mid + 1;
                now->rson->r = now->r;
            }
            update(now->rson, y, k);
        }

        push_up(now);
    }

    int query(node_y * now, int l, int r)
    {
        if (NULL == now)
            return -1;
        if (now->l >= l && now->r <= r)
            return now->res;
        int mid = (now->l + now->r) >> 1;
        if (r <= mid)
            return query(now->lson, l, r);
        else if (l > mid)
            return query(now->rson, l, r);
        else
            return max(query(now->lson, l, mid), query(now->rson, mid + 1, r));
    }

private:
    void push_up(node_y * now)
    {
        if (now)
        {
            if (now->lson)
            {
                now->res = now->lson->res;
            }

            if (now->rson && now->res < now->rson->res)
            {
                now->res = now->rson->res;
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

    node_x()
    {
        l = r = 0;
        lson = rson = NULL;
    }
};

class tree_x
{
public:
    node_x root;
    int n;

    void init(int _m, int _n)
    {
        root.l = 1;
        root.r = _m;

        n = _n;
        root.tr.init(_n);
    }

    void update(node_x * now, int x, int y, int k)
    {
        now->tr.update(&(now->tr.root), y, k);
        if (now->l == now->r)
            return;
        int mid = (now->l + now->r) >> 1;
        if (x <= mid)
        {
            if (NULL == now->lson)
            {
                now->lson = new node_x();
                now->lson->l = now->l;
                now->lson->r = mid;

                now->lson->tr.init(n);
            }
            update(now->lson, x, y, k);
        }
        else
        {
            if (NULL == now->rson)
            {
                now->rson = new node_x();
                now->rson->l = mid + 1;
                now->rson->r = now->r;

                now->rson->tr.init(n);
            }
            update(now->rson, x, y, k);
        }
    }

    int query(node_x * now, int lx, int rx, int ly, int ry)
    {
        if (NULL == now)
            return -1;
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
            return max(query(now->lson, lx, mid, ly, ry), query(now->rson, mid + 1, rx, ly, ry));
    }
};
int n;
tree_x tree;
int main()
{
    while (~scanf("%d", &n))
    {
        if (n == 0)
            break;
        tree.init(1005, 205);
        while (n--)
        {
            char op[5];
            scanf("%s", op + 1);
            if (op[1] == 'I')
            {
                int h, b;
                double a, l;
                scanf("%d%lf%lf", &h, &a, &l);
                b = a * 10 + 1;
                tree.update(&(tree.root), h, b, l * 10);
            }
            else if (op[1] == 'Q')
            {
                int h1, h2, b1, b2;
                double a1, a2;
                scanf("%d%d%lf%lf", &h1, &h2, &a1, &a2);
                b1 = a1 * 10 + 1;
                b2 = a2 * 10 + 1;
                if (h1 > h2)
                    swap(h1, h2);
                if (b1 > b2)
                    swap(b1, b2);
                int ans = tree.query(&(tree.root), h1, h2, b1, b2);
                if (ans == -1)
                    printf("%d\n", ans);
                else
                    printf("%.1lf\n", ans / 10.0);
            }
        }
    }
}
