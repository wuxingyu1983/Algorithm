// https://www.luogu.com.cn/problem/P4555

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

using namespace std;

int P[200005];
int L[200005];

string preprocString(string &s)
{
    string ret = "^";
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        ret += '#';
        ret += s.at(i);
    }
    ret += "#$";

    return ret;
}

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
        int tmp = update(d, idx, c, s, m, p * 2);
        if (tmp > d[p])
        {
            d[p] = tmp;
        }
    }
    if (idx > m)
    {
        int tmp = update(d, idx, c, m + 1, t, p * 2 + 1);
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
    string str;
    cin >> str;

    string sp = preprocString(str);

    int n = sp.length();
    int C = 0, R = 0;
    vector<int> d(4 * n + 5, 0);

    for (int i = 1; i < n - 1; i++)
    {
        int i_mirror = 2 * C - i;
        if (R > i)
        {
            P[i] = min(R - i, P[i_mirror]); // 防止超出 R
        }
        else
        {
            P[i] = 0; // 等于 R 的情况
            if (0 == L[i])
            {
                L[i] = 1;
            }
        }

        // 碰到之前讲的三种情况时候，需要利用中心扩展法
        while (sp.at(i + 1 + P[i]) == sp.at(i - 1 - P[i]))
        {
            L[i + 1 + P[i]] = 2 * P[i] + 3;
            P[i]++;
        }

        // 判断是否需要更新 R
        if (i + P[i] > R)
        {
            C = i;
            R = i + P[i];
        }
    }

    int max = 0;
    for (int i = 1; i < n - 2; i++)
    {
        int len = 2 * P[i] + 1;
        int left = i - P[i];

        while (1 < left && left <= i && len >= 0)
        {
            if (max < len + L[left - 1])
            {
                max = len + L[left - 1];
            }

            len -= 2;
            left += 1;
        }
    }

    cout << max / 2 << endl;

    return 0;
}
