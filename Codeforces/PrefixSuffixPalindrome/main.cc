// https://codeforces.com/contest/1326/problem/D2

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

int P[2000100];

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

string func(string &str)
{
    memset(P, 0, sizeof(int) * (str.length() * 2 + 3));

    string ret;
    int l = 0, r = str.length() - 1;
    string pre;

    while (l <= r && str.at(l) == str.at(r))
    {
        pre += str.at(l);
        l ++;
        r --;
    }

    if (l > r)
    {
        ret = str;
    }
    else
    {
        string s(str, l, r - l + 1);
        string sp = preprocString(s);
        int n = sp.length();
        int C = 0, R = 0;

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
            }

            // 碰到之前讲的三种情况时候，需要利用中心扩展法
            while (sp.at(i + 1 + P[i]) == sp.at(i - 1 - P[i]))
            {
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
        int centerIndex = 0;
        for (int i = 1; i < n - 1; i++)
        {
            if (P[i] > max && (1 == i - P[i] || n - 2 == i + P[i]))
            {
                max = P[i];
                centerIndex = i;
            }
        }
        int start = (centerIndex - max) / 2; // 最开始讲的求原字符串下标
        string mid(s.begin() + start, s.begin() + start + max);

        ret += pre;
        ret += mid;
        reverse(pre.begin(), pre.end());
        ret += pre;
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        string str;
        cin >> str;

        cout << func(str) << "\n";
    }
    
    return 0;
}
