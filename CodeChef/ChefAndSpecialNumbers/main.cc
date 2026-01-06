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
int lcms[1024];

int gcd(int a, int b)
{
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

void init(int mask, int mod)
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
        if (0 == (n % mod) && mask == (mask & (1 << n)))
        {
            sum[pos]++;
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

                        if (0 == newMod && 0 < n && mask == (mask & newSt))
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

long long getCnt(long long num, int mask, int mod)
{
    long long ret = 0;

    string strNum = to_string(num);
    int len = strNum.length();

    int preSt = 0, preMod = 0;

    for (int pos = 0; pos < len; pos++)
    {
        int d = strNum.at(pos) - '0';
        int down = 0, up = d - 1;

        if (0 == pos)
        {
            down = 1;

            if (1 < len)
            {
                ret += sum[len - 2];
            }
        }

        if (pos == len - 1)
        {
            up = d;
        }

        for (int n = down; n <= up; n++)
        {
            int newSt = preSt | (1 << n);
            int newMod = preMod;
            newMod += n * power[len - 1 - pos];
            newMod %= mod;

            if (len - 1 == pos)
            {
                if (0 == newMod && mask == (mask & newSt))
                {
                    ret++;
                }
            }
            else
            {
                int targetMod = (mod - newMod) % mod;
                for (int st = 1; st < 1024; st++)
                {
                    if (mask == (mask & (st | newSt)))
                    {
                        ret += dp[len - 2 - pos][st][targetMod];
                    }
                }
            }
        }

        if (pos < len - 1)
        {
            preSt |= 1 << d;
            preMod += d * power[len - 1 - pos];
            preMod %= mod;
        }
    }

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
            if (0 == (1 & n))
            {
                int l = 1;
                for (int idx = 1; idx < 10; idx++)
                {
                    if (n & (1 << idx))
                    {
                        l = l * idx / gcd(l, idx);
                    }
                }

                lcms[n] = l;
            }
        }
    }

    for (int i = 0; i < q; i++)
    {
        long long l, r;
        int k;

        cin >> l >> r >> k;

        long long cntL = 0, cntR = 0;
        for (int st = 1; st < 1024; st++)
        {
            if (0 == (1 & st) && k == __builtin_popcount(st))
            {
                init(st, lcms[st]);

                cntL += getCnt(l - 1, st, lcms[st]);
                cntR += getCnt(r, st, lcms[st]);
            }
        }

        if ((k & 1) && (k != 9))
        {
            long long cntL = 0, cntR = 0;
            for (int st = 1; st < 1024; st++)
            {
                if (0 == (1 & st) && 9 == __builtin_popcount(st))
                {
                    init(st, lcms[st]);

                    cntL += getCnt(l - 1, st, lcms[st]);
                    cntR += getCnt(r, st, lcms[st]);
                }
            }
        }

        printf("cntL = %lld, cntR = %lld\n", cntL, cntR);
        cout << cntR - cntL << endl;
    }

    return 0;
}
