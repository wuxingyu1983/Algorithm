// https://www.codechef.com/LTIME50/problems/MAXOR

#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

//using namespace std;

#define MAX_N   20
#define MAX_2N  1048576

long long dp[MAX_2N];
long long a[MAX_2N];

int main()
{
/*
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
*/
    int t;
    scanf("%d", &t);

    for (size_t iT = 0; iT < t; iT++)
    {
        memset(dp, 0, sizeof(dp));
        memset(a, 0, sizeof(a));

        int n;
        scanf("%d", &n);

        for (size_t iN = 0; iN < n; iN++)
        {
            int tmp;
            scanf("%d", &tmp);

            dp[tmp] ++;
            a[tmp] ++;
        }

        for (int i = 0; i < MAX_N; ++i)
        {
            for (int mask = 0; mask < MAX_2N; ++mask)
            {
                if (mask & (1 << i))
                {
                    dp[mask] += dp[mask ^ (1 << i)];
                }
            }
        }

        long long ans = 0;

        for (size_t mask = 0; mask < MAX_2N; mask++)
        {
            if (a[mask])
            {
                ans += a[mask] * (a[mask] - 1) / 2;
                ans += a[mask] * (dp[mask] - a[mask]);
            }
        }

        printf("%lld\n", ans);
    }
    
    return 0;
}
