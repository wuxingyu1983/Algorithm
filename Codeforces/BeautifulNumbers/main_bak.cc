// https://codeforces.com/problemset/problem/55/D

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
#include <bitset>

using namespace std;

#pragma GCC target("popcnt")

vector<int> subsets[512];
int lcm[512];
// int num[48] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 18, 20, 21, 24, 28, 30, 35, 36, 40, 42, 45, 56, 60, 63, 70, 72, 84, 90, 105, 120, 126, 140, 168, 180, 210, 252, 280, 315, 360, 420, 504, 630, 840, 1260, 2520};

long long dp[19][512][2520];

int gcd(int a, int b)
{
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

void init()
{
    for (int n = 1; n < 512; n++)
    {
        int l = 1;
        for (int idx = 0; idx < 10; idx++)
        {
            if (n & (1 << idx))
            {
                l = l * (idx + 1) / gcd(l, idx + 1);
            }
        }

        lcm[n] = l;

        for (int m = 1; m <= n; m++)
        {
            if (m == (m & n))
            {
                subsets[n].push_back(m);
            }
        }
    }
}

void initDP(int st)
{
    memset(dp, 0, sizeof(dp));

    int mod = lcm[st];

    int idx = 0;

    {
        dp[idx][0][0] = 1;

        for (int n = 1; n < 10; n++)
        {
            if (st & (1 << (n - 1)))
            {
                dp[idx][1 << (n - 1)][n % mod] = 1;
            }
        }
    }

    for (idx = 1; idx < 19; idx++)
    {
        long long tmp = pow(10, idx);
        tmp %= mod;

        // pre st = 0
        {
            dp[idx][0][0] += dp[idx - 1][0][0];

            for (int n = 1; n < 10; n++)
            {
                if (st & (1 << (n - 1)))
                {
                    int nMod = (tmp * n) % mod;
                    int newSt = 1 << (n - 1);
                    dp[idx][newSt][nMod % mod] += dp[idx - 1][0][0];
                }
            }
        }

        for (vector<int>::iterator it = subsets[st].begin(); it != subsets[st].end(); it++)
        {
            if (__builtin_popcount(*it) <= idx)
            {
                for (size_t m = 0; m < mod; m++)
                {
                    if (dp[idx - 1][*it][m])
                    {
                        dp[idx][*it][m] += dp[idx - 1][*it][m];

                        for (int n = 1; n < 10; n++)
                        {
                            if (st & (1 << (n - 1)))
                            {
                                int nMod = (tmp * n) % mod;
                                int newSt = *it | (1 << (n - 1));
                                dp[idx][newSt][(nMod + m) % mod] += dp[idx - 1][*it][m];
                            }
                        }
                    }
                }
            }
        }
    }
}

long long func(long long num, int st)
{
    long long ret = 0;

    int mod = lcm[st];

    string str = to_string(num);
    reverse(str.begin(), str.end());

    if (1 < str.length())
    {
        ret += dp[str.length() - 2][st][0];
    }

    int preSt = 0;
    int preMod = 0;

    for (int idx = str.length() - 1; idx >= 0; idx--)
    {
        int down = 0;
        int up = str.at(idx) - '0';
        if (str.length() - 1 == idx)
        {
            down = 1;
        }

        if (0 == idx)
        {
            up++;
        }

        long long tmp = pow(10, idx);
        tmp %= mod;

        for (size_t n = down; n < up; n++)
        {
            int newSt = preSt;
            if (0 < n)
            {
                newSt |= 1 << (n - 1);
            }

            if (newSt == (newSt & st))
            {
                int newMod = (preMod * 10 + n) * tmp;
                newMod %= mod;

                if (0 == idx)
                {
                    if (0 == newMod && newSt == st)
                    {
                        ret++;
                    }
                }
                else
                {
                    int needMod = (mod - newMod) % mod;
                    for (vector<int>::iterator it = subsets[st].begin(); it != subsets[st].end(); it++)
                    {
                        if (st == (newSt | (*it)))
                        {
                            ret += dp[idx - 1][*it][needMod];
                        }
                    }

                    if (st == newSt)
                    {
                        ret += dp[idx - 1][0][needMod];
                    }
                }
            }
        }

        up = str.at(idx) - '0';
        preMod = (preMod * 10 + up) % mod;

        if (0 < up)
        {
            preSt |= 1 << (up - 1);
            if (preSt != (preSt & st))
            {
                break;
            }
        }
    }

    return ret;
}

int main()
{
    init();

    int t;
    cin >> t;

    vector<long long> ls, rs;

    for (size_t i = 0; i < t; i++)
    {
        long long l, r;
        cin >> l >> r;

        ls.push_back(l);
        rs.push_back(r);
    }

    vector<long long> cnts(t, 0);
    for (int st = 1; st < 512; st++)
    {
        initDP(st);

        for (size_t i = 0; i < t; i++)
        {
            long long rrst = func(rs[i], st);
            long long lrst = func(ls[i] - 1, st);
            cnts[i] += rrst - lrst;
//            cout << st << ": rrst = " << rrst << ", lrst = " << lrst << endl;
        }
    }

    for (size_t i = 0; i < t; i++)
    {
        cout << cnts[i] << endl;
    }

    return 0;
}
