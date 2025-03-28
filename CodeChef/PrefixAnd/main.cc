// https://www.codechef.com/COOK126A/problems/ANDPREF?tab=statement

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

const int maxSt = 1048576;

long long dp[20][maxSt];
int cnt[maxSt];
int t;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t;

    for (size_t iT = 0; iT < t; iT++)
    {
        memset(dp, 0, sizeof(dp));
        memset(cnt, 0, sizeof(cnt));

        int n;
        cin >> n;

        for (size_t iN = 0; iN < n; iN++)
        {
            int tmp = 0;
            cin >> tmp;
            cnt[tmp] ++;
        }

        // init, 计算 mask 超集的个数
        for (int i = 0; i < 20; ++i)
        {
            for (int mask = 0; mask < maxSt; ++mask)
            {
                if (0 == (mask & (1 << i)))
                {
                    cnt[mask] += cnt[mask ^ (1 << i)];
                }
            }
        }

        long long ans = 0;

        cout << ans << endl;
    }

    return 0;
}
