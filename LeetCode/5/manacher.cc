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

class Solution
{
public:
    string longestPalindrome(string s)
    {
        memset(P, 0, sizeof(P));
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

        // 找出 P 的最大值
        int max = 0;
        int centerIndex = 0;
        for (int i = 1; i < n - 1; i++)
        {
            if (P[i] > max)
            {
                max = P[i];
                centerIndex = i;
            }
        }
        int start = (centerIndex - max) / 2; // 最开始讲的求原字符串下标

        string ret(s.begin() + start, s.begin() + start + max);
        return ret;
    }

private:
    string preprocString(string s)
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

private:
    int P[2005];
};

int main()
{
    string str;
    cin >> str;

    Solution s;
    cout << s.longestPalindrome(str) << endl;

    return 0;
}
