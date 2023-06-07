// https://www.luogu.com.cn/problem/P2051

#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
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

#define DEBUG   0
#define MOD     9999973
#define MAX_MN  102

long long dp[MAX_MN][MAX_MN][MAX_MN];     // dp[第i行][单个列的数量][两个列的数量]

int main()
{
    long long n, m;

    scanf("%lld %lld", &n, &m);

    int ans = 0;

    dp[1][1][0] = m;
    dp[1][2][0] = m * (m - 1) / 2;
    dp[1][0][0] = 1;

    if (1 == n)
    {
        ans = 1 + m + m * (m - 1) / 2;
    }
    else
    {
        for (size_t row = 2; row <= n; row++)
        {
            for (long long i = 0; i <= m; i++)
            {
                for (long long j = 0; j <= m; j++)
                {
                    if (m < i + j)
                    {
                        break;
                    }

                    dp[row][i][j] = dp[row - 1][i][j];

                    // 此行 只有 一个 炮
                    if (0 < i)
                    {
                        dp[row][i][j] += dp[row - 1][i - 1][j] * (m - i + 1 - j);
                        dp[row][i][j] %= MOD;
                    }

                    if (0 < j)
                    {
                        dp[row][i][j] += dp[row - 1][i + 1][j - 1] * (i + 1);
                        dp[row][i][j] %= MOD;
                    }

                    // 此行 有 2个 炮
                    if (1 < i)
                    {
                        dp[row][i][j] += dp[row - 1][i - 2][j] * (m - i + 2 - j) * (m - i + 1 - j) / 2;
                        dp[row][i][j] %= MOD;
                    }

                    if (1 < j)
                    {
                        dp[row][i][j] += dp[row - 1][i + 2][j - 2] * (i + 2) * (i + 1) / 2;
                        dp[row][i][j] %= MOD;
                    }

                    if (0 < i && 0 < j)
                    {
                        dp[row][i][j] += dp[row - 1][i][j - 1] * i * (m - i - j + 1);
                        dp[row][i][j] %= MOD;
                    }

                    if (n == row)
                    {
                        ans += dp[row][i][j];
                        ans %= MOD;
                    }
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
