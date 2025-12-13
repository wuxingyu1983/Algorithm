// https://toph.co/p/noora-number

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
#include <unordered_map>
#include <bitset>

using namespace std;

#pragma GCC target("popcnt")

int flag[1024];
long long dp[20][1024];
long long sum[20];

long long func(string strNum)
{
    long long ret = 0;
    int len = strNum.length();
    int pre = 0;

    for (size_t pos = 0; pos < len; pos++)
    {
        int d = strNum.at(pos) - '0';
        int down = 0;
        int up = d - 1;
        if (0 == pos)
        {
            down = 1;
            ret += sum[len - pos - 2];
        }

        if (len - 1 == pos)
        {
            up = d;

            for (size_t n = down; n <= up; n++)
            {
                if (flag[pre | (1 << n)])
                {
                    ret ++;
                }
            }
        }
        else
        {
            if (0 < d)
            {
                for (size_t i = 1; i < 1024; i++)
                {
                    if (dp[len - pos - 2][i])
                    {
                        for (size_t n = down; n <= up; n++)
                        {
                            if (flag[pre | i | (1 << n)])
                            {
                                ret += dp[len - pos - 2][i];
                            }
                        }
                    }
                }
            }
        }

        pre |= 1 << d;
    }
    

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    vector<string> vec;
    for (size_t i = 0; i < t; i++)
    {
        string str;
        cin >> str;

        vec.push_back(str);
    }
    
    // init
    {
        for (size_t n = 1; n < 1024; n++)
        {
            int max = 0;
            for (int i = 9; i >= 0; i--)
            {
                if (n & (1 << i))
                {
                    max = i;
                    break;
                }
            }

            if (__builtin_popcount(n) == max)
            {
                flag[n] = 1;
            }
        }

        int pos = 0;
        for (size_t i = 0; i < 10; i++)
        {
            dp[pos][1 << i] = 1;
            if (flag[1 << i])
            {
                sum[pos] ++;
            }
        }
       
        for (; pos < 19; pos++)
        {
            for (size_t n = 1; n < 1024; n++)
            {
                if (dp[pos][n])
                {
                    for (size_t i = 0; i < 10; i++)
                    {
                        dp[pos + 1][n | (1 << i)] += dp[pos][n];

                        if (0 < i && flag[n | (1 << i)])
                        {
                            sum[pos + 1] += dp[pos][n];
                        }
                    }
                }
            }
        }

        for (pos = 1; pos < 20; pos++)
        {
            sum[pos] += sum[pos - 1];
        }
    }

    for (size_t i = 0; i < t; i++)
    {
        long long ans = func(vec[i]);
        cout << ans << "\n";
    }

    return 0;
}
