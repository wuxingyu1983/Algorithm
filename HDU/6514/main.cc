// https://acm.hdu.edu.cn/showproblem.php?pid=6514

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;

#define MAX_MN 10000001
#define ROOT 1

char land[MAX_MN];
int dp[MAX_MN];

class Monitor
{
public:
    int x1, y1, x2, y2;

    Monitor(int _x1, int _y1, int _x2, int _y2) : x1(_x1),
                                                  y1(_y1),
                                                  x2(_x2),
                                                  y2(_y2) {}
};

vector<Monitor> vecIn;      // 进入扫描线的顺序队列
vector<Monitor> vecOut;     // 出扫描线的顺序队列

bool cmpIn (Monitor &a, Monitor &b) { return a.y1 < b.y1; }
bool cmpOut (Monitor &a, Monitor &b) { return a.y2 < b.y2; }

vector<int> d;
vector<int> b;

void update(int l, int r, int c, int s, int t, int p)
{
    // [l, r] 为修改区间, c 为被修改的元素的变化量, [s, t] 为当前节点包含的区间, p
    // 为当前节点的编号
    if (l <= s && t <= r)
    {
        d[p] += (t - s + 1) * c, b[p] += c;
        return;
    } // 当前区间为修改区间的子集时直接修改当前节点的值,然后打标记,结束修改
    int m = s + ((t - s) >> 1);
    if (b[p] && s != t)
    {
        // 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p]; // 将标记下传给子节点
        b[p] = 0;                               // 清空当前节点的标记
    }
    if (l <= m)
        update(l, r, c, s, m, p * 2);
    if (r > m)
        update(l, r, c, m + 1, t, p * 2 + 1);
    d[p] = d[p * 2] + d[p * 2 + 1];
}

int getsum(int l, int r, int s, int t, int p)
{
    // [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p 为当前节点的编号
    if (l <= s && t <= r)
        return d[p];
    // 当前区间为询问区间的子集时直接返回当前区间的和
    int m = s + ((t - s) >> 1);
    if (b[p])
    {
        // 如果当前节点的懒标记非空,则更新当前节点两个子节点的值和懒标记值
        d[p * 2] += b[p] * (m - s + 1), d[p * 2 + 1] += b[p] * (t - m);
        b[p * 2] += b[p], b[p * 2 + 1] += b[p]; // 将标记下传给子节点
        b[p] = 0;                               // 清空当前节点的标记
    }
    int sum = 0;
    if (l <= m)
        sum = getsum(l, r, s, m, p * 2);
    if (r > m)
        sum += getsum(l, r, m + 1, t, p * 2 + 1);
    return sum;
}

int main()
{
    int n, m;   // n = rows, m = cols
    cin >> n >> m;

    int p;
    cin >> p;

    vecIn.reserve(p + 1);
    vecOut.reserve(p + 1);
    
    for (size_t i = 0; i < p; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        x1 --;
        y1 --;
        x2 --;
        y2 --;

        vecIn.push_back(Monitor(x1, y1, x2, y2));
    }

    // sort
    sort(vecIn.begin(), vecIn.end(), cmpIn);

    // segment tree
    d.resize(4 * n, 0);
    b.resize(4 * n, 0);

    int vecInHead = 0;
    int vecOutHead = 0;

    for (size_t col = 0; col < m; col++)
    {
        bool needSort = false;

        while (vecInHead < vecIn.size() && vecIn[vecInHead].y1 == col)
        {
            update(vecIn[vecInHead].x1, vecIn[vecInHead].x2, 1, 0, n - 1, ROOT);

            vecOut.push_back(vecIn[vecInHead]);
            needSort = true;

            vecInHead ++;
        }

        if (needSort)
        {
            sort(vecOut.begin(), vecOut.end(), cmpOut);
        }

        if (0 < vecOut.size())
        {
            for (size_t row = 0; row < n; row++)
            {
                if (0 < getsum(row, row, 0, n - 1, ROOT))
                {
                    land[row * m + col] = 1;
                }
            }
        }

        while (vecOutHead < vecOut.size() && vecOut[vecOutHead].y2 == col)
        {
            update(vecOut[vecOutHead].x1, vecOut[vecOutHead].x2, -1, 0, n - 1, ROOT);

            vecOutHead++;
        }
    }

    for (size_t row = 0; row < n; row++)
    {
        for (size_t col = 1; col < m; col++)
        {
            dp[row * m + col] += dp[row * m + col - 1] + land[row * m + col];
        }
    }

    for (size_t col = 0; col < m; col++)
    {
        for (size_t row = 1; row < n; row++)
        {
            dp[row * m + col] += dp[(row - 1) * m + col];
        }
    }

    int q;
    cin >> q;

    for (size_t i = 0; i < q; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        x1 --;
        y1 --;
        x2 --;
        y2 --;

        int total = (y2 - y1 + 1) * (x2 - x1 + 1);
        int cnt = dp[x2 * m + y2];
        if (0 < x1)
            cnt -= dp[(x1 - 1) * m + y2];
        if (0 < y1)
            cnt -= dp[x2 * m + (y1 - 1)];
        if (0 < x1 && 0 < y1)
            cnt += dp[(x1 - 1) * m + (y1 - 1)];
        if (total == cnt)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    

    return 0;
}
