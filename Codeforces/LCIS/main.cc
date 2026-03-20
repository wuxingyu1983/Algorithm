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
int preIdx[MAX_NM][MAX_NM];
int len[MAX_NM][MAX_NM];

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
    int tmpN, tmpM;
    vector<long long> vecF;
    vector<long long> vecS;

    cin >> tmpN;
    for (size_t i = 0; i < tmpN; i++)
    {
        long long tmp;
        cin >> tmp;
        vecF.push_back(tmp);
    }

    cin >> tmpM;
    for (size_t i = 0; i < tmpM; i++)
    {
        long long tmp;
        cin >> tmp;
        vecS.push_back(tmp);
    }
    
    n = max(tmpN, tmpM);

    vector<long long> vxy;
    for (size_t i = 0; i < tmpN; i++)
    {
        for (size_t j = 0; j < tmpM; j++)
        {
            if (vecF[i] == vecS[j])
            {
                vxy.push_back((vecF[i] << 18) | ((i + 1) << 9) | (j + 1));
            }
        }
    }
    
    // sort
    sort(vxy.begin(), vxy.end());

    int maxLen = 0;
    int maxIdx = 0;
    long long lastV = -1;
    int beginPos = -1;

    for (size_t i = 0; i < vxy.size(); i++)
    {
        long long v = vxy[i] >> 18;
        int x = (vxy[i] >> 9) & 511;
        int y = vxy[i] & 511;

        if (lastV != v)
        {
            if (0 <= lastV)
            {
                while (beginPos < i)
                {
                    int tmpX = (vxy[beginPos] >> 9) & 511;
                    int tmpY = vxy[vxy[beginPos]] & 511;

                    upd1(1, n, 1, tmpX, tmpY, len[tmpX][tmpY]);

                    beginPos++;
                }
            }

            beginPos = i;
        }

        lastV = v;

        // find max in [1 - (x - 1)][1 - (y - 1)]
        qy1(1, n, 1, 1, x - 1, 1, y - 1);

        int tmpLen = 1 + mxans;
        len[x][y] = tmpLen;
        preIdx[x][y] = mxidxans;

        if (tmpLen > maxLen)
        {
            maxLen = tmpLen;
            maxIdx = (x << 9) | y;
        }
    }
    

    return 0;
}
