// https://www.hackerearth.com/zh/problem/algorithm/find-the-number-of-ordered-pairs-1/

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

using namespace std;

#define MAX_M 20
#define MAX_2M 1048576

long long dp[MAX_2M];
int arr[MAX_2M];

int main()
{
    int t;
    cin >> t;

    for (size_t iT = 0; iT < t; iT++)
    {
        int n;
        cin >> n;

        memset(dp, 0, sizeof(dp));

        for (size_t iN = 0; iN < n; iN++)
        {
            int a;
            cin >> a;

            arr[iN] = a;

            dp[a] ++;
        }

        for (int i = 0; i < MAX_M; ++i)
        {
            for (int mask = 0; mask < MAX_2M; ++mask)
            {
                if (mask & (1 << i))
                    dp[mask] += dp[mask ^ (1 << i)];
            }
        }

        long long ans = 0;

        for (size_t i = 0; i < n; i++)
        {
            ans += dp[MAX_2M - 1 - arr[i]];
        }

        cout << ans << endl;
    }

    return 0;
}
