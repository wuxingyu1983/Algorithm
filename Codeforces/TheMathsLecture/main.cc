// https://codeforces.com/problemset/problem/507/D

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

int dp[1000][100];
int mods[1000];

int main()
{
    int n, k, m;
    cin >> n >> k >> m;

    // init
    mods[0] = 1 % k;
    for (size_t i = 1; i < n; i++)
    {
        mods[i] = (mods[i - 1] * 10) % k;
    }

    long long total = 1;
    for (size_t i = 0; i < n; i++)
    {
        int begin = 0;
        if (i == n - 1 || 0 == i)
        {
            begin = 1;
        }

        if (0 == i)
        {
            for (size_t num = begin; num < 10; num++)
            {
                dp[i][num % k] ++;
            }
        }
        else
        {
            total *= 10;
            total %= m;

            for (size_t num = 1; num < 10; num++)
            {
                int newJ = (num * mods[i]) % k;
                dp[i][newJ] ++;
            }

            for (size_t j = 1; j < k; j++)
            {
                if (dp[i - 1][j])
                {
                    for (size_t num = begin; num < 10; num++)
                    {
                        int newJ = (j + num * mods[i]) % k;
                        dp[i][newJ] += dp[i - 1][j];
                        dp[i][newJ] %= m;
                    }
                }
            }
        }
    }
    total *= 9;
    total %= m;

    int sum = 0;
    for (size_t j = 1; j < k; j++)
    {
        sum += dp[n - 1][j];
        sum %= m;
    }
    
    int ans = 0;
    ans = (m + total - sum) % m;

    cout << ans << endl;

    return 0;
}
