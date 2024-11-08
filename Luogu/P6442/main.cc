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
long long pow2[MAX_2M];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    int maxSt = (1 << m) - 1;

    pow2[0] = 1;
    for (size_t iN = 1; iN <= n; iN++)
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

        dp[maxSt - tmp] ++;

        pow2[iN] = pow2[iN - 1] << 1;
        pow2[iN] %= MOD;
    }
    
    for (int i = 0; i < m; ++i)
    {
        for (int st = 0; st <= maxSt; ++st)
        {
            if (0 == (st & (1 << i)))
            {
                dp[st] += dp[st ^ (1 << i)];
            }
        }
    }

    long long ans = 0;

    for (int st = 0; st <= maxSt; ++st)
    {
        int ones = 0;
        for (size_t i = 0; i < m; i++)
        {
            if (st & (1 << i))
            {
                ones ++;
            }
        }
        
        if (1 & ones)
        {
            ans += (MOD - pow2[dp[st]]);
        }
        else
        {
            ans += pow2[dp[st]];
        }

        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
}
