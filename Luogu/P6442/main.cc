// https://www.luogu.com.cn/problem/P6442

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
#define MOD 1000000007

long long dp[MAX_2M];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    for (size_t iN = 0; iN < n; iN++)
    {
        int k;
        cin >> k;

        int tmp = 0;
        for (size_t iK = 0; iK < k; iK++)
        {
            int toy;
            cin >> toy;

            tmp |= 1 << (toy - 1);
        }

        dp[tmp] ++;
    }
    
    int maxSt = (1 << m) - 1;
    for (int i = 0; i < m; ++i)
    {
        for (int st = 0; st <= maxSt; ++st)
        {
            if (st & (1 << i))
            {
                dp[st] += dp[st ^ (1 << i)];
                dp[st] %= MOD;
            }
        }
    }

    long long ans = 0;

    for (int st = 0; st <= maxSt; ++st)
    {
        int zeros = 0;
        for (size_t i = 0; i < m; i++)
        {
            if (0 == (st & (1 << i)))
            {
                zeros ++;
            }
        }
        
        if (1 & zeros)
        {
            ans += (MOD - dp[st]);
        }
        else
        {
            ans += dp[st];
        }

        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
}
