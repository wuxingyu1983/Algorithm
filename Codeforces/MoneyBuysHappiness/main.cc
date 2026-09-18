// https://codeforces.com/problemset/problem/1974/E

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
#include <unordered_map>
#include <deque>

using namespace std;

int cs[50], hs[50];

long long dp[100001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int m, x;
        cin >> m >> x;

        int sum = 0;
        for (int j = 0; j < m; j++)
        {
            cin >> cs[j] >> hs[j];

            sum += hs[j];
        }

        memset(dp, 0, sizeof(dp));

        int ans = 0;

        // month 0
        {
            if (0 == cs[0])
            {
                dp[hs[0]] = x;

                if (1 == m)
                {
                    ans = hs[0];
                }
            }
            else
            {
                dp[0] = x;
            }
        }

        for (int j = 1; j < m; j++)
        {
            for (int k = sum; k >= 0; k--)
            {
                if (0 < dp[k])
                {
                    // 消费，获取快乐
                    if (dp[k] >= cs[j])
                    {
                        dp[k + hs[j]] = max(dp[k + hs[j]], dp[k] - cs[j] + x);

                        if (m - 1 == j)
                        {
                            ans = max(ans, k + hs[j]);
                        }
                    }

                    // 不消费
                    {
                        dp[k] += x;

                        if (m - 1 == j)
                        {
                            ans = max(ans, k);
                        }
                    }
                }
            }
        }

        cout << ans << "\n";
    }

    return 0;
}