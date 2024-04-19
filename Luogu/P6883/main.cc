// https://www.luogu.com.cn/problem/P6883

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

#define MAX_N 20
#define MAX_K 20
#define MAX_NK 1048576

int n, k;
int cost[MAX_N][MAX_N];
int dp[2][MAX_NK];
char bits[MAX_NK];
int act;

int main()
{
    cin >> n >> k;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cin >> cost[i][j];
        }
    }

    // init
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 1; j <= i; j <<= 1)
        {
            if (j & i)
            {
                bits[i]++;
            }
        }
    }
    memset(dp, -1, sizeof(dp));
    act = 0;
    dp[act][(1 << n) - 1] = 0;

    int ans = -1;

    if (k == n)
    {
        ans = 0;
    }
    else
    {
        for (int i = n - 1; i > 0; i--)
        {
            int mask = ~(1 << i);
            for (int j = 0; j < (1 << n); j++)
            {
                // do nothing
                if (0 > dp[1 - act][j] || dp[act][j] < dp[1 - act][j])
                {
                    dp[1 - act][j] = dp[act][j];
                }

                if (0 <= dp[act][j] && (j & (1 << i)))
                {
                    int tmp = -1;

                    for (int k = 0; k < i; k++)
                    {
                        if (0 > tmp || tmp > cost[i][k])
                        {
                            tmp = cost[i][k];
                        }
                    }

                    tmp += dp[act][j];

                    if (0 > dp[1 - act][j & mask] || tmp < dp[1 - act][j & mask])
                    {
                        dp[1 - act][j & mask] = tmp;
                    }
                }
            }

            memset(dp[act], -1, sizeof(dp[act]));
            act = 1 - act;
        }

        for (int i = 0; i < n - 1; i++)
        {
            int mask = ~(1 << i);
            for (int j = 0; j < (1 << n); j++)
            {
                // do nothing
                if (0 > dp[1 - act][j] || dp[act][j] < dp[1 - act][j])
                {
                    dp[1 - act][j] = dp[act][j];
                }

                if (0 <= dp[act][j] && (j & (1 << i)))
                {
                    for (int k = i + 1; k < n; k++)
                    {
                        int tmp = dp[act][j] + cost[i][k];
                        if (0 > dp[1 - act][(j & mask) | (1 << k)] || tmp < dp[1 - act][(j & mask) | (1 << k)])
                        {
                            dp[1 - act][(j & mask) | (1 << k)] = tmp;
                        }
                    }
                }
            }

            memset(dp[act], -1, sizeof(dp[act]));
            act = 1 - act;
        }

        for (int j = (1 << n) - 1; j >= 0; j--)
        {
            if (bits[j] == k)
            {
                if (0 <= dp[act][j])
                {
                    if (0 > ans || ans > dp[act][j])
                    {
                        ans = dp[act][j];
                    }
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
