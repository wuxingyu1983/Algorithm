// https://usaco.org/index.php?page=viewproblem2&cpid=1309
// https://www.luogu.com.cn/problem/P9131

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;

#define MAX_N 100001
#define MOD 1000000007

int problems[MAX_N];
long long dp[1048576];
long long origin[1048576];

int n, m;

int main()
{
    cin >> n >> m;

    for (size_t i = 0; i < m; i++)
    {
        string str;
        cin >> str;

        for (size_t j = 0; j < n; j++)
        {
            if ('H' == str.at(j))
            {
                problems[j] |= 1 << i;
            }
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        dp[problems[i]]++;
        origin[problems[i]]++;
    }

    int finalSt = (1 << m) - 1;

    for (size_t i = 0; i <= finalSt; i++)
    {
        if (1 < dp[i])
        {
            // A[n][1] + A[n][2] + ... + A[n][n]
            long long tmp = 1;
            long long sum = 0;

            for (size_t j = 1; j <= dp[i]; j++)
            {
                tmp *= dp[i] - j + 1;
                tmp %= MOD;

                sum += tmp;
                sum %= MOD;
            }

            dp[i] = sum;
            origin[i] = sum;
        }
    }

    dp[0]++;

    for (size_t lp = 0; lp < m; lp++)
    {
        for (int i = 0; i < m; ++i)
        {
            for (int mask = finalSt; mask > 0; mask--)
            {
                if (0 < origin[mask])
                {
                    long long tmp = dp[0];
                    for (int subMask = (mask - 1) & mask; subMask > 0; subMask = (subMask - 1) & mask)
                    {
                        tmp += dp[subMask];
                        tmp %= MOD;
                    }

                    dp[mask] = origin[mask] * tmp;
                    dp[mask] %= MOD;
                }
                /*
                                if (mask & (1 << i))
                                {
                                    dp[mask] += dp[mask ^ (1 << i)];
                                    dp[mask] %= MOD;
                                }
                */
            }
        }
    }

    long long ans = 0;

    for (size_t i = 0; i <= finalSt; i++)
    {
        ans += dp[i];
        ans %= MOD;
    }

    cout << ans - 1 << endl;

    return 0;
}
