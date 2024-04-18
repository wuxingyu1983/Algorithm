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
int minCost[MAX_N];
int dp[MAX_NK];
char bits[MAX_NK];

int main()
{
    cin >> n >> k;

    for (size_t i = 0; i < n; i++)
    {
        minCost[i] = -1;
        for (size_t j = 0; j < n; j++)
        {
            cin >> cost[i][j];
            if (i != j)
            {
                if (0 > minCost[i] || minCost[i] > cost[i][j])
                {
                    minCost[i] = cost[i][j];
                }
            }
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
        for (int i = 0; i < n; i++)
        {
            int mask = ~(1 << i);
            for (int j = (1 << n) - 1; j >= 0; j--)
            {
                if (0 <= dp[j] && (j & (1 << i)))
                {
                    int tmp = dp[j] + minCost[i];
                    if (0 > dp[j & mask] || tmp < dp[j & mask])
                    {
                        dp[j & mask] = tmp;
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
