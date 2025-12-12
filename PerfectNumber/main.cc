// https://codeforces.com/problemset/problem/919/B

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

long long dp[11][10][11];
long long sum[11][10];

int main()
{
    int k;
    cin >> k;

    // init
    {
        int pos = 0;
        for (size_t n = 0; n < 10; n++)
        {
            dp[pos][n][n] = 1;
        }
       
        for (; pos < 10; pos++)
        {
            for (size_t n = 0; n < 10; n++)
            {
                for (size_t sum = 0; sum <= 10; sum++)
                {
                    if (dp[pos][n][sum])
                    {
                        for (size_t i = 0; i < 10; i++)
                        {
                            if (10 >= i + sum)
                            {
                                dp[pos + 1][i][i + sum] += dp[pos][n][sum];
                            }
                        }
                    }
                }
            }
        }
       
        for (pos = 0; pos < 11; pos++)
        {
            sum[pos][0] = dp[pos][0][10];

            for (size_t n = 1; n < 10; n++)
            {
                sum[pos][n] = sum[pos][n - 1] + dp[pos][n][10];
            }
        }

        cout << sum[10][9] << endl;
    }

    return 0;
}
