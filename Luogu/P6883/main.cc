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
int dp[MAX_NK];
char bits[MAX_NK];

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
    dp[(1 << n) - 1] = 0;

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
                if (0 <= dp[j] && (j & (1 << i)))
                {
                    int tmp = -1;

                    for (int k = 0; k < i; k++)
                    {
                        if (0 > tmp || tmp > cost[i][k])
                        {
                            tmp = cost[i][k];
                        }
                    }

                    tmp += dp[j];

                    if (0 > dp[j & mask] || tmp < dp[j & mask])
                    {
                        dp[j & mask] = tmp;
                    }
                }
            }
        }

        for (int i = 0; i < n - 1; i++)
        {
            int mask = ~(1 << i);
            for (int j = 0; j < (1 << n); j++)
            {
                if (0 <= dp[j] && (j & (1 << i)))
                {
                    for (int k = i + 1; k < n; k++)
                    {
                        int tmp = dp[j] + cost[i][k];
                        if (0 > dp[(j & mask) | (1 << k)] || tmp < dp[(j & mask) | (1 << k)])
                        {
                            dp[(j & mask) | (1 << k)] = tmp;
                        }
                    }
                }
            }
        }

        for (int j = (1 << n) - 1; j >= 0; j--)
        {
            if (bits[j] == k)
            {
                if (0 > ans || ans > dp[j])
                {
                    ans = dp[j];
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
