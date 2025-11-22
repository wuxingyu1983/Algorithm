// https://codeforces.com/problemset/problem/914/C

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

const int mod = 1000000007;

int C[1001][1001];
int ops[1001];
long long dp[1001];

int main()
{
    string strN;
    int k;

    cin >> strN;
    cin >> k;

    // init
    {
        ops[1] = 1;
        for (size_t i = 2; i <= 1000; i++)
        {
            ops[i] = 1 + ops[__builtin_popcount(i)];
        }

        for (size_t n = 1; n <= 1000; n++)
        {
            for (size_t m = 0; m <= n; m++)
            {
                if (0 == m || m == n)
                {
                    C[n][m] = 1;
                }
                else
                {
                    C[n][m] = C[n - 1][m] + C[n - 1][m - 1];
                    C[n][m] %= mod;
                }
            }
        }
    }

    int preOnes = 0;
    for (size_t pos = 0; pos < strN.length(); pos++)
    {
        int num = strN.at(pos) - '0';

        if (0 < num)
        {
            int remain = strN.length() - 1 - pos;

            if (0 < remain)
            {
                for (size_t i = 0; i <= remain; i++)
                {
                    dp[preOnes + i] += C[remain][i];
                    dp[preOnes + i] %= mod;
                }
            }
        }

        preOnes += num;
    }

    dp[preOnes] += 1;
    dp[preOnes] %= mod;

    int ret = 0;

    if (0 == k)
    {
        if (0 < preOnes)
        {
            ret = 1;
        }
    }
    else
    {
        for (size_t i = 0; i <= 1000; i++)
        {
            if (k == ops[i])
            {
                ret += dp[i];
                ret %= mod;
            }
        }

        if (1 == k)
        {
            ret += mod - 1;
            ret %= mod;
        }
    }

    cout << ret << endl;

    return 0;
}
