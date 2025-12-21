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
// __builtin_popcount(n)

const long long mod = 998244353;

long long powers[18];
long long sums[18];
long long dp[18][1024];

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
        

    }

    cout << (mod + func(r, k) - func(l - 1, k)) % mod << endl;

    return 0;
}
