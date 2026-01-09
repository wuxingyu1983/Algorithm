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
long long sum[19][10];
long long dp[19][1024][2520];
int lcm[48] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 18, 20, 21, 24, 28, 30, 35, 36, 40, 42, 45, 56, 60, 63, 70, 72, 84, 90, 105, 120, 126, 140, 168, 180, 210, 252, 280, 315, 360, 420, 504, 630, 840, 1260, 2520};
vector<int> masks[2521];
vector<long long> cntL[3], cntR[3];
vector<long long> ls, rs;
vector<int> ks;

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
        int st = 1 << n;
        if (0 == (n % mod))
        {
            for (vector<int>::iterator it = masks[mod].begin(); it != masks[mod].end(); ++it)
            {
                if (*it == (st & (*it)))
                {
                    sum[pos][__builtin_popcount(*it)]++;
                }
            }
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
                            for (vector<int>::iterator it = masks[mod].begin(); it != masks[mod].end(); ++it)
                            {
                                if (*it == (newSt & (*it)))
                                {
                                    sum[pos + 1][__builtin_popcount(*it)] += dp[pos][oldSt][oldMod];
                                }
                            }
                        }
                    }
                }
            }
        }

        for (int i = 1; i < 10; i++)
        {
            sum[pos + 1][i] += sum[pos][i];
        }
    }
}

void getCnt(long long num, int mod, vector<long long>& cnt)
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
                for (int i = 1; i < 10; i++)
                {
                    cnt[i] += sum[len - 2][i];
                }
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
                if (0 == newMod)
                {
                    for (vector<int>::iterator it = masks[mod].begin(); it != masks[mod].end(); ++it)
                    {
                        if (*it == (newSt & (*it)))
                        {
                            cnt[__builtin_popcount(*it)] += 1;
                        }
                    }
                }
            }
            else
            {
                int targetMod = (mod - newMod) % mod;
                for (int st = 1; st < 1024; st++)
                {
                    if (dp[len - 2 - pos][st][targetMod])
                    {
                        for (vector<int>::iterator it = masks[mod].begin(); it != masks[mod].end(); ++it)
                        {
                            if (*it == ((st | newSt) & (*it)))
                            {
                                cnt[__builtin_popcount(*it)] += dp[len - 2 - pos][st][targetMod];
                            }
                        }
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

                masks[l].push_back(n);
            }
        }
    }

    for (int i = 0; i < q; i++)
    {
        cntL[i].assign(10, 0);
        cntR[i].assign(10, 0);
    }

    for (int i = 0; i < q; i++)
    {
        long long l, r;
        int k;

        cin >> l >> r >> k;

        ls.push_back(l);
        rs.push_back(r);
        ks.push_back(k);
    }

    for (int i = 0; i < 48; i++)
    {
        init(lcm[i]);

        for (int j = 0; j < q; j++)
        {
            getCnt(ls[j] - 1, lcm[i], cntL[j]);
            getCnt(rs[j], lcm[i], cntR[j]);
        }
    }

    for (int j = 0; j < q; j++)
    {
        long long sumL = 0, sumR = 0;

        for (int i = ks[j], f = 1; i < 10; i++, f *= -1)
        {
            sumL += f * cntL[j][i];
            sumR += f * cntR[j][i];
        }

        cout << sumR - sumL << endl;
    }

    return 0;
}
