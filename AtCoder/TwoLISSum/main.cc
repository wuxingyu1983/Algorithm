// https://atcoder.jp/contests/arc149/tasks/arc149_b

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

// 最优解，A 转换成 全部 递增的，B 的 LIS(B) + n

const int MAX_N = 300001;
vector<int> vecA, vecB;

// segment tree func
int update(vector<int> &d, int idx, int c, int s, int t, int p)
{
    if (idx == s && idx == t)
    {
        d[p] = c;
        return c;
    }
    int m = s + ((t - s) >> 1);
    if (idx <= m)
    {
        unsigned long long tmp = update(d, idx, c, s, m, p * 2);
        if (tmp > d[p])
        {
            d[p] = tmp;
        }
    }
    if (idx > m)
    {
        unsigned long long tmp = update(d, idx, c, m + 1, t, p * 2 + 1);
        if (tmp > d[p])
        {
            d[p] = tmp;
        }
    }

    return d[p];
}

int getMax(vector<int> &d, int l, int r, int s, int t, int p)
{
    if (l > r)
    {
        return 0;
    }
    if (l <= s && t <= r)
        return d[p];
    int m = s + ((t - s) >> 1);
    int max = 0;
    if (l <= m)
    {
        max = getMax(d, l, r, s, m, p * 2);
    }
    if (r > m)
    {
        int tmp = getMax(d, l, r, m + 1, t, p * 2 + 1);
        if (tmp > max)
        {
            max = tmp;
        }
    }
    return max;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        vecA.push_back(a);
    }

    for (size_t i = 0; i < n; i++)
    {
        int b;
        cin >> b;
        vecB.push_back(b);
    }

    vector<int> vec(n, 0);
    for (size_t i = 0; i < n; i++)
    {
        vec[vecA[i] - 1] = vecB[i];
    }
    
    int maxB = 0;
    vector<int> d(n * 4 + 10, 0);
    for (size_t i = 0; i < n; i++)
    {
        int l = getMax(d, 1, vec[i], 1, n, 1);
        if (maxB < l + 1)
        {
            maxB = l + 1;
        }
        update(d, vec[i], l + 1, 1, n, 1);
    }

    cout << n + maxB << "\n";

    return 0;
}
