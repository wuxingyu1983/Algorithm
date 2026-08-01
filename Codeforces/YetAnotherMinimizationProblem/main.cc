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
        }
        else if (2 == n)
        {
            ans = max((a[1] + a[2]) * (a[1] + a[2]) + (b[1] + b[2]) * (b[1] + b[2]), (a[1] + b[2]) * (a[1] + b[2]) + (b[1] + a[2]) * (b[1] + a[2]));
        }
        else
        {
            fixed *= (n - 1);

            memset(sum, 0, sizeof(sum));
            memset(dp, 0, sizeof(dp));
            int active = 0;

            for (int iN = n; iN >= 1; iN--)
            {
                sum[iN] = sum[iN + 1] + a[iN] + b[iN];
            }


        }

        cout << ans << "\n";
    }

    return 0;
}
