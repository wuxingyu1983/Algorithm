// https://atcoder.jp/contests/dp/tasks/dp_l

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

using namespace std;

const int MAXN = 3001;
long long a[MAXN];
long long dp[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (1 & n)
            dp[i][i] = a[i];
        else
            dp[i][i] = 0 - a[i];
    }

    for (int step = 1; step < n; step++)
    {
        // 计算 dp[i][i + step]
        if (1 & (n - 1 - step))
        {
            for (int i = 1; i <= n - step; i++)
            {
                dp[i][i + step] = min(dp[i + 1][i + step] - a[i], dp[i][i + step - 1] - a[i + step]);
            }
        }
        else
        {
            for (int i = 1; i <= n - step; i++)
            {
                dp[i][i + step] = max(a[i] + dp[i + 1][i + step], dp[i][i + step - 1] + a[i + step]);
            }
        }
    }

    cout << dp[1][n] << "\n";

    return 0;
}
