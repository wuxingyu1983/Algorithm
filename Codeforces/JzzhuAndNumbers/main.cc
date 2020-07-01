// SOS DP
// http://codeforces.com/blog/entry/45223
// inclusion-exclusion principle
#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

#define DEBUG   0
#define MOD     1000000007
#define MAX_N   1000000

int p[MAX_N + 1];
int bits[MAX_N + 1];
int dp[21][MAX_N + 1];

using namespace std;

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    p[0] = 1;
    for (size_t i = 0; i < n; i++)
    {
        int a;
#if DEBUG
        inFile >> a;
#else
        cin >> a;
#endif
        if (0 < i)
        {
            p[i] = (p[i - 1] * 2) % MOD;
        }

        dp[0][a] ++;
    }
    
    p[n] = (p[n - 1] * 2) % MOD;

    for (size_t mask = 1; mask <= 1048576; mask <<= 1)
    {
        for (size_t i = 1; i <= MAX_N; i++)
        {
            if (i & mask)
            {
                bits[i] ++;
            }
        }
    }

    for (size_t b = 1; b <= 20; b++)
    {
        for (size_t i = 0; i <= MAX_N; i++)
        {
            if (i & (1 << (b - 1)))
            {
                // 1
                dp[b][i] = dp[b - 1][i];
            }
            else
            {
                // 0
                dp[b][i] = dp[b - 1][i];
                if ((i | (1 << (b - 1))) <= MAX_N)
                {
                    dp[b][i] += dp[b - 1][i | (1 << (b - 1))];
                }
            }

            dp[b][i] %= MOD;
        }
    }

    long long ret = p[n] - 1;

    for (size_t i = 1; i <= MAX_N; i++)
    {
        if (1 & bits[i])
        {
            ret -= (p[dp[20][i]] - 1);
            ret += MOD;
            ret %= MOD;
        }
        else
        {
            ret += (p[dp[20][i]] - 1);
            ret %= MOD;
        }
    }

    cout << ret << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
