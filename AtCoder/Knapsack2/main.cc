// https://atcoder.jp/contests/dp/tasks/dp_e

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

const int MAXN = 101;
long long dp[100001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long w;
    cin >> n >> w;

    int ans = 0;
    for (int i = 0; i < n; i ++)
    {
        long long wi;
        int vi;
        cin >> wi >> vi;

        for (int j = 100000; j > 0; j --)
        {
            if (0 < dp[j])
            {
                if (w >= dp[j] + wi)
                {
                    if (0 == dp[j + vi] || dp[j + vi] > dp[j] + wi)
                    {
                        dp[j + vi] = dp[j] + wi;

                        if (j + vi > ans)
                        {
                            ans = j + vi;
                        }
                    }
                }
            }
        }

        if (0 == dp[vi] || dp[vi] > wi)
        {
            dp[vi] = wi;

            if (vi > ans)
            {
                ans = vi;
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
