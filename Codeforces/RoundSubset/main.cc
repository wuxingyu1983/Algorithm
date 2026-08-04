// https://codeforces.com/contest/837/problem/D

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

using namespace std;

const int MAXN = 201;
const int mask = 16383;
const int DIGITS = 14;
int cnt2[MAXN], cnt5[MAXN];
unordered_set<int> dp[MAXN];      // dp[k]

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        long long a;
        cin >> a;

        long long tmp = a;
        while (tmp % 2 == 0)
        {
            cnt2[i]++;
            tmp /= 2;
        }
        
        tmp = a;
        while (tmp % 5 == 0)
        {
            cnt5[i]++;
            tmp /= 5;
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = k - 1; j >= max(k + i - n, 0); j--)
        {
            for (auto it = dp[j].begin(); it != dp[j].end(); it++)
            {
                int old2 = *it >> DIGITS;
                int old5 = *it & mask;
                int new2 = old2 + cnt2[i];
                int new5 = old5 + cnt5[i];
                dp[j + 1].insert((new2 << DIGITS) + new5);
                if (k == j + 1)
                {
                    ans = max(ans, min(new2, new5));
                }
            }

            if (0 == j)
            {
                // Add the current number as a new subset of size 1
                dp[1].insert((cnt2[i] << DIGITS) + cnt5[i]);
                if (k == 1)
                {
                    ans = max(ans, min(cnt2[i], cnt5[i]));
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
