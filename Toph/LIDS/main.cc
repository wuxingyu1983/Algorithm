// https://toph.co/p/lids

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

long long dp[11][10][10];   // dp[pos][num][len]

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // init
    {
        int pos = 0;
        for (int n = 1; n < 10; n++)
        {
            dp[pos][n][1] = 1;
        }
       
        for (; pos < 10; pos++)
        {
            for (int n = 1; n < 10; n++)
            {
                dp[pos + 1][n][1] = 1;
            }

            // pos => pos + 1
            for (int num = 0; num < 10; num++)
            {
                for (int len = 0; len < 10; len++)
                {
                    dp[pos + 1][num][len] += dp[pos][num][len];
                }
            }

            for (int num = 0; num < 10; num++)
            {
                for (int len = 0; len < 10; len++)
                {
                    if (dp[pos][num][len])
                    {
                        for (int sub = 1; sub < num; sub++)
                        {
                            dp[pos + 1][sub][len + 1] += dp[pos][num][len];
                        }
                    }
                }
            }
        }
    }

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++)
    {
        long long x, y;
        cin >> x >> y;

//        printf("Case %d: %lld %lld\n", i, x, y);
    }

    return 0;
}
