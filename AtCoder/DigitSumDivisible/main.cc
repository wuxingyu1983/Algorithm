// https://atcoder.jp/contests/abc336/tasks/abc336_e

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

long long dp[15][127][127]; // dp[pos][sum][mod]
int powers[15];

long long func(string strN, int m)
{
    long long ret = 0;
    int len = strN.length();

    // init
    {
        memset(powers, 0, sizeof(powers));
        powers[0] = 1 % m;
        for (size_t i = 1; i < 15; i++)
        {
            powers[i] = (powers[i - 1] * 10) % m;
        }

        memset(dp, 0, sizeof(dp));
        int pos = 0;
        for (size_t n = 0; n < 10; n++)
        {
            dp[pos][n][n % m] = 1;
            if (pos < len - 1 && n == m)
            {
                ret++;
            }
        }

        for (pos = 1; pos < len - 1; pos++)
        {
            for (int oldSum = 0; oldSum <= m; oldSum++)
            {
                for (int oldMod = 0; oldMod < m; oldMod++)
                {
                    if (dp[pos - 1][oldSum][oldMod])
                    {
                        for (int n = 0; n < 10; n++)
                        {
                            int newSum = oldSum + n;
                            if (newSum <= m)
                            {
                                int newMod = (powers[pos] * n + oldMod) % m;
                                dp[pos][newSum][newMod] += dp[pos - 1][oldSum][oldMod];
                                if (m == newSum && 0 == newMod)
                                {
                                    ret += dp[pos - 1][oldSum][oldMod];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int preSum = 0, preMod = 0;
    for (size_t pos = 0; pos < len; pos++)
    {
        int d = strN.at(pos) - '0';
        int down = 0, up = d - 1;
        if (0 == pos)
        {
            down = 1;
        }
        if (len - 1 == pos)
        {
            up = d;
        }

        for (int n = down; n <= up; n++)
        {
            int tmpSum = preSum + n;
            if (m < tmpSum)
            {
                break;
            }

            int tmpMod = (preMod * 10 + n * powers[len - 1 - pos]) % m;
            if (len - 1 == pos)
            {
                if (m == tmpSum && 0 == tmpMod)
                {
                    ret++;
                }
            }
            else
            {
                ret += dp[len - 2 - pos][m - tmpSum][(m - tmpMod) % m];
            }
        }

        preSum += d;
        if (m < preSum)
        {
            break;
        }
        preMod = (preMod * 10 + d * powers[len - 1 - pos]) % m;
    }

    return ret;
}

int main()
{
    string strN;
    cin >> strN;

    long long ans = 0;

    int maxM = 126;
    if (maxM > 9 * strN.length())
    {
        maxM = 9 * strN.length();
    }

    for (size_t m = 1; m <= maxM; m++)
    {
        ans += func(strN, m);
    }

    cout << ans << endl;

    return 0;
}
