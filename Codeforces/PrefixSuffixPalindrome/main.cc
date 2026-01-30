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

int P[2000005];

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
    string ret;
    int l = 0, r = str.length() - 1;
    string pre;

    if (l <= r && str.at(l) == str.at(r))
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
    }

    return ret;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        string str;
        cin >> str;

        cout << func(str) << endl;
    }
    
    return 0;
}
