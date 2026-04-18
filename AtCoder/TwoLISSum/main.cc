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

const int MAX_N = 300001;
vector<int> vecA, vecB;
int preMaxA[MAX_N]; // 顺序处理 vecA, idx 时，之前以1 —— vecA[idx]为结尾的 LIS 的最大长度
int preMaxB[MAX_N];

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

    vector<int> da(n * 4 + 10, 0);
    vector<int> db(n * 4 + 10, 0);
    
    int max = 0;
    int maxA = 0, maxB = 0;

    // get origin LIS(A) + LIS(B)
    for (size_t i = 0; i < n; i++)
    {
        int l = getMax(da, 1, vecA[i], 1, n, 1);
        if (maxA < l + 1)
        {
            maxA = l + 1;
        }

        preMaxA[i] = l + 1;
        update(da, vecA[i], l + 1, 1, n, 1);
    }
    
    for (size_t i = 0; i < n; i++)
    {
        int l = getMax(db, 1, vecB[i], 1, n, 1);
        if (maxB < l + 1)
        {
            maxB = l + 1;
        }

        preMaxB[i] = l + 1;
        update(db, vecB[i], l + 1, 1, n, 1);
    }

    max = maxA + maxB;
    
    

    cout << max << "\n";

    return 0;
}
