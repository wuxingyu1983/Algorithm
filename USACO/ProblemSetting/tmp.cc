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
long long dp[2][1048576];
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

    int act = 0;

    for (size_t i = 0; i < n; i++)
    {
        dp[act][problems[i]]++;
        origin[problems[i]]++;
    }

    int finalSt = (1 << m) - 1;

    for (size_t i = 0; i <= finalSt; i++)
    {
        if (1 < dp[act][i])
        {
            // A[n][1] + A[n][2] + ... + A[n][n]
            long long tmp = 1;
            long long sum = 0;

            for (size_t j = 1; j <= dp[act][i]; j++)
            {
                tmp *= dp[act][i] - j + 1;
                tmp %= MOD;

                sum += tmp;
                sum %= MOD;
            }

            dp[act][i] = sum;
            origin[i] = sum;
        }
    }

    dp[act][0]++;

    int nAct = 1 - act;

    for (size_t lp = 0; lp < m; lp++)
    {
        memcpy(dp[nAct], dp[act], sizeof(dp[act]));

        swap(act, nAct);

        for (int i = 0; i < m; ++i)
        {
            for (int mask = finalSt; mask > 0; mask--)
            {
                if (mask & (1 << i))
                {
                    dp[act][mask] += dp[act][mask ^ (1 << i)];
                    dp[act][mask] %= MOD;
                }
            }
        }

        for (int mask = finalSt; mask > 0; mask--)
        {
            if (0 < origin[mask])
            {
                long long tmp = (dp[act][mask] - dp[nAct][mask] + MOD) % MOD;   // mask 的真子集

                dp[act][mask] = origin[mask] * tmp;
                dp[act][mask] %= MOD;
            }
            else
            {
                dp[act][mask] = 0;
            }
        }
    }

    long long ans = 0;

    for (size_t i = 0; i <= finalSt; i++)
    {
        ans += dp[act][i];
        ans %= MOD;
    }

    cout << ans - 1 << endl;

    return 0;
}
