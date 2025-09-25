// https://codeforces.com/problemset/problem/1036/C

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

long long dp[19][10][4];
long long sums[19];

long long func(long long num)
{
    long long ret = 0;

    return ret;
}

int main()
{
    int t;
    cin >> t;

    // init
    {
        int idx = 0;
        for (int n = 0; n < 10; n++)
        {
            if (0 == n)
            {
                dp[idx][n][0] = 1;
            }
            else
            {
                dp[idx][n][1] = 1;
            }
        }

        sums[idx] = 10;

        for (idx = 0; idx <= 19; idx++)
        {
            for (int n = 0; n < 10; n++)
            {
                if (0 == n)
                {
                    for (int cnt = 0; cnt < 4; cnt++)
                    {
                        for (int m = 0; m < 10; m++)
                        {
                            dp[idx][n][cnt] += dp[idx - 1][m][cnt];
                        }
                    }
                }
                else
                {
                    for (int cnt = 1; cnt < 4; cnt++)
                    {
                        for (int m = 0; m < 10; m++)
                        {
                            dp[idx][n][cnt] += dp[idx - 1][m][cnt - 1];
                        }

                        sums[idx] += dp[idx][n][cnt];
                    }
                }
            }

            sums[idx] += sums[idx - 1];
        }
    }

    for (size_t iT = 0; iT < t; iT++)
    {
        long long l, r;
        cin >> l >> r;

        cout << func(r) - func(l - 1) << endl;
    }

    return 0;
}
