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

const int mod = 1000000007;
int dp[2001][9][2000];
int mods[2001];

int main()
{
    int m, d;
    cin >> m >> d;

    string a, b;
    cin >> a;
    cin >> b;

    // init
    int len = b.length();
    mods[len] = 1 % m;
    for (int idx = len - 1; idx > 0; idx--)
    {
        mods[idx] = (mods[idx + 1] * 10) % m;
    }

    if (len & 1)
    {
        // odd, 奇数
        for (int n = 0; n < 10; n++)
        {
            if (n != d)
            {
                dp[len][n][n % m] = 1;
            }
        }
    }
    else
    {
        // even, 偶数
        dp[len][d][d % m] = 1;
    }

    for (int idx = len - 1; idx > 0; idx--)
    {
        if (idx & 1)
        {
            // odd, 奇数
            for (int iM = 0; iM < m; iM++)
            {
                if (dp[idx + 1][d][iM])
                {
                    for (int n = 0; n < 10; n++)
                    {
                        if (n != d)
                        {
                            int newM = (iM + mods[idx] * n) % m;
                            dp[idx][n][newM] += dp[idx + 1][d][iM];
                            dp[idx][n][newM] %= mod;
                        }
                    }
                }
            }
            
        }
        else
        {
            // even, 偶数
            for (int n = 0; n < 10; n++)
            {
                if (n != d)
                {
                    for (int iM = 0; iM < m; iM++)
                    {
                        if (dp[idx + 1][n][iM])
                        {
                            int newM = (iM + mods[idx] * d) % m;
                            dp[idx][d][newM] += dp[idx + 1][n][iM];
                            dp[idx][d][newM] %= mod;
                        }
                    }
                }
            }
            
        }
    }

    return 0;
}
