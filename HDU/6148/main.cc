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
long long dp[100][3][10];
long long sum[100];

int main()
{
    int t;
    cin >> t;

    // init
    int idx = 0;
    for (int n = 0; n < 10; n++)
    {
        dp[idx][0][n] = 1;
    }
    sum[idx] = 9;

    for (idx = 1; idx < 100; idx++)
    {
        // type = 0
        for (int n = 0; n < 10; n++)
        {
            dp[idx][0][n] += dp[idx - 1][0][n];
            sum[idx] += dp[idx][0][n];
        }

        // type = 1
        for (int n = 0; n < 10; n++)
        {
            for (int m = n; m < 10; m++)
            {
                dp[idx][1][n] += dp[idx - 1][0][m];
                dp[idx][1][n] += dp[idx - 1][1][m];
            }

            dp[idx][1][n] %= mod;
            sum[idx] += dp[idx][1][n];
            sum[idx] %= mod;
        }

        // type = 2
        for (int n = 1; n < 10; n++)
        {
            for (int m = 0; m <= n; m++)
            {
                dp[idx][1][n] += dp[idx - 1][0][m];
                dp[idx][1][n] += dp[idx - 1][1][m];
                dp[idx][1][n] += dp[idx - 1][2][m];
            }

            dp[idx][1][n] %= mod;
            sum[idx] += dp[idx][1][n];
            sum[idx] %= mod;
        }

        sum[idx] += sum[idx - 1];
        sum[idx] %= mod;
    }

    for (size_t i = 0; i < t; i++)
    {
        string strNum;
        cin >> strNum;


    }
    

    return 0;
}
