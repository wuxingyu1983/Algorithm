// https://atcoder.jp/contests/dp/tasks/dp_n

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
#include <unordered_set>
#include <unordered_map>

using namespace std;

const int MAXN = 401;
long long dp[MAXN][MAXN];
long long sum[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> a(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];

        sum[i] = sum[i - 1] + a[i];

        if (1 < i)
            dp[i - 1][i] = a[i - 1] + a[i];
    }

    for (int step = 2; step < n; step++)
    {
        for (int i = 1; i + step <= n; i++)
        {
            int j = i + step;

            for (int k = i; k < j; k++)
            {
                if (0 == dp[i][j] || dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1] < dp[i][j])
                    dp[i][j] = dp[i][k] + dp[k + 1][j] + sum[j] - sum[i - 1];
            }
        }
    }

    cout << dp[1][n] << "\n";

    return 0;
}
