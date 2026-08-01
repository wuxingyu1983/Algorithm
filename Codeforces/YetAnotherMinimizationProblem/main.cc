// https://codeforces.com/contest/1637/problem/D

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

using namespace std;

const int MAXN = 102;
int sum[MAXN];
long long dp[2][10001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (int iT = 0; iT < t; iT++)
    {
        int n;
        cin >> n;

        vector<int> a(n + 1), b(n + 1);
        long long fixed = 0;

        for (int iN = 1; iN <= n; iN++)
        {
            cin >> a[iN];
            fixed += a[iN] * a[iN];
        }
        
        for (int iN = 1; iN <= n; iN++)
        {
            cin >> b[iN];
            fixed += b[iN] * b[iN];
        }

        long long ans = 0;

        if (1 == n)
        {
            cout << 0 << "\n";
        }
        else if (2 == n)
        {
            ans = max((a[1] + a[2]) * (a[1] + a[2]) + (b[1] + b[2]) * (b[1] + b[2]), (a[1] + b[2]) * (a[1] + b[2]) + (b[1] + a[2]) * (b[1] + a[2]));
            cout << ans << "\n";
        }
        else
        {
            fixed *= (n - 1);

            memset(sum, 0, sizeof(sum));
            memset(dp, 0, sizeof(dp));
            int act = 0;

            for (int iN = n; iN >= 1; iN--)
            {
                sum[iN] = sum[iN + 1] + a[iN] + b[iN];
            }

            // iN = n - 1
            {
                // a[n - 1], a[n] and b[n - 1], b[n]
                dp[act][a[n - 1] + a[n]] = a[n - 1] * a[n] + b[n - 1] * b[n];
                int s = b[n - 1] + a[n];
                long long v = b[n - 1] * a[n] + a[n - 1] * b[n];
                if (0 == dp[act][s] || v < dp[act][s])
                {
                    dp[act][s] = v;
                }
            }

            for (int iN = n - 2; iN >= 1; iN--)
            {
                act = 1 - act;
                memset(dp[act], 0, sizeof(dp[act]));

                for (int s = 1; s <= 10000; s++)
                {
                    if (0 < dp[1 - act][s])
                    {
                        // a[iN] 和 b[iN] 没有交换
                        int newS = s + a[iN];
                        long long newV = dp[1 - act][s] + a[iN] * s + b[iN] * (sum[iN + 1] - s);
                        if (0 == dp[act][newS] || newV < dp[act][newS])
                        {
                            dp[act][newS] = newV;

                            if (1 == iN)
                            {
                                if (0 == ans || newV < ans)
                                {
                                    ans = newV;
                                }
                            }
                        }

                        // a[iN] 和 b[iN] 交换
                        newS = s + b[iN];
                        newV = dp[1 - act][s] + b[iN] * s + a[iN] * (sum[iN + 1] - s);
                        if (0 == dp[act][newS] || newV < dp[act][newS])
                        {
                            dp[act][newS] = newV;

                            if (1 == iN)
                            {
                                if (0 == ans || newV < ans)
                                {
                                    ans = newV;
                                }
                            }
                        }
                    }
                }
            }
            cout << 2 * ans * fixed << "\n";
        }
    }

    return 0;
}
