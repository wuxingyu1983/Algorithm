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
    for (size_t i = 0; i < (1 << n); i++)
    {
        for (size_t j = 1; j <= i; j <<= 1)
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
    }

    cout << ans << endl;

    return 0;
}
