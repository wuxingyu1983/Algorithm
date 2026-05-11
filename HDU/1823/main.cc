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

#define MAXN 1010
#define MAXM 210
#define lson now << 1
#define rson now << 1 | 1
using namespace std;
struct node_y
{
    int l, r;
    int res;
};
// 内层线段树
struct tree_y
{
    node_y tree[MAXN << 2];
    void push_up(int now) { tree[now].res = max(tree[lson].res, tree[rson].res); };
    void build(int now, int l, int r)
    {
        tree[now].l = l;
        tree[now].r = r;
        tree[now].res = -1;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
        push_up(now);
    }
    void update(int now, int y, int k)
    {
        if (tree[now].l == tree[now].r)
        {
            tree[now].res = max(tree[now].res, k);
            return;
        }
        int mid = (tree[now].l + tree[now].r) >> 1;
        if (y <= mid)
            update(lson, y, k);
        else
            update(rson, y, k);
        push_up(now);
    }
    int query(int now, int l, int r)
    {
        if (tree[now].l >= l && tree[now].r <= r)
            return tree[now].res;
        int mid = (tree[now].l + tree[now].r) >> 1;
        if (r <= mid)
            return query(lson, l, r);
        else if (l > mid)
            return query(rson, l, r);
        else
            return max(query(lson, l, mid), query(rson, mid + 1, r));
    }
};
struct node_x
{
    int l, r;
    tree_y tr;
};
struct tree_x
{
    int m;
    node_x tree[MAXM << 2];
    void build(int now, int l, int r)
    {
        tree[now].l = l;
        tree[now].r = r;
        tree[now].tr.build(1, 1, m);
        if (tree[now].l == tree[now].r)
            return;
        int mid = (l + r) >> 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
    }
    void update(int now, int x, int y, int k)
    {
        tree[now].tr.update(1, y, k);
        if (tree[now].l == tree[now].r)
            return;
        int mid = (tree[now].l + tree[now].r) >> 1;
        if (x <= mid)
            update(lson, x, y, k);
        else
            update(rson, x, y, k);
    }
    int query(int now, int lx, int rx, int ly, int ry)
    {
        if (tree[now].l >= lx && tree[now].r <= rx)
        {
            return tree[now].tr.query(1, ly, ry);
        }
        int mid = (tree[now].l + tree[now].r) >> 1;
        if (rx <= mid)
            return query(lson, lx, rx, ly, ry);
        else if (lx > mid)
            return query(rson, lx, rx, ly, ry);
        else
            return max(query(lson, lx, mid, ly, ry), query(rson, mid + 1, rx, ly, ry));
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
        tree.m = 1005;
        tree.build(1, 1, 205);
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
                tree.update(1, h, b, l * 10);
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
                int ans = tree.query(1, h1, h2, b1, b2);
                if (ans == -1)
                    printf("%d\n", ans);
                else
                    printf("%.1lf\n", ans / 10.0);
            }
        }
    }
}
