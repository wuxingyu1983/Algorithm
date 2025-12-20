// https://www.hackerearth.com/zh/problem/algorithm/sallu-bhai-and-ias-8838ac8d/?purpose=login&source=problem-page&update=google

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
#include <unordered_set>
#include <bitset>

using namespace std;

int lcm[48] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 18, 20, 21, 24, 28, 30, 35, 36, 40, 42, 45, 56, 60, 63, 70, 72, 84, 90, 105, 120, 126, 140, 168, 180, 210, 252, 280, 315, 360, 420, 504, 630, 840, 1260, 2520};
unordered_map<int, unordered_set<int>> mltmap;
long long dp[13][1024][2520]; // dp[pos][mask][mod]
long long sum[13];
long long powers[10];

int gcd(int a, int b)
{
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

void init()
{
    for (size_t i = 1; i < 10; i++)
    {
        powers[i] = pow(i, i);
    }

    for (int n = 1023; n > 0; n--)
    {
        int l = 0;
        for (int idx = 1; idx < 10; idx++)
        {
            if (n & (1 << idx))
            {
                if (0 == l)
                {
                    l = 1;
                }
                l = l * idx / gcd(l, idx);
            }
        }

        if (0 < l)
        {
            if (mltmap.end() == mltmap.find(l))
            {
                unordered_set<int> st;
                st.insert(n);

                mltmap[l] = st;
            }
            else
            {
                mltmap[l].insert(n);
            }
        }
    }
}

void initDP(int mask, int mod, unordered_set<int> &st)
{
    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));

    int pos = 0;
    for (size_t n = 0; n < 10; n++)
    {
        if (mask & (1 << n))
        {
            dp[pos][1 << n][powers[n] % mod] = 1;

            auto search = st.find(1 << n);
            if (search != st.end())
            {
                sum[pos] += 1;
            }
        }
    }

    for (; pos < 12; pos++)
    {
        for (int oldMask = 1; oldMask < 1024; oldMask++)
        {
            for (int oldMod = 0; oldMod < mod; oldMod++)
            {
                if (dp[pos][oldMask][oldMod])
                {
                    for (int n = 0; n < 10; n++)
                    {
                        if (mask & (1 << n))
                        {
                            int newMask = oldMask | (1 << n);
                            int newMod = (oldMod + powers[n]) & mod;

                            dp[pos + 1][newMask][newMod] += dp[pos][oldMask][oldMod];

                            if (0 < n)
                            {
                                auto search = st.find(newMask);
                                if (search != st.end())
                                {
                                    sum[pos + 1] += dp[pos][oldMask][oldMod];
                                }
                            }
                        }
                    }
                }
            }
        }

        sum[pos + 1] += sum[pos];
    }
}

long long func(int num, int mask, int mod, unordered_set<int> &st)
{
    long long ret = 0;

    string strN = to_string(num);
    int len = strN.length();

    int preMask = 0;
    int preMod = 0;
    for (int pos = 0; pos < len; pos++)
    {
        int d = strN.at(pos) - '0';
        int down = 0;
        int up = d - 1;

        if (0 == pos)
        {
            down = 1;

            if (1 < len)
            {
                ret += sum[len - 2];
            }
        }

        if (len - 1 == pos)
        {
            up = d;
        }

        for (size_t n = down; n <= up; n++)
        {
            if (mask & (1 << n))
            {
                int tmpMask = preMask | (1 << n);
                int tmpMod = (preMod + powers[n]) % mod;

                if (0 <= len - 2 - pos)
                {
                    for (size_t m = 0; m < 1024; m++)
                    {
                        auto search = st.find(tmpMask | m);
                        if (search != st.end())
                        {
                            ret += dp[len - 2 - pos][m][(mod - tmpMod) % mod];
                        }
                    }
                }
                else
                {
                    if (0 == tmpMod)
                    {
                        auto search = st.find(tmpMask);
                        if (search != st.end())
                        {
                            ret += 1;
                        }
                    }
                }
            }
        }

        preMask |= 1 << d;
        preMod += powers[d];
        preMod %= mod;
    }

    return ret;
}

int main()
{
    int q;
    cin >> q;

    vector<long long> ls, rs;

    for (size_t i = 0; i < q; i++)
    {
        long long l, r;
        cin >> l >> r;

        ls.push_back(l);
        rs.push_back(r);
    }

    init();

    vector<long long> ans(q, 0);

    for (size_t i = 0; i < 48; i++)
    {
        int mod = lcm[i];
        int mask = 1; // 0 - valid

        auto search = mltmap.find(mod);
        if (search != mltmap.end())
        {
            for (auto it : search->second)
            {
                mask |= it;
            }
        }

        initDP(mask, mod, search->second);

        for (size_t j = 0; j < q; j++)
        {
            ans[j] += func(rs[j], mask, mod, search->second) - func(ls[j] - 1, mask, mod, search->second);
        }
    }

    for (size_t i = 0; i < q; i++)
    {
        cout << ans[i] << endl;
    }

    return 0;
}
