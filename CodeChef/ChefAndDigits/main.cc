// https://www.codechef.com/problems/DGTCNT

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

long long dp[18][262144];
long long sum[18];

int initDP(int st, vector<int> &vec, int maxLen)
{
    int ret = 0;

    int needLen = 0;
    vector<int> offsets(10, -1);
    int preOff = 0;
    for (int n = 0; n < 10; n++)
    {
        if (st & (1 << n))
        {
            needLen += vec[n];

            offsets[n] = preOff;
            preOff += vec[n];
        }
    }

    if (18 < maxLen)
    {
        maxLen = 18;
    }

    if (maxLen < needLen)
    {
        return -1;
    }

    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));

    int goal = (1 << needLen) - 1;
    int pos = 0;
    for (int n = 0; n < 10; n++)
    {
        if (st & (1 << n))
        {
            dp[pos][1 << offsets[n]] = 1;
            if (goal == (1 << offsets[n]))
            {
                sum[pos]++;
            }
        }
    }

    for (; pos < 17; pos++)
    {
        for (int oldSt = 1; oldSt <= goal; oldSt++)
        {
            if (dp[pos][oldSt])
            {
                for (int n = 0; n < 10; n++)
                {
                    int newSt = oldSt;

                    if (st & (1 << n))
                    {
                        int mask = (1 << vec[n]) - 1;
                        mask <<= offsets[n];
                        int cnt = __builtin_popcount(mask & oldSt);
                        if (cnt >= vec[n])
                        {
                            continue;
                        }

                        // cnt < vec[n]
                        newSt |= 1 << (offsets[n] + cnt);
                    }

                    dp[pos + 1][newSt] += dp[pos][oldSt];

                    if (0 < n && newSt == goal)
                    {
                        sum[pos + 1] += dp[pos][oldSt];
                    }
                }
            }
        }

        sum[pos + 1] += sum[pos];
    }

    return ret;
}

long long func(string strN, int st, vector<int> &vec)
{
    long long ret = 0;

    int needLen = 0;
    vector<int> offsets(10, -1);
    int preOff = 0;
    for (int n = 0; n < 10; n++)
    {
        if (st & (1 << n))
        {
            needLen += vec[n];

            offsets[n] = preOff;
            preOff += vec[n];
        }
    }

    int len = strN.length();
    if (len < needLen)
    {
        return 0;
    }

    int goal = (1 << needLen) - 1;
    int preSt = 0;
    for (int pos = 0; pos < len; pos++)
    {
        int d = strN.at(pos) - '0';
        int down = 0, up = d - 1;

        if (0 == pos)
        {
            down = 1;

            if (len > 1)
            {
                ret += sum[len - 2];
            }
        }

        if (len - 1 == pos)
        {
            up = d;
        }

        for (int n = down; n <= up; n++)
        {
            int newSt = preSt;
            if (st & (1 << n))
            {
                int mask = (1 << vec[n]) - 1;
                mask <<= offsets[n];
                int cnt = __builtin_popcount(mask & preSt);

                if (cnt >= vec[n])
                {
                    continue;
                }

                // cnt < vec[n]
                newSt |= 1 << (offsets[n] + vec[n] - cnt - 1);
            }

            if (pos == len - 1)
            {
                if (goal == newSt)
                {
                    ret += 1;
                }
            }
            else
            {
                ret += dp[len - 2 - pos][goal - newSt];
            }
        }

        // proc preSt
        if (st & (1 << d))
        {
            int mask = (1 << vec[d]) - 1;
            mask <<= offsets[d];
            int cnt = __builtin_popcount(mask & preSt);

            if (cnt >= vec[d])
            {
                break;
            }

            // cnt < vec[d]
            preSt |= 1 << (offsets[d] + vec[d] - cnt - 1);
        }
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (size_t i = 0; i < t; i++)
    {
        long long l, r;
        cin >> l >> r;
        l--;

        vector<int> vecA;
        for (size_t n = 0; n < 10; n++)
        {
            int a;
            cin >> a;
            vecA.push_back(a);
        }

        string strL = to_string(l);
        string strR = to_string(r);
        long long cntL = 0, cntR = 0;
        for (int st = 1; st < 1024; st++)
        {
            if (0 == initDP(st, vecA, strR.length()))
            {
                if (1 & __builtin_popcount(st))
                {
                    cntL += func(strL, st, vecA);
                    cntR += func(strR, st, vecA);
                }
                else
                {
                    cntL -= func(strL, st, vecA);
                    cntR -= func(strR, st, vecA);
                }
            }
        }

        cout << (r - cntR) - (l - cntL) << "\n";
    }

    return 0;
}
