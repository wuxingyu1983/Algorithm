// https://www.codechef.com/problems/WORKCHEF?tab=statement

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
#include <map>
#include <unordered_map>
#include <bitset>

using namespace std;

#pragma GCC target("popcnt")

long long power[19];
long long sum[19];
long long dp[19][1024][2520];
unordered_multimap<int, int> mltmap;

int gcd(int a, int b)
{
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

void init(int mod)
{
    int pos = 0;
    power[pos] = 1;

    for (pos = 1; pos < 19; pos++)
    {
        power[pos] = (power[pos - 1] * 10) % mod;
    }
    
    memset(sum, 0, sizeof(sum));
    memset(dp, 0, sizeof(dp));

    pos = 0;
    for (int n = 0; n < 10; n++)
    {
        dp[pos][1 << n][n % mod] = 1;
        if (0 == (n % mod) && 0 < n)
        {
            sum[pos] ++;
        }
    }
    
    for (; pos < 18; pos++)
    {
        for (int oldSt = 1; oldSt < 1024; oldSt++)
        {
            for (int oldMod = 0; oldMod < mod; oldMod++)
            {
                if (dp[pos][oldSt][oldMod])
                {
                    for (int n = 0; n < 10; n++)
                    {
                        int newSt = oldSt | (1 << n);
                        int newMod = (oldMod + n * power[pos + 1]) % mod;

                        dp[pos + 1][newSt][newMod] += dp[pos][oldSt][oldMod];

                        if (0 == newMod && 0 < n)
                        {
                            sum[pos + 1] += dp[pos][oldSt][oldMod];
                        }
                    }
                }
            }
        }

        sum[pos + 1] += sum[pos];
    }
}

long long getCnt(long long num, int k, int mod)
{
    long long ret = 0;

    return ret;
}

int main()
{
    int q;
    cin >> q;

    // init
    {
        for (int n = 1; n < 1024; n++)
        {
            int l = 1;
            for (int idx = 0; idx < 10; idx++)
            {
                if (n & (1 << idx))
                {
                    l = l * idx / gcd(l, idx);
                }
            }

            mltmap.insert(make_pair<int, int>(__builtin_popcount(n), (int)l));
        }
    }

    for (int i = 0; i < q; i++)
    {
        long long l, r;
        int k;

        cin >> l >> r >> k;

        long long cntL = 0, cntR = 0;
        auto range = mltmap.equal_range(k);
        for (auto it = range.first; it != range.second; ++it)
        {
            init(it->second);

            cntL += getCnt(l - 1, k, it->second);
            cntR += getCnt(r, k, it->second);
        }

        if ((k & 1) && (k != 9))
        {
            range = mltmap.equal_range(9);
            for (auto it = range.first; it != range.second; ++it)
            {
                init(it->second);

                cntL += getCnt(l - 1, 9, it->second);
                cntR += getCnt(r, 9, it->second);
            }
        }

        cout << cntR - cntL << endl;
    }

    return 0;
}
