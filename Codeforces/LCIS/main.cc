// https://codeforces.com/problemset/problem/10/D

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

const int MAX_NM = 510;
const int maxn = MAX_NM * 3;
const int inf = 1e8;
int n, q, mx[maxn][maxn], mxidx[maxn][maxn];
int fg, xo, mxidxans, mxans;

void upd2(int l, int r, int o, int x, int y, int v)
{
    if (l == r)
    {           // 如果找到了二维下标
        if (fg) // 如果此时正好找到了一维下标，就赋值
            mx[xo][o] = v, mxidx[xo][o] = (x << 9) | y;
        else
        { // 否则更新一维的情况
            if (mx[xo << 1][o] > mx[xo << 1 | 1][o])
            {
                mx[xo][o] = mx[xo << 1][o];
                mxidx[xo][o] = mxidx[xo << 1][o];
            }
            else
            {
                mx[xo][o] = mx[xo << 1 | 1][o];
                mxidx[xo][o] = mxidx[xo << 1 | 1][o];
            }
        }
        return;
    }
    int mid = l + ((r - l) >> 1);
    if (y <= mid)
        upd2(l, mid, o << 1, x, y, v);
    else
        upd2(mid + 1, r, o << 1 | 1, x, y, v);
    if (mx[xo][o << 1] > mx[xo][o << 1 | 1])
    {
        mx[xo][o] = mx[xo][o << 1];
        mxidx[xo][o] = mxidx[xo][o << 1];
    }
    else
    {
        mx[xo][o] = mx[xo][o << 1 | 1];
        mxidx[xo][o] = mxidx[xo][o << 1 | 1];
    }
}

void upd1(int l, int r, int o, int x, int y, int v)
{ // x为要更新的一维下标，y为要更新的二维下标
    if (l == r)
    {
        fg = 1; // 打上标记方便二维线段树确定一维节点
        xo = o;
        upd2(1, n, 1, x, y, v);
        return;
    }
    int mid = l + ((r - l) >> 1);
    if (x <= mid)
        upd1(l, mid, o << 1, x, y, v);
    else
        upd1(mid + 1, r, o << 1 | 1, x, y, v);
    fg = 0, xo = o;
    upd2(1, n, 1, x, y, v);
}

void qy2(int l, int r, int o, int pre, int ly, int ry)
{
    if (ly <= l && ry >= r)
    {
        mxans = max(mxans, mx[pre][o]);
        if (mxans <= mx[pre][o])
        {
            mxidxans = mxidx[pre][o];
        }
        return;
    }
    int mid = l + ((r - l) >> 1);
    if (ly <= mid)
        qy2(l, mid, o << 1, pre, ly, ry);
    if (ry > mid)
        qy2(mid + 1, r, o << 1 | 1, pre, ly, ry);
}

void qy1(int l, int r, int o, int lx, int rx, int ly, int ry)
{
    if (lx <= l && rx >= r)
    {
        qy2(1, n, 1, o, ly, ry);
        return;
    }
    int mid = l + ((r - l) >> 1);
    if (lx <= mid)
        qy1(l, mid, o << 1, lx, rx, ly, ry);
    if (rx > mid)
        qy1(mid + 1, r, o << 1 | 1, lx, rx, ly, ry);
}

int main()
{
    int n, m;
    vector<int> vecF;
    vector<int> vecS;

    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        vecF.push_back(tmp);
    }

    cin >> m;
    for (size_t i = 0; i < m; i++)
    {
        int tmp;
        cin >> tmp;
        vecS.push_back(tmp);
    }
    


    return 0;
}
