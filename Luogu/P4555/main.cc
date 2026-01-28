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

int main()
{
    string str;
    cin >> str;

    string sp = preprocString(str);

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

    return 0;
}
