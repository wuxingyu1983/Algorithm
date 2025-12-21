// https://codeforces.com/contest/1073/problem/E

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

const long long mod = 998244353;

long long powers[18];
long long sums[18];
long long dp[18][1024];
long long cnts[18][1024];

long long func(long long num, int k)
{
    long long ret = 0;



    return ret;
}

int main()
{
    long long l, r;
    int k;

    cin >> l >> r >> k;

    // init
    {
        powers[0] = 1;
        for (size_t i = 1; i < 18; i++)
        {
            powers[i] = (powers[i - 1] * 10) % mod;
        }
        
        int pos = 0;
        for (int n = 0; n < 10; n++)
        {
            cnts[pos][1 << n] = 1;

            dp[pos][1 << n] = n;
            sums[pos] += n;
        }
        
        for (; pos < 17; pos++)
        {
            for (int mask = 1; mask < 1024; mask++)
            {
                if (cnts[pos][mask])
                {
                    for (int n = 0; n < 10; n++)
                    {
                        int newMask = mask | (1 << n);
                        if (k >= __builtin_popcount(newMask))
                        {
                            cnts[pos + 1][newMask] += cnts[pos][mask];

                            long long tmp = (n * powers[pos + 1] * (cnts[pos][mask] % mod)) % mod;
                            dp[pos + 1][newMask] += tmp;
                            dp[pos + 1][newMask] %= mod;

                            if (0 < n)
                            {
                                sums[pos + 1] += tmp;
                                sums[pos + 1] %= mod;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << (mod + func(r, k) - func(l - 1, k)) % mod << endl;

    return 0;
}
