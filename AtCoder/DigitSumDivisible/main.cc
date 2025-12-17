// https://atcoder.jp/contests/abc336/tasks/abc336_e

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

long long dp[15][127][127];     // dp[pos][num][mod]
long long powers[15];

long long func(string strN, int m)
{
    long long ret = 0;
    int len = strN.length();

    // init
    {
        memset(powers, 0, sizeof(powers));
        powers[0] = 1 % m;
        for (size_t i = 1; i < 15; i++)
        {
            powers[i] = (powers[i - 1] * 10) % m;
        }

        memset(dp, 0, sizeof(dp));
        int pos = 0;
        for (size_t n = 0; n <= m; n++)
        {
            dp[pos][n][n % m] = 1;
            if (n == m)
            {
                ret ++;
            }
        }

        
    }

    return ret;
}

int main()
{
    string strN;
    cin >> strN;
    
    long long ans = 0;

    for (size_t m = 1; m <= 126; m++)
    {
        ans += func(strN, m);
    }

    cout << ans << endl;

    return 0;
}
