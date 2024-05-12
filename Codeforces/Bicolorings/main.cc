// https://codeforces.com/problemset/problem/1051/D
// 状压DP

#include <cmath>
#include <cstdio>
#include <vector>
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
#include <cstring>

using namespace std;

#define MAX_N   1001
#define MAX_K   2001
#define MOD 998244353   

int dp[MAX_N][MAX_K][4];
int n, k;

int main()
{
    cin >> n >> k;

    // init
    dp[0][1][0] = 1;
    dp[0][1][3] = 1;
    dp[0][2][1] = 1;
    dp[0][2][2] = 1;

    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 1; j <= k; j++)
        {
            if (dp[i][j][0])
            {
                dp[i + 1][j][0] += dp[i][j][0];
                dp[i + 1][j][0] %= MOD;

                if (j < k)
                {
                    dp[i + 1][j + 1][1] += dp[i][j][0];
                    dp[i + 1][j + 1][1] %= MOD;
                    dp[i + 1][j + 1][2] += dp[i][j][0];
                    dp[i + 1][j + 1][2] %= MOD;
                    dp[i + 1][j + 1][3] += dp[i][j][0];
                    dp[i + 1][j + 1][3] %= MOD;
                }
            }

            if (dp[i][j][3])
            {
                dp[i + 1][j][3] += dp[i][j][3];
                dp[i + 1][j][3] %= MOD;

                if (j < k)
                {
                    dp[i + 1][j + 1][0] += dp[i][j][3];
                    dp[i + 1][j + 1][0] %= MOD;
                    dp[i + 1][j + 1][1] += dp[i][j][3];
                    dp[i + 1][j + 1][1] %= MOD;
                    dp[i + 1][j + 1][2] += dp[i][j][3];
                    dp[i + 1][j + 1][2] %= MOD;
                }
            }

            if (dp[i][j][1])
            {
                dp[i + 1][j][1] += dp[i][j][1];
                dp[i + 1][j][1] %= MOD;
                dp[i + 1][j][0] += dp[i][j][1];
                dp[i + 1][j][0] %= MOD;
                dp[i + 1][j][3] += dp[i][j][1];
                dp[i + 1][j][3] %= MOD;

                if (j < k - 1)
                {
                    dp[i + 1][j + 2][2] += dp[i][j][1];
                    dp[i + 1][j + 2][2] %= MOD;
                }
            }

            if (dp[i][j][2])
            {
                dp[i + 1][j][2] += dp[i][j][2];
                dp[i + 1][j][2] %= MOD;
                dp[i + 1][j][0] += dp[i][j][2];
                dp[i + 1][j][0] %= MOD;
                dp[i + 1][j][3] += dp[i][j][2];
                dp[i + 1][j][3] %= MOD;

                if (j < k - 1)
                {
                    dp[i + 1][j + 2][1] += dp[i][j][2];
                    dp[i + 1][j + 2][1] %= MOD;
                }
            }
        }
    }

    int ans = 0;

    for (size_t st = 0; st < 4; st++)
    {
        ans += dp[n - 1][k][st];
        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
}
