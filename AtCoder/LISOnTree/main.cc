// https://atcoder.jp/contests/abc165/tasks/abc165_f

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

    vector<int> vecA(n + 1, 0);
    for (size_t i = 1; i <= n; i++)
    {
        int a;
        cin >> a;

        vecA[i] = a;
    }
    
    

    return 0;
}
