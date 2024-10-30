// https://www.codechef.com/problems/COVERING

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

#define MAX_N 20
#define MAX_2N 1048576
#define MOD 1000000007

long long pow2[MAX_N + 1];
long long d[MAX_2N];
long long f[MAX_2N];
long long g[MAX_2N];
long long h[MAX_2N];
long long sum[MAX_N + 1];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int maxSt = (1 << n) - 1;

    for (size_t i = 0; i <= maxSt; i++)
    {
        cin >> f[i];
    }
    
    for (size_t i = 0; i <= maxSt; i++)
    {
        cin >> g[i];
    }

    for (size_t i = 0; i <= maxSt; i++)
    {
        cin >> h[i];
    }

    // init
    for (int i = 0; i < MAX_N; ++i)
    {
        for (int mask = 0; mask <= maxSt; ++mask)
        {
            if (mask & (1 << i))
                f[mask] += f[mask ^ (1 << i)];
                g[mask] += g[mask ^ (1 << i)];
                h[mask] += h[mask ^ (1 << i)];
        }
    }

    for (size_t i = 0; i <= maxSt; i++)
    {
        d[i] = f[i] * g[i];
        d[i] %= MOD;
        d[i] *= h[i];
        d[i] %= MOD;
    }

    pow2[0] = 1;
    for (size_t i = 1; i <= MAX_N; i++)
    {
        pow2[i] = pow2[i - 1] << 1;
    }

    sum[0] = 1;
    for (size_t i = 1; i <= MAX_N; i++)
    {
        if (i & 1)
        {
            sum[i] = sum[i - 1] - pow2[i];
        }
        else
        {
            sum[i] = sum[i - 1] + pow2[i];
        }

        sum[i] += MOD;
        sum[i] %= MOD;
    }

    long long ans = 0;

    for (size_t st = 0; st <= maxSt; st++)
    {
        int ones = 0;
        for (size_t i = 0; i < n; i++)
        {
            if (st & (1 << i))
            {
                ones ++;
            }
        }

        long long tmp = d[st] * pow2[ones];
        tmp %= MOD;

        tmp *= sum[n - ones];
        tmp %= MOD;

        ans += tmp;
        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
}
