// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2470

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

string extend(string &s)
{
    string ret(s);
    string sp = preprocString(s);

    memset(P, 0, sizeof(P));

    int n = sp.length();
    int C = 0, R = 0;
    int i_mirror = 0;
    int centerIndex = 0, max = 0;
    for (int i = 1; i < n - 1; i++)
    {
        i_mirror = 2 * C - i;
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

        if (n - 2 == R)
        {
            i_mirror = 2 * C - i;
            max = P[i];
            centerIndex = i;
            break;
        }
    }

    if (1 < i_mirror)
    {
        int idx = (centerIndex - max) / 2 - 1;
        while (0 <= idx)
        {
            ret += s.at(idx);
            idx--;
        }
    }

    return ret;
}

int main()
{
    string str;

    while (cin >> str)
    {
        cout << extend(str) << endl;
    }

    return 0;
}
